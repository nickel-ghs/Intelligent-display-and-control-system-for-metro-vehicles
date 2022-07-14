#include "head.h"
#include "DCU_M.h"

void dcu_converse();

Fl_Box *DCUm_Data[4][11];
Fl_Box *DCUm_Switch[4][12];

//数据填充
void DCUm_Proccess()
{
	//模拟量;将DCU 左6个,右5个模拟量数据填入表格中
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 11; i++)
		{
			if (i != 1 && i != 3 && i != 5 && i != 6 && i != 7 && i != 8)
			{
				sprintf(DCUm_Buff[j][i], "%d", (mvb.get_ushort(DCUm_Port[j], i * 2)));
				DCUm_Data[j][i]->label(DCUm_Buff[j][i]);
				DCUm_Data[j][i]->redraw();
			}
			if (i == 3) //电机综合转速
			{
				sprintf(DCUm_Buff[j][i], "%0.1f", (mvb.get_ushort(DCUm_Port[j], i * 2) * 0.1));
				DCUm_Data[j][i]->label(DCUm_Buff[j][i]);
				DCUm_Data[j][i]->redraw();
			}
			if ((i >= 5 && i <= 8) || i == 1) //电机温度1、2、3、4&&中间电流
			{
				if (mvb.get_ushort(DCUm_Port[j], i * 2) <= 32767)
				{
					sprintf(DCUm_Buff[j][i], "%d", (mvb.get_ushort(DCUm_Port[j], i * 2)));
					DCUm_Data[j][i]->label(DCUm_Buff[j][i]);
					DCUm_Data[j][i]->redraw();
				}
				else
				{
					sprintf(DCUm_Buff[j][i], "%s%d", "-", (65535 - mvb.get_ushort(DCUm_Port[j], i * 2) + 1));
					DCUm_Data[j][i]->label(DCUm_Buff[j][i]);
					DCUm_Data[j][i]->redraw();
				}
			}
		}
		//开关量；将DCU 左6个,右6个开关量数据填入表格中
		for (int i = 0; i < 12; i++)
		{
			if (mvb.get_ubit(DCUm_Port[j], 23 - i / 8, i % 8))
			{
				DCUm_Switch[j][i]->label("1"); //开
			}
			else
			{
				DCUm_Switch[j][i]->label("0");
			}
			DCUm_Switch[j][i]->redraw();
		}
	}
}
//控制单元
void dcu_converse()
{
	for (int i = 0; i < 11; i++)
	{
		DCUm_Data[0][i] = DCU_Data0[i];
		DCUm_Data[1][i] = DCU_Data1[i];
		DCUm_Data[2][i] = DCU_Data2[i];
		DCUm_Data[3][i] = DCU_Data3[i];
	}
	for (int i = 0; i < 12; i++)
	{
		DCUm_Switch[0][i] = DCU_Switch0[i];
		DCUm_Switch[1][i] = DCU_Switch1[i];
		DCUm_Switch[2][i] = DCU_Switch2[i];
		DCUm_Switch[3][i] = DCU_Switch3[i];
	}
}

//维护界面切换至DCU界面
void dcu_m_cb(Fl_Button *, void *)
{
	if (!group_dcum_window->visible())
	{
		group_dcum_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--DCU数据");
		if (tempwin == NULL)
			group_dcum_window->hide();
		else
			tempwin->hide();
		tempwin = group_dcum_window;

		dcu_converse(); //
	}
}
// DCU界面切换至维护界面
void dcum_return_cb(Fl_Button *, void *)
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
