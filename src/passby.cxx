/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 10:37:51
 * @LastEditors: ubuntu
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/passby.cxx
 */
#include "head.h"
#include "passby.h"

// group_passby_window线路/车站选择界面初始化
void Passby_Proccess()
{
	for (int i = 0; i < 9; i++)
	{
		//第一行底黄字黑，二~八底黑字白
		if (mvb.get_ubit(Passby_Box_Struct[i].Passby_Port, Passby_Box_Struct[i].Passby_Byte, Passby_Box_Struct[i].Passby_Bit))
		{
			Passby_box[i]->color(FL_YELLOW);
			Passby_box[i]->labelcolor(FL_BLACK);
		}
		else
		{
			Passby_box[i]->color(FL_BLACK);
			Passby_box[i]->labelcolor(FL_WHITE);
		}
		Passby_box[i]->redraw();
	}
}
