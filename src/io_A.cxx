#include "head.h"
#define MY_GRAY 46
char io_page = 1, io_A = 1;

// 32个DIM(NAME)的顔色更新-->变灰色
void color_init()
{
	ioA_label_1->color(MY_GRAY);
	ioA_label_2->color(MY_GRAY);
	ioA_label_3->color(MY_GRAY);
	ioA_label_4->color(MY_GRAY);
	ioA_label_5->color(MY_GRAY);
	ioA_label_6->color(MY_GRAY);
	ioA_label_7->color(MY_GRAY);
	ioA_label_8->color(MY_GRAY);
	ioA_label_9->color(MY_GRAY);
	ioA_label_10->color(MY_GRAY);
	ioA_label_11->color(MY_GRAY);
	ioA_label_12->color(MY_GRAY);
	ioA_label_13->color(MY_GRAY);
	ioA_label_14->color(MY_GRAY);
	ioA_label_15->color(MY_GRAY);
	ioA_label_16->color(MY_GRAY);
	ioA_label_17->color(MY_GRAY);
	ioA_label_18->color(MY_GRAY);
	ioA_label_19->color(MY_GRAY);
	ioA_label_20->color(MY_GRAY);
	ioA_label_21->color(MY_GRAY);
	ioA_label_22->color(MY_GRAY);
	ioA_label_23->color(MY_GRAY);
	ioA_label_24->color(MY_GRAY);
	ioA_label_25->color(MY_GRAY);
	ioA_label_26->color(MY_GRAY);
	ioA_label_27->color(MY_GRAY);
	ioA_label_28->color(MY_GRAY);
	ioA_label_29->color(MY_GRAY);
	ioA_label_30->color(MY_GRAY);
	ioA_label_31->color(MY_GRAY);
	ioA_label_32->color(MY_GRAY);
}

//初始化
void ioA_proccess()
{
	unsigned short port;
	static char buf_ioA[5][10];

	if (io_A == 1)
		port = 0x03;
	else
		port = 0x04;
	//写数据
	if (io_page == 1) //第一页
	{
		ioA_group_1->label("DIM");

		ioA_label_1->label("牵引");
		if (mvb.get_ubit(port, 1, 0))
			ioA_label_1->color(FL_GREEN);
		else
			ioA_label_1->color(MY_GRAY);

		ioA_label_2->label("司机室占有");
		if (mvb.get_ubit(port, 1, 1))
			ioA_label_2->color(FL_GREEN);
		else
			ioA_label_2->color(MY_GRAY);

		ioA_label_3->label("向前(列车线)");
		if (mvb.get_ubit(port, 1, 2))
			ioA_label_3->color(FL_GREEN);
		else
			ioA_label_3->color(MY_GRAY);

		ioA_label_4->label("向后(列车线)");
		if (mvb.get_ubit(port, 1, 3))
			ioA_label_4->color(FL_GREEN);
		else
			ioA_label_4->color(MY_GRAY);

		ioA_label_5->label("警惕旁路");
		if (mvb.get_ubit(port, 1, 4))
			ioA_label_5->color(FL_GREEN);
		else
			ioA_label_5->color(MY_GRAY);

		ioA_label_6->label("警惕按钮");
		if (mvb.get_ubit(port, 1, 5))
			ioA_label_6->color(FL_GREEN);
		else
			ioA_label_6->color(MY_GRAY);

		ioA_label_7->label("L_紧急制动(列车线)");
		if (mvb.get_ubit(port, 1, 6))
			ioA_label_7->color(FL_GREEN);
		else
			ioA_label_7->color(MY_GRAY);

		ioA_label_8->label("");
		ioA_label_9->label("");

		ioA_label_10->label("L_无库用电源供电");
		if (mvb.get_ubit(port, 0, 1))
			ioA_label_10->color(FL_GREEN);
		else
			ioA_label_10->color(MY_GRAY);

		ioA_label_11->label("");
		ioA_label_12->label("");

		ioA_label_13->label("L_本侧司机室\n紧急停车按下");
		if (mvb.get_ubit(port, 0, 4))
			ioA_label_13->color(FL_GREEN);
		else
			ioA_label_13->color(MY_GRAY);

		ioA_label_14->label("L_紧急停车(列车线)");
		if (mvb.get_ubit(port, 0, 5))
			ioA_label_14->color(FL_GREEN);
		else
			ioA_label_14->color(MY_GRAY);

		ioA_label_15->label("线电流限制");
		if (mvb.get_ubit(port, 0, 6))
			ioA_label_15->color(FL_GREEN);
		else
			ioA_label_15->color(MY_GRAY);

		ioA_label_16->label("");

		ioA_label_17->label("停放制动缓解旁路");
		if (mvb.get_ubit(port, 3, 0))
			ioA_label_17->color(FL_GREEN);
		else
			ioA_label_17->color(MY_GRAY);

		ioA_label_18->label("所有制动缓解旁路");
		if (mvb.get_ubit(port, 3, 1))
			ioA_label_18->color(FL_GREEN);
		else
			ioA_label_18->color(MY_GRAY);

		ioA_label_19->label("所有制动缓解");
		if (mvb.get_ubit(port, 3, 2))
			ioA_label_19->color(FL_GREEN);
		else
			ioA_label_19->color(MY_GRAY);

		ioA_label_20->label("本车停放制动缓解");
		if (mvb.get_ubit(port, 3, 3))
			ioA_label_20->color(FL_GREEN);
		else
			ioA_label_20->color(MY_GRAY);

		ioA_label_21->label("本车摩擦制动2缓解");
		if (mvb.get_ubit(port, 3, 4))
			ioA_label_21->color(FL_GREEN);
		else
			ioA_label_21->color(MY_GRAY);

		ioA_label_22->label("本车摩擦制动1缓解");
		if (mvb.get_ubit(port, 3, 5))
			ioA_label_22->color(FL_GREEN);
		else
			ioA_label_22->color(MY_GRAY);

		ioA_label_23->label("L_本车摩擦制动1切除");
		if (mvb.get_ubit(port, 3, 6))
			ioA_label_23->color(FL_GREEN);
		else
			ioA_label_23->color(MY_GRAY);

		ioA_label_24->label("L_本车摩擦制动2切除");
		if (mvb.get_ubit(port, 3, 7))
			ioA_label_24->color(FL_GREEN);
		else
			ioA_label_24->color(MY_GRAY);

		ioA_label_25->label("无库用供电旁路");
		if (mvb.get_ubit(port, 2, 0))
			ioA_label_25->color(FL_GREEN);
		else
			ioA_label_25->color(MY_GRAY);

		ioA_label_26->label("L_制动");
		if (mvb.get_ubit(port, 2, 1))
			ioA_label_26->color(FL_GREEN);
		else
			ioA_label_26->color(MY_GRAY);

		ioA_label_27->label("总风压力可用旁路");
		if (mvb.get_ubit(port, 2, 2))
			ioA_label_27->color(FL_GREEN);
		else
			ioA_label_27->color(MY_GRAY);

		ioA_label_28->label("");

		ioA_label_29->label("升弓允许旁路");
		if (mvb.get_ubit(port, 2, 4))
			ioA_label_29->color(FL_GREEN);
		else
			ioA_label_29->color(MY_GRAY);

		ioA_label_30->label("慢行开关");
		if (mvb.get_ubit(port, 2, 5))
			ioA_label_30->color(FL_GREEN);
		else
			ioA_label_30->color(MY_GRAY);

		ioA_label_31->label("RM模式");
		if (mvb.get_ubit(port, 2, 6))
			ioA_label_31->color(FL_GREEN);
		else
			ioA_label_31->color(MY_GRAY);

		ioA_label_32->label("URM模式(ATC旁路)");
		if (mvb.get_ubit(port, 2, 7))
			ioA_label_32->color(FL_GREEN);
		else
			ioA_label_32->color(MY_GRAY);
	}
	else if (io_page == 2) //第二页
	{
		ioA_group_1->label("DXM.O");

		ioA_label_1->label("整车空调启动");
		if (mvb.get_ubit(port, 17, 0))
			ioA_label_1->color(FL_GREEN);
		else
			ioA_label_1->color(MY_GRAY);

		ioA_label_2->label("TC车空调启动");
		if (mvb.get_ubit(port, 17, 1))
			ioA_label_2->color(FL_GREEN);
		else
			ioA_label_2->color(MY_GRAY);

		ioA_label_3->label("整车空调关");
		if (mvb.get_ubit(port, 17, 2))
			ioA_label_3->color(FL_GREEN);
		else
			ioA_label_3->color(MY_GRAY);

		ioA_label_4->label("里程计距离信号");
		if (mvb.get_ubit(port, 17, 3))
			ioA_label_4->color(FL_GREEN);
		else
			ioA_label_4->color(MY_GRAY);

		ioA_label_5->label("");

		ioA_label_6->label("旁路状态显示");
		if (mvb.get_ubit(port, 17, 5))
			ioA_label_6->color(FL_GREEN);
		else
			ioA_label_6->color(MY_GRAY);

		ioA_label_7->label("");
		ioA_label_8->label("");
		ioA_label_9->label("");
		ioA_label_10->label("");
		ioA_label_11->label("");
		ioA_label_12->label("");
		ioA_label_13->label("");
		ioA_label_14->label("");
		ioA_label_15->label("");
		ioA_label_16->label("");
		ioA_label_17->label("");
		ioA_label_18->label("");
		ioA_label_19->label("");

		ioA_label_20->label("VCMe要求紧急制动");
		if (mvb.get_ubit(port, 19, 3))
			ioA_label_20->color(FL_GREEN);
		else
			ioA_label_20->color(MY_GRAY);

		ioA_label_21->label("两台DC/DC不工作");
		if (mvb.get_ubit(port, 19, 4))
			ioA_label_21->color(FL_GREEN);
		else
			ioA_label_21->color(MY_GRAY);

		ioA_label_22->label("");
		ioA_label_23->label("");
		ioA_label_24->label("");
		ioA_label_25->label("");
		ioA_label_26->label("");
		ioA_label_27->label("");
		ioA_label_28->label("");
		ioA_label_29->label("");
		ioA_label_30->label("");
		ioA_label_31->label("");
		ioA_label_32->label("");
	}
	else if (io_page == 3) //第三页
	{
		ioA_group_1->label("DXM.I");
		ioA_label_1->label("门零速旁路");
		if (mvb.get_ubit(port, 5, 0))
			ioA_label_1->color(FL_GREEN);
		else
			ioA_label_1->color(MY_GRAY);

		ioA_label_2->label("");

		ioA_label_3->label("门零速监视");
		if (mvb.get_ubit(port, 5, 2))
			ioA_label_3->color(FL_GREEN);
		else
			ioA_label_3->color(MY_GRAY);

		ioA_label_4->label("门开命令左");
		if (mvb.get_ubit(port, 5, 3))
			ioA_label_4->color(FL_GREEN);
		else
			ioA_label_4->color(MY_GRAY);

		ioA_label_5->label("门开命令右");
		if (mvb.get_ubit(port, 5, 4))
			ioA_label_5->color(FL_GREEN);
		else
			ioA_label_5->color(MY_GRAY);

		ioA_label_6->label("门关命令左");
		if (mvb.get_ubit(port, 5, 5))
			ioA_label_6->color(FL_GREEN);
		else
			ioA_label_6->color(MY_GRAY);

		ioA_label_7->label("门关命令右");
		if (mvb.get_ubit(port, 5, 6))
			ioA_label_7->color(FL_GREEN);
		else
			ioA_label_7->color(MY_GRAY);

		ioA_label_8->label("");
		ioA_label_9->label("");

		ioA_label_10->label("列车门关好左");
		if (mvb.get_ubit(port, 4, 1))
			ioA_label_10->color(FL_GREEN);
		else
			ioA_label_10->color(MY_GRAY);

		ioA_label_11->label("列车门关好右");
		if (mvb.get_ubit(port, 4, 2))
			ioA_label_11->color(FL_GREEN);
		else
			ioA_label_11->color(MY_GRAY);

		ioA_label_12->label("本车左门状态监控");
		if (mvb.get_ubit(port, 4, 3))
			ioA_label_12->color(FL_GREEN);
		else
			ioA_label_12->color(MY_GRAY);

		ioA_label_13->label("本车右门状态监控");
		if (mvb.get_ubit(port, 4, 4))
			ioA_label_13->color(FL_GREEN);
		else
			ioA_label_13->color(MY_GRAY);

		ioA_label_14->label("");
		ioA_label_15->label("");

		ioA_label_16->label("门关好旁路");
		if (mvb.get_ubit(port, 4, 7))
			ioA_label_16->color(FL_GREEN);
		else
			ioA_label_16->color(MY_GRAY);

		ioA_label_17->label("车钩监视旁路");
		if (mvb.get_ubit(port, 7, 0))
			ioA_label_17->color(FL_GREEN);
		else
			ioA_label_17->color(MY_GRAY);

		ioA_label_18->label("联挂好");
		if (mvb.get_ubit(port, 7, 1))
			ioA_label_18->color(FL_GREEN);
		else
			ioA_label_18->color(MY_GRAY);

		ioA_label_19->label("救援模式");
		if (mvb.get_ubit(port, 7, 2))
			ioA_label_19->color(FL_GREEN);
		else
			ioA_label_19->color(MY_GRAY);

		ioA_label_20->label("灯测试");
		if (mvb.get_ubit(port, 7, 3))
			ioA_label_20->color(FL_GREEN);
		else
			ioA_label_20->color(MY_GRAY);

		ioA_label_21->label("");
		ioA_label_22->label("");

		ioA_label_23->label("电池已输出");
		if (mvb.get_ubit(port, 7, 6))
			ioA_label_23->color(FL_GREEN);
		else
			ioA_label_23->color(MY_GRAY);

		ioA_label_24->label("电池欠压");
		if (mvb.get_ubit(port, 7, 7))
			ioA_label_24->color(FL_GREEN);
		else
			ioA_label_24->color(MY_GRAY);

		ioA_label_25->label("火灾报警");
		if (mvb.get_ubit(port, 6, 0))
			ioA_label_25->color(FL_GREEN);
		else
			ioA_label_25->color(MY_GRAY);

		ioA_label_26->label("L_火灾故障");
		if (mvb.get_ubit(port, 6, 1))
			ioA_label_26->color(FL_GREEN);
		else
			ioA_label_26->color(MY_GRAY);

		ioA_label_27->label("空调关命令");
		if (mvb.get_ubit(port, 6, 2))
			ioA_label_27->color(FL_GREEN);
		else
			ioA_label_27->color(MY_GRAY);

		ioA_label_28->label("");

		ioA_label_29->label("空调开命令");
		if (mvb.get_ubit(port, 6, 4))
			ioA_label_29->color(FL_GREEN);
		else
			ioA_label_29->color(MY_GRAY);

		ioA_label_30->label("TC车空调开命令");
		if (mvb.get_ubit(port, 6, 5))
			ioA_label_30->color(FL_GREEN);
		else
			ioA_label_30->color(MY_GRAY);

		ioA_label_31->label("强迫缓解命令");
		if (mvb.get_ubit(port, 6, 6))
			ioA_label_31->color(FL_GREEN);
		else
			ioA_label_31->color(MY_GRAY);

		ioA_label_32->label("    500kpa命令来自运输装置");
		if (mvb.get_ubit(port, 6, 7))
			ioA_label_32->color(FL_GREEN);
		else
			ioA_label_32->color(MY_GRAY);
	}
	ioA_label_1->redraw();
	ioA_label_2->redraw();
	ioA_label_3->redraw();
	ioA_label_4->redraw();
	ioA_label_5->redraw();
	ioA_label_6->redraw();
	ioA_label_7->redraw();
	ioA_label_8->redraw();
	ioA_label_9->redraw();
	ioA_label_10->redraw();
	ioA_label_11->redraw();
	ioA_label_12->redraw();
	ioA_label_13->redraw();
	ioA_label_14->redraw();
	ioA_label_15->redraw();
	ioA_label_16->redraw();
	ioA_label_17->redraw();
	ioA_label_18->redraw();
	ioA_label_19->redraw();
	ioA_label_20->redraw();
	ioA_label_21->redraw();
	ioA_label_22->redraw();
	ioA_label_23->redraw();
	ioA_label_24->redraw();
	ioA_label_25->redraw();
	ioA_label_26->redraw();
	ioA_label_27->redraw();
	ioA_label_28->redraw();
	ioA_label_29->redraw();
	ioA_label_30->redraw();
	ioA_label_31->redraw();
	ioA_label_32->redraw();
	// AXM数据
	sprintf(buf_ioA[0], "%0.2f", mvb.get_ushort(port, 24) * 0.0003051); //运输装置压力传感器压力值
	io_transit_press->label(buf_ioA[0]);
	sprintf(buf_ioA[1], "%0.2f", mvb.get_ushort(port, 26) * 0.0003051); //手动基准值
	io_benchmark->label(buf_ioA[1]);
	sprintf(buf_ioA[2], "%0.2f", mvb.get_ushort(port, 28) * 0.004884);
	io_netv_table->label(buf_ioA[2]); //网压表
	sprintf(buf_ioA[3], "%0.2f", mvb.get_ushort(port, 30) * 0.004884);
	io_speed_table->label(buf_ioA[3]); //速度表
}

//"TC1"按钮
void io_a1_cb(Fl_Button *, void *)
{
	io_A = 1;
	color_init();
}

//"TC2"按钮
void io_a2_cb(Fl_Button *, void *)
{
	io_A = 2;
	color_init();
}

//"上一页"按钮
void ioA_pageup_cb(Fl_Button *, void *)
{
	if (io_page > 1)
	{
		io_page--;
		color_init();
	}
}

//"下一页"按钮
void ioA_pagedown_cb(Fl_Button *, void *)
{
	if (io_page < 3)
	{
		io_page++;
		color_init();
	}
}
