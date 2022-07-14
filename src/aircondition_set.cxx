#include "head.h"
#include "aircondition_set.h"

//空调设置选择：六个按钮（除最后两个）的回调函数：向port发送用户点击了哪个按钮
void AircSet_Select_Mode_cb(Fl_Button *, long i)
{
	AirSet_No = i;

	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ushort(port, 26, AirSet_No);
	mvb.lp_put_alldata();
	Air_Set_Flag = 1; //标志位，表示信息量被释放
}

void Airc_Set_Proccess()
{
	//显示车辆号
	for (int i = 0; i < 6; i++)
	{
		if ((mvb.get_ushort(0x3A, i * 4) * 65536 + mvb.get_ushort(0x3A, i * 4 + 2)) > 0)
		{
			//从mvb获取数据
			sprintf(AircSet_Number_Buff[i], "%06d", mvb.get_ushort(0x3A, i * 4) * 65536 + mvb.get_ushort(0x3A, i * 4 + 2));
			AircSet_Number[i]->label(AircSet_Number_Buff[i]);
		}
		else
		{
			AircSet_Number[i]->label("000000");
		}
		AircSet_Number[i]->redraw();
	}

	//显示室内温度
	for (int i = 0; i < 6; i++)
	{
		if (mvb.get_ushort(AircSet_Indoor_Struct[i].Indoor_Port, AircSet_Indoor_Struct[i].Indoor_Byte) <= 32767)
		{
			sprintf(AircSet_Temp_Buff[i], "%0.1f", (mvb.get_ushort(AircSet_Indoor_Struct[i].Indoor_Port, AircSet_Indoor_Struct[i].Indoor_Byte) * 0.1));
			Airc_Set_Temp[i]->label(AircSet_Temp_Buff[i]);
			Airc_Set_Temp[i]->redraw();
		}
		else
		{
			sprintf(AircSet_Temp_Buff[i], "%s%0.1f%s", "-", (65535 - mvb.get_ushort(AircSet_Indoor_Struct[i].Indoor_Port, AircSet_Indoor_Struct[i].Indoor_Byte) + 1) * 0.1, "℃");
			Airc_Set_Temp[i]->label(AircSet_Temp_Buff[i]);
			Airc_Set_Temp[i]->redraw();
		}
	}

	//显示目标温度
	for (int i = 0; i < 6; i++)
	{
		if (mvb.get_ushort(AircSet_Target_Struct[i].Target_Port, AircSet_Target_Struct[i].Target_Byte) <= 32767)
		{
			sprintf(AircSet_Target_Buff[i], "%0.1f", (mvb.get_ushort(AircSet_Target_Struct[i].Target_Port, AircSet_Target_Struct[i].Target_Byte) * 0.1));
			Airc_Target_Temp[i]->label(AircSet_Target_Buff[i]);
			Airc_Target_Temp[i]->redraw();
		}
		else
		{
			sprintf(AircSet_Target_Buff[i], "%s%0.1f%s", "-", (65535 - mvb.get_ushort(AircSet_Target_Struct[i].Target_Port, AircSet_Target_Struct[i].Target_Byte) + 1) * 0.1, "℃");
			Airc_Target_Temp[i]->label(AircSet_Target_Buff[i]);
			Airc_Target_Temp[i]->redraw();
		}
	}
}

//火灾模式
void AircSet_Fire_cb(Fl_Button *o, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	if (o->value())
		o->value(0);
	else
		o->value(1);

	if (o->value()) //火灾按钮被按
	{
		// mvb发送数据
		mvb.put_ushort(port, 26, 1024);
		mvb.lp_put_alldata();
		AircSet_Fire_Flag = 1; //标志位

		//前面按钮deactivate
		for (int i = 1; i <= 6; i++)
		{
			AircSet_Butt[i]->value(0);
			AircSet_Butt[i]->deactivate();
			AircSet_Butt[i]->redraw();
		}
		AircSet_Butt[8]->deactivate();
		AircSet_Butt[8]->redraw();
	}
	else //火灾按钮没被按
	{
		mvb.put_ushort(port, 26, 0);
		mvb.lp_put_alldata();
		AircSet_Fire_Flag = 0;
		for (int i = 1; i <= 6; i++)
		{
			AircSet_Butt[i]->value(0);
			AircSet_Butt[i]->activate();
			AircSet_Butt[i]->redraw();
		}
		AircSet_Butt[8]->activate();
		AircSet_Butt[8]->redraw();
	}
}

//空调测试
void AircSet_Test_cb(Fl_Button *o, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	if (o->value())
		o->value(0);
	else
		o->value(1);

	if (o->value()) //没被按
	{
		mvb.put_ushort(port, 26, 2);
		mvb.lp_put_alldata();
		AircSet_Test_Flag = 1;

		for (int i = 1; i <= 7; i++)
		{
			AircSet_Butt[i]->value(0);
			AircSet_Butt[i]->deactivate();
			AircSet_Butt[i]->redraw();
		}
	}
	else //被按
	{
		mvb.put_ushort(port, 26, 0);
		mvb.lp_put_alldata();
		AircSet_Test_Flag = 0;

		for (int i = 1; i <= 7; i++)
		{
			AircSet_Butt[i]->value(0);
			AircSet_Butt[i]->activate();
			AircSet_Butt[i]->redraw();
		}
	}
}

//设置界面切换至空调设置界面
void aircondition_set_cb(Fl_Button *, void *)
{
	if (!group_aircondition_all_window->visible())
	{
		group_aircondition_all_window->show();
		label_window->label("空调设置");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_aircondition_all_window;
	}
}

//空调设置界面切换至设置界面
void aircondition_return_cb(Fl_Button *, void *)
{
	if (!group_set_window->visible())
	{
		group_set_window->show();
		label_window->label("设置");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_set_window;
	}
}
