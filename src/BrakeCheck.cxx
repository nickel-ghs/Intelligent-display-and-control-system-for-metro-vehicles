/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 10:03:07
 * @LastEditors: ubuntu
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/BrakeCheck.cxx
 */
#include "head.h"
#include "BrakeCheck.h"
//初始化
void BrakeCheck_proccess()
{
	int i, j;
	//载荷
	for (int i = 0; i < 6; i++) //六个载荷检测
	{
		sprintf(BrakeCheck_Load_Buff[i], "%d", mvb.get_ushort(Brake_Check_Load_Struct[i].Load_Port, Brake_Check_Load_Struct[i].Load_Byte));
		BrakeCheck_Load[i]->label(BrakeCheck_Load_Buff[i]);
		BrakeCheck_Load[i]->redraw();
	}
	//自检结果显示
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (mvb.get_ubit(Brake_Check_Result_Struct[i][j].Result_Port, Brake_Check_Result_Struct[i][j].Result_Byte, Brake_Check_Result_Struct[i][j].Result_Bit))
			{
				BrakeCheck_Result[i + 1]->label(BrakeCheck_Array[j]);
				BrakeCheck_Result[i + 1]->redraw();
				break;
			}
		}
		if (j == 4)
		{
			BrakeCheck_Result[i + 1]->label("    ");
			BrakeCheck_Result[i + 1]->redraw();
		}
	}
}

//制动自检开始按钮
void BrakeCheck_Start_cb(Fl_Button *o, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ubit(port, 12, 7, 1);
	mvb.lp_put_alldata();
	BrakeCheck_Start_Flag = 1;

	BrakeCheck_Start_Butt->value(1);
}
