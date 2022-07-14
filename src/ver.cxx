#include "head.h"

static unsigned char page = 0;
//不同界面的处理函数，一共4个界面
void ver1_process();
void ver2_process();
void ver3_process();
void ver4_process();

//管理界面version软件界面的目录
const char ver_name1[][30] = {{"VCMe硬件版本"},
							  {"VCMe固件版本"},
							  {"VCMe软件版本"},
							  {"EDRM底层版本"},
							  {"EDRM逻辑版本"},
							  {"EDRM配置版本"},
							  {"AXM_FPGA版本号"},
							  {"DXM1版本号"},
							  {"DXM2版本号"},
							  {"DIM版本号"},
							  {"HMI版本号"},
							  {"逻辑软件版本号"},
							  {"逆变软件版本号"},
							  {"粘着软件版本号"},
							  {"通信软件版本号"},
							  {"SIV_DSP软件版本号"},
							  {"SIV_PPC软件版本号"},
							  {"BCU软件版本号"},
							  {"ATC软件版本"},
							  {"空调软件版本"},
							  {"ACSU_PROG软件版本"},
							  {"ACSU_DATA软件版本"},
							  {"1号门软件版本号"},
							  {"2号门软件版本号"},
							  {"3号门软件版本号"},
							  {"4号门软件版本号"},
							  {"5号门软件版本号"},
							  {"6号门软件版本号"},
							  {"7号门软件版本号"},
							  {"8号门软件版本号"},
							  {"AXM_CPU版本号"},
							  {""},
							  {""},
							  {""},
							  {""},
							  {""},
							  {""},
							  {""},
							  {""},
							  {""}};
//不同界面的处理函数，一共4个界面
void ver_process()
{
	if (page == 0)
	{
		ver1_process();
	}
	else if (page == 1)
	{
		ver2_process();
	}
	else if (page == 2)
	{
		ver3_process();
	}
	else if (page == 3)
	{
		ver4_process();
	}
	else
		;
}
//按钮下一页的处理函数
void version_next_cb(Fl_Button *, void *)
{
	unsigned short i, k;
	if (page == 3) //如果已经是最后一页，跳转到第一页
	{
		page = 0;
	}
	else
	{
		page++;
	}
	k = page * 10;			 //每一页有十行数据
	for (i = 0; i < 10; i++) //画出每一行的数据
	{
		//管理界面version软件界面的目录改变成下一页的
		vr_name[i]->copy_label(ver_name1[i + k]);
		vr_name[i]->redraw();
	}
}
/*vr_d[]的分布
 *0   1   2   3   4   5
 *6   7   8   9  10  11
 *12  13  14  15  16  17
 *18  19  20  21  22  23
 *24  25  26  27  28  29

 *30  31  32  33  34  35
 *36  37  38  39  40  41
 *42  43  44  45  46  47
 *48  49  50  51  52  53
 *54  55  56  57  58  59
 */

void ver1_process()
{
	unsigned short i, j, k, k1, t, t1, u;
	unsigned char dt[4];
	char buff[10];
	// VCMe 硬件版本，固件版本，软件版本；第一页前三行
	for (i = 0; i < 3; i++) //循环三次，每次一行
	{
		k = 6 * i;
		t = 2 * i;
		//将第一到第三行的第一列和最后一列设置为buff
		for (j = 0; j < 2; j++)
		{
			k1 = k + 5 * j;				  // k1=0,5;  6,11;  12,17;
			t1 = t + 6 * j;				  // t1=0,6;  2,8;  4,10;
			u = mvb.get_ushort(0x30, t1); //将0x30端口的第t1个字节位置的一个short(两个字节)取出来

			dt[0] = u & 0x0f;		 //取第二个字节的低4位，前面+0000
			dt[1] = (u >> 4) & 0x0f; //取第二个字节的高4位，前面+0000
			dt[2] = (u >> 8) & 0xff; //取第一个字节
			sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
			vr_d[k1]->copy_label(buff); //将第一到第三行的第一列和最后一列设置为buff
			vr_d[k1]->redraw();
		}
		//将第一到第三行的第二，三，四，五列设置为----
		for (j = 0; j < 4; j++)
		{
			// k=0,6,12;k+j+1=1,2,3,4;  7,8,9,10;  13,14,15,16;
			vr_d[k + j + 1]->copy_label("-----");
			vr_d[k + j + 1]->redraw();
		}
	}
	// EDRM底层版本，逻辑版本，配置版本；第一页四五六行
	for (i = 0; i < 3; i++)
	{
		k = 6 * i + 18; //显示下标
		t = 4 * i + 6;	//协议位置
		for (j = 0; j < 2; j++)
		{
			k1 = k + 5 * j;
			t1 = t + 12 * j;
			dt[2] = mvb.get_uchar(0x35, t1);
			dt[1] = mvb.get_uchar(0x35, t1 + 1);
			dt[0] = mvb.get_uchar(0x35, t1 + 2);
			sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
			vr_d[k1]->copy_label(buff);
			vr_d[k1]->redraw();
		}
		for (j = 0; j < 4; j++)
		{
			vr_d[k + j + 1]->copy_label("-----");
			vr_d[k + j + 1]->redraw();
		}
	}
	// AXM_FPGA版本号；第七行

	k = 36; //显示下标
	t = 24; //协议位置
	for (j = 0; j < 2; j++)
	{
		k1 = k + 5 * j;
		t1 = t + 2 * j;
		u = mvb.get_uchar(0x30, t1);
		dt[0] = u & 0x07;
		dt[1] = (u >> 3) & 0x07;
		dt[2] = (u >> 6) & 0x03;
		sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
		vr_d[k1]->copy_label(buff);
		vr_d[k1]->redraw();
	}
	for (i = 0; i < 4; i++)
	{
		vr_d[k + 1 + i]->copy_label("----");
		vr_d[k + 1 + i]->redraw();
	}
	// DXM
	for (i = 0; i < 2; i++)
	{
		k = 6 * i + 42; //显示下标
		t = 2 * i;		//协议位置
		for (j = 0; j < 6; j++)
		{
			k1 = k + j;
			t1 = t + 4 * j;
			u = mvb.get_ushort(0x31, t1);
			dt[0] = u & 0x0f;
			dt[1] = (u >> 4) & 0x0f;
			dt[2] = (u >> 8) & 0xff;
			sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
			vr_d[k1]->copy_label(buff);
			vr_d[k1]->redraw();
		}
	}
	// DIM版本号，第八九十行

	k = 54; //显示下标
	t = 24; //协议位置
	for (j = 0; j < 2; j++)
	{
		k1 = k + 5 * j;
		t1 = t + 2 * j;
		u = mvb.get_ushort(0x31, t1);
		dt[0] = u & 0x0f;
		dt[1] = (u >> 4) & 0x0f;
		dt[2] = (u >> 8) & 0xff;
		sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
		vr_d[k1]->copy_label(buff);
		vr_d[k1]->redraw();
	}
	for (i = 0; i < 4; i++)
	{
		vr_d[k + 1 + i]->copy_label("----");
		vr_d[k + 1 + i]->redraw();
	}
}

void ver2_process()
{
	unsigned short i, j, k, k1, t, t1, u;
	unsigned char dt[4];
	char buff[10];
	// HMI版本号

	k = 0;	//显示下标
	t = 28; //协议位置
	for (j = 0; j < 2; j++)
	{
		k1 = k + 5 * j;
		t1 = t + 2 * j;
		u = mvb.get_ushort(0x31, t1);
		dt[0] = u & 0x0f;
		dt[1] = (u >> 4) & 0x0f;
		dt[2] = (u >> 8) & 0xff;
		sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
		vr_d[k1]->copy_label(buff);
		vr_d[k1]->redraw();
	}
	for (i = 0; i < 4; i++)
	{
		vr_d[k + 1 + i]->copy_label("----");
		vr_d[k + 1 + i]->redraw();
	}
	// 逻辑软件版本，逆变软件版本，粘着软件版本
	for (i = 0; i < 4; i++)
	{
		k = 6 * i + 7; //显示下标
		t = 2 * i;	   //协议位置
		for (j = 0; j < 4; j++)
		{
			k1 = k + j;
			t1 = t + 8 * j;
			u = mvb.get_ushort(0x32, t1);
			dt[0] = u & 0x0f;
			dt[1] = (u >> 4) & 0x0f;
			dt[2] = (u >> 8) & 0xff;
			sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
			vr_d[k1]->copy_label(buff);
			vr_d[k1]->redraw();
		}
		k = 6 * i + 6;
		for (j = 0; j < 2; j++)
		{
			vr_d[k + 5 * j]->copy_label("-----");
			vr_d[k + 5 * j]->redraw();
		}
	}
	// SIV_DSP  SIV_PPC
	for (i = 0; i < 2; i++)
	{
		k = 6 * i + 30; //显示下标
		t = 2 * i;		//协议位置
		for (j = 0; j < 2; j++)
		{
			k1 = k + 5 * j;
			t1 = t + 4 * j;
			u = mvb.get_ushort(0x33, t1);
			dt[0] = u & 0x0f;
			dt[1] = (u >> 4) & 0x0f;
			dt[2] = (u >> 8) & 0xff;
			sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
			vr_d[k1]->copy_label(buff);
			vr_d[k1]->redraw();
		}
		for (j = 0; j < 4; j++)
		{
			vr_d[k + 1 + i]->copy_label("----");
			vr_d[k + 1 + i]->redraw();
		}
	}
	// BCU
	k = 42;
	for (i = 0; i < 4; i++)
	{
		if (i % 2 == 0)
		{
			j = i + 1;
		}
		else
		{
			j = i - 1;
		}
		u = mvb.get_uchar(0x33, 16 + j);

		dt[0] = u & 0x0f;
		dt[1] = (u >> 4) & 0x0f;
		sprintf(buff, "V%d.%d", dt[1], dt[0]);
		if (i == 0)
		{
			vr_d[k + 0]->copy_label(buff);
			vr_d[k + 0]->redraw();
		}
		else if (i == 1)
		{
			vr_d[k + 2]->copy_label(buff);
			vr_d[k + 2]->redraw();
		}
		else if (i == 2)
		{
			vr_d[k + 5]->copy_label(buff);
			vr_d[k + 5]->redraw();
		}
		else if (i == 3)
		{
			vr_d[k + 3]->copy_label(buff);
			vr_d[k + 3]->redraw();
		}
	}
	vr_d[k + 1]->copy_label("----");
	vr_d[k + 4]->copy_label("----");
	vr_d[k + 1]->redraw();
	vr_d[k + 4]->redraw();
	// ATC
	k = 48; //显示下标
	t = 25; //协议位置
	for (j = 0; j < 2; j++)
	{
		k1 = k + 5 * j;
		t1 = t + 4 * j;
		dt[2] = mvb.get_uchar(0x33, t1);
		dt[1] = mvb.get_uchar(0x33, t1 + 1);
		dt[0] = mvb.get_uchar(0x33, t1 + 2);
		sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
		vr_d[k1]->copy_label(buff);
		vr_d[k1]->redraw();
	}
	for (i = 0; i < 4; i++)
	{
		vr_d[k + 1 + i]->copy_label("----");
		vr_d[k + 1 + i]->redraw();
	}
	//空调
	k = 54;
	t = 0;
	for (i = 0; i < 6; i++)
	{
		k1 = k + i;
		t1 = t + 2 * i;
		u = mvb.get_ushort(0x34, t1);
		dt[0] = u & 0x0f;
		dt[1] = (u >> 4) & 0x0f;
		dt[2] = (u >> 8) & 0xff;
		sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
		vr_d[k1]->copy_label(buff);
		vr_d[k1]->redraw();
	}
}
void ver3_process()
{
	unsigned short i, j, k, k1, t, t1, u, i1;
	unsigned char dt[4];
	unsigned short port;
	char buff[10];
	// 1车ACSU_PROG+DATA
	k = 0;	//显示下标
	t = 28; //协议位置
	for (j = 0; j < 2; j++)
	{
		k1 = k + 6 * j;
		t1 = t + 2 * j;
		u = mvb.get_ushort(0x34, t1);
		dt[0] = u & 0xff;
		dt[1] = (u >> 8) & 0xff;
		sprintf(buff, "V%d.%d", dt[1], dt[0]);
		vr_d[k1]->copy_label(buff);
		vr_d[k1]->redraw();
	}
	for (i = 0; i < 4; i++)
	{
		vr_d[k + 1 + i]->copy_label("----");
		vr_d[k + 1 + i]->redraw();
	}
	// 6车ACSU_PROG+DATA
	k = 5; //显示下标
	t = 0; //协议位置
	for (j = 0; j < 2; j++)
	{
		k1 = k + 6 * j;
		t1 = t + 2 * j;
		u = mvb.get_ushort(0x35, t1);
		dt[0] = u & 0xff;
		dt[1] = (u >> 8) & 0xff;
		sprintf(buff, "V%d.%d", dt[1], dt[0]);
		vr_d[k1]->copy_label(buff);
		vr_d[k1]->redraw();
	}
	for (i = 0; i < 4; i++)
	{
		vr_d[7 + i]->copy_label("----");
		vr_d[7 + i]->redraw();
	}
	// door
	port = 0x36;
	for (i1 = 0; i1 < 3; i1++)
	{
		for (i = 0; i < 2; i++)
		{
			t = 16 * i; //协议位置
			k = 12 + 2 * i1 + i;
			for (j = 0; j < 8; j++)
			{
				k1 = k + 6 * j;
				t1 = t + 2 * j;
				u = mvb.get_ushort(port, t1);
				dt[0] = u & 0xff;
				dt[1] = (u >> 8) & 0xff;
				sprintf(buff, "V%d.%d", dt[1], dt[0]);
				vr_d[k1]->copy_label(buff);
				vr_d[k1]->redraw();
			}
		}
		port++;
	}
}

void ver4_process()
{
	unsigned short i, j, k, k1, t, t1, u;
	unsigned char dt[4];
	char buff[10];
	// AXM_CPU版本号

	k = 0;	//显示下标
	t = 25; //协议位置
	for (j = 0; j < 2; j++)
	{
		k1 = k + 5 * j;
		t1 = t + 2 * j;
		u = mvb.get_uchar(0x30, t1);
		dt[0] = u & 0x07;
		dt[1] = (u >> 3) & 0x07;
		dt[2] = (u >> 6) & 0x03;
		sprintf(buff, "V%d.%d.%d", dt[2], dt[1], dt[0]);
		vr_d[k1]->copy_label(buff);
		vr_d[k1]->redraw();
	}
	for (i = 0; i < 4; i++)
	{
		vr_d[k + 1 + i]->copy_label("----");
		vr_d[k + 1 + i]->redraw();
	}

	//多余的控件清掉
	for (i = 6; i < 60; i++)
	{
		vr_d[i]->label("");
		vr_d[i]->redraw();
	}
}

// version初始化，将第一页内容显示
void init_ver()
{
	unsigned short i;
	page = 0;
	for (i = 0; i < 10; i++)
	{
		vr_name[i]->copy_label(ver_name1[i]);
		vr_name[i]->redraw();
	}
}
