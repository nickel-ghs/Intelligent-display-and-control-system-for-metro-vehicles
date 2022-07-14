#include "head.h"
#include <stdlib.h>

static unsigned short port = 0x01;
static char portlabel[10] = "";
static unsigned char portNo = 4;

// Del按钮
void searchdata_del_cb(Fl_Button *, void *)
{
	searchdata_input->value("");
}

//数字输入按钮0~F
void searchdata_number_cb(Fl_Button *o, void *)
{
	searchdata_input->insert(o->label(), 0);
}

//"开始查找按钮"
void searchdata_search_cb(Fl_Button *, void *)
{
	for (int i = 0; i < 200; i++)
	{
		if (short(strtol(searchdata_input->value(), NULL, 16)) == pit_num[i]) //查找到
		{
			port = short(strtol(searchdata_input->value(), NULL, 16));
			sprintf(portlabel, "%x", port);

			searchdata_label->label(portlabel);
			searchdata_input->value("");
			portNo = pit_size[i];
			break;
		}
	}
}
// bit 16行x18列
//初始化
void portdata_proccess()
{
	// printf("port=%d,portNo=%d value=%d,value=%d\n",port,portNo,mvb.get_ushort(port,0),mvb.get_ushort(160,0));
	Fl_Value_Output *box[48];
	Fl_Value_Output *output[256];
	unsigned char temp;
	if (portNo == 0)
		temp = 2;
	else if (portNo == 1)
		temp = 4;
	else if (portNo == 2)
		temp = 8;
	else if (portNo == 3)
		temp = 16;
	else if (portNo == 4)
		temp = 32;

	box[0] = value_d0;
	box[1] = value_d2;
	box[2] = value_d4;
	box[3] = value_d6;
	box[4] = value_d8;
	box[5] = value_d10;
	box[6] = value_d12;
	box[7] = value_d14;
	box[8] = value_d16;
	box[9] = value_d18;
	box[10] = value_d20;
	box[11] = value_d22;
	box[12] = value_d24;
	box[13] = value_d26;
	box[14] = value_d28;
	box[15] = value_d30;

	box[16] = value_w0;
	box[17] = value_w1;
	box[18] = value_w2;
	box[19] = value_w3;
	box[20] = value_w4;
	box[21] = value_w5;
	box[22] = value_w6;
	box[23] = value_w7;
	box[24] = value_w8;
	box[25] = value_w9;
	box[26] = value_w10;
	box[27] = value_w11;
	box[28] = value_w12;
	box[29] = value_w13;
	box[30] = value_w14;
	box[31] = value_w15;
	box[32] = value_w16;
	box[33] = value_w17;
	box[34] = value_w18;
	box[35] = value_w19;
	box[36] = value_w20;
	box[37] = value_w21;
	box[38] = value_w22;
	box[39] = value_w23;
	box[40] = value_w24;
	box[41] = value_w25;
	box[42] = value_w26;
	box[43] = value_w27;
	box[44] = value_w28;
	box[45] = value_w29;
	box[46] = value_w30;
	box[47] = value_w31;

	output[0] = bit0000;
	output[1] = bit0001;
	output[2] = bit0002;
	output[3] = bit0003;
	output[4] = bit0004;
	output[5] = bit0005;
	output[6] = bit0006;
	output[7] = bit0007;
	output[8] = bit0008;
	output[9] = bit0009;
	output[10] = bit0010;
	output[11] = bit0011;
	output[12] = bit0012;
	output[13] = bit0013;
	output[14] = bit0014;
	output[15] = bit0015;
	output[16] = bit0200;
	output[17] = bit0201;
	output[18] = bit0202;
	output[19] = bit0203;
	output[20] = bit0204;
	output[21] = bit0205;
	output[22] = bit0206;
	output[23] = bit0207;
	output[24] = bit0208;
	output[25] = bit0209;
	output[26] = bit0210;
	output[27] = bit0211;
	output[28] = bit0212;
	output[29] = bit0213;
	output[30] = bit0214;
	output[31] = bit0215;
	output[32] = bit0400;
	output[33] = bit0401;
	output[34] = bit0402;
	output[35] = bit0403;
	output[36] = bit0404;
	output[37] = bit0405;
	output[38] = bit0406;
	output[39] = bit0407;
	output[40] = bit0408;
	output[41] = bit0409;
	output[42] = bit0410;
	output[43] = bit0411;
	output[44] = bit0412;
	output[45] = bit0413;
	output[46] = bit0414;
	output[47] = bit0415;
	output[48] = bit0600;
	output[49] = bit0601;
	output[50] = bit0602;
	output[51] = bit0603;
	output[52] = bit0604;
	output[53] = bit0605;
	output[54] = bit0606;
	output[55] = bit0607;
	output[56] = bit0608;
	output[57] = bit0609;
	output[58] = bit0610;
	output[59] = bit0611;
	output[60] = bit0612;
	output[61] = bit0613;
	output[62] = bit0614;
	output[63] = bit0615;
	output[64] = bit0800;
	output[65] = bit0801;
	output[66] = bit0802;
	output[67] = bit0803;
	output[68] = bit0804;
	output[69] = bit0805;
	output[70] = bit0806;
	output[71] = bit0807;
	output[72] = bit0808;
	output[73] = bit0809;
	output[74] = bit0810;
	output[75] = bit0811;
	output[76] = bit0812;
	output[77] = bit0813;
	output[78] = bit0814;
	output[79] = bit0815;
	output[80] = bit1000;
	output[81] = bit1001;
	output[82] = bit1002;
	output[83] = bit1003;
	output[84] = bit1004;
	output[85] = bit1005;
	output[86] = bit1006;
	output[87] = bit1007;
	output[88] = bit1008;
	output[89] = bit1009;
	output[90] = bit1010;
	output[91] = bit1011;
	output[92] = bit1012;
	output[93] = bit1013;
	output[94] = bit1014;
	output[95] = bit1015;
	output[96] = bit1200;
	output[97] = bit1201;
	output[98] = bit1202;
	output[99] = bit1203;
	output[100] = bit1204;
	output[101] = bit1205;
	output[102] = bit1206;
	output[103] = bit1207;
	output[104] = bit1208;
	output[105] = bit1209;
	output[106] = bit1210;
	output[107] = bit1211;
	output[108] = bit1212;
	output[109] = bit1213;
	output[110] = bit1214;
	output[111] = bit1215;
	output[112] = bit1400;
	output[113] = bit1401;
	output[114] = bit1402;
	output[115] = bit1403;
	output[116] = bit1404;
	output[117] = bit1405;
	output[118] = bit1406;
	output[119] = bit1407;
	output[120] = bit1408;
	output[121] = bit1409;
	output[122] = bit1410;
	output[123] = bit1411;
	output[124] = bit1412;
	output[125] = bit1413;
	output[126] = bit1414;
	output[127] = bit1415;
	output[128] = bit1600;
	output[129] = bit1601;
	output[130] = bit1602;
	output[131] = bit1603;
	output[132] = bit1604;
	output[133] = bit1605;
	output[134] = bit1606;
	output[135] = bit1607;
	output[136] = bit1608;
	output[137] = bit1609;
	output[138] = bit1610;
	output[139] = bit1611;
	output[140] = bit1612;
	output[141] = bit1613;
	output[142] = bit1614;
	output[143] = bit1615;
	output[144] = bit1800;
	output[145] = bit1801;
	output[146] = bit1802;
	output[147] = bit1803;
	output[148] = bit1804;
	output[149] = bit1805;
	output[150] = bit1806;
	output[151] = bit1807;
	output[152] = bit1808;
	output[153] = bit1809;
	output[154] = bit1810;
	output[155] = bit1811;
	output[156] = bit1812;
	output[157] = bit1813;
	output[158] = bit1814;
	output[159] = bit1815;
	output[160] = bit2000;
	output[161] = bit2001;
	output[162] = bit2002;
	output[163] = bit2003;
	output[164] = bit2004;
	output[165] = bit2005;
	output[166] = bit2006;
	output[167] = bit2007;
	output[168] = bit2008;
	output[169] = bit2009;
	output[170] = bit2010;
	output[171] = bit2011;
	output[172] = bit2012;
	output[173] = bit2013;
	output[174] = bit2014;
	output[175] = bit2015;
	output[176] = bit2200;
	output[177] = bit2201;
	output[178] = bit2202;
	output[179] = bit2203;
	output[180] = bit2204;
	output[181] = bit2205;
	output[182] = bit2206;
	output[183] = bit2207;
	output[184] = bit2208;
	output[185] = bit2209;
	output[186] = bit2210;
	output[187] = bit2211;
	output[188] = bit2212;
	output[189] = bit2213;
	output[190] = bit2214;
	output[191] = bit2215;
	output[192] = bit2400;
	output[193] = bit2401;
	output[194] = bit2402;
	output[195] = bit2403;
	output[196] = bit2404;
	output[197] = bit2405;
	output[198] = bit2406;
	output[199] = bit2407;
	output[200] = bit2408;
	output[201] = bit2409;
	output[202] = bit2410;
	output[203] = bit2411;
	output[204] = bit2412;
	output[205] = bit2413;
	output[206] = bit2414;
	output[207] = bit2415;
	output[208] = bit2600;
	output[209] = bit2601;
	output[210] = bit2602;
	output[211] = bit2603;
	output[212] = bit2604;
	output[213] = bit2605;
	output[214] = bit2606;
	output[215] = bit2607;
	output[216] = bit2608;
	output[217] = bit2609;
	output[218] = bit2610;
	output[219] = bit2611;
	output[220] = bit2612;
	output[221] = bit2613;
	output[222] = bit2614;
	output[223] = bit2615;
	output[224] = bit2800;
	output[225] = bit2801;
	output[226] = bit2802;
	output[227] = bit2803;
	output[228] = bit2804;
	output[229] = bit2805;
	output[230] = bit2806;
	output[231] = bit2807;
	output[232] = bit2808;
	output[233] = bit2809;
	output[234] = bit2810;
	output[235] = bit2811;
	output[236] = bit2812;
	output[237] = bit2813;
	output[238] = bit2814;
	output[239] = bit2815;
	output[240] = bit3000;
	output[241] = bit3001;
	output[242] = bit3002;
	output[243] = bit3003;
	output[244] = bit3004;
	output[245] = bit3005;
	output[246] = bit3006;
	output[247] = bit3007;
	output[248] = bit3008;
	output[249] = bit3009;
	output[250] = bit3010;
	output[251] = bit3011;
	output[252] = bit3012;
	output[253] = bit3013;
	output[254] = bit3014;
	output[255] = bit3015;

	for (int i = 0; i < (temp / 2); i++)
	{
		box[i]->value(mvb.get_ushort(port, i * 2));
	}
	for (int ii = (temp / 2); ii < 16; ii++)
	{
		box[ii]->value(0);
	}

	for (int j = 16; j < (temp + 16); j++)
	{
		box[j]->value(mvb.get_uchar(port, j - 16));
	}
	for (int jj = (temp + 16); jj < 48; jj++)
	{
		box[jj]->value(0);
	}

	for (int m = 0; m < (temp * 8); m++)
	{
		output[m]->value(mvb.get_ubit(port, m / 8, m % 8));
	}
	for (int mm = (temp * 8); mm < 256; mm++)
	{
		output[mm]->value(0);
	}
	portdata_overview_window->redraw();
}
