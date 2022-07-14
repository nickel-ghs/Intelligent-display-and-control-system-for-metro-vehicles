#include "head.h"
#include "total.h"
static char Total_Data_Buff[7][15]; //临时存储值

//初始化
void total_proccess()
{
	unsigned short port;
	port = 0x28;

	for (int i = 0; i < 7; i++)
	{
		//七个能耗数据显示
		sprintf(Total_Data_Buff[i], "%d", mvb.get_uint(port, i * 4));
		Total_Data[i]->label(Total_Data_Buff[i]);
		Total_Data[i]->redraw();
	}
}
//六个设置按钮
void total_input_cb(Fl_Button *, long i)
{
	totalno = i;			 //设置哪个能耗
	counttotal = 0;			 //用户输入计数位
	Group_Total_Set->show(); //数字键盘
	total_input->value("");
}
//数字键盘0~9数字按钮
void totaln_input_cb(Fl_Button *o, void *)
{
	counttotal++;
	if (counttotal <= 10)
	{
		total_input->insert(o->label(), 0);
	}
}

//数字键盘del按键
void total_input_del_cb(Fl_Button *, void *)
{
	total_input->value("");
	counttotal = 0;
}
//数字键盘确认按键
void total_confirm_cb(Fl_Button *, void *)
{
	unsigned short port;
	static char buf[10];
	if (total_set_flag == 0)
	{
		FILE *fp;
		// power_p.txt power_aux.txt power_r.txt power_dc.txt power_tc.txt \
		compressor_tc1.txt 2.txt分别存储牵引能耗，辅助能耗，再生能耗，DC/DC能耗，C1车压缩机工作时间，C2车压缩机工作时间
		if (totalno == 1)
			fp = fopen("power_p.txt", "rw+");
		else if (totalno == 2)
			fp = fopen("power_aux.txt", "rw+");
		else if (totalno == 3)
			fp = fopen("power_r.txt", "rw+");
		else if (totalno == 6)
			fp = fopen("power_dc.txt", "rw+");
		else if (totalno == 4)
			fp = fopen("compressor_tc1.txt", "rw+");
		else if (totalno == 5)
			fp = fopen("compressor_tc2.txt", "rw+");

		for (int n = 0; n < 10; n++)
			buf[n] = '\0';
		sprintf(buf, "%s", total_input->value());

		//发送数据
		if (tc_no == 1)
		{
			port = 0x1b3;
			fseek(fp, 0, SEEK_SET);
			fwrite(buf, 1, 10, fp);
			mvb.put_uint(port, (totalno - 1) * 4, atoi(total_input->value()));
			mvb.put_ubit(port, 31, totalno - 1, 1);
			mvb.lp_put_alldata();
			total_set_flag = 1;
		}
		else
		{
			port = 0x6b3;
			fseek(fp, 0, SEEK_SET);
			fwrite(buf, 1, 10, fp);
			mvb.put_uint(port, (totalno - 1) * 4, atoi(total_input->value()));
			mvb.put_ubit(port, 31, totalno - 1, 1);
			mvb.lp_put_alldata();
			total_set_flag = 1;
		}
		fclose(fp);
		counttotal = 0;
		total_input->value("");
	}
}
//数字键盘取消按键
void total_cancel_cb(Fl_Button *, void *)
{
	Group_Total_Set->hide(); //数字键盘隐藏
	//清零
	counttotal = 0;
	total_input->value("");
	//六个设置按键都释放
	for (int i = 1; i <= 6; i++)
	{
		total_select_butt[i]->value(0);
	}
}
