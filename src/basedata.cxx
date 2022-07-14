/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 10:10:15
 * @LastEditors: ubuntu
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/basedata.cxx
 */
#include "head.h"

static char Base_Time_Buff[2][30];
static char Base_TrainNum[10];

// group_top界面初始化
void Basedata_Proccess()
{
	unsigned short port;
	short timetempd_y, timetempd_m, timetempd_d, timetempd_h, timetempd_mi, timetempd_s;

	port = 0xff;
	//时间
	timetempd_y = mvb.get_uchar(port, 0);
	timetempd_m = mvb.get_uchar(port, 1);
	timetempd_d = mvb.get_uchar(port, 2);
	timetempd_h = mvb.get_uchar(port, 3);
	timetempd_mi = mvb.get_uchar(port, 4);
	timetempd_s = mvb.get_uchar(port, 5);

	sprintf(Base_Time_Buff[0], "%04d-%02d-%02d", timetempd_y + 2000, timetempd_m, timetempd_d);
	sprintf(Base_Time_Buff[1], "%02d:%02d:%02d", timetempd_h, timetempd_mi, timetempd_s);
	Basedata_Date->label(Base_Time_Buff[0]);
	Basedata_Time->label(Base_Time_Buff[1]);

	Basedata_Date->redraw();
	Basedata_Time->redraw();

	//列车编组号显示
	if ((0 < mvb.get_ushort(0x3a, 24) * 65536 + mvb.get_ushort(0x3a, 26)) && (mvb.get_ushort(0x3a, 24) * 65536 + mvb.get_ushort(0x3a, 26) <= 999999))
	{
		sprintf(Base_TrainNum, "编组: %05d", mvb.get_ushort(0x3a, 24) * 65536 + mvb.get_ushort(0x3a, 26));
		Basedata_TrainNum->label(Base_TrainNum);
	}
	else
		Basedata_TrainNum->label("编组: -----");
	Basedata_TrainNum->redraw();
}
