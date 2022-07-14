#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <i2cfun.h>
#include <FL/Fl_Group.H>
#include <FL/Fl.H>

void diameter_proccess();
Fl_Button *diameter_temp;
static int diameter_data[7] = {0};
static int diameter_no = 1;
static char count_diameter;
static char diameter1_char[5] = "", diameter2_char[5] = "";
char diameter_set_flag = 0;

//初始化
void diameter_proccess()
{
	unsigned short port;
	static char Diameter_Display_Buff[6][6];

	//将六个车的轮径值打印出来
	port = 0x29;
	for (int i = 1; i <= 6; i++)
	{
		//从port读入轮径，也可以从diameterlist.txt读入
		sprintf(Diameter_Display_Buff[i - 1], "%d", mvb.get_ushort(port, (i - 1) * 2));
		Diameter_Display[i]->label(Diameter_Display_Buff[i - 1]);
		Diameter_Display[i]->redraw();
	}
}

//六个输入框的回调函数
void diameter_sel_cb(Fl_Button *, long i)
{
	diameter_no = i;
	diameter_temp = diameter[diameter_no];
	diameter_temp->take_focus();
	diameter_temp->label("");
	//初始化
	count_diameter = 0;
	diameter1_char[0] = '\0';
}

//数字键盘的0~9数字按键的处理函数
void diameter_input_cb(Fl_Button *o, void *)
{
	count_diameter++;
	if (count_diameter <= 3) //输入长度小于等于3
	{
		//每按一次执行一次，将按键输入拼装成一个整数
		diameter2_char[0] = atoi(o->label()) + 48; // 48--'0';int-->char
		diameter2_char[1] = '\0';
		strcat(diameter1_char, diameter2_char);

		diameter_temp->copy_label(diameter1_char);
		diameter_temp->redraw();
		diameter_data[diameter_no] = (diameter1_char[0] - 48) * 100 + (diameter1_char[1] - 48) * 10 + (diameter1_char[2] - 48);

		if (count_diameter == 3)
		{
			//轮径要求(770,840),越区变805
			if (atoi(diameter_temp->label()) < 770)
				diameter_temp->copy_label("805");
			else if (atoi(diameter_temp->label()) > 840)
				diameter_temp->copy_label("805");
		}
	}
}

//数值键盘的del键，清除当前框数据
void diameter_input_del_cb(Fl_Button *, void *)
{
	diameter_temp->label("");
	diameter1_char[0] = '\0';
	count_diameter = 0;
}

//确定按钮---将用户输入数据写入port
void diameter_confirm_cb(Fl_Button *, void *)
{
	unsigned short port;
	char diameter_buff[7][5];

	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if (diameter_set_flag == 0)
	{
		FILE *fp;
		fp = fopen("diameterlist.txt", "rw+");

		for (int i = 1; i <= 6; i++)
		{
			if (diameter_data[i] >= 770 && diameter_data[i] <= 840) //
			{
				//将数据写入diameterlist.txt
				sprintf(diameter_buff[i], "%d", diameter_data[i]);
				fseek(fp, i * 10 + 4, SEEK_SET);
				fwrite(diameter_buff[i], 1, 3, fp);
				//将数据放入port
				mvb.put_ushort(port, 12 + (i - 1) * 2, diameter_data[i]);
				mvb.put_ubit(port, 0, i - 1, 1);
				mvb.lp_put_alldata();
			}
		}
		diameter_set_flag = 1;
		fclose(fp);
	}
	count_diameter = 0;
}

//取消按钮---清除框内所有输入
void diameter_cancel_cb(Fl_Button *, void *)
{
	diameter[1]->label("");
	diameter[2]->label("");
	diameter[3]->label("");
	diameter[4]->label("");
	diameter[5]->label("");
	diameter[6]->label("");
}

//维护界面切换至轮径设置界面
void diameter_cb(Fl_Button *, void *)
{
	if (!group_diameter_window->visible())
	{
		group_diameter_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--轮径设置");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_diameter_window;

		//六个输入框清零
		diameter_temp = diameter[1];
		diameter_temp->take_focus();
		diameter[1]->label("");
		diameter[2]->label("");
		diameter[3]->label("");
		diameter[4]->label("");
		diameter[5]->label("");
		diameter[6]->label("");
		//计数，输入缓存清零
		count_diameter = 0;
		diameter1_char[0] = '\0';
	}
}

//轮径设置界面切换至维护界面
void diameter_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}
