#include <stdio.h>
#include <stdlib.h>
#include "wrong.h"
#include "head.h"
#include <mvb.h>
#include "../surface/mofang.h"
#include <unistd.h>
#include <sys/stat.h>

#define wronginfo_offset 23
#define wronginfo_length 109
#define wronginfo_ReadLeng 72
#define grade_offset 5
#define prompt_offset 7

#define guide_length 82

unsigned char WrongStatus[WRONGBYTENO];	   //故障状态
unsigned char OldWrongStatus[WRONGBYTENO]; //前一次得到的故障状态
unsigned short ListNo = 0;				   //现存故障总数
char Page = 0;
struct WrongInfo wrongrecordinfo[1010];
struct WrongInfo wronginfo[MAXWRONGNO]; //存放当前的所有故障信息

static void search_wrong();						   //查询现有故障
static void analyse_wrong();					   //分析故障发生和消失
static void wrong_dispear(unsigned short wrongno); //故障消失处理函数
static void wrong_appear(unsigned short wrongno);  //新故障发生处理函数
static void record_wrong_s(WrongInfo *winfo);	   //将故障信息存到event.bin文本
static void record_wrong_e(WrongInfo *winfo);
char get_cnum();			 //求轻微故障个数
static void get_confirmno(); //求已确认的故障数目
void wrongrecord_init();
void wrongnum(); //计算界面故障的序号
void wrong_prompt();

struct stat statbuf;
static char wrongnobuf[10][20];	  //存放编号序列
static char wrong_value[10][100]; //显示每行的内容存放
static char wrong_time[10][50];	  //显示每行的时间存放
static char count = 0;			  //主界面确认提示计数器

char Confrm_flag = 0;

long row; //故障行数
int ShowingWrongP;

void get_wrong()
{
	search_wrong();
	analyse_wrong();
}

//得到所有的现存故障数据，存储在WrongStatus[]中
static void search_wrong() //从端口收集故障，存储到WrongStatus[]数组
{
	unsigned short port;
	if (vcmflag)
	{
		// DCU故障数据
		// D1车
		port = 0x30;
		//从port读取错误数据
		WrongStatus[0] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[1] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[2] = (mvb.get_uchar(port, 3)) & 0x7f;
		WrongStatus[3] = (mvb.get_uchar(port, 2)) & 0xff;
		WrongStatus[4] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[5] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[6] = (mvb.get_uchar(port, 7)) & 0x3f;
		WrongStatus[7] = (mvb.get_uchar(port, 6)) & 0xf0;
		WrongStatus[8] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[9] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[10] = (mvb.get_uchar(port, 11)) & 0xfe;
		WrongStatus[11] = (mvb.get_uchar(port, 10)) & 0xe7;
		// M车
		WrongStatus[12] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[13] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[14] = (mvb.get_uchar(port, 15)) & 0x7f;
		WrongStatus[15] = (mvb.get_uchar(port, 14)) & 0xff;
		WrongStatus[16] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[17] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[18] = (mvb.get_uchar(port, 19)) & 0x3f;
		WrongStatus[19] = (mvb.get_uchar(port, 18)) & 0xf0;
		WrongStatus[20] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[21] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[22] = (mvb.get_uchar(port, 23)) & 0xfe;
		WrongStatus[23] = (mvb.get_uchar(port, 22)) & 0xe7;
		// D2车
		WrongStatus[24] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[25] = (mvb.get_uchar(port, 24)) & 0xff;
		WrongStatus[26] = (mvb.get_uchar(port, 27)) & 0x7f;
		WrongStatus[27] = (mvb.get_uchar(port, 26)) & 0xff;
		WrongStatus[28] = (mvb.get_uchar(port, 29)) & 0xff;
		WrongStatus[29] = (mvb.get_uchar(port, 28)) & 0xff;
		WrongStatus[30] = (mvb.get_uchar(port, 31)) & 0x3f;
		WrongStatus[31] = (mvb.get_uchar(port, 30)) & 0xf0;
		port = 0x31;
		WrongStatus[32] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[33] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[34] = (mvb.get_uchar(port, 3)) & 0xfe;
		WrongStatus[35] = (mvb.get_uchar(port, 2)) & 0xe7;
		// SIV故障数据
		// D1车
		WrongStatus[36] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[37] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[38] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[39] = (mvb.get_uchar(port, 6)) & 0x7f;
		WrongStatus[40] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[41] = (mvb.get_uchar(port, 8)) & 0x07;
		WrongStatus[42] = (mvb.get_uchar(port, 11)) & 0xff;
		// M车
		WrongStatus[43] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[44] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[45] = (mvb.get_uchar(port, 15)) & 0xff;
		WrongStatus[46] = (mvb.get_uchar(port, 14)) & 0x7f;
		WrongStatus[47] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[48] = (mvb.get_uchar(port, 16)) & 0x07;
		WrongStatus[49] = (mvb.get_uchar(port, 19)) & 0xff;
		// D2车
		WrongStatus[50] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[51] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[52] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[53] = (mvb.get_uchar(port, 22)) & 0x7f;
		WrongStatus[54] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[55] = (mvb.get_uchar(port, 27)) & 0x07;
		WrongStatus[56] = (mvb.get_uchar(port, 26)) & 0xff;
		// EBCU故障数据
		port = 0x32;
		// D1车
		WrongStatus[57] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[58] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[59] = (mvb.get_uchar(port, 3)) & 0xff;
		WrongStatus[60] = (mvb.get_uchar(port, 2)) & 0xff;
		WrongStatus[61] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[62] = (mvb.get_uchar(port, 4)) & 0xfd;
		WrongStatus[63] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[64] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[65] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[66] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[67] = (mvb.get_uchar(port, 11)) & 0xfd;
		WrongStatus[68] = (mvb.get_uchar(port, 10)) & 0xff;
		WrongStatus[69] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[70] = (mvb.get_uchar(port, 12)) & 0x0f;
		// M车
		WrongStatus[71] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[72] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[73] = (mvb.get_uchar(port, 19)) & 0xff;
		WrongStatus[74] = (mvb.get_uchar(port, 18)) & 0xff;
		WrongStatus[75] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[76] = (mvb.get_uchar(port, 20)) & 0xfd;
		WrongStatus[77] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[78] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[79] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[80] = (mvb.get_uchar(port, 24)) & 0xff;
		WrongStatus[81] = (mvb.get_uchar(port, 27)) & 0xfd;
		WrongStatus[82] = (mvb.get_uchar(port, 26)) & 0xff;
		WrongStatus[83] = (mvb.get_uchar(port, 29)) & 0xff;
		WrongStatus[84] = (mvb.get_uchar(port, 28)) & 0x0f;
		// D2车
		port = 0x33;
		WrongStatus[85] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[86] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[87] = (mvb.get_uchar(port, 3)) & 0xff;
		WrongStatus[88] = (mvb.get_uchar(port, 2)) & 0xff;
		WrongStatus[89] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[90] = (mvb.get_uchar(port, 4)) & 0xfd;
		WrongStatus[91] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[92] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[93] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[94] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[95] = (mvb.get_uchar(port, 11)) & 0xfd;
		WrongStatus[96] = (mvb.get_uchar(port, 10)) & 0xff;
		WrongStatus[97] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[98] = (mvb.get_uchar(port, 12)) & 0x0f;
		//门故障数据
		// D1车
		port = 0x34;
		WrongStatus[99] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[100] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[101] = (mvb.get_uchar(port, 3)) & 0xff;
		WrongStatus[102] = (mvb.get_uchar(port, 2)) & 0xff;
		WrongStatus[103] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[104] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[105] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[106] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[107] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[108] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[109] = (mvb.get_uchar(port, 11)) & 0xff;
		WrongStatus[110] = (mvb.get_uchar(port, 10)) & 0xff;
		WrongStatus[111] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[112] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[113] = (mvb.get_uchar(port, 15)) & 0xff;
		WrongStatus[114] = (mvb.get_uchar(port, 14)) & 0xff;
		WrongStatus[115] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[116] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[117] = (mvb.get_uchar(port, 19)) & 0xff;
		WrongStatus[118] = (mvb.get_uchar(port, 18)) & 0xff;
		WrongStatus[119] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[120] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[121] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[122] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[123] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[124] = (mvb.get_uchar(port, 24)) & 0x0f;
		WrongStatus[125] = (mvb.get_uchar(port, 27)) & 0xff;
		WrongStatus[126] = (mvb.get_uchar(port, 26)) & 0x0f;
		// M车
		port = 0x35;
		WrongStatus[127] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[128] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[129] = (mvb.get_uchar(port, 3)) & 0xff;
		WrongStatus[130] = (mvb.get_uchar(port, 2)) & 0xff;
		WrongStatus[131] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[132] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[133] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[134] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[135] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[136] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[137] = (mvb.get_uchar(port, 11)) & 0xff;
		WrongStatus[138] = (mvb.get_uchar(port, 10)) & 0xff;
		WrongStatus[139] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[140] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[141] = (mvb.get_uchar(port, 15)) & 0xff;
		WrongStatus[142] = (mvb.get_uchar(port, 14)) & 0xff;
		WrongStatus[143] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[144] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[145] = (mvb.get_uchar(port, 19)) & 0xff;
		WrongStatus[146] = (mvb.get_uchar(port, 18)) & 0xff;
		WrongStatus[147] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[148] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[149] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[150] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[151] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[152] = (mvb.get_uchar(port, 24)) & 0x0f;
		WrongStatus[153] = (mvb.get_uchar(port, 27)) & 0xff;
		WrongStatus[154] = (mvb.get_uchar(port, 26)) & 0x0f;
		// D2车
		port = 0x36;
		WrongStatus[155] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[156] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[157] = (mvb.get_uchar(port, 3)) & 0xff;
		WrongStatus[158] = (mvb.get_uchar(port, 2)) & 0xff;
		WrongStatus[159] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[160] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[161] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[162] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[163] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[164] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[165] = (mvb.get_uchar(port, 11)) & 0xff;
		WrongStatus[166] = (mvb.get_uchar(port, 10)) & 0xff;
		WrongStatus[167] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[168] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[169] = (mvb.get_uchar(port, 15)) & 0xff;
		WrongStatus[170] = (mvb.get_uchar(port, 14)) & 0xff;
		WrongStatus[171] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[172] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[173] = (mvb.get_uchar(port, 19)) & 0xff;
		WrongStatus[174] = (mvb.get_uchar(port, 18)) & 0xff;
		WrongStatus[175] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[176] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[177] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[178] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[179] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[180] = (mvb.get_uchar(port, 24)) & 0x0f;
		WrongStatus[181] = (mvb.get_uchar(port, 27)) & 0xff;
		WrongStatus[182] = (mvb.get_uchar(port, 26)) & 0x0f;
		//空调故障数据
		// D1车
		port = 0x39;
		WrongStatus[183] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[184] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[185] = (mvb.get_uchar(port, 3)) & 0xff;
		WrongStatus[186] = (mvb.get_uchar(port, 2)) & 0xff;
		WrongStatus[187] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[188] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[189] = (mvb.get_uchar(port, 7)) & 0x0f;
		WrongStatus[190] = (mvb.get_uchar(port, 6)) & 0x01;
		// M车
		WrongStatus[191] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[192] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[193] = (mvb.get_uchar(port, 11)) & 0xff;
		WrongStatus[194] = (mvb.get_uchar(port, 10)) & 0xff;
		WrongStatus[195] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[196] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[197] = (mvb.get_uchar(port, 15)) & 0x0f;
		WrongStatus[198] = (mvb.get_uchar(port, 14)) & 0x01;
		// D2车
		WrongStatus[199] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[200] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[201] = (mvb.get_uchar(port, 19)) & 0xff;
		WrongStatus[202] = (mvb.get_uchar(port, 18)) & 0xff;
		WrongStatus[203] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[204] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[205] = (mvb.get_uchar(port, 23)) & 0x0f;
		WrongStatus[206] = (mvb.get_uchar(port, 22)) & 0x01;
		// PIS故障数据
		port = 0x3c;
		WrongStatus[207] = (mvb.get_uchar(port, 1)) & 0x07;
		WrongStatus[208] = (mvb.get_uchar(port, 3)) & 0x1f;
		WrongStatus[209] = (mvb.get_uchar(port, 5)) & 0x03;
		WrongStatus[210] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[211] = (mvb.get_uchar(port, 6)) & 0x7f;
		WrongStatus[212] = (mvb.get_uchar(port, 11)) & 0x07;
		WrongStatus[213] = (mvb.get_uchar(port, 13)) & 0x03;
		WrongStatus[214] = (mvb.get_uchar(port, 15)) & 0xff;
		WrongStatus[215] = (mvb.get_uchar(port, 14)) & 0x3f;
		WrongStatus[216] = (mvb.get_uchar(port, 28)) & 0x00; //协议变更,CBTC严重和中等故障去掉
		WrongStatus[217] = (mvb.get_uchar(port, 30)) & 0x00;
		//设备通讯故障
		port = 0x3d;
		// D1车
		WrongStatus[218] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[219] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[220] = (mvb.get_uchar(port, 3)) & 0x01;
		// M车
		WrongStatus[221] = (mvb.get_uchar(port, 5)) & 0x94;
		WrongStatus[222] = (mvb.get_uchar(port, 4)) & 0xd9;
		// D2车
		WrongStatus[223] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[224] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[225] = (mvb.get_uchar(port, 9)) & 0x01;
		//网络判断故障
		WrongStatus[226] = (mvb.get_uchar(port, 11)) & 0x03;
		WrongStatus[227] = (mvb.get_uchar(port, 10)) & 0xfe;
		WrongStatus[228] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[229] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[230] = (mvb.get_uchar(port, 15)) & 0xff;
		WrongStatus[231] = (mvb.get_uchar(port, 14)) & 0xff;
		WrongStatus[232] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[233] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[234] = (mvb.get_uchar(port, 19)) & 0xff;
		WrongStatus[235] = (mvb.get_uchar(port, 18)) & 0xff;
		WrongStatus[236] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[237] = (mvb.get_uchar(port, 20)) & 0x03;
		// CBTC故障
		port = 0x3c;
		WrongStatus[238] = (mvb.get_uchar(port, 21)) & 0x7f;
		WrongStatus[239] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[240] = (mvb.get_uchar(port, 23)) & 0x01;
		WrongStatus[241] = (mvb.get_uchar(port, 22)) & 0x17;
	}
	else
	{
		for (int i = 0; i < WRONGBYTENO; i++)
			WrongStatus[i] = 0;
	}
}

static void analyse_wrong() //对WrongStatus[]数组数值进行判断，看是否有故障变化
{
	unsigned char com;
	char k = 1;
	unsigned short wrong_no;

	for (int i = 0; i < WRONGBYTENO; i++)
	{
		com = OldWrongStatus[i] ^ WrongStatus[i]; //旧的故障字节与当前值异或,结果不为0则表示有变化
		if (com)								  //有故障变化
		{
			for (int j = 0; j < 8; j++)
			{
				if (com & (k << j)) // com字节此位为1,此位有变化,异或不相同得为1
				{
					wrong_no = i * 8 + j + 1;			 //计算对应的故障代码
														 //如果旧的故障字节此位为1,则表示此故障消失
					if ((OldWrongStatus[i] >> j) & 0x01) //故障消失
					{
						wrong_dispear(wrong_no); //如果某一位数值从1变0，则证明有故障消失，如x故障消失了。wrong_dispear（x）
					}
					else //新故障出现
					{
						wrong_appear(wrong_no); //如果某一位数值从0变1，则证明有新的故障出现；如x故障出现//wrong_no
					}
				}
			}
		}
		OldWrongStatus[i] = WrongStatus[i];
	}
}

static void wrong_appear(unsigned short wrong_no) //获得故障发生时的时间及其他参数
{
	FILE *wrongfp;
	FILE *fp;
	int ret;
	char guide_buf[4][4];
	wrongfp = fopen("wrong.txt", "rt");

	fp = fopen("guide.txt", "r");
	if (fp == NULL)
	{
		return;
	}
	if (wrongfp == NULL)
	{
		printf("open wrong.txt error\n");
		return;
	}
	wronginfo[ListNo].WrongTime.tm_year = mvb.get_uchar(0xff, 1);
	wronginfo[ListNo].WrongTime.tm_mon = mvb.get_uchar(0xff, 0);
	wronginfo[ListNo].WrongTime.tm_mday = mvb.get_uchar(0xff, 3);
	wronginfo[ListNo].WrongTime.tm_hour = mvb.get_uchar(0xff, 2);
	wronginfo[ListNo].WrongTime.tm_min = mvb.get_uchar(0xff, 5);
	wronginfo[ListNo].WrongTime.tm_sec = mvb.get_uchar(0xff, 4);

	wronginfo[ListNo].WrongTimeEnd.tm_year = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_mon = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_mday = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_hour = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_min = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_sec = 0;
	/*故障内容*/
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + wronginfo_offset, SEEK_SET);
	ret = fread(wronginfo[ListNo].WrongValue, 1, wronginfo_ReadLeng, wrongfp);

	//故障级别
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + grade_offset, SEEK_SET);
	fread(&wronginfo[ListNo].WrongClass, 1, 1, wrongfp);

	//故障提示
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + 7, SEEK_SET);
	fread(guide_buf[0], 1, 3, wrongfp);

	if (atoi(guide_buf[0]))
	{
		fseek(fp, (atoi(guide_buf[0]) - 1) * guide_length + 4, SEEK_SET);
		fread(&wronginfo[ListNo].WrongPrompt[0], 1, 49, fp);
	}
	else
	{
		sprintf(wronginfo[ListNo].WrongPrompt[0], "%s", "");
	}

	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + 11, SEEK_SET);
	fread(guide_buf[1], 1, 3, wrongfp);

	if (atoi(guide_buf[1]))
	{
		fseek(fp, ((atoi(guide_buf[1])) - 1) * guide_length + 4, SEEK_SET);
		fread(&wronginfo[ListNo].WrongPrompt[1], 1, 49, fp);
	}
	else
	{
		sprintf(wronginfo[ListNo].WrongPrompt[1], "%s", "");
	}

	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + 15, SEEK_SET);
	fread(guide_buf[2], 1, 3, wrongfp);

	if (atoi(guide_buf[2]))
	{
		fseek(fp, (atoi(guide_buf[2]) - 1) * guide_length + 4, SEEK_SET);
		fread(&wronginfo[ListNo].WrongPrompt[2], 1, 49, fp);
	}
	else
	{
		sprintf(wronginfo[ListNo].WrongPrompt[2], "%s", "");
	}

	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + 19, SEEK_SET);
	fread(guide_buf[3], 1, 3, wrongfp);

	if (atoi(guide_buf[3]))
	{
		fseek(fp, (atoi(guide_buf[3]) - 1) * guide_length + 4, SEEK_SET);
		fread(&wronginfo[ListNo].WrongPrompt[3], 1, 50, fp);
	}
	else
	{
		sprintf(wronginfo[ListNo].WrongPrompt[3], "%s", "");
	}

#ifdef DEBUG

	printf("%d wrong Value %s\n", ListNo, wronginfo[ListNo].WrongValue);
	printf("wrong level %s\n", wronginfo[ListNo].WrongLevel);
	printf("wrong prompt %s\n", wronginfo[ListNo].WrongPrompt);
#endif
	/*故障代码*/
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length, SEEK_SET);
	fread(&wronginfo[ListNo].WrongList, 1, 4, wrongfp);
	/*故障序号*/
	wronginfo[ListNo].WrongCode = wrong_no;
	wronginfo[ListNo].Confirmed = NO;
	wronginfo[ListNo].WrongLen = 0;
	record_wrong_s(&wronginfo[ListNo]); //将故障信息存到event.bin文本

	if (ListNo < MAXWRONGNO - 1)
		ListNo++;
	else
		ListNo = MAXWRONGNO - 1;
	fclose(wrongfp);
	fclose(fp);
}

static void record_wrong_s(WrongInfo *winfo) //将故障信息存到event.bin文本
{
	short wrong_len = 0;
	FILE *fp;
	char temp_char;
	short temp_short;
	if (!access("file/event.bin", 0))
	{
		fp = fopen("file/event.bin", "r+b");
		fseek(fp, 0, SEEK_SET);
		fread(&wrong_len, sizeof(short), 1, fp);
		if (wrong_len > 999)
			wrong_len = 0; //判断文本故障是否到了1000条，循环存储
	}
	else
	{
		fp = fopen("file/event.bin", "wb");
		fwrite(&wrong_len, sizeof(short), 1, fp);
		fclose(fp);
		fp = fopen("file/event.bin", "r+b");
	}
	if (fp != NULL)
	{
		fseek(fp, wrong_len * 19 + 2, SEEK_SET);
		winfo->WrongLen = wrong_len;

		temp_short = (short)(winfo->WrongTime.tm_year + 2000);
		fwrite(&temp_short, sizeof(short), 1, fp);
		temp_char = (char)(winfo->WrongTime.tm_mon);
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)(winfo->WrongTime.tm_mday);
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTime.tm_hour;
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTime.tm_min;
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTime.tm_sec;
		fwrite(&temp_char, sizeof(char), 1, fp);

		temp_short = (short)(winfo->WrongTimeEnd.tm_year + 2000);
		fwrite(&temp_short, sizeof(short), 1, fp);
		temp_char = (char)(winfo->WrongTimeEnd.tm_mon);
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)(winfo->WrongTimeEnd.tm_mday);
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTimeEnd.tm_hour;
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTimeEnd.tm_min;
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTimeEnd.tm_sec;
		fwrite(&temp_char, sizeof(char), 1, fp);

		temp_short = (short)winfo->WrongCode;
		fwrite(&temp_short, sizeof(short), 1, fp);

		temp_char = (char)(atoi(winfo->WrongClass));
		fwrite(&temp_char, sizeof(char), 1, fp);

		temp_short = (short)(atoi(winfo->WrongList));
		fwrite(&temp_short, sizeof(short), 1, fp);

		fseek(fp, 0, SEEK_SET);
		wrong_len++; //每增加一条故障，l加1
		fwrite(&wrong_len, sizeof(short), 1, fp);
	}
	fclose(fp);
}

static void wrong_dispear(unsigned short wrong_no)
{
	int l, m;
	for (l = 0; l < ListNo; l++)
	{
		if (wrong_no == wronginfo[l].WrongCode) //找到了该故障
		{
			/*故障消除时的时间*/
			wronginfo[l].WrongTimeEnd.tm_year = mvb.get_uchar(0xff, 1);
			wronginfo[l].WrongTimeEnd.tm_mon = mvb.get_uchar(0xff, 0);
			wronginfo[l].WrongTimeEnd.tm_mday = mvb.get_uchar(0xff, 3);
			wronginfo[l].WrongTimeEnd.tm_hour = mvb.get_uchar(0xff, 2);
			wronginfo[l].WrongTimeEnd.tm_min = mvb.get_uchar(0xff, 5);
			wronginfo[l].WrongTimeEnd.tm_sec = mvb.get_uchar(0xff, 4);
			record_wrong_e(&wronginfo[l]);
			//删除此故障
			for (m = l; m < (ListNo - 1); m++)
				wronginfo[m] = wronginfo[m + 1];

			if (ListNo > 0)
				ListNo--;
		}
	}
}

static void record_wrong_e(WrongInfo *winfo)
{
	FILE *fp;
	char temp_char;
	short temp_short;

	fp = fopen("file/event.bin", "r+b");

	if (fp != NULL)
	{
		fseek(fp, winfo->WrongLen * 19 + 2, SEEK_SET);
		temp_short = (short)(winfo->WrongTime.tm_year + 2000);
		fwrite(&temp_short, sizeof(short), 1, fp);
		temp_char = (char)(winfo->WrongTime.tm_mon);
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)(winfo->WrongTime.tm_mday);
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTime.tm_hour;
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTime.tm_min;
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTime.tm_sec;
		fwrite(&temp_char, sizeof(char), 1, fp);

		temp_short = (short)(winfo->WrongTimeEnd.tm_year + 2000);
		fwrite(&temp_short, sizeof(short), 1, fp);
		temp_char = (char)(winfo->WrongTimeEnd.tm_mon);
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)(winfo->WrongTimeEnd.tm_mday);
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTimeEnd.tm_hour;
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTimeEnd.tm_min;
		fwrite(&temp_char, sizeof(char), 1, fp);
		temp_char = (char)winfo->WrongTimeEnd.tm_sec;
		fwrite(&temp_char, sizeof(char), 1, fp);

		temp_short = (short)winfo->WrongCode;
		fwrite(&temp_short, sizeof(short), 1, fp);

		temp_char = (char)(atoi(winfo->WrongClass));
		fwrite(&temp_char, sizeof(char), 1, fp);

		temp_short = (short)(atoi(winfo->WrongList));
		fwrite(&temp_short, sizeof(short), 1, fp);
	}
	fclose(fp);
}

//故障显示
void wrong_show_cur()
{
	int i;
	int CurrentRow;

	if (wrong_exciting_butt->value()) //现存故障显示
	{
		if (ListNo > 0)
		{
			for (i = 0; i < 10; i++)
			{
				CurrentRow = Page * 10 + i;

				sprintf(wrong_value[i], " %d     %d    %s", atoi(wronginfo[CurrentRow].WrongClass), atoi(wronginfo[CurrentRow].WrongList), wronginfo[CurrentRow].WrongValue);
				wrongbutt[i]->label(wrong_value[i]);
				sprintf(wrong_time[i], "%04d-%02d-%02d %02d:%02d:%02d\n-", 2000 + wronginfo[CurrentRow].WrongTime.tm_year, wronginfo[CurrentRow].WrongTime.tm_mon, wronginfo[CurrentRow].WrongTime.tm_mday, wronginfo[CurrentRow].WrongTime.tm_hour, wronginfo[CurrentRow].WrongTime.tm_min, wronginfo[CurrentRow].WrongTime.tm_sec);
				wrongbut[i]->label(wrong_time[i]);
				if ((Page * 10 + i) >= ListNo)
				{
					wrongbutt[i]->label("");
					wrongbut[i]->label("");
				}
			}
		}
		else
		{
			for (i = 0; i < 10; i++)
			{
				wrongbutt[i]->label("");
				wrongbut[i]->label("");
			}
		}
	}
	else if (wrong_record_butt->value()) //故障履历显示
	{
		for (i = 0; i < 10; i++)
		{
			CurrentRow = Page * 10 + i;
			sprintf(wrong_value[i], " %d     %d    %s", atoi(wrongrecordinfo[CurrentRow].WrongClass), atoi(wrongrecordinfo[CurrentRow].WrongList), wrongrecordinfo[CurrentRow].WrongValue);
			wrongbutt[i]->label(wrong_value[i]);
			if (wrongrecordinfo[CurrentRow].WrongTimeEnd.tm_year > 2000)
				sprintf(wrong_time[i], "%04d-%02d-%02d %02d:%02d:%02d\n%04d-%02d-%02d %02d:%02d:%02d", wrongrecordinfo[CurrentRow].WrongTime.tm_year, wrongrecordinfo[CurrentRow].WrongTime.tm_mon, wrongrecordinfo[CurrentRow].WrongTime.tm_mday, wrongrecordinfo[CurrentRow].WrongTime.tm_hour, wrongrecordinfo[CurrentRow].WrongTime.tm_min, wrongrecordinfo[CurrentRow].WrongTime.tm_sec, wrongrecordinfo[CurrentRow].WrongTimeEnd.tm_year, wrongrecordinfo[CurrentRow].WrongTimeEnd.tm_mon, wrongrecordinfo[CurrentRow].WrongTimeEnd.tm_mday, wrongrecordinfo[CurrentRow].WrongTimeEnd.tm_hour, wrongrecordinfo[CurrentRow].WrongTimeEnd.tm_min, wrongrecordinfo[CurrentRow].WrongTimeEnd.tm_sec);
			else
				sprintf(wrong_time[i], "%04d-%02d-%02d %02d:%02d:%02d\n-", wrongrecordinfo[CurrentRow].WrongTime.tm_year, wrongrecordinfo[CurrentRow].WrongTime.tm_mon, wrongrecordinfo[CurrentRow].WrongTime.tm_mday, wrongrecordinfo[CurrentRow].WrongTime.tm_hour, wrongrecordinfo[CurrentRow].WrongTime.tm_min, wrongrecordinfo[CurrentRow].WrongTime.tm_sec);
			wrongbut[i]->label(wrong_time[i]);
			if ((Page * 10 + i) > (statbuf.st_size / 19 - 1))
			{
				wrongbutt[i]->label("");
				wrongbut[i]->label("");
			}
		}
	}
	wrong_window->redraw();
}

//统计轻微故障的数目
char get_cnum()
{
	char num = 0;
	for (int m = 0; m < ListNo; m++)
	{
		if ((atoi(wronginfo[m].WrongClass) != 1) && (atoi(wronginfo[m].WrongClass) != 2))
			num = num + 1;
	}
	return num;
}

//中等和严重故障发生运行界面报警
void wrong_prompt()
{
	static char wrong_base[80];
	char flag = 0;
	unsigned char select_ok = 0;
	int i;

	if (ListNo - get_cnum() < 1)
	{
		wrong_main_alarm->color(FL_BLACK);
	}
	else
	{
		if (ListNo > 0)
		{
			for (i = ListNo - 1; i >= 0; i--)
			{
				sprintf(wrong_base, "%s", wronginfo[i].WrongValue);

				if ((atoi(wronginfo[i].WrongClass) != 1) && (atoi(wronginfo[i].WrongClass) != 2))
				{
					continue;
				}
				if (wronginfo[i].Confirmed == NO)
				{
					if (atoi(wronginfo[i].WrongClass) == 1) //严重故障
					{
						wrong_main_alarm->color(FL_RED);
						wrong_main_alarm->labelcolor(FL_WHITE);
						wrong_main_alarm->label(wrong_base);
					}
					else if (atoi(wronginfo[i].WrongClass) == 2) //中等故障
					{
						wrong_main_alarm->color(FL_YELLOW);
						wrong_main_alarm->labelcolor(FL_BLACK);
						wrong_main_alarm->label(wrong_base);
					}
					ShowingWrongP = i;
					flag = 1;
					wrong_main_alarm->redraw();
					break;
				}
			}
		}
		else
		{
			wrong_main_alarm->color(FL_BLACK);
			wrong_main_alarm->label("");
			wrong_main_alarm->redraw();
		}

		if (!flag)
		{
			for (i = ListNo - 1; i >= 0; i--)
			{
				if ((atoi(wronginfo[i].WrongClass) == 1) || (atoi(wronginfo[i].WrongClass) == 2))
				{

					if (select_ok == count)
					{
						sprintf(wrong_base, "%d:%s", atoi(wronginfo[i].WrongClass), wronginfo[i].WrongValue);
						wrong_main_alarm->color(FL_BLACK);
						wrong_main_alarm->labelcolor(FL_WHITE);
						wrong_main_alarm->label(wrong_base);
						wrong_main_alarm->redraw();
					}
					select_ok++;
				}
			}
		}
	}

	//显示中等和严重故障总数及已确认的数目函数调用
	get_confirmno();
}

//显示中等和严重故障总数及已确认的数目
static void get_confirmno()
{
	static char buf_confirmno[10];
	char confirmno = 0;

	for (int i = 0; i < ListNo; i++)
	{
		if (wronginfo[i].Confirmed == YES)
			confirmno++;
	}
	if (confirmno >= (ListNo - get_cnum()))
	{
		confirmno = 0;
	}

	sprintf(buf_confirmno, "%d/%d", count, ListNo - get_cnum()); // confirmno,ListNo-get_cnum());

	wrong_alarm_numaaa->label(buf_confirmno);
}

//主界面错误提示确认
void main_error_confirm_cb(Fl_Button *, void *)
{

	count++;
	wronginfo[ShowingWrongP].Confirmed = YES;

	if (count >= (ListNo - get_cnum()) || (ListNo == get_cnum()))
	{
		count = 0;
	}
}

void wrongnum()
{
	int i;
	for (i = 0; i < 10; i++)
	{
		sprintf(wrongnobuf[i], "%d", Page * 10 + i + 1);
		wrongno[i]->label(wrongnobuf[i]);
	}
}

//上一页故障
void wrong_pre_cb(Fl_Button *, void *)
{
	if (wrong_exciting_butt->value())
	{
		if (Page > 0)
			Page--;
		else
			Page = char(ListNo / MAXROW);
		for (int i = 1; i < 10; i++)
		{
			wrongbutt[i]->value(0);
			wrongbut[i]->color(FL_BLACK);
		}
		wrongbut[0]->color(179);
		wrongbutt[0]->value(1);
	}
	else if (wrong_record_butt->value())
	{
		for (int i = 1; i < 10; i++)
		{
			wrongbutt[i]->value(0);
			wrongbut[i]->color(FL_BLACK);
		}
		if (Page > 0)
			Page--;
		else
			Page = (statbuf.st_size / 190);
	}
	wrongnum();
}

//下一页故障
void wrong_next_cb(Fl_Button *, void *)
{
	if (wrong_exciting_butt->value())
	{
		Page++;
		if (Page > (ListNo / MAXROW))
			Page = 0;
		for (int i = 1; i < 10; i++)
		{
			wrongbutt[i]->value(0);
			wrongbut[i]->color(FL_BLACK);
		}
		wrongbut[0]->color(179);
		wrongbutt[0]->value(1);
	}
	else if (wrong_record_butt->value())
	{
		for (int i = 1; i < 10; i++)
		{
			wrongbutt[i]->value(0);
			wrongbut[i]->color(FL_BLACK);
		}
		Page++;
		if (Page > statbuf.st_size / 190)
			Page = 0;
	}
	wrongnum();
}

void wrong_select_cb(Fl_Button *o, long i)
{
	row = i;

	for (int i = 0; i < 10; i++)
	{
		wrongbutt[i]->value(0);
		wrongbut[i]->color(FL_BLACK);
	}
	wrongbutt[row - 1]->value(1);
	wrongbut[row - 1]->color(179);
}

//切换至现存故障界面
void wrong_exciting_cb(Fl_Button *, void *)
{
	Page = 0;
	wrongnum();
	wrong_overview_window->show();
	wrong_guide_window->hide();
	wrong_advice_butt->activate();
}

//切换至故障履历界面
void wrong_record_cb(Fl_Button *, void *)
{
	Page = 0;
	wrongnum();
	wrongrecord_init();
	wrong_overview_window->show();
	wrong_guide_window->hide();
	wrong_advice_butt->deactivate();
}

//切换至故障提示界面
void wrong_advice_cb(Fl_Button *, void *)
{
	guide_wronginfo->value(wronginfo[Page * 10 + row - 1].WrongValue);
	guide_wrongguide_1->value(wronginfo[Page * 10 + row - 1].WrongPrompt[0]);
	guide_wrongguide_2->value(wronginfo[Page * 10 + row - 1].WrongPrompt[1]);
	guide_wrongguide_3->value(wronginfo[Page * 10 + row - 1].WrongPrompt[2]);
	guide_wrongguide_4->value(wronginfo[Page * 10 + row - 1].WrongPrompt[3]);

	wrong_guide_window->show();
	wrong_overview_window->hide();
	wrong_guide_window->redraw();
}

void wrongrecord_init()
{
	FILE *fp;
	FILE *wrongfp;
	short l;

	char temp_char;
	short temp_short;

	stat("file/event.bin", &statbuf);

	fp = fopen("file/event.bin", "r+b");
	wrongfp = fopen("wrong.txt", "r+");
	if (fp == NULL)
	{
		return;
	}
	if (wrongfp == NULL)
	{
		return;
	}

	fseek(fp, 0, SEEK_SET);
	fread(&l, sizeof(short), 1, fp);

	if (statbuf.st_size > 1900)
	{
		for (int i = 0; i < 1000; i++)
		{
			if (l < 1)
				l = 1000;
			//故障等级
			fseek(fp, (l - 1) * 19 + 2 + 16, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			sprintf(wrongrecordinfo[i].WrongClass, "%d", temp_char);
			//故障代码
			fseek(fp, (l - 1) * 19 + 2 + 17, SEEK_SET);
			fread(&temp_short, sizeof(short), 1, fp);
			sprintf(wrongrecordinfo[i].WrongList, "%d", temp_short);
			//故障信息
			fseek(fp, (l - 1) * 19 + 2 + 14, SEEK_SET);
			fread(&temp_short, sizeof(short), 1, fp);
			fseek(wrongfp, (temp_short - 1) * wronginfo_length + wronginfo_offset, SEEK_SET);
			fread(wrongrecordinfo[i].WrongValue, 1, 59, wrongfp);
			//故障发生时间
			fseek(fp, (l - 1) * 19 + 2, SEEK_SET);
			fread(&temp_short, sizeof(short), 1, fp);
			wrongrecordinfo[i].WrongTime.tm_year = temp_short;
			fseek(fp, (l - 1) * 19 + 2 + 2, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTime.tm_mon = temp_char;
			fseek(fp, (l - 1) * 19 + 2 + 3, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTime.tm_mday = temp_char;
			fseek(fp, (l - 1) * 19 + 2 + 4, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTime.tm_hour = temp_char;
			fseek(fp, (l - 1) * 19 + 2 + 5, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTime.tm_min = temp_char;
			fseek(fp, (l - 1) * 19 + 2 + 6, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTime.tm_sec = temp_char;
			//故障消除时间
			fseek(fp, (l - 1) * 19 + 2 + 7, SEEK_SET);
			fread(&temp_short, sizeof(short), 1, fp);
			wrongrecordinfo[i].WrongTimeEnd.tm_year = temp_short;
			fseek(fp, (l - 1) * 19 + 2 + 9, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTimeEnd.tm_mon = temp_char;
			fseek(fp, (l - 1) * 19 + 2 + 10, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTimeEnd.tm_mday = temp_char;
			fseek(fp, (l - 1) * 19 + 2 + 11, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTimeEnd.tm_hour = temp_char;
			fseek(fp, (l - 1) * 19 + 2 + 12, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTimeEnd.tm_min = temp_char;
			fseek(fp, (l - 1) * 19 + 2 + 13, SEEK_SET);
			fread(&temp_char, sizeof(char), 1, fp);
			wrongrecordinfo[i].WrongTimeEnd.tm_sec = temp_char;

			l--;
		}
	}
	else
	{
		for (int j = 0; j < 1000; j++)
		{
			if (l)
			{
				//故障等级
				fseek(fp, (l - 1) * 19 + 2 + 16, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				sprintf(wrongrecordinfo[j].WrongClass, "%d", temp_char);
				//故障代码
				fseek(fp, (l - 1) * 19 + 2 + 17, SEEK_SET);
				fread(&temp_short, sizeof(short), 1, fp);
				sprintf(wrongrecordinfo[j].WrongList, "%d", temp_short);
				//故障信息
				fseek(fp, (l - 1) * 19 + 2 + 14, SEEK_SET);
				fread(&temp_short, sizeof(short), 1, fp);
				fseek(wrongfp, (temp_short - 1) * wronginfo_length + wronginfo_offset, SEEK_SET);
				fread(wrongrecordinfo[j].WrongValue, 1, 59, wrongfp);
				//故障发生时间
				fseek(fp, (l - 1) * 19 + 2, SEEK_SET);
				fread(&temp_short, sizeof(short), 1, fp);
				wrongrecordinfo[j].WrongTime.tm_year = temp_short;
				fseek(fp, (l - 1) * 19 + 2 + 2, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTime.tm_mon = temp_char;
				fseek(fp, (l - 1) * 19 + 2 + 3, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTime.tm_mday = temp_char;
				fseek(fp, (l - 1) * 19 + 2 + 4, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTime.tm_hour = temp_char;
				fseek(fp, (l - 1) * 19 + 2 + 5, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTime.tm_min = temp_char;
				fseek(fp, (l - 1) * 19 + 2 + 6, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTime.tm_sec = temp_char;
				//故障消除时间
				fseek(fp, (l - 1) * 19 + 2 + 7, SEEK_SET);
				fread(&temp_short, sizeof(short), 1, fp);
				wrongrecordinfo[j].WrongTimeEnd.tm_year = temp_short;
				fseek(fp, (l - 1) * 19 + 2 + 9, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTimeEnd.tm_mon = temp_char;
				fseek(fp, (l - 1) * 19 + 2 + 10, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTimeEnd.tm_mday = temp_char;
				fseek(fp, (l - 1) * 19 + 2 + 11, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTimeEnd.tm_hour = temp_char;
				fseek(fp, (l - 1) * 19 + 2 + 12, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTimeEnd.tm_min = temp_char;
				fseek(fp, (l - 1) * 19 + 2 + 13, SEEK_SET);
				fread(&temp_char, sizeof(char), 1, fp);
				wrongrecordinfo[j].WrongTimeEnd.tm_sec = temp_char;

				l--;
			}
		}
	}
	fclose(fp);
	fclose(wrongfp);
}
