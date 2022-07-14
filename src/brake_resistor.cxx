#include "head.h"
void brake_resistor_process();

//初始化
void brake_resistor_process()
{
	unsigned short port;
	port = 0x12;

	//风机接触器状态
	if (mvb.get_ubit(port, 23, 2))
		blower_contactor_m11->color(FL_GREEN); //颜色变绿
	else
		blower_contactor_m11->color(FL_GRAY); //颜色变绿

	if (mvb.get_ubit(port, 23, 3))
		blower_contactor_m21->color(FL_GREEN);
	else
		blower_contactor_m21->color(FL_GRAY);

	if (mvb.get_ubit(port, 23, 4))
		blower_contactor_m22->color(FL_GREEN);
	else
		blower_contactor_m22->color(FL_GRAY);

	if (mvb.get_ubit(port, 23, 5))
		blower_contactor_m12->color(FL_GREEN);
	else
		blower_contactor_m12->color(FL_GRAY);

	blower_contactor_m11->redraw();
	blower_contactor_m21->redraw();
	blower_contactor_m22->redraw();
	blower_contactor_m12->redraw();
}

//切换至制动电阻例行试验界面
void brake_resistor_test_cb(Fl_Button *, void *)
{
	if (!brake_resistor_window->visible())
	{
		brake_resistor_window->show();
		label_window->label("制动电阻例行试验");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = brake_resistor_window;
	}
	//进界面一级菜单按钮全屏蔽
	group_main_butt->deactivate();
}

//制动电阻例行试验界面切换回检修界面；返回按钮
void brake_resistor_return_cb(Fl_Button *o, void *)
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
	}

	//数据发送
	mvb.put_ubit(port, 31, 0, 0);
	mvb.put_ubit(port, 31, 1, 0);
	mvb.put_ubit(port, 31, 2, 0);
	mvb.put_ubit(port, 31, 3, 0);
	mvb.put_ubit(port, 31, 4, 0);
	mvb.lp_put_alldata();

	//试验全部取消
	brake_test_start_but->label("开始测试");
	brake_test_start_but->value(0);
	blower_start_but->deactivate();
	blower_start_but->value(0);
	blower_start_m21_but->deactivate();
	blower_start_m21_but->value(0);
	blower_start_m22_but->deactivate();
	blower_start_m22_but->value(0);
	blower_start_m12_but->deactivate();
	blower_start_m12_but->value(0);

	//返回至检修界面时一级菜单按钮恢复
	group_main_butt->activate();
}

//开始测试按钮
void test_start_cb(Fl_Button *o, void *)
{
	unsigned short port;

	if (o->value())
		o->value(0);
	else
		o->value(1);

	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if (o->value())
	{
		o->label("结束测试");
		mvb.put_ubit(port, 31, 0, 1);
		mvb.lp_put_alldata();
		//按钮使能
		blower_start_but->activate();
		blower_start_m21_but->activate();
		blower_start_m22_but->activate();
		blower_start_m12_but->activate();
	}
	else
	{
		o->label("开始测试");
		mvb.put_ubit(port, 31, 0, 0);
		mvb.lp_put_alldata();
		blower_start_but->deactivate();
		blower_start_but->value(0);
		blower_start_m21_but->deactivate();
		blower_start_m21_but->value(0);
		blower_start_m22_but->deactivate();
		blower_start_m22_but->value(0);
		blower_start_m12_but->deactivate();
		blower_start_m12_but->value(0);
	}
}

//风机启动;"制动电阻风机启动(Mp1)"按钮
void blower_start_cb(Fl_Button *o, void *) // M11
{
	unsigned short port;

	if (o->value())
		o->value(0);
	else
		o->value(1);

	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if (o->value())
	{
		mvb.put_ubit(port, 31, 1, 1);
		mvb.lp_put_alldata();
	}
	else
	{
		mvb.put_ubit(port, 31, 1, 0);
		mvb.lp_put_alldata();
	}
}

//"制动电阻风机启动(M1)"按钮，
void blower_start_m21_cb(Fl_Button *o, void *) // M21
{
	unsigned short port;

	if (o->value())
		o->value(0);
	else
		o->value(1);

	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if (o->value())
	{
		mvb.put_ubit(port, 31, 2, 1);
		mvb.lp_put_alldata();
	}
	else
	{
		mvb.put_ubit(port, 31, 2, 0);
		mvb.lp_put_alldata();
	}
}
//"制动电阻风机启动(M2)"按钮
void blower_start_m22_cb(Fl_Button *o, void *) // M22
{
	unsigned short port;

	if (o->value())
		o->value(0);
	else
		o->value(1);

	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if (o->value())
	{
		mvb.put_ubit(port, 31, 3, 1);
		mvb.lp_put_alldata();
	}
	else
	{
		mvb.put_ubit(port, 31, 3, 0);
		mvb.lp_put_alldata();
	}
}
//"制动电阻风机启动(Mp2)"按钮
void blower_start_m12_cb(Fl_Button *o, void *) // M12
{
	unsigned short port;

	if (o->value())
		o->value(0);
	else
		o->value(1);

	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;

	if (o->value())
	{
		mvb.put_ubit(port, 31, 4, 1);
		mvb.lp_put_alldata();
	}
	else
	{
		mvb.put_ubit(port, 31, 4, 0);
		mvb.lp_put_alldata();
	}
}
