/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 10:25:59
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/brightness.cxx
 */

#include "head.h"

char light_num = 2; //亮度指数，默认亮度为2
long Buzzer_Switch_No;
char Brightness_Flag; //手动和自动模式变量控制  1:手动模式  0：自动模式

//降低亮度
void brightness_down_cb(Fl_Button *, void *)
{
	if ((light_num > 0) && (Brightness_Flag == 1))
	{
		light_num--;
		SetLcdBright(200 - light_num * 40); // lcd亮度一次减少40
		for (int i = 0; i <= light_num; i++)
		{
			//五个light_box并联形成亮度显示控件
			//亮度显示控件通过改变颜色表明颜色变化，绿色/灰色
			light_box[i]->color(FL_GREEN); //
			light_box[i]->redraw();
		}
		if (light_num < 4)
		{
			for (int j = light_num + 1; j < 5; j++)
			{
				light_box[j]->color(FL_GRAY);
				light_box[j]->redraw();
			}
		}
	}
}

void brightness_up_cb(Fl_Button *, void *)
{
	if ((light_num < 4) && (Brightness_Flag == 1))
	{
		light_num++;
		SetLcdBright(200 - light_num * 40);
		for (int i = 0; i <= light_num; i++)
		{
			light_box[i]->color(FL_GREEN);
			light_box[i]->redraw();
		}
		if (light_num < 4)
		{
			for (int j = light_num + 1; j < 5; j++)
			{
				light_box[j]->color(FL_GRAY);
				light_box[j]->redraw();
			}
		}
	}
}

//自动模式选择
void Brightness_Auto_Mode_cb(Fl_Button *, void *)
{
	Brightness_Flag = 0;
	brightness_up_butt->deactivate(); //按钮不使能
	brightness_down_butt->deactivate();
}

//手动模式选择
void Brightness_Manu_Mode_cb(Fl_Button *, void *)
{
	Brightness_Flag = 1;
	brightness_up_butt->activate();
	brightness_down_butt->activate();
}

//蜂鸣器控制
void Buzzer_Switch_cb(Fl_Button *, long i)
{
	Buzzer_Switch_No = i;

	if (Buzzer_Switch_No == 1)
		BuzzerOn();
	else
		BuzzerOff();
}
