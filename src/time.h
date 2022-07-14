#include "head.h"
#include "time.h"

//时间设置输入
void time_input_cb(Fl_Button *o, void *)
{
	countt++;
	if (countt <= 4)
		timey_input->insert(o->label(), 0);
	else if (countt > 4 & countt <= 6)
		timem_input->insert(o->label(), 0);
	else if (countt > 6 & countt <= 8)
		timed_input->insert(o->label(), 0);
	else if (countt > 8 & countt <= 10)
		timeh_input->insert(o->label(), 0);
	else if (countt > 10 & countt <= 12)
		timemi_input->insert(o->label(), 0);
	else if (countt > 12 & countt <= 14)
		times_input->insert(o->label(), 0);
}

void time_input_del_cb(Fl_Button *, void *)
{
	timey_input->value("");
	timem_input->value("");
	timed_input->value("");
	timeh_input->value("");
	timemi_input->value("");
	times_input->value("");
	countt = 0;
}

//时间设置确认与取消
void time_confirm_cb(Fl_Button *, void *)
{
	if ((atoi(timey_input->value()) >= 2014) && (atoi(timey_input->value()) <= 2084) && (atoi(timem_input->value()) > 0) && (atoi(timem_input->value()) <= 12) && (atoi(timed_input->value()) > 0) && (atoi(timed_input->value()) <= 31) && (atoi(timeh_input->value()) >= 0) && (atoi(timeh_input->value()) <= 23) && (atoi(timemi_input->value()) >= 0) && (atoi(timemi_input->value()) < 60) && (atoi(times_input->value()) >= 0) && (atoi(times_input->value()) < 60))
	{
		char buff_time[20];

		sprintf(buff_time, "%s-%s-%s %s:%s:%s", timey_input->value(), timem_input->value(), timed_input->value(), timeh_input->value(), timemi_input->value(), times_input->value());
		settime(buff_time);

		time_t t;
		struct tm *p;
		time(&t);
		unsigned short port;
		p = localtime(&t);

		if (tc_no == 1)
			port = 0x1b1;
		else
			port = 0x6b1;

		mvb.put_uchar(port, 6, p->tm_year - 100);
		mvb.put_uchar(port, 7, p->tm_mon + 1);
		mvb.put_uchar(port, 8, p->tm_mday);
		mvb.put_uchar(port, 9, p->tm_hour);
		mvb.put_uchar(port, 10, p->tm_min);
		mvb.put_uchar(port, 11, p->tm_sec);
		mvb.put_ubit(port, 1, 1, 1);
		mvb.lp_put_alldata();
		time_set_flag = 1;
		time_update_flag = 1;
	}
}

void hmi_synchro()
{
	unsigned short port;
	now_time_flag = mvb.get_ubit(0xff, 7, 0);
	char cc[23];

	//时间更新
	if ((old_time_flag == 0) && now_time_flag && (time_set_flag == 0) && (time_update_flag == 0) && (mvb.get_uchar(0xff, 0) >= 14) && (mvb.get_uchar(0xff, 0) <= 84) && (mvb.get_uchar(0xff, 1) >= 1) && (mvb.get_uchar(0xff, 1) <= 12) && (mvb.get_uchar(0xff, 2) >= 1) && (mvb.get_uchar(0xff, 2) <= 31) && (mvb.get_uchar(0xff, 3) <= 23) && (mvb.get_uchar(0xff, 4) < 60) && (mvb.get_uchar(0xff, 5) < 60))
	{
		sprintf(cc, "%04d-%02d-%02d %02d:%02d:%02d", mvb.get_uchar(0xff, 0) + 2000, mvb.get_uchar(0xff, 1), mvb.get_uchar(0xff, 2), mvb.get_uchar(0xff, 3), mvb.get_uchar(0xff, 4), mvb.get_uchar(0xff, 5));
		settime(cc);
	}

	old_time_flag = now_time_flag;

	if (time_update_flag == 1)
	{
		time_update_count++;
		if (time_update_count == 16)
		{
			time_update_flag = 0;
			time_update_count = 0;
		}
	}

	//时间设置延时
	if (time_set_flag)
	{
		if (tc_no == 1)
			port = 0x1b1;
		else
			port = 0x6b1;
		Time_Count++;
		if (Time_Count == 6)
		{
			mvb.put_ubit(port, 1, 1, 0);
			mvb.lp_put_alldata();
			Time_Count = 0;
			time_set_flag = 0;
		}
	}
}

//维护界面切换至时间设置界面
void time_cb(Fl_Button *, void *)
{
	if (!group_time_window->visible())
	{
		group_time_window->show();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--时间日期设置");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_time_window;
		countt = 0;
	}
}

//时间设置界面切换至维护界面
void time_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}
