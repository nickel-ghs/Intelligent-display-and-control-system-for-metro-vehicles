#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <i2cfun.h>
#include <FL/Fl_Group.H>
#include <FL/Fl.H>

Fl_Button *CarID_temp;			//接收当前窗口的对象
static int CarID_data[7] = {0}; //接收用户输入
static int CarID_no = 1;		//车号窗口，一共有6个
static char count_CarID;		// count_CarID记录用户已输入数据的位数
static char CarID1_char[8] = "", CarID2_char[8] = "";
char CarID_set_flag = 0; //标志位，信号量；==0：可以操作；==1：不可以操作
//六个车号窗口的回调函数；根据用户的点击将处理函数的焦点集中到当前窗口
void CarID_sel_cb(Fl_Button *, long i)
{
	CarID_no = i;				  //用户点击的是哪一个窗口
	CarID_temp = CarID[CarID_no]; //返回当前窗口的对象
	CarID_temp->take_focus();	  //将处理函数的焦点集中到当前窗口
	CarID_temp->label("");		  //用户点击的窗口内部数据清零
	count_CarID = 0;			  //用户输入数据的位数设置为开始，即0
	CarID1_char[0] = '\0';		  //用户输入清0
}
//十个数字按键的回调函数
void CarID_input_cb(Fl_Button *o, void *)
{
	count_CarID++;		  // count_CarID记录用户已输入数据的位数
	if (count_CarID <= 6) //输入数据最高6位
	{
		//在CarID1_char后面加上一个数据atoi(o->label()) + 48，按键数值+'0'；
		CarID2_char[0] = atoi(o->label()) + 48; // 48-->'0';格式转换int-->char
		CarID2_char[1] = '\0';
		strcat(CarID1_char, CarID2_char);
		//将用户按键输入数据放到窗口中
		CarID_temp->copy_label(CarID1_char); // CarID_temp的label换成CarID1_char
		CarID_temp->redraw();
		CarID_data[CarID_no] = (CarID1_char[0] - 48) * 100000 + (CarID1_char[1] - 48) * 10000 + (CarID1_char[2] - 48) * 1000 + (CarID1_char[3] - 48) * 100 + (CarID1_char[4] - 48) * 10 + (CarID1_char[5] - 48);
	}
}
//数字键盘的del按钮的回调函数，删除当前窗口的已输入数据
void CarID_input_del_cb(Fl_Button *, void *)
{
	CarID_temp->label("");
	CarID1_char[0] = '\0';
	count_CarID = 0;
}
//确认按钮的回调函数
void CarID_confirm_cb(Fl_Button *, void *)
{
	unsigned short port;
	char CarID_buff[7][8]; //七行八列

	if (tc_no == 1)
		port = 0x1b2;
	else
		port = 0x6b2;

	if (CarID_set_flag == 0)
	{
		FILE *fp;
		fp = fopen("CarID.txt", "rw+");

		for (int i = 1; i <= 6; i++)
		{
			if (CarID_data[i] >= 0 && CarID_data[i] <= 999999) //确认数据格式时候正确
			{
				/*		CardID.txt:存放
						000:000000.
						NO1:200101.
						NO2:200102.
						NO3:200103.
						NO4:200104.
						NO5:200105.
						NO6:200106.
				*/
				sprintf(CarID_buff[i], "%d", CarID_data[i]);
				fseek(fp, i * 13 + 4, SEEK_SET); //重定位流上的文件指针为文件起始位置：去掉"NO1:"四位
				fwrite(CarID_buff[i], 1, 6, fp); //读取"200101"四位到CarID_buff[i]中，
				//数据组装并发送到port
				mvb.put_ushort(port, i * 4 + 2, CarID_data[i] / 65536);	  // i*4+2=6,10,14,18,22,26;65535:1111.1111.1111.1111;取16位以上数据
				mvb.put_ushort(port, (i + 1) * 4, CarID_data[i] % 65536); //(i + 1) * 4=8,12,16,20,24,28;取16位以下数据
				mvb.put_ubit(port, 1, i + 1, 1);						  // i+1=2,3,4,5,6,7;
				mvb.lp_put_alldata();
			}
		}
		CarID_set_flag = 1;
		fclose(fp);
	}
	count_CarID = 0;
}
//取消按钮的回调函数，直接全部清零
void CarID_cancel_cb(Fl_Button *, void *)
{
	CarID[1]->label("");
	CarID[2]->label("");
	CarID[3]->label("");
	CarID[4]->label("");
	CarID[5]->label("");
	CarID[6]->label("");
}

//维护界面切换至车号设置界面
void CarID_cb(Fl_Button *, void *)
{
	if (!group_diameter_window->visible())
	{
		group_CarID_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--车号设置");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_CarID_window;
		//切换至车号设置界面后自动默认操作第一个车号
		CarID_temp = CarID[1];
		CarID_temp->take_focus();
		CarID_temp->label("");
		//初始化
		count_CarID = 0;
		CarID1_char[0] = '\0';
	}
}

//车号设置界面切换至维护界面
void CarID_return_cb(Fl_Button *, void *)
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
