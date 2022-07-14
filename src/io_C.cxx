#include "head.h"
#define MY_GRAY 46
char io_C = 1;

void colorC_init()
{
	ioC_label_1->color(MY_GRAY);
	ioC_label_2->color(MY_GRAY);
	ioC_label_3->color(MY_GRAY);
	ioC_label_4->color(MY_GRAY);
	ioC_label_5->color(MY_GRAY);
	ioC_label_6->color(MY_GRAY);
	ioC_label_7->color(MY_GRAY);
	ioC_label_8->color(MY_GRAY);
	ioC_label_9->color(MY_GRAY);
	ioC_label_10->color(MY_GRAY);
	ioC_label_11->color(MY_GRAY);
	ioC_label_12->color(MY_GRAY);
	ioC_label_13->color(MY_GRAY);
	ioC_label_14->color(MY_GRAY);
	ioC_label_15->color(MY_GRAY);
	ioC_label_16->color(MY_GRAY);
	ioC_label_17->color(MY_GRAY);
	ioC_label_18->color(MY_GRAY);
	ioC_label_19->color(MY_GRAY);
	ioC_label_20->color(MY_GRAY);
	ioC_label_21->color(MY_GRAY);
	ioC_label_22->color(MY_GRAY);
	ioC_label_23->color(MY_GRAY);
	ioC_label_24->color(MY_GRAY);
	ioC_label_25->color(MY_GRAY);
	ioC_label_26->color(MY_GRAY);
	ioC_label_27->color(MY_GRAY);
	ioC_label_28->color(MY_GRAY);
	ioC_label_29->color(MY_GRAY);
	ioC_label_30->color(MY_GRAY);
	ioC_label_31->color(MY_GRAY);
	ioC_label_32->color(MY_GRAY);
	ioC_label_33->color(MY_GRAY);
	ioC_label_34->color(MY_GRAY);
	ioC_label_35->color(MY_GRAY);
	ioC_label_36->color(MY_GRAY);
	ioC_label_37->color(MY_GRAY);
	ioC_label_38->color(MY_GRAY);
	ioC_label_39->color(MY_GRAY);
	ioC_label_40->color(MY_GRAY);
	ioC_label_41->color(MY_GRAY);
	ioC_label_42->color(MY_GRAY);
	ioC_label_43->color(MY_GRAY);
	ioC_label_44->color(MY_GRAY);
	ioC_label_45->color(MY_GRAY);
	ioC_label_46->color(MY_GRAY);
	ioC_label_47->color(MY_GRAY);
	ioC_label_48->color(MY_GRAY);
	ioC_label_49->color(MY_GRAY);
	ioC_label_50->color(MY_GRAY);
	ioC_label_51->color(MY_GRAY);
	ioC_label_52->color(MY_GRAY);
	ioC_label_53->color(MY_GRAY);
	ioC_label_54->color(MY_GRAY);
	ioC_label_55->color(MY_GRAY);
	ioC_label_56->color(MY_GRAY);
	ioC_label_57->color(MY_GRAY);
	ioC_label_58->color(MY_GRAY);
	ioC_label_59->color(MY_GRAY);
	ioC_label_60->color(MY_GRAY);
	ioC_label_61->color(MY_GRAY);
	ioC_label_62->color(MY_GRAY);
	ioC_label_63->color(MY_GRAY);
	ioC_label_64->color(MY_GRAY);
}

void ioC_proccess()
{
	unsigned short port;

	if (io_C == 1)
		port = 0x03;
	else
		port = 0x04;

	ioC_label_1->label("本车停放制动缓解");
	if (mvb.get_ubit(port, 13, 0))
		ioC_label_1->color(FL_GREEN);
	else
		ioC_label_1->color(MY_GRAY);

	ioC_label_2->label("本车摩擦制动1缓解");
	if (mvb.get_ubit(port, 13, 1))
		ioC_label_2->color(FL_GREEN);
	else
		ioC_label_2->color(MY_GRAY);

	ioC_label_3->label("本车摩擦制动2缓解");
	if (mvb.get_ubit(port, 13, 2))
		ioC_label_3->color(FL_GREEN);
	else
		ioC_label_3->color(MY_GRAY);

	ioC_label_4->label("");
	ioC_label_5->label("");

	ioC_label_6->label("L_本车摩擦制动1切除");
	if (mvb.get_ubit(port, 13, 5))
		ioC_label_6->color(FL_GREEN);
	else
		ioC_label_6->color(MY_GRAY);

	ioC_label_7->label("L_本车摩擦制动2切除");
	if (mvb.get_ubit(port, 13, 6))
		ioC_label_7->color(FL_GREEN);
	else
		ioC_label_7->color(MY_GRAY);

	ioC_label_8->label("");

	ioC_label_9->label("火灾报警");
	if (mvb.get_ubit(port, 12, 0))
		ioC_label_9->color(FL_GREEN);
	else
		ioC_label_9->color(MY_GRAY);

	ioC_label_10->label("L_火灾故障");
	if (mvb.get_ubit(port, 12, 1))
		ioC_label_10->color(FL_GREEN);
	else
		ioC_label_10->color(MY_GRAY);

	ioC_label_11->label("半自动车钩联挂好");
	if (mvb.get_ubit(port, 12, 2))
		ioC_label_11->color(FL_GREEN);
	else
		ioC_label_11->color(MY_GRAY);

	ioC_label_12->label("半自动末端");
	if (mvb.get_ubit(port, 12, 3))
		ioC_label_12->color(FL_GREEN);
	else
		ioC_label_12->color(MY_GRAY);

	ioC_label_13->label("列车门关好左C");
	if (mvb.get_ubit(port, 12, 4))
		ioC_label_13->color(FL_GREEN);
	else
		ioC_label_13->color(MY_GRAY);

	ioC_label_14->label("列车门关好右C");
	if (mvb.get_ubit(port, 12, 5))
		ioC_label_14->color(FL_GREEN);
	else
		ioC_label_14->color(MY_GRAY);

	ioC_label_15->label("本车左门状态监控");
	if (mvb.get_ubit(port, 12, 6))
		ioC_label_15->color(FL_GREEN);
	else
		ioC_label_15->color(MY_GRAY);

	ioC_label_16->label("本车右门状态监控");
	if (mvb.get_ubit(port, 12, 7))
		ioC_label_16->color(FL_GREEN);
	else
		ioC_label_16->color(MY_GRAY);

	if (io_C == 1)
	{
		ioC_label_17->label("380V拓展接触器监控");
		if (mvb.get_ubit(port, 15, 0))
			ioC_label_17->color(FL_GREEN);
		else
			ioC_label_17->color(MY_GRAY);
	}
	else
	{
		ioC_label_17->label("");
	}

	ioC_label_18->label("压缩机运行");
	if (mvb.get_ubit(port, 15, 1))
		ioC_label_18->color(FL_GREEN);
	else
		ioC_label_18->color(MY_GRAY);

	ioC_label_19->label("总风压力低于5.5bar");
	if (mvb.get_ubit(port, 15, 2))
		ioC_label_19->color(FL_GREEN);
	else
		ioC_label_19->color(MY_GRAY);

	ioC_label_20->label("");
	ioC_label_21->label("");
	ioC_label_22->label("");
	ioC_label_23->label("");
	ioC_label_24->label("");
	ioC_label_25->label("");
	ioC_label_26->label("");
	ioC_label_27->label("");
	ioC_label_28->label("");
	ioC_label_29->label("");
	ioC_label_30->label("");
	ioC_label_31->label("");
	ioC_label_32->label("");

	if (io_C == 1)
	{
		ioC_group3->label("DXM1.O");

		ioC_label_33->label("380V拓展允许");
		if (mvb.get_ubit(port, 21, 0))
			ioC_label_33->color(FL_GREEN);
		else
			ioC_label_33->color(MY_GRAY);
	}
	else加速度
	{
		ioC_group3->label("");
		ioC_label_33->label("");
	}
	ioC_label_34->label("允许空压机运行");
	if (mvb.get_ubit(port, 21, 1))
		ioC_label_34->color(FL_GREEN);
	else
		ioC_label_34->color(MY_GRAY);
	ioC_label_35->label("");
	ioC_label_36->label("");
	ioC_label_37->label("");
	ioC_label_38->label("");
	ioC_label_39->label("");
	ioC_label_40->label("");
	ioC_label_41->label("");
	ioC_label_42->label("");
	ioC_label_43->label("");
	ioC_label_44->label("");
	ioC_label_45->label("");
	ioC_label_46->label("");
	ioC_label_47->label("");
	ioC_label_48->label("");

	ioC_label_49->label("");
	ioC_label_50->label("");
	ioC_label_51->label("");
	ioC_label_52->label("");
	ioC_label_53->label("");
	ioC_label_54->label("");
	ioC_label_55->label("");
	ioC_label_56->label("");
	ioC_label_57->label("");
	ioC_label_58->label("");
	ioC_label_59->label("");
	ioC_label_60->label("");
	ioC_label_61->label("");
	ioC_label_62->label("");
	ioC_label_63->label("");
	ioC_label_64->label("");

	ioC_label_1->redraw();
	ioC_label_2->redraw();
	ioC_label_3->redraw();
	ioC_label_4->redraw();
	ioC_label_5->redraw();
	ioC_label_6->redraw();
	ioC_label_7->redraw();
	ioC_label_8->redraw();
	ioC_label_9->redraw();
	ioC_label_10->redraw();
	ioC_label_11->redraw();
	ioC_label_12->redraw();
	ioC_label_13->redraw();
	ioC_label_14->redraw();
	ioC_label_15->redraw();
	ioC_label_16->redraw();
	ioC_label_17->redraw();
	ioC_label_18->redraw();
	ioC_label_19->redraw();
	ioC_label_20->redraw();
	ioC_label_21->redraw();
	ioC_label_22->redraw();
	ioC_label_23->redraw();
	ioC_label_24->redraw();
	ioC_label_25->redraw();
	ioC_label_26->redraw();
	ioC_label_27->redraw();
	ioC_label_28->redraw();
	ioC_label_29->redraw();
	ioC_label_30->redraw();
	ioC_label_31->redraw();
	ioC_label_32->redraw();
	ioC_label_33->redraw();
	ioC_label_34->redraw();
	ioC_label_35->redraw();
	ioC_label_36->redraw();
	ioC_label_37->redraw();
	ioC_label_38->redraw();
	ioC_label_39->redraw();
	ioC_label_40->redraw();
	ioC_label_41->redraw();
	ioC_label_42->redraw();
	ioC_label_43->redraw();
	ioC_label_44->redraw();
	ioC_label_45->redraw();
	ioC_label_46->redraw();
	ioC_label_47->redraw();
	ioC_label_48->redraw();
	ioC_label_49->redraw();
	ioC_label_50->redraw();
	ioC_label_51->redraw();
	ioC_label_52->redraw();
	ioC_label_53->redraw();
	ioC_label_54->redraw();
	ioC_label_55->redraw();
	ioC_label_56->redraw();
	ioC_label_57->redraw();
	ioC_label_58->redraw();
	ioC_label_59->redraw();
	ioC_label_60->redraw();
	ioC_label_61->redraw();
	ioC_label_62->redraw();
	ioC_label_63->redraw();
	ioC_label_64->redraw();
}

void io_c1_cb(Fl_Button *, void *)
{
	io_C = 1;
	colorC_init();
}

void io_c2_cb(Fl_Button *, void *)
{
	io_C = 2;
	colorC_init();
}
