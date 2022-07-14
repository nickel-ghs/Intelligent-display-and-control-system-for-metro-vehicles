/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-24 15:30:15
 * @LastEditors: ubuntu
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/DCU.cxx
 */
#include "head.h"
#include "DCU.h"

//车厢选择；Mp1,M1,M2,Mp2四个车厢选择按钮的回调函数
void DCU_Select_Car_cb(Fl_Button *, long i)
{
	DCU_Car_NO = i;

	switch (DCU_Car_NO)
	{
	case 2:
		DCU_Port = 0x10;
		break;
	case 3:
		DCU_Port = 0x11;
		break;
	case 4:
		DCU_Port = 0x12;
		break;
	case 5:
		DCU_Port = 0x13;
		break;
	}

	DCU_Clear();
}

//数据清除
void DCU_Clear()
{
	for (int i = 0; i < 11; i++)
	{
		DCU_Data[i]->label("");
		DCU_Data[i]->redraw();
	}

	for (int i = 0; i < 12; i++)
	{
		DCU_Switch[i]->label("");
		DCU_Switch[i]->redraw();
	}
}

void DCU_Proccess()
{
	//模拟量;将DCU 左6个,右5个模拟量数据填入表格中
	for (int i = 0; i < 11; i++)
	{
		if (i != 1 && i != 3 && i != 5 && i != 6 && i != 7 && i != 8)
		{
			sprintf(DCU_Buff[i], "%d", (mvb.get_ushort(DCU_Port, i * 2)));
			DCU_Data[i]->label(DCU_Buff[i]);
			DCU_Data[i]->redraw();
		}
		if (i == 3) //电机综合转速
		{
			sprintf(DCU_Buff[i], "%0.1f", (mvb.get_ushort(DCU_Port, i * 2) * 0.1));
			DCU_Data[i]->label(DCU_Buff[i]);
			DCU_Data[i]->redraw();
		}
		if ((i >= 5 && i <= 8) || i == 1) //电机温度1、2、3、4&&中间电流
		{
			if (mvb.get_ushort(DCU_Port, i * 2) <= 32767)
			{
				sprintf(DCU_Buff[i], "%d", (mvb.get_ushort(DCU_Port, i * 2)));
				DCU_Data[i]->label(DCU_Buff[i]);
				DCU_Data[i]->redraw();
			}
			else
			{
				sprintf(DCU_Buff[i], "%s%d", "-", (65535 - mvb.get_ushort(DCU_Port, i * 2) + 1));
				DCU_Data[i]->label(DCU_Buff[i]);
				DCU_Data[i]->redraw();
			}
		}
	}

	//开关量；将DCU 左6个,右6个开关量数据填入表格中
	for (int i = 0; i < 12; i++)
	{
		if (mvb.get_ubit(DCU_Port, 23 - i / 8, i % 8))
		{
			DCU_Switch[i]->label("1");
		}
		else
		{
			DCU_Switch[i]->label("0");
		}
		DCU_Switch[i]->redraw();
	}
}
