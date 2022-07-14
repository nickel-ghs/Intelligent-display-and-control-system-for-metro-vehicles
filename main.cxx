#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include "surface/train-ningbo.h"
#include "src/head.h"
#include <FL/Fl_PNG_Image.H>
#include <mvb.h>
#include <i2cfun.h>

void init_pit();
char vcm();
void run_timeout(void *);
void wrong_timeout(void *);
void init_time();
void Layout_Function(); //界面函数调用
void Array_Initial();	//主界面各设备数组名初始化

int tc_no;
char vcmflag;
short pit_num[200];			//端口号
char pit_size[200];			//端口大小
short pit_temp1, pit_temp2; //端口数据界面端口大小端处理临时变量
char old_brake24_flag, new_brake24_flag, old_brake26_flag, new_brake26_flag;

int main(int argc, char **argv)
{
	init_pit();
	InitBright();	   //初始化亮度
	StopLcdAutoRun(1); //停止lcd自动运行
	SetLcdBright(80);  //设置Lcd亮度为80
	mvb.init(0x60, 2);
	mvb.mvb_as_EMD(1);
	mvb.mvb_auto_switch();
	SetKeySort(2); // 0 监控 1 tpx20 2 tpx21
	SetTpxSort(2); // 0 IDD 1 tpx20 2 tpx21
	set_os_time(); //设置系统时间
	// fluid主体窗口显示
	make_window();
	body_window->show();
	image_deal_proccess(); //图标处理函数
	Door_Array_Initial();  //门设备数组名初始化函数
	Main_Door_Flag = 1;
	set_cab_proccess(); //断电后操作端按钮显示

	if (tc_no == 1)						   //显示器版本号
		mvb.put_ushort(0x1b0, 30, 0x0106); // V1.0.6   844模式
	else
		mvb.put_ushort(0x6b0, 30, 0x0106);
	mvb.lp_put_alldata();

	//显示该窗口并进入FLTK 事件循环固定格式
	Fl::add_timeout(0.3, run_timeout);	 //每0.3秒执行一次run_timeout
	Fl::add_timeout(0.5, wrong_timeout); //每0.5秒执行一次wrong_timeout
	return Fl::run();
}

void run_timeout(void *)
{
	static unsigned short iddlife;
	unsigned int port;
	vcmflag = vcm();
	// vcmflag=1;

	/*---------给网络发显示器的生命信号  start------------*/
	iddlife++; //记录run_timeout的运行次数

	if (tc_no == 1) //显示器版本号
	{
		mvb.put_ushort(0x1b0, 0, iddlife);
		mvb.lp_put_alldata();
	}
	else
	{
		mvb.put_ushort(0x6b0, 0, iddlife);
		mvb.lp_put_alldata();
	}
	init_time(); //取系统时间发送网络

	/*---------给网络发显示器的生命信号  end------------*/
	if (vcmflag)
	{
		Layout_Function();
		//人工模式时，未按警惕按钮超过2秒弹窗报警
		{
			if (mvb.get_ubit(0x39, 9, 1))
			{
				Alarm_Button_window->show();
				BuzzerOn();
				usleep(500000);
				BuzzerOff();
			}
			else
			{
				Alarm_Button_window->hide();
				BuzzerOff();
			}
		}
		//手动模式可操作逻辑
		/*{
			//有库用供电&有外部供风
		  if((mvb.get_ushort(0x01,12)==32)||(mvb.get_ushort(0x01,12)==64))
		  {
			  if(PIS_TMS_Button->value()==1)
			  {
				  Broadcast_Pre->activate();
			  Broadcast_Next->activate();
			  broadcast_in->activate();
			  broadcast_out->activate();
			  }
			  else
			  {
				  Broadcast_Pre->deactivate();
			  Broadcast_Next->deactivate();
			  broadcast_in->deactivate();
			  broadcast_out->deactivate();
			  }
		  }
		  else if((mvb.get_ushort(0x01,12)!=32)&&(mvb.get_ushort(0x01,12)!=64))
		  {
			  Broadcast_Pre->activate();
			Broadcast_Next->activate();
			broadcast_in->activate();
			broadcast_out->activate();
		  }
		}*/
	}
	else
	{
		if (!start_window->visible())
			start_window->show();
	}

	//制动系统24或26小时未自检
	// M1车6号门 EDCU的内部安全继电器失效
	new_brake24_flag = mvb.get_ubit(0x16, 10, 6);
	if (old_brake24_flag == 0 && new_brake24_flag == 1) //上升沿
	{
		brake24_window->show();
	}
	old_brake24_flag = new_brake24_flag;
	//安全互锁回路异常故障
	new_brake26_flag = mvb.get_ubit(0x16, 10, 7);
	if (old_brake26_flag == 0 && new_brake26_flag == 1)
	{
		brake26_window->show();
	}
	old_brake26_flag = new_brake26_flag;

	Fl::repeat_timeout(0.3, run_timeout);
}

//界面处理函数，将界面打开与函数process类函数关联
void Layout_Function()
{
	unsigned short port_start;
	if (start_window->visible())
		start_window->hide();
	if (group_main_window->visible())
	{
		Main_Proccess();
		wrong_prompt(); //中等和严重故障发生运行界面报警
	}
	if (group_net_window->visible())
		net_proccess();
	if (group_ioA_window->visible())
		ioA_proccess();
	if (group_ioB_window->visible())
		ioB_proccess();
	if (group_ioC_window->visible())
		ioC_proccess();
	if (group_top->visible())
		Basedata_Proccess();
	if (group_aircondition_all_window->visible())
		Airc_Set_Proccess();
	if (group_brakecheck_window->visible())
		BrakeCheck_proccess();
	else
	{
		port_start = tc_no > 1 ? 0x6b0 : 0x1b0;
		mvb.put_ubit(port_start, 12, 7, 0);
		mvb.lp_put_alldata();
		BrakeCheck_Start_Butt->value(0);
	}
	if (group_transport_window->visible())
		transport_proccess();
	if (group_portdata_window->visible())
		portdata_proccess();
	if (group_version_window->visible())
	{
		ver_process();
	}
	if (group_total_window->visible())
	{
		total_proccess();
	}
	if (group_line_window->visible())
	{
		line_proccess();
	}
	if (group_station_set_window->visible())
	{
		station_set_proccess();
	}
	if (group_dcu_window->visible())
	{
		DCU_Proccess();
	}
	if (group_dcum_window->visible())
	{
		DCUm_Proccess();
	}
	if (group_siv_window->visible())
	{
		SIV_Proccess();
	}
	if (group_diameter_window->visible())
	{
		diameter_proccess();
	}
	if (group_acceleration_window->visible())
	{
		acceleration_proccess();
	}
	if (group_wrong_window->visible())
	{
		wrong_show_cur();
	}
	if (group_event_window->visible())
	{
		event_show_cur();
	}
	if (group_passby_window->visible())
	{
		Passby_Proccess();
	}
}

void wrong_timeout(void *)
{
	init_time();	  //取系统时间发送网络
	sleep_proccess(); //进程休眠
	hmi_synchro();	  //时间同步
	get_wrong();
	bright_auto_process(); //自动背光调节

	/************显示屏背光和钥匙绑定********************/

	FILE *fp;
	char Buff_Set_Cab[5];
	fp = fopen("Set_Cab.txt", "r+");
	fseek(fp, 0, SEEK_SET);
	fread(Buff_Set_Cab, 1, 1, fp);
	Set_Cab_Flag = atoi(Buff_Set_Cab);
	fclose(fp);
	if (Set_Cab_Flag == 1)
	{
		if ((tc_no == 1 && mvb.get_ubit(0x01, 26, 0)) || (tc_no == 2 && mvb.get_ubit(0x01, 26, 1)))
		{
			LcdBrightOn(); // Lcd亮起
		}
		else
		{
			LcdBrightOff();
		}
	}

	/************显示屏背光和钥匙绑定  End********************************/

	Fl::repeat_timeout(0.5, wrong_timeout); //重复运行回调函数,每隔0.5s
}
//取系统时间发送网络
void init_time()
{
	time_t t;
	struct tm *p;
	time(&t);

	unsigned short port;
	if (tc_no == 1)
		port = 0x1b1;
	else
		port = 0x6b1;
	p = localtime(&t);

	//通信协议，将p->tm_year - 100放到port的第6个字节中
	mvb.put_uchar(port, 6, p->tm_year - 100);
	mvb.put_uchar(port, 7, p->tm_mon + 1);
	mvb.put_uchar(port, 8, p->tm_mday);
	mvb.put_uchar(port, 9, p->tm_hour);
	mvb.put_uchar(port, 10, p->tm_min);
	mvb.put_uchar(port, 11, p->tm_sec);

	mvb.lp_put_alldata(); //所有数据都发送
}
//网络核心控制单元
char vcm()
{
	static unsigned short oldvcmlife, vcmcount, countflag = 0;
	unsigned short vcmlife;
	unsigned short port;
	port = 0xf0;
	vcmlife = mvb.get_ushort(port, 0);
	if (vcmlife ^ oldvcmlife)
	{
		countflag = 1;
		vcmcount = 0;
		oldvcmlife = vcmlife;
		return 1;
	}
	else
	{
		oldvcmlife = vcmlife;
		vcmcount++;
		if (vcmcount < 10)
		{
			if (countflag)
				return 1;
			else
				return 0;
		}
		else
		{
			countflag = 0;
			return 0;
		}
	}
}
//数据解析
void init_pit()
{
	FILE *fp;
	char buf_no[5], buff_command[20], bufpit1[30], bufpit2[30];

	//读写模式打开train.txt,读取tc_no第几车
	fp = fopen("train.txt", "r+");
	fseek(fp, 0, SEEK_SET); //重定位流上的文件指针为文件起始位置
	//读取一个字节并输出
	fread(buf_no, 1, 1, fp);
	tc_no = atoi(buf_no);
	printf("tc_no=%d\n", tc_no);
	fclose(fp);

	//命令行上输出cp pit_b pit -f
	// pit_b为原始文件，不做修改，作为原始数据保存（数据无意义）；pit_b为操作数据，每次程序运行从pit复制
	sprintf(buff_command, "%s", "cp pit_b pit -f"); // buff_command="cp pit_b pit -f"
	system(buff_command);

	//根据train.txt中的内容选择向pit写入
	fp = fopen("pit", "a+");
	//第一位表明是第几组;第二位tc_no == 1时为0x01,tc_no != 1时为0x06;第三位固定为0x02；\
			第四位分别为0xc4,0xc8,0xcc,0xd0,0xd4;每五、六位结束为0x00,0x04;
	if (tc_no == 1)
	{
		bufpit1[0] = 0xb0;
		bufpit1[1] = 0x01;
		bufpit1[2] = 0x02;
		bufpit1[3] = 0xc4;
		bufpit1[4] = 0x00;
		bufpit1[5] = 0x04;

		bufpit1[6] = 0xb1;
		bufpit1[7] = 0x01;
		bufpit1[8] = 0x02;
		bufpit1[9] = 0xc8;
		bufpit1[10] = 0x00;
		bufpit1[11] = 0x04;

		bufpit1[12] = 0xb2;
		bufpit1[13] = 0x01;
		bufpit1[14] = 0x02;
		bufpit1[15] = 0xcc;
		bufpit1[16] = 0x00;
		bufpit1[17] = 0x04;

		bufpit1[18] = 0xb3;
		bufpit1[19] = 0x01;
		bufpit1[20] = 0x02;
		bufpit1[21] = 0xd0;
		bufpit1[22] = 0x00;
		bufpit1[23] = 0x04;

		bufpit1[24] = 0xb4;
		bufpit1[25] = 0x01;
		bufpit1[26] = 0x02;
		bufpit1[27] = 0xd4;
		bufpit1[28] = 0x00;
		bufpit1[29] = 0x04;
		fwrite(bufpit1, 1, 30, fp); //将bufpit1写入pit
	}
	else
	{
		bufpit2[0] = 0xb0;
		bufpit2[1] = 0x06;
		bufpit2[2] = 0x02;
		bufpit2[3] = 0xc4;
		bufpit2[4] = 0x00;
		bufpit2[5] = 0x04;

		bufpit2[6] = 0xb1;
		bufpit2[7] = 0x06;
		bufpit2[8] = 0x02;
		bufpit2[9] = 0xc8;
		bufpit2[10] = 0x00;
		bufpit2[11] = 0x04;

		bufpit2[12] = 0xb2;
		bufpit2[13] = 0x06;
		bufpit2[14] = 0x02;
		bufpit2[15] = 0xcc;
		bufpit2[16] = 0x00;
		bufpit2[17] = 0x04;

		bufpit2[18] = 0xb3;
		bufpit2[19] = 0x06;
		bufpit2[20] = 0x02;
		bufpit2[21] = 0xd0;
		bufpit2[22] = 0x00;
		bufpit2[23] = 0x04;

		bufpit2[24] = 0xb4;
		bufpit2[25] = 0x06;
		bufpit2[26] = 0x02;
		bufpit2[27] = 0xd4;
		bufpit2[28] = 0x00;
		bufpit2[29] = 0x04;
		fwrite(bufpit2, 1, 30, fp);
	}
	fclose(fp);

	// pit_b每六个字节为一组，short pit_num[i]两个字节保存六字节中的2位，1位；char pit_size[i]一个字节保存六字节6位
	// pit_num和pit_size都仅仅在portdata.cxx中使用
	fp = fopen("pit_b", "r+");
	for (int i = 0; i < 200; i++)
	{
		fseek(fp, i * 6, SEEK_SET); //重定位流上的文件指针为文件起始位置+i*6
		fread(&pit_temp1, sizeof(short), 1, fp);

		//字节序调换，由小端转换成大端字节序
		// pit_temp1为短整形，为2字节，
		pit_temp2 = pit_temp1;
		pit_temp1 <<= 8;
		pit_temp2 >>= 8;
		pit_num[i] = (pit_temp1 & 0xff00) | (pit_temp2 & 0x00ff);

		fseek(fp, i * 6 + 5, SEEK_SET); //重定位流上的文件指针为文件起始位置+i*6+5
		fread(&pit_size[i], sizeof(char), 1, fp);
	}
	fclose(fp);
}
