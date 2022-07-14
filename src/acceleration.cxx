#include "head.h"

void acceleration_proccess();
char acceleration_flag = 1; //目标速度和起始速度输入控制变量

//初始化
void acceleration_proccess()
{
	unsigned short port;
	static char buf_acceleration[5][10];
	port = 0x29;

	//制动状态
	if (mvb.get_ubit(port, 23, 6) == 1)
		acceleration_brake_status->label("1");
	else
		acceleration_brake_status->label("0");
	//右边五个框的值
	sprintf(buf_acceleration[0], "%0.2f", mvb.get_ushort(port, 16) * 0.01);
	acceleration_ave_speed->label(buf_acceleration[0]); //平均加速度
	sprintf(buf_acceleration[1], "%0.2f", mvb.get_ushort(port, 18) * 0.01);
	acceleration_cur_speed->label(buf_acceleration[1]); //平均减速度
	sprintf(buf_acceleration[2], "%0.1f", mvb.get_ushort(port, 20) * 0.1);
	acceleration_brake_distance->label(buf_acceleration[2]); //制动距离
	sprintf(buf_acceleration[3], "%0.2f", mvb.get_ushort(port, 14) * 0.1);
	reduce_start_speed->label(buf_acceleration[3]); //减速度开始时的速度
	sprintf(buf_acceleration[4], "%0.2f", mvb.get_ushort(0x01, 4) * 0.1);
	realtime_speed->label(buf_acceleration[4]); //实时速度

	acceleration_ave_speed->redraw();
	acceleration_cur_speed->redraw();
	acceleration_brake_distance->redraw();
	reduce_start_speed->redraw();
	realtime_speed->redraw();
}

//"开始测试"按钮
void acceleration_start_cb(Fl_Button *o, void *)
{
	unsigned short port;

	if (tc_no == 1)
	{
		port = 0x1b2;
	}
	else
	{
		port = 0x6b2;
	}

	if ((0 <= atoi(acceleration_speedstart_input->value()) <= 80) && (0 <= atoi(acceleration_speedaim_input->value()) <= 80)) //速度都必须在[0,80]区间
	{
		mvb.put_ushort(port, 2, atoi(acceleration_speedstart_input->value()));
		mvb.put_ushort(port, 4, atoi(acceleration_speedaim_input->value()));
		mvb.put_ubit(port, 1, 0, 1);
		mvb.lp_put_alldata();
	}
}

//数字键盘0~9数字按钮
void acceleration_input_cb(Fl_Button *o, void *)
{
	if (acceleration_flag) //开始速度框
		acceleration_speedstart_input->insert(o->label(), 0);
	else //终止速度框
		acceleration_speedaim_input->insert(o->label(), 0);
}

//数字键盘"del"按钮,所以输入删除
void acceleration_input_del_cb(Fl_Button *, void *)
{
	acceleration_speedstart_input->value("");
	acceleration_speedaim_input->value("");
	acceleration_flag = 1;
}

//数字键盘"确定"按钮
void acceleration_confirm_cb(Fl_Button *, void *)
{
	acceleration_flag = 0;
}

//测试取消按钮
void acceleration_cancel_cb(Fl_Button *o, void *)
{
	unsigned short port;

	if (tc_no == 1)
	{
		port = 0x1b2;
	}
	else
	{
		port = 0x6b2;
	}

	mvb.put_uchar(port, 2, 0);
	mvb.put_uchar(port, 4, 0);
	mvb.put_ubit(port, 1, 0, 0);
	mvb.lp_put_alldata();
}

//维护界面切换至加速度测试界面
void Acceleration_cb(Fl_Button *, void *)
{
	if (!group_acceleration_window->visible())
	{
		group_acceleration_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--加速度测试");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_acceleration_window;
	}
}

//加速度测试界面切换至维护界面
void acceleration_return_cb(Fl_Button *, void *)
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
