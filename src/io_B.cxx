#include "head.h"
#define MY_GRAY 46
char io_B = 1;

void colorB_init()
{
	ioB_label_1->color(MY_GRAY);
	ioB_label_2->color(MY_GRAY);
	ioB_label_3->color(MY_GRAY);
	ioB_label_4->color(MY_GRAY);
	ioB_label_5->color(MY_GRAY);
	ioB_label_6->color(MY_GRAY);
	ioB_label_7->color(MY_GRAY);
	ioB_label_8->color(MY_GRAY);
	ioB_label_9->color(MY_GRAY);
	ioB_label_10->color(MY_GRAY);
	ioB_label_11->color(MY_GRAY);
	ioB_label_12->color(MY_GRAY);
	ioB_label_13->color(MY_GRAY);
	ioB_label_14->color(MY_GRAY);
	ioB_label_15->color(MY_GRAY);
	ioB_label_16->color(MY_GRAY);
	ioB_label_17->color(MY_GRAY);
	ioB_label_18->color(MY_GRAY);
	ioB_label_19->color(MY_GRAY);
	ioB_label_20->color(MY_GRAY);
	ioB_label_21->color(MY_GRAY);
	ioB_label_22->color(MY_GRAY);
	ioB_label_23->color(MY_GRAY);
	ioB_label_24->color(MY_GRAY);
	ioB_label_25->color(MY_GRAY);
	ioB_label_26->color(MY_GRAY);
	ioB_label_27->color(MY_GRAY);
	ioB_label_28->color(MY_GRAY);
	ioB_label_29->color(MY_GRAY);
	ioB_label_30->color(MY_GRAY);
	ioB_label_31->color(MY_GRAY);
	ioB_label_32->color(MY_GRAY);

	ioB_label_33->color(MY_GRAY);
	ioB_label_34->color(MY_GRAY);
	ioB_label_35->color(MY_GRAY);
	ioB_label_36->color(MY_GRAY);
	ioB_label_37->color(MY_GRAY);
	ioB_label_38->color(MY_GRAY);
	ioB_label_39->color(MY_GRAY);
	ioB_label_40->color(MY_GRAY);
	ioB_label_41->color(MY_GRAY);
	ioB_label_42->color(MY_GRAY);
	ioB_label_43->color(MY_GRAY);
	ioB_label_44->color(MY_GRAY);
	ioB_label_45->color(MY_GRAY);
	ioB_label_46->color(MY_GRAY);
	ioB_label_47->color(MY_GRAY);
	ioB_label_48->color(MY_GRAY);
	ioB_label_49->color(MY_GRAY);
	ioB_label_50->color(MY_GRAY);
	ioB_label_51->color(MY_GRAY);
	ioB_label_52->color(MY_GRAY);
	ioB_label_53->color(MY_GRAY);
	ioB_label_54->color(MY_GRAY);
	ioB_label_55->color(MY_GRAY);
	ioB_label_56->color(MY_GRAY);
	ioB_label_57->color(MY_GRAY);
	ioB_label_58->color(MY_GRAY);
	ioB_label_59->color(MY_GRAY);
	ioB_label_60->color(MY_GRAY);
	ioB_label_61->color(MY_GRAY);
	ioB_label_62->color(MY_GRAY);
	ioB_label_63->color(MY_GRAY);
	ioB_label_64->color(MY_GRAY);
}

void ioB_proccess()
{
	unsigned short port;

	if (io_B == 1)
		port = 0x03;
	else
		port = 0x04;

	ioB_label_1->label("L_本弓隔离");
	if (mvb.get_ubit(port, 9, 0))
		ioB_label_1->color(FL_GREEN);
	else
		ioB_label_1->color(MY_GRAY);

	ioB_label_2->label("升弓指令");
	if (mvb.get_ubit(port, 9, 1))
		ioB_label_2->color(FL_GREEN);
	else
		ioB_label_2->color(MY_GRAY);

	ioB_label_3->label("降弓指令");
	if (mvb.get_ubit(port, 9, 2))
		ioB_label_3->color(FL_GREEN);
	else
		ioB_label_3->color(MY_GRAY);

	ioB_label_4->label("本弓升");
	if (mvb.get_ubit(port, 9, 3))
		ioB_label_4->color(FL_GREEN);
	else
		ioB_label_4->color(MY_GRAY);

	ioB_label_5->label("列车占有(列车线)");
	if (mvb.get_ubit(port, 9, 4))
		ioB_label_5->color(FL_GREEN);
	else
		ioB_label_5->color(MY_GRAY);

	ioB_label_6->label("本车停放制动缓解");
	if (mvb.get_ubit(port, 9, 5))
		ioB_label_6->color(FL_GREEN);
	else
		ioB_label_6->color(MY_GRAY);

	ioB_label_7->label("本车摩擦制动1缓解");
	if (mvb.get_ubit(port, 9, 6))
		ioB_label_7->color(FL_GREEN);
	else
		ioB_label_7->color(MY_GRAY);

	ioB_label_8->label("本车摩擦制动2缓解");
	if (mvb.get_ubit(port, 9, 7))
		ioB_label_8->color(FL_GREEN);
	else
		ioB_label_8->color(MY_GRAY);

	ioB_label_9->label("火灾报警");
	if (mvb.get_ubit(port, 8, 0))
		ioB_label_9->color(FL_GREEN);
	else
		ioB_label_9->color(MY_GRAY);

	ioB_label_10->label("L_火灾故障");
	if (mvb.get_ubit(port, 8, 1))
		ioB_label_10->color(FL_GREEN);
	else
		ioB_label_10->color(MY_GRAY);

	ioB_label_11->label("L_本车摩擦制动1切除");
	if (mvb.get_ubit(port, 8, 2))
		ioB_label_11->color(FL_GREEN);
	else
		ioB_label_11->color(MY_GRAY);

	ioB_label_12->label("L_本车摩擦制动2切除");
	if (mvb.get_ubit(port, 8, 3))
		ioB_label_12->color(FL_GREEN);
	else
		ioB_label_12->color(MY_GRAY);

	ioB_label_13->label("列车门关好右B");
	if (mvb.get_ubit(port, 8, 4))
		ioB_label_13->color(FL_GREEN);
	else
		ioB_label_13->color(MY_GRAY);

	ioB_label_14->label("列车门关好左B");
	if (mvb.get_ubit(port, 8, 5))
		ioB_label_14->color(FL_GREEN);
	else
		ioB_label_14->color(MY_GRAY);

	ioB_label_15->label("本车左门状态监控");
	if (mvb.get_ubit(port, 8, 6))
		ioB_label_15->color(FL_GREEN);
	else
		ioB_label_15->color(MY_GRAY);

	ioB_label_16->label("本车右门状态监控");
	if (mvb.get_ubit(port, 8, 7))
		ioB_label_16->color(FL_GREEN);
	else
		ioB_label_16->color(MY_GRAY);

	ioB_label_17->label("脚踏泵升弓截断塞门");
	if (mvb.get_ubit(port, 11, 0))
		ioB_label_17->color(FL_GREEN);
	else
		ioB_label_17->color(MY_GRAY);

	ioB_label_18->label("");
	ioB_label_19->label("");
	ioB_label_20->label("");
	ioB_label_21->label("");
	ioB_label_22->label("");

	ioB_label_23->label("刀开关受电弓位(允许升弓)");
	if (mvb.get_ubit(port, 11, 6))
		ioB_label_23->color(FL_GREEN);
	else
		ioB_label_23->color(MY_GRAY);

	ioB_label_24->label("刀开关库用位(允许库用)");
	if (mvb.get_ubit(port, 11, 7))
		ioB_label_24->color(FL_GREEN);
	else
		ioB_label_24->color(MY_GRAY);

	ioB_label_25->label("");
	ioB_label_26->label("");
	ioB_label_27->label("");
	ioB_label_28->label("");
	ioB_label_29->label("");
	ioB_label_30->label("");
	ioB_label_31->label("");
	ioB_label_32->label("");

	//输出
	ioB_label_33->label("");
	ioB_label_34->label("");
	ioB_label_35->label("");
	ioB_label_36->label("");
	ioB_label_37->label("");
	ioB_label_38->label("");
	ioB_label_39->label("");
	ioB_label_40->label("");
	ioB_label_41->label("");
	ioB_label_42->label("");
	ioB_label_43->label("");
	ioB_label_44->label("");
	ioB_label_45->label("");
	ioB_label_46->label("");
	ioB_label_47->label("");
	ioB_label_48->label("");
	ioB_label_49->label("");
	ioB_label_50->label("");
	ioB_label_51->label("");
	ioB_label_52->label("");
	ioB_label_53->label("");
	ioB_label_54->label("");
	ioB_label_55->label("");
	ioB_label_56->label("");
	ioB_label_57->label("");
	ioB_label_58->label("");
	ioB_label_59->label("");
	ioB_label_60->label("");
	ioB_label_61->label("");
	ioB_label_62->label("");
	ioB_label_63->label("");
	ioB_label_64->label("");

	ioB_label_1->redraw();
	ioB_label_2->redraw();
	ioB_label_3->redraw();
	ioB_label_4->redraw();
	ioB_label_5->redraw();
	ioB_label_6->redraw();
	ioB_label_7->redraw();
	ioB_label_8->redraw();
	ioB_label_9->redraw();
	ioB_label_10->redraw();
	ioB_label_11->redraw();
	ioB_label_12->redraw();
	ioB_label_13->redraw();
	ioB_label_14->redraw();
	ioB_label_15->redraw();
	ioB_label_16->redraw();
	ioB_label_17->redraw();
	ioB_label_18->redraw();
	ioB_label_19->redraw();
	ioB_label_20->redraw();
	ioB_label_21->redraw();
	ioB_label_22->redraw();
	ioB_label_23->redraw();
	ioB_label_24->redraw();
	ioB_label_25->redraw();
	ioB_label_26->redraw();
	ioB_label_27->redraw();
	ioB_label_28->redraw();
	ioB_label_29->redraw();
	ioB_label_30->redraw();
	ioB_label_31->redraw();
	ioB_label_32->redraw();

	ioB_label_33->redraw();
	ioB_label_34->redraw();
	ioB_label_35->redraw();
	ioB_label_36->redraw();
	ioB_label_37->redraw();
	ioB_label_38->redraw();
	ioB_label_39->redraw();
	ioB_label_40->redraw();
	ioB_label_41->redraw();
	ioB_label_42->redraw();
	ioB_label_43->redraw();
	ioB_label_44->redraw();
	ioB_label_45->redraw();
	ioB_label_46->redraw();
	ioB_label_47->redraw();
	ioB_label_48->redraw();
	ioB_label_49->redraw();
	ioB_label_50->redraw();
	ioB_label_51->redraw();
	ioB_label_52->redraw();
	ioB_label_53->redraw();
	ioB_label_54->redraw();
	ioB_label_55->redraw();
	ioB_label_56->redraw();
	ioB_label_57->redraw();
	ioB_label_58->redraw();
	ioB_label_59->redraw();
	ioB_label_60->redraw();
	ioB_label_61->redraw();
	ioB_label_62->redraw();
	ioB_label_63->redraw();
	ioB_label_64->redraw();
}

void io_b1_cb(Fl_Button *, void *)
{
	io_B = 1;
	colorB_init();
}

void io_b2_cb(Fl_Button *, void *)
{
	io_B = 2;
	colorB_init();
}
