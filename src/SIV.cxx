/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-24 15:12:32
 * @LastEditors: ubuntu
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/SIV.cxx
 */
#include "head.h"
#include "SIV.h"

//车厢选择，TC1和TC2按钮的回调函数
void SIV_Select_Car_cb(Fl_Button *, long i)
{
	SIV_Car_NO = i;
	SIV_Clear();
}

//界面数据清除
void SIV_Clear()
{
	for (int i = 0; i < 13; i++)
	{
		SIV_Data[i]->label("");
		SIV_Data[i]->redraw();
	}

	for (int i = 0; i < 5; i++)
	{
		SIV_Switch[i]->label("");
		SIV_Switch[i]->redraw();
	}
}

void SIV_Proccess()
{
	//模拟量；将SIV 前十七个模拟量数据填入表格中
	for (int i = 0; i < 17; i++)
	{
		if (i != 15 && i != 16)
		{
			sprintf(SIV_Buff[i], "%d", (mvb.get_ushort(SIV_Data_Struct[SIV_Car_NO - 1][i].SIV_Port, SIV_Data_Struct[SIV_Car_NO - 1][i].SIV_Byte)));
			SIV_Data[i]->label(SIV_Buff[i]);
			SIV_Data[i]->redraw();
		}
		else
		{
			if (mvb.get_ushort(SIV_Data_Struct[SIV_Car_NO - 1][i].SIV_Port, SIV_Data_Struct[SIV_Car_NO - 1][i].SIV_Byte) <= 32767)
			{
				sprintf(SIV_Buff[i], "%d", (mvb.get_ushort(SIV_Data_Struct[SIV_Car_NO - 1][i].SIV_Port, SIV_Data_Struct[SIV_Car_NO - 1][i].SIV_Byte)));
				SIV_Data[i]->label(SIV_Buff[i]);
				SIV_Data[i]->redraw();
			}
			else
			{
				sprintf(SIV_Buff[i], "%s%d", "-", (65535 - mvb.get_ushort(SIV_Data_Struct[SIV_Car_NO - 1][i].SIV_Port, SIV_Data_Struct[SIV_Car_NO - 1][i].SIV_Byte) + 1));
				SIV_Data[i]->label(SIV_Buff[i]);
				SIV_Data[i]->redraw();
			}
		}
	}
	//充电机蓄电池充电电流

	//开关量；将SIV 后七个开关量数据填入表格中
	for (int i = 0; i < 7; i++)
	{
		if (mvb.get_ubit(SIV_Switch_Struct[SIV_Car_NO - 1][i].Switch_Port, SIV_Switch_Struct[SIV_Car_NO - 1][i].Switch_Byte, SIV_Switch_Struct[SIV_Car_NO - 1][i].Switch_Bit))
		{
			SIV_Switch[i]->label("1");
		}
		else
		{
			SIV_Switch[i]->label("0");
		}
		SIV_Switch[i]->redraw();
	}
}
