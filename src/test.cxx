#include "head.h"
char mp1_vvvf_isolation_flag = 0;
char m1_vvvf_isolation_flag = 0;

//"保持制动切除"按钮
void test_brake_cut_cb(Fl_Light_Button *o, void *) //保持制动切除
{
	//发送数据
	unsigned short port;
	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if ((o->value()) == 0)
	{
		mvb.put_ubit(port, 31, 5, 0);
	}
	else
	{
		mvb.put_ubit(port, 31, 5, 1);
	}
}

//"整车电制动切除"按钮
void Ebrake_all_cb(Fl_Light_Button *o, void *) //整车电制动切除
{
	unsigned short port;
	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if ((o->value()) == 0)
	{
		mvb.put_ubit(port, 30, 2, 0);
	}
	else
	{
		mvb.put_ubit(port, 30, 2, 1);
	}
}

//"2车制动切除"按钮
void Ebrake_2_cb(Fl_Light_Button *o, void *) // 2车电制动切除
{
	unsigned short port;
	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if ((o->value()) == 0)
	{
		mvb.put_ubit(port, 31, 6, 0);
	}
	else
	{
		mvb.put_ubit(port, 31, 6, 1);
	}
}

//"3车制动切除"按钮
void Ebrake_3_cb(Fl_Light_Button *o, void *) // 3车电制动切除
{
	unsigned short port;
	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if ((o->value()) == 0)
	{
		mvb.put_ubit(port, 31, 7, 0);
	}
	else
	{
		mvb.put_ubit(port, 31, 7, 1);
	}
}

//"4车制动切除"按钮
void Ebrake_4_cb(Fl_Light_Button *o, void *) // 4车电制动切除
{
	unsigned short port;
	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if ((o->value()) == 0)
	{
		mvb.put_ubit(port, 30, 0, 0);
	}
	else
	{
		mvb.put_ubit(port, 30, 0, 1);
	}
}

//"5车制动切除"按钮
void Ebrake_5_cb(Fl_Light_Button *o, void *) // 5车电制动切除
{
	unsigned short port;
	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if ((o->value()) == 0)
	{
		mvb.put_ubit(port, 30, 1, 0);
	}
	else
	{
		mvb.put_ubit(port, 30, 1, 1);
	}
}

//切换至测试界面
void test_cb(Fl_Button *, void *)
{
	if (!group_test_window->visible())
	{
		group_test_window->show();
		label_window->label("测试");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_test_window;
		//返回主界面按钮取消使能
		group_main_butt->deactivate();
	}
}

//返回按钮
void test_return_cb(Fl_Button *o, void *)
{
	unsigned short port;
	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;
	//界面切换
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		label_window->label("维护");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
		group_main_butt->activate();
	}
	//数据发送
	mvb.put_ubit(port, 30, 0, 0);
	mvb.put_ubit(port, 30, 1, 0);
	mvb.put_ubit(port, 30, 2, 0);
	mvb.put_ubit(port, 31, 5, 0);
	mvb.put_ubit(port, 31, 6, 0);
	mvb.put_ubit(port, 31, 7, 0);
	mvb.lp_put_alldata();
	//按钮全部释放
	test_brake_cut_butt->value(0);
	Ebrake_2_Butt->value(0);
	Ebrake_3_Butt->value(0);
	Ebrake_4_Butt->value(0);
	Ebrake_5_Butt->value(0);
	Ebrake_all_Butt->value(0);
}
