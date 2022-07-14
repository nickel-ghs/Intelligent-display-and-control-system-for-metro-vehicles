#include <stdio.h>
#include <stdlib.h>
#include <i2cfun.h>
#include "wrong.h"
#include "head.h"
#include <mvb.h>
#include <unistd.h>
#include <sys/stat.h>

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
		// 2车
		port = 0x14;
		WrongStatus[0] = (mvb.get_uchar(port, 1)) & 0x8f;
		WrongStatus[1] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[2] = (mvb.get_uchar(port, 3)) & 0xbd;
		WrongStatus[3] = (mvb.get_uchar(port, 2)) & 0xf9;
		WrongStatus[4] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[5] = (mvb.get_uchar(port, 4)) & 0x01;
		WrongStatus[6] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[7] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[8] = (mvb.get_uchar(port, 9)) & 0x3e;
		WrongStatus[9] = (mvb.get_uchar(port, 8)) & 0xe3;
		WrongStatus[10] = (mvb.get_uchar(port, 11)) & 0x1f;
		WrongStatus[11] = (mvb.get_uchar(port, 10)) & 0x00;
		// 3车
		port = 0x14;
		WrongStatus[12] = (mvb.get_uchar(port, 13)) & 0x8f;
		WrongStatus[13] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[14] = (mvb.get_uchar(port, 15)) & 0xbd;
		WrongStatus[15] = (mvb.get_uchar(port, 14)) & 0xf9;
		WrongStatus[16] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[17] = (mvb.get_uchar(port, 16)) & 0x01;
		WrongStatus[18] = (mvb.get_uchar(port, 19)) & 0xff;
		WrongStatus[19] = (mvb.get_uchar(port, 18)) & 0xff;
		WrongStatus[20] = (mvb.get_uchar(port, 21)) & 0x3e;
		WrongStatus[21] = (mvb.get_uchar(port, 20)) & 0xe3;
		WrongStatus[22] = (mvb.get_uchar(port, 23)) & 0x1f;
		WrongStatus[23] = (mvb.get_uchar(port, 22)) & 0x00;
		// 4车
		port = 0x15;
		WrongStatus[24] = (mvb.get_uchar(port, 1)) & 0x8f;
		WrongStatus[25] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[26] = (mvb.get_uchar(port, 3)) & 0xbd;
		WrongStatus[27] = (mvb.get_uchar(port, 2)) & 0xf9;
		WrongStatus[28] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[29] = (mvb.get_uchar(port, 4)) & 0x01;
		WrongStatus[30] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[31] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[32] = (mvb.get_uchar(port, 9)) & 0x3e;
		WrongStatus[33] = (mvb.get_uchar(port, 8)) & 0xe3;
		WrongStatus[34] = (mvb.get_uchar(port, 11)) & 0x1f;
		WrongStatus[35] = (mvb.get_uchar(port, 10)) & 0x00;
		// 5车
		port = 0x15;
		WrongStatus[36] = (mvb.get_uchar(port, 13)) & 0x8f;
		WrongStatus[37] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[38] = (mvb.get_uchar(port, 15)) & 0xbd;
		WrongStatus[39] = (mvb.get_uchar(port, 14)) & 0xf9;
		WrongStatus[40] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[41] = (mvb.get_uchar(port, 16)) & 0x01;
		WrongStatus[42] = (mvb.get_uchar(port, 19)) & 0xff;
		WrongStatus[43] = (mvb.get_uchar(port, 18)) & 0xff;
		WrongStatus[44] = (mvb.get_uchar(port, 21)) & 0x3e;
		WrongStatus[45] = (mvb.get_uchar(port, 20)) & 0xe3;
		WrongStatus[46] = (mvb.get_uchar(port, 23)) & 0x1f;
		WrongStatus[47] = (mvb.get_uchar(port, 22)) & 0x00;
		// SIV故障数据
		// 1车
		port = 0xb;
		WrongStatus[48] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[49] = (mvb.get_uchar(port, 12)) & 0xbf;
		WrongStatus[50] = (mvb.get_uchar(port, 15)) & 0xff;
		WrongStatus[51] = (mvb.get_uchar(port, 14)) & 0xff;
		WrongStatus[52] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[53] = (mvb.get_uchar(port, 16)) & 0x05;
		WrongStatus[54] = (mvb.get_uchar(port, 19)) & 0x00;
		WrongStatus[55] = (mvb.get_uchar(port, 18)) & 0x00;
		WrongStatus[56] = (mvb.get_uchar(port, 21)) & 0x00;
		WrongStatus[57] = (mvb.get_uchar(port, 20)) & 0xfc;
		// 6车
		port = 0xc;
		WrongStatus[58] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[59] = (mvb.get_uchar(port, 12)) & 0xbf;
		WrongStatus[60] = (mvb.get_uchar(port, 15)) & 0xff;
		WrongStatus[61] = (mvb.get_uchar(port, 14)) & 0xff;
		WrongStatus[62] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[63] = (mvb.get_uchar(port, 16)) & 0x05;
		WrongStatus[64] = (mvb.get_uchar(port, 19)) & 0x00;
		WrongStatus[65] = (mvb.get_uchar(port, 18)) & 0x00;
		WrongStatus[66] = (mvb.get_uchar(port, 21)) & 0x00;
		WrongStatus[67] = (mvb.get_uchar(port, 20)) & 0xfc;
		// BCU故障数据
		port = 0x17;
		// 1车
		WrongStatus[68] = (mvb.get_uchar(port, 1)) & 0x03;
		WrongStatus[69] = (mvb.get_uchar(port, 0)) & 0xa7;
		WrongStatus[70] = (mvb.get_uchar(port, 3)) & 0x77;
		WrongStatus[71] = (mvb.get_uchar(port, 2)) & 0xef;
		WrongStatus[72] = (mvb.get_uchar(port, 5)) & 0x03;
		WrongStatus[73] = (mvb.get_uchar(port, 4)) & 0xa7;
		WrongStatus[74] = (mvb.get_uchar(port, 7)) & 0x73;
		WrongStatus[75] = (mvb.get_uchar(port, 6)) & 0xef;
		// 2车
		WrongStatus[76] = (mvb.get_uchar(port, 9)) & 0x03;
		WrongStatus[77] = (mvb.get_uchar(port, 8)) & 0xa7;
		WrongStatus[78] = (mvb.get_uchar(port, 11)) & 0x77;
		WrongStatus[79] = (mvb.get_uchar(port, 10)) & 0xef;
		WrongStatus[80] = (mvb.get_uchar(port, 13)) & 0x03;
		WrongStatus[81] = (mvb.get_uchar(port, 12)) & 0xa7;
		WrongStatus[82] = (mvb.get_uchar(port, 15)) & 0x73;
		WrongStatus[83] = (mvb.get_uchar(port, 14)) & 0xef;
		// 3车
		WrongStatus[84] = (mvb.get_uchar(port, 17)) & 0x03;
		WrongStatus[85] = (mvb.get_uchar(port, 16)) & 0xa7;
		WrongStatus[86] = (mvb.get_uchar(port, 19)) & 0x77;
		WrongStatus[87] = (mvb.get_uchar(port, 18)) & 0xef;
		WrongStatus[88] = (mvb.get_uchar(port, 21)) & 0x03;
		WrongStatus[89] = (mvb.get_uchar(port, 20)) & 0xa7;
		WrongStatus[90] = (mvb.get_uchar(port, 23)) & 0x73;
		WrongStatus[91] = (mvb.get_uchar(port, 22)) & 0xef;
		port = 0x18;
		// 6车
		WrongStatus[92] = (mvb.get_uchar(port, 1)) & 0x03;
		WrongStatus[93] = (mvb.get_uchar(port, 0)) & 0xa7;
		WrongStatus[94] = (mvb.get_uchar(port, 3)) & 0x77;
		WrongStatus[95] = (mvb.get_uchar(port, 2)) & 0xef;
		WrongStatus[96] = (mvb.get_uchar(port, 5)) & 0x03;
		WrongStatus[97] = (mvb.get_uchar(port, 4)) & 0xa7;
		WrongStatus[98] = (mvb.get_uchar(port, 7)) & 0x73;
		WrongStatus[99] = (mvb.get_uchar(port, 6)) & 0xef;
		// 5车
		WrongStatus[100] = (mvb.get_uchar(port, 9)) & 0x03;
		WrongStatus[101] = (mvb.get_uchar(port, 8)) & 0xa7;
		WrongStatus[102] = (mvb.get_uchar(port, 11)) & 0x77;
		WrongStatus[103] = (mvb.get_uchar(port, 10)) & 0xef;
		WrongStatus[104] = (mvb.get_uchar(port, 13)) & 0x03;
		WrongStatus[105] = (mvb.get_uchar(port, 12)) & 0xa7;
		WrongStatus[106] = (mvb.get_uchar(port, 15)) & 0x73;
		WrongStatus[107] = (mvb.get_uchar(port, 14)) & 0xef;
		// 4车
		WrongStatus[108] = (mvb.get_uchar(port, 17)) & 0x03;
		WrongStatus[109] = (mvb.get_uchar(port, 16)) & 0xa7;
		WrongStatus[110] = (mvb.get_uchar(port, 19)) & 0x77;
		WrongStatus[111] = (mvb.get_uchar(port, 18)) & 0xef;
		WrongStatus[112] = (mvb.get_uchar(port, 21)) & 0x03;
		WrongStatus[113] = (mvb.get_uchar(port, 20)) & 0xa7;
		WrongStatus[114] = (mvb.get_uchar(port, 23)) & 0x73;
		WrongStatus[115] = (mvb.get_uchar(port, 22)) & 0xef;
		// EDCU故障
		// 1车
		port = 0x21;
		WrongStatus[116] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[117] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[118] = (mvb.get_uchar(port, 3)) & 0x01;
		WrongStatus[119] = (mvb.get_uchar(port, 2)) & 0x00;
		WrongStatus[120] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[121] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[122] = (mvb.get_uchar(port, 7)) & 0x01;
		WrongStatus[123] = (mvb.get_uchar(port, 6)) & 0x00;
		WrongStatus[124] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[125] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[126] = (mvb.get_uchar(port, 11)) & 0x01;
		WrongStatus[127] = (mvb.get_uchar(port, 10)) & 0x00;
		WrongStatus[128] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[129] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[130] = (mvb.get_uchar(port, 15)) & 0x01;
		WrongStatus[131] = (mvb.get_uchar(port, 14)) & 0x00;
		WrongStatus[132] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[133] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[134] = (mvb.get_uchar(port, 19)) & 0x01;
		WrongStatus[135] = (mvb.get_uchar(port, 18)) & 0x00;
		WrongStatus[136] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[137] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[138] = (mvb.get_uchar(port, 23)) & 0x01;
		WrongStatus[139] = (mvb.get_uchar(port, 22)) & 0x00;
		WrongStatus[140] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[141] = (mvb.get_uchar(port, 24)) & 0xff;
		WrongStatus[142] = (mvb.get_uchar(port, 27)) & 0x01;
		WrongStatus[143] = (mvb.get_uchar(port, 26)) & 0x00;
		WrongStatus[144] = (mvb.get_uchar(port, 29)) & 0xff;
		WrongStatus[145] = (mvb.get_uchar(port, 28)) & 0xff;
		WrongStatus[146] = (mvb.get_uchar(port, 31)) & 0x01;
		WrongStatus[147] = (mvb.get_uchar(port, 30)) & 0x00;
		// 2车
		port = 0x22;
		WrongStatus[148] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[149] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[150] = (mvb.get_uchar(port, 3)) & 0x01;
		WrongStatus[151] = (mvb.get_uchar(port, 2)) & 0x00;
		WrongStatus[152] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[153] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[154] = (mvb.get_uchar(port, 7)) & 0x01;
		WrongStatus[155] = (mvb.get_uchar(port, 6)) & 0x00;
		WrongStatus[156] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[157] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[158] = (mvb.get_uchar(port, 11)) & 0x01;
		WrongStatus[159] = (mvb.get_uchar(port, 10)) & 0x00;
		WrongStatus[160] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[161] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[162] = (mvb.get_uchar(port, 15)) & 0x01;
		WrongStatus[163] = (mvb.get_uchar(port, 14)) & 0x00;
		WrongStatus[164] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[165] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[166] = (mvb.get_uchar(port, 19)) & 0x01;
		WrongStatus[167] = (mvb.get_uchar(port, 18)) & 0x00;
		WrongStatus[168] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[169] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[170] = (mvb.get_uchar(port, 23)) & 0x01;
		WrongStatus[171] = (mvb.get_uchar(port, 22)) & 0x00;
		WrongStatus[172] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[173] = (mvb.get_uchar(port, 24)) & 0xff;
		WrongStatus[174] = (mvb.get_uchar(port, 27)) & 0x01;
		WrongStatus[175] = (mvb.get_uchar(port, 26)) & 0x00;
		WrongStatus[176] = (mvb.get_uchar(port, 29)) & 0xff;
		WrongStatus[177] = (mvb.get_uchar(port, 28)) & 0xff;
		WrongStatus[178] = (mvb.get_uchar(port, 31)) & 0x01;
		WrongStatus[179] = (mvb.get_uchar(port, 30)) & 0x00;
		// 3车
		port = 0x23;
		WrongStatus[180] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[181] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[182] = (mvb.get_uchar(port, 3)) & 0x01;
		WrongStatus[183] = (mvb.get_uchar(port, 2)) & 0x00;
		WrongStatus[184] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[185] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[186] = (mvb.get_uchar(port, 7)) & 0x01;
		WrongStatus[187] = (mvb.get_uchar(port, 6)) & 0x00;
		WrongStatus[188] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[189] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[190] = (mvb.get_uchar(port, 11)) & 0x01;
		WrongStatus[191] = (mvb.get_uchar(port, 10)) & 0x00;
		WrongStatus[192] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[193] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[194] = (mvb.get_uchar(port, 15)) & 0x01;
		WrongStatus[195] = (mvb.get_uchar(port, 14)) & 0x00;
		WrongStatus[196] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[197] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[198] = (mvb.get_uchar(port, 19)) & 0x01;
		WrongStatus[199] = (mvb.get_uchar(port, 18)) & 0x00;
		WrongStatus[200] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[201] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[202] = (mvb.get_uchar(port, 23)) & 0x01;
		WrongStatus[203] = (mvb.get_uchar(port, 22)) & 0x00;
		WrongStatus[204] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[205] = (mvb.get_uchar(port, 24)) & 0xff;
		WrongStatus[206] = (mvb.get_uchar(port, 27)) & 0x01;
		WrongStatus[207] = (mvb.get_uchar(port, 26)) & 0x00;
		WrongStatus[208] = (mvb.get_uchar(port, 29)) & 0xff;
		WrongStatus[209] = (mvb.get_uchar(port, 28)) & 0xff;
		WrongStatus[210] = (mvb.get_uchar(port, 31)) & 0x01;
		WrongStatus[211] = (mvb.get_uchar(port, 30)) & 0x00;
		// 4车
		port = 0x24;
		WrongStatus[212] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[213] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[214] = (mvb.get_uchar(port, 3)) & 0x01;
		WrongStatus[215] = (mvb.get_uchar(port, 2)) & 0x00;
		WrongStatus[216] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[217] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[218] = (mvb.get_uchar(port, 7)) & 0x01;
		WrongStatus[219] = (mvb.get_uchar(port, 6)) & 0x00;
		WrongStatus[220] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[221] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[222] = (mvb.get_uchar(port, 11)) & 0x01;
		WrongStatus[223] = (mvb.get_uchar(port, 10)) & 0x00;
		WrongStatus[224] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[225] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[226] = (mvb.get_uchar(port, 15)) & 0x01;
		WrongStatus[227] = (mvb.get_uchar(port, 14)) & 0x00;
		WrongStatus[228] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[229] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[230] = (mvb.get_uchar(port, 19)) & 0x01;
		WrongStatus[231] = (mvb.get_uchar(port, 18)) & 0x00;
		WrongStatus[232] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[233] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[234] = (mvb.get_uchar(port, 23)) & 0x01;
		WrongStatus[235] = (mvb.get_uchar(port, 22)) & 0x00;
		WrongStatus[236] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[237] = (mvb.get_uchar(port, 24)) & 0xff;
		WrongStatus[238] = (mvb.get_uchar(port, 27)) & 0x01;
		WrongStatus[239] = (mvb.get_uchar(port, 26)) & 0x00;
		WrongStatus[240] = (mvb.get_uchar(port, 29)) & 0xff;
		WrongStatus[241] = (mvb.get_uchar(port, 28)) & 0xff;
		WrongStatus[242] = (mvb.get_uchar(port, 31)) & 0x01;
		WrongStatus[243] = (mvb.get_uchar(port, 30)) & 0x00;
		// 5车
		port = 0x25;
		WrongStatus[244] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[245] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[246] = (mvb.get_uchar(port, 3)) & 0x01;
		WrongStatus[247] = (mvb.get_uchar(port, 2)) & 0x00;
		WrongStatus[248] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[249] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[250] = (mvb.get_uchar(port, 7)) & 0x01;
		WrongStatus[251] = (mvb.get_uchar(port, 6)) & 0x00;
		WrongStatus[252] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[253] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[254] = (mvb.get_uchar(port, 11)) & 0x01;
		WrongStatus[255] = (mvb.get_uchar(port, 10)) & 0x00;
		WrongStatus[256] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[257] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[258] = (mvb.get_uchar(port, 15)) & 0x01;
		WrongStatus[259] = (mvb.get_uchar(port, 14)) & 0x00;
		WrongStatus[260] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[261] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[262] = (mvb.get_uchar(port, 19)) & 0x01;
		WrongStatus[263] = (mvb.get_uchar(port, 18)) & 0x00;
		WrongStatus[264] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[265] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[266] = (mvb.get_uchar(port, 23)) & 0x01;
		WrongStatus[267] = (mvb.get_uchar(port, 22)) & 0x00;
		WrongStatus[268] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[269] = (mvb.get_uchar(port, 24)) & 0xff;
		WrongStatus[270] = (mvb.get_uchar(port, 27)) & 0x01;
		WrongStatus[271] = (mvb.get_uchar(port, 26)) & 0x00;
		WrongStatus[272] = (mvb.get_uchar(port, 29)) & 0xff;
		WrongStatus[273] = (mvb.get_uchar(port, 28)) & 0xff;
		WrongStatus[274] = (mvb.get_uchar(port, 31)) & 0x01;
		WrongStatus[275] = (mvb.get_uchar(port, 30)) & 0x00;
		// 6车
		port = 0x26;
		WrongStatus[276] = (mvb.get_uchar(port, 1)) & 0xff;
		WrongStatus[277] = (mvb.get_uchar(port, 0)) & 0xff;
		WrongStatus[278] = (mvb.get_uchar(port, 3)) & 0x01;
		WrongStatus[279] = (mvb.get_uchar(port, 2)) & 0x00;
		WrongStatus[280] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[281] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[282] = (mvb.get_uchar(port, 7)) & 0x01;
		WrongStatus[283] = (mvb.get_uchar(port, 6)) & 0x00;
		WrongStatus[284] = (mvb.get_uchar(port, 9)) & 0xff;
		WrongStatus[285] = (mvb.get_uchar(port, 8)) & 0xff;
		WrongStatus[286] = (mvb.get_uchar(port, 11)) & 0x01;
		WrongStatus[287] = (mvb.get_uchar(port, 10)) & 0x00;
		WrongStatus[288] = (mvb.get_uchar(port, 13)) & 0xff;
		WrongStatus[289] = (mvb.get_uchar(port, 12)) & 0xff;
		WrongStatus[290] = (mvb.get_uchar(port, 15)) & 0x01;
		WrongStatus[291] = (mvb.get_uchar(port, 14)) & 0x00;
		WrongStatus[292] = (mvb.get_uchar(port, 17)) & 0xff;
		WrongStatus[293] = (mvb.get_uchar(port, 16)) & 0xff;
		WrongStatus[294] = (mvb.get_uchar(port, 19)) & 0x01;
		WrongStatus[295] = (mvb.get_uchar(port, 18)) & 0x00;
		WrongStatus[296] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[297] = (mvb.get_uchar(port, 20)) & 0xff;
		WrongStatus[298] = (mvb.get_uchar(port, 23)) & 0x01;
		WrongStatus[299] = (mvb.get_uchar(port, 22)) & 0x00;
		WrongStatus[300] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[301] = (mvb.get_uchar(port, 24)) & 0xff;
		WrongStatus[302] = (mvb.get_uchar(port, 27)) & 0x01;
		WrongStatus[303] = (mvb.get_uchar(port, 26)) & 0x00;
		WrongStatus[304] = (mvb.get_uchar(port, 29)) & 0xff;
		WrongStatus[305] = (mvb.get_uchar(port, 28)) & 0xff;
		WrongStatus[306] = (mvb.get_uchar(port, 31)) & 0x01;
		WrongStatus[307] = (mvb.get_uchar(port, 30)) & 0x00;
		// HVAC故障数据
		// 1车
		port = 0x5;
		WrongStatus[308] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[309] = (mvb.get_uchar(port, 20)) & 0x3f;
		WrongStatus[310] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[311] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[312] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[313] = (mvb.get_uchar(port, 24)) & 0x1f;
		// 2车
		port = 0x6;
		WrongStatus[314] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[315] = (mvb.get_uchar(port, 20)) & 0x3f;
		WrongStatus[316] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[317] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[318] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[319] = (mvb.get_uchar(port, 24)) & 0x1f;
		// 3车
		port = 0x7;
		WrongStatus[320] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[321] = (mvb.get_uchar(port, 20)) & 0x3f;
		WrongStatus[322] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[323] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[324] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[325] = (mvb.get_uchar(port, 24)) & 0x1f;
		// 4车
		port = 0x8;
		WrongStatus[326] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[327] = (mvb.get_uchar(port, 20)) & 0x3f;
		WrongStatus[328] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[329] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[330] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[331] = (mvb.get_uchar(port, 24)) & 0x1f;
		// 5车
		port = 0x9;
		WrongStatus[332] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[333] = (mvb.get_uchar(port, 20)) & 0x3f;
		WrongStatus[334] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[335] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[336] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[337] = (mvb.get_uchar(port, 24)) & 0x1f;
		// 6车
		port = 0xa;
		WrongStatus[338] = (mvb.get_uchar(port, 21)) & 0xff;
		WrongStatus[339] = (mvb.get_uchar(port, 20)) & 0x3f;
		WrongStatus[340] = (mvb.get_uchar(port, 23)) & 0xff;
		WrongStatus[341] = (mvb.get_uchar(port, 22)) & 0xff;
		WrongStatus[342] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[343] = (mvb.get_uchar(port, 24)) & 0x1f;
		// PIS故障数据
		port = 0x27;
		WrongStatus[344] = (mvb.get_uchar(port, 1)) & 0x07;
		WrongStatus[345] = (mvb.get_uchar(port, 0)) & 0x00;
		WrongStatus[346] = (mvb.get_uchar(port, 3)) & 0xff;
		WrongStatus[347] = (mvb.get_uchar(port, 2)) & 0x00;
		WrongStatus[348] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[349] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[350] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[351] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[352] = (mvb.get_uchar(port, 21)) & 0x07;
		WrongStatus[353] = (mvb.get_uchar(port, 23)) & 0x03;
		WrongStatus[354] = (mvb.get_uchar(port, 25)) & 0xff;
		WrongStatus[355] = (mvb.get_uchar(port, 24)) & 0x3f;
		WrongStatus[356] = (mvb.get_uchar(port, 27)) & 0x01;
		WrongStatus[357] = (mvb.get_uchar(port, 28)) & 0x03;
		WrongStatus[358] = (mvb.get_uchar(port, 30)) & 0x03;
		// TCMS故障数据
		port = 0x02; //网络未给出此设备通信故障的协议，来了后换端口
		WrongStatus[359] = (mvb.get_uchar(port, 15)) & 0xfd;
		WrongStatus[360] = (mvb.get_uchar(port, 14)) & 0x7f;
		WrongStatus[361] = (mvb.get_uchar(port, 17)) & 0x18;
		WrongStatus[362] = (mvb.get_uchar(port, 16)) & 0x39;
		WrongStatus[363] = (mvb.get_uchar(port, 19)) & 0x18;
		WrongStatus[364] = (mvb.get_uchar(port, 18)) & 0x79;
		WrongStatus[365] = (mvb.get_uchar(port, 21)) & 0x18;
		WrongStatus[366] = (mvb.get_uchar(port, 20)) & 0x79;
		WrongStatus[367] = (mvb.get_uchar(port, 23)) & 0x18;
		WrongStatus[368] = (mvb.get_uchar(port, 22)) & 0x39;
		WrongStatus[369] = (mvb.get_uchar(port, 25)) & 0xfd;
		WrongStatus[370] = (mvb.get_uchar(port, 24)) & 0x7f;
		port = 0x39;
		WrongStatus[371] = (mvb.get_uchar(port, 1)) & 0x0c;
		WrongStatus[372] = (mvb.get_uchar(port, 0)) & 0x3f;
		WrongStatus[373] = (mvb.get_uchar(port, 3)) & 0x01;
		WrongStatus[374] = (mvb.get_uchar(port, 2)) & 0xde;
		WrongStatus[375] = (mvb.get_uchar(port, 5)) & 0xff;
		WrongStatus[376] = (mvb.get_uchar(port, 4)) & 0xff;
		WrongStatus[377] = (mvb.get_uchar(port, 7)) & 0xff;
		WrongStatus[378] = (mvb.get_uchar(port, 6)) & 0xff;
		WrongStatus[379] = (mvb.get_uchar(port, 9)) & 0x39;
		WrongStatus[380] = (mvb.get_uchar(port, 8)) & 0x00;
		// 增加受电弓切除故障信息
		port = 0x16;
		WrongStatus[381] = (mvb.get_uchar(port, 19)) & 0xc0;
		WrongStatus[382] = (mvb.get_uchar(port, 10)) & 0x0F;
		// 增加门CAN网络断线故障信息
		// port=0x20;
		// WrongStatus[383]=(mvb.get_uchar(port,21))&0x3f;
		// 增加门CAN网络断线故障
		port = 0x39;
		WrongStatus[383] = (mvb.get_uchar(port, 11)) & 0x7f;
		WrongStatus[384] = (mvb.get_uchar(port, 10)) & 0x7f;
		WrongStatus[385] = (mvb.get_uchar(port, 13)) & 0x7f;
		WrongStatus[386] = (mvb.get_uchar(port, 12)) & 0x7f;
		WrongStatus[387] = (mvb.get_uchar(port, 15)) & 0x7f;
		WrongStatus[388] = (mvb.get_uchar(port, 14)) & 0x7f;
	}
	else
	{
		for (int i = 0; i < WRONGBYTENO; i++) //存储故障数组的最大字节数
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
					wrong_no = i * 8 + j + 1;			 //计算对应的故障代码行
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

//获得故障发生时的时间及其他参数
static void wrong_appear(unsigned short wrong_no)
{
	FILE *wrongfp;
	FILE *fp;
	int ret;
	char guide_buf[4][4];
	wrongfp = fopen("wrong.txt", "rt");
	if (wrongfp == NULL)
	{
		printf("open wrong.txt error\n");
		return;
	}
	fp = fopen("guide.txt", "r");
	if (fp == NULL)
	{
		return;
	}
	//开始时间
	wronginfo[ListNo].WrongTime.tm_year = mvb.get_uchar(0xff, 0);
	wronginfo[ListNo].WrongTime.tm_mon = mvb.get_uchar(0xff, 1);
	wronginfo[ListNo].WrongTime.tm_mday = mvb.get_uchar(0xff, 2);
	wronginfo[ListNo].WrongTime.tm_hour = mvb.get_uchar(0xff, 3);
	wronginfo[ListNo].WrongTime.tm_min = mvb.get_uchar(0xff, 4);
	wronginfo[ListNo].WrongTime.tm_sec = mvb.get_uchar(0xff, 5);
	//结束时间
	wronginfo[ListNo].WrongTimeEnd.tm_year = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_mon = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_mday = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_hour = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_min = 0;
	wronginfo[ListNo].WrongTimeEnd.tm_sec = 0;
	/*故障内容*/
	//将故障内容写入wrong.txt
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + wronginfo_offset, SEEK_SET);
	ret = fread(wronginfo[ListNo].WrongValue, 1, wronginfo_ReadLeng, wrongfp);
	//故障级别
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + grade_offset, SEEK_SET);
	fread(&wronginfo[ListNo].WrongClass, 1, 1, wrongfp);
	//故障提示存在guide.txt
	// NO.1
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + 7, SEEK_SET);
	fread(guide_buf[0], 1, 3, wrongfp);
	if (atoi(guide_buf[0]))
	{
		fseek(fp, (atoi(guide_buf[0]) - 1) * guide_length + 4, SEEK_SET);
		fread(&wronginfo[ListNo].WrongPrompt[0], 1, 75, fp);
	}
	else
	{
		sprintf(wronginfo[ListNo].WrongPrompt[0], "%s", "");
	}
	// NO.2
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + 11, SEEK_SET);
	fread(guide_buf[1], 1, 3, wrongfp);
	if (atoi(guide_buf[1]))
	{
		fseek(fp, ((atoi(guide_buf[1])) - 1) * guide_length + 4, SEEK_SET);
		fread(&wronginfo[ListNo].WrongPrompt[1], 1, 75, fp);
	}
	else
	{
		sprintf(wronginfo[ListNo].WrongPrompt[1], "%s", "");
	}
	// NO.3
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + 15, SEEK_SET);
	fread(guide_buf[2], 1, 3, wrongfp);
	if (atoi(guide_buf[2]))
	{
		fseek(fp, (atoi(guide_buf[2]) - 1) * guide_length + 4, SEEK_SET);
		fread(&wronginfo[ListNo].WrongPrompt[2], 1, 75, fp);
	}
	else
	{
		sprintf(wronginfo[ListNo].WrongPrompt[2], "%s", "");
	}
	// NO.4
	fseek(wrongfp, (wrong_no - 1) * wronginfo_length + 19, SEEK_SET);
	fread(guide_buf[3], 1, 3, wrongfp);
	if (atoi(guide_buf[3]))
	{
		fseek(fp, (atoi(guide_buf[3]) - 1) * guide_length + 4, SEEK_SET);
		fread(&wronginfo[ListNo].WrongPrompt[3], 1, 75, fp);
	}
	else
	{
		sprintf(wronginfo[ListNo].WrongPrompt[3], "%s", "");
	}
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
//将故障信息存到event.bin文本
static void record_wrong_s(WrongInfo *winfo)
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

		//开始时间
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
		//结束时间
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
		//故障条目在文本中的行目
		temp_short = (short)winfo->WrongCode;
		fwrite(&temp_short, sizeof(short), 1, fp);
		//故障等级
		temp_char = (char)(atoi(winfo->WrongClass));
		fwrite(&temp_char, sizeof(char), 1, fp);
		//故障代码
		temp_short = (short)(atoi(winfo->WrongList));
		fwrite(&temp_short, sizeof(short), 1, fp);
		//故障数目
		fseek(fp, 0, SEEK_SET);
		wrong_len++; //每增加一条故障，l加1
		fwrite(&wrong_len, sizeof(short), 1, fp);
	}
	fclose(fp);
}
//消除故障
static void wrong_dispear(unsigned short wrong_no)
{
	int l, m;
	for (l = 0; l < ListNo; l++)
	{
		if (wrong_no == wronginfo[l].WrongCode) //找到了该故障
		{
			/*故障消除时的时间*/
			wronginfo[l].WrongTimeEnd.tm_year = mvb.get_uchar(0xff, 0);
			wronginfo[l].WrongTimeEnd.tm_mon = mvb.get_uchar(0xff, 1);
			wronginfo[l].WrongTimeEnd.tm_mday = mvb.get_uchar(0xff, 2);
			wronginfo[l].WrongTimeEnd.tm_hour = mvb.get_uchar(0xff, 3);
			wronginfo[l].WrongTimeEnd.tm_min = mvb.get_uchar(0xff, 4);
			wronginfo[l].WrongTimeEnd.tm_sec = mvb.get_uchar(0xff, 5);
			record_wrong_e(&wronginfo[l]);
			//删除此故障
			for (m = l; m < (ListNo - 1); m++)
				wronginfo[m] = wronginfo[m + 1];
			//删掉最后故障的提示信息
			if (ListNo < 1000)
			{
				sprintf(wronginfo[ListNo].WrongPrompt[0], "%s", "");
				sprintf(wronginfo[ListNo].WrongPrompt[1], "%s", "");
				sprintf(wronginfo[ListNo].WrongPrompt[2], "%s", "");
				sprintf(wronginfo[ListNo].WrongPrompt[3], "%s", "");
				sprintf(wronginfo[ListNo - 1].WrongPrompt[0], "%s", "");
				sprintf(wronginfo[ListNo - 1].WrongPrompt[1], "%s", "");
				sprintf(wronginfo[ListNo - 1].WrongPrompt[2], "%s", "");
				sprintf(wronginfo[ListNo - 1].WrongPrompt[3], "%s", "");
			}

			if (ListNo > 0)
				ListNo--;
		}
	}
}
//将wrong记录在file/event.bin中
static void record_wrong_e(WrongInfo *winfo)
{
	FILE *fp;
	char temp_char;
	short temp_short;

	fp = fopen("file/event.bin", "r+b");
	//将wrong记录在file/event.bin中
	if (fp != NULL)
	{
		//开始时间；格式：年月日时分秒
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
		//结束时间
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
		//故障条目在文本中的行目
		temp_short = (short)winfo->WrongCode;
		fwrite(&temp_short, sizeof(short), 1, fp);
		//故障等级
		temp_char = (char)(atoi(winfo->WrongClass));
		fwrite(&temp_char, sizeof(char), 1, fp);
		//故障代码
		temp_short = (short)(atoi(winfo->WrongList));
		fwrite(&temp_short, sizeof(short), 1, fp);
	}
	fclose(fp);
}

//事件信息界面，现存故障上一页按钮
void Wrong_Pre_cb(Fl_Button *, void *)
{
	if (Wrong_Page > 0)
		Wrong_Page--;
	else
		Wrong_Page = char(ListNo / 10); // ListNo现存故障总数,每一页10个故障
}

//事件信息界面,现存故障下一页按钮
void Wrong_Next_cb(Fl_Button *, void *)
{
	Wrong_Page++;
	if (Wrong_Page > (ListNo / 10))
		Wrong_Page = 0;
}

//故障履历上一页；上一页按钮
void Event_Pre_cb(Fl_Button *, void *)
{
	if (Event_Page > 0)
		Event_Page--;
	else
		Event_Page = statbuf.st_size / 304; // 19*16=304，Event_Page<304
}

//故障履历下一页；下一页按钮
void Event_Next_cb(Fl_Button *, void *)
{
	Event_Page++;
	if (Event_Page > (statbuf.st_size / 304))
		Event_Page = 0;
}

//故障履历第一页；第一页按钮
void Event_Page1_cb(Fl_Button *, void *)
{
	Event_Page = 0;
}

//故障履历最后一页；最后页按钮
void Event_PageLast_cb(Fl_Button *, void *)
{
	Event_Page = statbuf.st_size / 304;
}

//故障显示
void wrong_show_cur()
{
	int i;
	int CurrentRow;
	//故障页码纠正
	if (Wrong_Page >= ListNo / 10)
		Wrong_Page = ListNo / 10;
	if (ListNo == 0)
	{
		for (i = 0; i < 10; i++)
		{
			Wrong_Time_butt[i]->label("");
			Wrong_Level_butt[i]->label("");
			Wrong_Text_butt[i]->label("");
			Wrong_Code_butt[i]->label("");
			wrongno[i]->label("");
			Wrong_Time_butt[i]->redraw();
			Wrong_Level_butt[i]->redraw();
			Wrong_Text_butt[i]->redraw();
			Wrong_Code_butt[i]->redraw();
			wrongno[i]->redraw();
		}
		//故障提示
		Wrong_Guide_1->label("");
		Wrong_Guide_2->label("");
		Wrong_Guide_3->label("");
		Wrong_Guide_4->label("");
		Wrong_Guide_1->redraw();
		Wrong_Guide_2->redraw();
		Wrong_Guide_3->redraw();
		Wrong_Guide_4->redraw();
		//总故障条数显示
		Wrong_Total_Number->label("0");
		Wrong_Total_Number->redraw();
		//总故障页数显示
		Wrong_Total_Page->label("0");
		Wrong_Total_Page->redraw();
		//第几页故障显示
		Wrong_NO_Page->label("0");
		Wrong_NO_Page->redraw();
	}
	else
	{
		for (i = 0; i < 10; i++)
		{
			CurrentRow = Wrong_Page * 10 + i;
			sprintf(wrong_time[i], "%04d-%02d-%02d %02d:%02d:%02d", 2000 + wronginfo[CurrentRow].WrongTime.tm_year, wronginfo[CurrentRow].WrongTime.tm_mon, wronginfo[CurrentRow].WrongTime.tm_mday, wronginfo[CurrentRow].WrongTime.tm_hour, wronginfo[CurrentRow].WrongTime.tm_min, wronginfo[CurrentRow].WrongTime.tm_sec);
			Wrong_Time_butt[i]->label(wrong_time[i]);
			Wrong_Level_butt[i]->label(wronginfo[CurrentRow].WrongClass);
			Wrong_Text_butt[i]->label(wronginfo[CurrentRow].WrongValue);
			Wrong_Code_butt[i]->label(wronginfo[CurrentRow].WrongList);
			sprintf(wrong_number[i], "%d", CurrentRow + 1);
			wrongno[i]->label(wrong_number[i]);
			if ((Wrong_Page * 10 + i) >= ListNo)
			{
				Wrong_Time_butt[i]->label("");
				Wrong_Level_butt[i]->label("");
				Wrong_Text_butt[i]->label("");
				Wrong_Code_butt[i]->label("");
				wrongno[i]->label("");
			}
			Wrong_Time_butt[i]->redraw();
			Wrong_Level_butt[i]->redraw();
			Wrong_Text_butt[i]->redraw();
			Wrong_Code_butt[i]->redraw();
			wrongno[i]->redraw();
			//故障提示
			Wrong_Guide_1->label(wronginfo[Wrong_Page * 10 + row - 1].WrongPrompt[0]);
			Wrong_Guide_2->label(wronginfo[Wrong_Page * 10 + row - 1].WrongPrompt[1]);
			Wrong_Guide_3->label(wronginfo[Wrong_Page * 10 + row - 1].WrongPrompt[2]);
			Wrong_Guide_4->label(wronginfo[Wrong_Page * 10 + row - 1].WrongPrompt[3]);
			Wrong_Guide_1->redraw();
			Wrong_Guide_2->redraw();
			Wrong_Guide_3->redraw();
			Wrong_Guide_4->redraw();
			//总故障条数显示
			sprintf(Wrong_Total_Number_Temp, "%d", ListNo);
			Wrong_Total_Number->label(Wrong_Total_Number_Temp);
			Wrong_Total_Number->redraw();
			//总故障页数显示
			sprintf(Wrong_Total_Page_Temp, "%d", ListNo / 10 + 1);
			Wrong_Total_Page->label(Wrong_Total_Page_Temp);
			Wrong_Total_Page->redraw();
			//第几页故障显示
			sprintf(Wrong_NO_Page_Temp, "%d", Wrong_Page + 1);
			Wrong_NO_Page->label(Wrong_NO_Page_Temp);
			Wrong_NO_Page->redraw();
		}
	}
}

void event_show_cur()
{
	int i;
	int CurrentRow1;
	for (i = 0; i < 16; i++)
	{
		CurrentRow1 = Event_Page * 16 + i;
		Event_Code_Box[i]->label(wrongrecordinfo[CurrentRow1].WrongList);
		sprintf(event_date[i], "%04d-%02d-%02d", wrongrecordinfo[CurrentRow1].WrongTime.tm_year, wrongrecordinfo[CurrentRow1].WrongTime.tm_mon, wrongrecordinfo[CurrentRow1].WrongTime.tm_mday);
		Event_Date_Box[i]->label(event_date[i]);
		sprintf(event_time[i], "%02d:%02d:%02d", wrongrecordinfo[CurrentRow1].WrongTime.tm_hour, wrongrecordinfo[CurrentRow1].WrongTime.tm_min, wrongrecordinfo[CurrentRow1].WrongTime.tm_sec);
		Event_Time_Box[i]->label(event_time[i]);
		Event_Level_Box[i]->label(wrongrecordinfo[CurrentRow1].WrongClass);
		Event_Text_Box[i]->label(wrongrecordinfo[CurrentRow1].WrongValue);
		sprintf(event_number[i], "%d", CurrentRow1 + 1);
		Event_No[i]->label(event_number[i]);
		if ((Event_Page * 16 + i) > (statbuf.st_size / 19 - 1))
		{
			Event_Code_Box[i]->label("");
			Event_Date_Box[i]->label("");
			Event_Time_Box[i]->label("");
			Event_Level_Box[i]->label("");
			Event_Text_Box[i]->label("");
			Event_No[i]->label("");
		}
		Event_Code_Box[i]->redraw();
		Event_Date_Box[i]->redraw();
		Event_Time_Box[i]->redraw();
		Event_Level_Box[i]->redraw();
		Event_Text_Box[i]->redraw();
		Event_No[i]->redraw();
	}
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
			fread(wrongrecordinfo[i].WrongValue, 1, wronginfo_ReadLeng, wrongfp);
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

void wrong_select_cb(Fl_Button *o, long i)
{
	row = i;
	for (int k = 0; k < 10; k++)
	{
		Wrong_Text_butt[k]->value(0);
		Wrong_Code_butt[k]->value(0);
		Wrong_Level_butt[k]->value(0);
		Wrong_Time_butt[k]->value(0);
	}
	Wrong_Text_butt[row - 1]->value(1);
	Wrong_Code_butt[row - 1]->value(1);
	Wrong_Level_butt[row - 1]->value(1);
	Wrong_Time_butt[row - 1]->value(1);
	//故障建议和措施显示
	Wrong_Guide_1->label(wronginfo[Wrong_Page * 10 + row - 1].WrongPrompt[0]);
	Wrong_Guide_2->label(wronginfo[Wrong_Page * 10 + row - 1].WrongPrompt[1]);
	Wrong_Guide_3->label(wronginfo[Wrong_Page * 10 + row - 1].WrongPrompt[2]);
	Wrong_Guide_4->label(wronginfo[Wrong_Page * 10 + row - 1].WrongPrompt[3]);
	Wrong_Guide_1->redraw();
	Wrong_Guide_2->redraw();
	Wrong_Guide_3->redraw();
	Wrong_Guide_4->redraw();
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

//显示中等和严重故障总数及已确认的数目
static void get_confirmno()
{
	static char buf_confirmno[10];

	sprintf(buf_confirmno, "%d/%d", count, ListNo - get_cnum());
	wrong_alarm_numaaa->label(buf_confirmno);
	wrong_alarm_numaaa->redraw();
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
		wrong_main_alarm->label("");
		wrong_main_alarm->redraw();
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
						if (Buzzer_Switch_No == 1)
						{
							BuzzerOn();
						}
					}
					else if (atoi(wronginfo[i].WrongClass) == 2) //中等故障
					{
						wrong_main_alarm->color(FL_YELLOW);
						wrong_main_alarm->labelcolor(FL_BLACK);
						wrong_main_alarm->label(wrong_base);
						if (Buzzer_Switch_No == 1)
						{
							// Count_Medium++;
							// if(Count_Medium==8)
							{
								BuzzerOn();
								usleep(50000);
								BuzzerOff();
								Count_Medium = 0;
							}
						}
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
						BuzzerOff();
					}
					select_ok++;
				}
			}
		}
	}

	//显示中等和严重故障总数及已确认的数目函数调用
	get_confirmno();
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

//切换至事件信息界面
void main_wrong_cb(Fl_Button *, void *)
{
	if (!group_wrong_window->visible())
	{
		group_wrong_window->show();
		group_maintenance_top->hide();
		group_top->show();
		label_window->label("事件信息");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_wrong_window;
		Wrong_Page = 0; //初始页数为0
	}
}

//维护界面切换至事件记录查询界面
void event_cb(Fl_Button *, void *)
{
	if (!group_event_window->visible())
	{
		group_event_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--事件记录查询");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_event_window;

		wrongrecord_init();
	}
}

//事件记录查询界面切换至维护界面;返回按钮
void event_return_cb(Fl_Button *, void *)
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
