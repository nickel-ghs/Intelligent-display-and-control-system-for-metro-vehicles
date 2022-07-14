/*
 * @Author: your name
 * @Date: 2022-06-24 11:10:15
 * @LastEditTime: 2022-06-25 10:27:48
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/Broadcast_Switch.cxx
 */

#include "head.h"

long Transfer_Switch_No, LineMap_Switch_No, PISControl_Switch_No;
// char Transfer_Switch_Flag,LineMap_Switch_Flag,PISControl_Switch_Flag;
long PM_Mode_No;

//换乘广播
/*void Transfer_Switch_cb(Fl_Button*,long i)
{
	unsigned short port;
	Transfer_Switch_No=i;
	port=tc_no>1?0x6b1:0x1b1;

	mvb.put_ubit(port,1,1,Transfer_Switch_No);
	mvb.lp_put_alldata();
	Transfer_Switch_Flag=1;
}

//线路地图
void LineMap_Switch_cb(Fl_Button*,long i)
{
	unsigned short port;
	LineMap_Switch_No=i;
	port=tc_no>1?0x6b1:0x1b1;

	mvb.put_ubit(port,1,1,LineMap_Switch_No);
	mvb.lp_put_alldata();
	LineMap_Switch_Flag=1;
}*/

// PIS控制来源，两个按钮的回调函数：向port发送用户点击了哪个按钮
void PISControl_Switch_cb(Fl_Button *, long i)
{
	unsigned short port;
	PISControl_Switch_No = i;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ubit(port, 13, 0, PISControl_Switch_No);
	mvb.lp_put_alldata();
}

//反向运行模式，两个按钮的回调函数：向port发送用户点击了哪个按钮
void PISControl_Switch_cb_1(Fl_Button *, long i)
{
	unsigned short port;
	PISControl_Switch_No = i;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ubit(port, 13, 7, PISControl_Switch_No);
	mvb.lp_put_alldata();
}

// PM模式，两个按钮的回调函数：向port发送用户点击了哪个按钮+按钮是否使能
void PM_Mode_cb(Fl_Button *, long i)
{
	unsigned short port;
	PM_Mode_No = i;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ubit(port, 13, 6, PM_Mode_No);
	mvb.lp_put_alldata();

	if (PM_Mode_No == 1)
	{
		//下方四个控制按钮使能
		Broadcast_Pre->activate();
		Broadcast_Next->activate();
		broadcast_in->activate();
		broadcast_out->activate();
	}
	else
	{
		Broadcast_Pre->deactivate();
		Broadcast_Next->deactivate();
		broadcast_in->deactivate();
		broadcast_out->deactivate();
	}
}
