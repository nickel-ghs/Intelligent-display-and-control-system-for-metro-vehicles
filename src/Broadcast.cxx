#include "head.h"
char Broadcast_Speaker_Flag = 0, Broadcast_Pre_Flag = 0, Broadcast_Next_Flag = 0, Broadcast_in_Flag = 0, Broadcast_out_Flag = 0, Broadcast_Confirm_Flag = 0;

char Broadcast_Page = 0, Broadcast_No = 1, PageMax = 2;

static char Broadcast_Label[51][50] = {"", "区间临时停车", "列车再次启动", "大客流广播", "限速运行", "不停站通过",
									   "运行途中车门解锁", "前方站清客", "本站清客", "站内疏散", "区间疏散(无疏散平台)",
									   "区间疏散(有疏散平台)", "部分车门不能打开", "全部车门不能打开", "部分屏蔽门不能打开", "全部屏蔽门不能打开",
									   "车厢火警", "乘客求助", "全线列车暂停服务", "紧急广播停止", "------------------",
									   "------", "------", "------", "------", "------",
									   "------", "------", "------", "------", "------",
									   "------", "------", "------", "------", "------",
									   "------", "------", "------", "------", "------",
									   "------", "------", "------", "------", "------",
									   "------", "------", "------", "------", "------"};

static char Broadcast_Buff[11][5] = {};

//紧急广播初始化
void Broadcast_Init()
{
	for (int temp = 1; temp <= 10; temp++)
	{
		//画图
		Broadcast_Num[temp]->label("");
		sprintf(Broadcast_Buff[temp], "%d", Broadcast_Page * 10 + temp);
		Broadcast_Num[temp]->label(Broadcast_Buff[temp]);
		Broadcast_Num[temp]->redraw();
		Broadcast_Item[temp]->label("");
		Broadcast_Item[temp]->value(0);
		Broadcast_Item[temp]->label(Broadcast_Label[Broadcast_Page * 10 + temp]);
		Broadcast_Item[temp]->redraw();

		//第二页最后两个标注设置为99和100
		if ((Broadcast_Page == 1) && (temp == 9))
		{
			sprintf(Broadcast_Buff[temp], "%d", 99);
			Broadcast_Num[temp]->label(Broadcast_Buff[temp]);
		}
		else if ((Broadcast_Page == 1) && (temp == 10))
		{
			sprintf(Broadcast_Buff[temp], "%d", 100);
			Broadcast_Num[temp]->label(Broadcast_Buff[temp]);
		}
	}
}
//紧急广播十个选项的回调函数
void Broadcast_SelectNum_cb(Fl_Button *, long num)
{
	Broadcast_No = num;
}

//紧急广播确定按钮
void Broadcast_Confirm_cb(Fl_Button *, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;
	if ((Broadcast_Page == 1) && (Broadcast_No == 9))
	{
		mvb.put_ushort(port, 2, 99);
	}
	else
	{
		mvb.put_ushort(port, 2, Broadcast_Page * 10 + Broadcast_No);
	}
	Broadcast_Confirm_Flag = 1;
	mvb.lp_put_alldata();
}

//紧急广播取消按钮
void Broadcast_Cancel_cb(Fl_Button *o, void *)
{
	unsigned short port;

	if (o->value())
		o->value(0);
	else
		o->value(1);

	if (tc_no == 1)
		port = 0x1b0;
	else
		port = 0x6b0;

	if (o->value())
	{
		mvb.put_ubit(port, 13, 5, 1);
		mvb.put_ushort(port, 2, 0);
		mvb.lp_put_alldata();
		//页面十个选项不使能
		for (int i = 1; i <= 10; i++)
		{
			Broadcast_Item[i]->value(0);
			Broadcast_Item[i]->deactivate();
		}
	}
	else
	{
		mvb.put_ubit(port, 13, 5, 0);
		mvb.lp_put_alldata();

		for (int i = 1; i <= 10; i++)
		{
			Broadcast_Item[i]->activate();
		}
	}
}
//页面跳转--上一页
void Broadcast_PageUp_cb(Fl_Button *, void *)
{
	if (Broadcast_Page < PageMax - 1)
		Broadcast_Page++;
	Broadcast_Init();
}
//页面跳转--下一页
void Broadcast_PageDown_cb(Fl_Button *, void *)
{
	if (Broadcast_Page > 0)
		Broadcast_Page--;
	Broadcast_Init();
}

//上一站
void Broadcast_Pre_cb(Fl_Button *, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ubit(port, 13, 2, 1);
	mvb.lp_put_alldata();
	Broadcast_Pre_Flag = 1;
}

//下一站
void Broadcast_Next_cb(Fl_Button *, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ubit(port, 13, 1, 1);
	mvb.lp_put_alldata();
	Broadcast_Next_Flag = 1;
}

//进站广播
void Broadcast_in_cb(Fl_Button *, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ubit(port, 13, 3, 1);
	mvb.lp_put_alldata();
	Broadcast_in_Flag = 1;
}

//出站广播
void Broadcast_out_cb(Fl_Button *, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ubit(port, 13, 4, 1);
	mvb.lp_put_alldata();
	Broadcast_out_Flag = 1;
}

//切换至紧急广播界面
void main_emergency_cb(Fl_Button *, void *)
{
	if (!group_emergency_window->visible())
	{
		main_emergency_butt->value(0);
		group_emergency_window->show();
		label_window->label("紧急广播");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_emergency_window;

		Broadcast_Init(); //广播初始化
	}
}
