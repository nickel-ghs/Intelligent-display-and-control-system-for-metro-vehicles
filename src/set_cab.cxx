/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-24 16:27:44
 * @LastEditors: ubuntu
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/set_cab.cxx
 */
#include "head.h"
char Set_Cab_Flag = 0;

void write_cab();
void set_cab_proccess();

//"设置为1端"按钮
void set_frst_cab_cb(Fl_Button *, void *)
{
	FILE *fp;
	char Buff_Set_Cab_W[5];

	tc_no = 1;
	write_cab();
	init_pit();		   //
	mvb.init(0x60, 2); // mvb初始化

	sec_cab_bt->deactivate(); //"设置为2端"按钮取消使能

	// Set_Cab.txt当"设置为2端"或"设置为1端"按钮锁定时为1,否则为0;
	Buff_Set_Cab_W[0] = 49;
	fp = fopen("Set_Cab.txt", "r+");
	fseek(fp, 0, SEEK_SET);
	fwrite(Buff_Set_Cab_W, 1, 1, fp);
	fclose(fp);
}

//"设置为2端"按钮
void set_sec_cab_cb(Fl_Button *, void *)
{
	FILE *fp;
	char Buff_Set_Cab_W[5];

	tc_no = 2;
	write_cab();
	init_pit();
	mvb.init(0x60, 2);
	first_cab_bt->deactivate();

	// Set_Cab.txt当"设置为2端"或"设置为1端"按钮锁定时为1,否则为0;
	Buff_Set_Cab_W[0] = 49;
	fp = fopen("Set_Cab.txt", "r+");
	fseek(fp, 0, SEEK_SET);
	fwrite(Buff_Set_Cab_W, 1, 1, fp);
	fclose(fp);
}

//取消按钮
void operation_cancel_cb(Fl_Button *, void *)
{
	FILE *fp;
	char Buff_Set_Cab_W[5];

	first_cab_bt->value(0);
	sec_cab_bt->value(0);
	first_cab_bt->activate();
	sec_cab_bt->activate();

	// Set_Cab.txt当"设置为2端"或"设置为1端"按钮锁定时为1,否则为0;
	Buff_Set_Cab_W[0] = 48;
	fp = fopen("Set_Cab.txt", "r+");
	fseek(fp, 0, SEEK_SET);
	fwrite(Buff_Set_Cab_W, 1, 1, fp);
	fclose(fp);
}
//向train.txt写入tc_no
void write_cab()
{
	FILE *fp;
	char Cab_Buff[5] = {0};
	fp = fopen("train.txt", "w+");
	if (fp == NULL)
	{
		return;
	}

	fseek(fp, 0, SEEK_SET);
	sprintf(Cab_Buff, "%d", tc_no);
	fwrite(Cab_Buff, 1, 1, fp);
	fclose(fp);
}

void set_cab_proccess()
{
	/*if(tc_no==1)
	{
		first_cab_bt->value(1);
		sec_cab_bt->value(0);
	}
	else
	{
		first_cab_bt->value(0);
		sec_cab_bt->value(1);
	}
	first_cab_bt->redraw();
	sec_cab_bt->redraw();*/
}
