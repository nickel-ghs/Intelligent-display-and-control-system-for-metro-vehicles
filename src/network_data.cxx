#include "head.h"
static char Net_Number_Buff[6][10]; //车辆号临时存储值

//网络拓扑界面
void net_proccess()
{
	unsigned short port;
	int Net_Car_ID = 0;
	//画车辆号
	for (Net_Car_ID = 0; Net_Car_ID < 6; Net_Car_ID++)
	{
		{
			if ((mvb.get_ushort(0x3A, Net_Car_ID * 4) * 65536 + mvb.get_ushort(0x3A, Net_Car_ID * 4 + 2)) > 0)
			{
				sprintf(Net_Number_Buff[Net_Car_ID], "%06d", mvb.get_ushort(0x3A, Net_Car_ID * 4) * 65536 + mvb.get_ushort(0x3A, Net_Car_ID * 4 + 2));
				Net_Number[Net_Car_ID]->label(Net_Number_Buff[Net_Car_ID]);
			}
			else
			{
				Net_Number[Net_Car_ID]->label("000000");
			}
			Net_Number[Net_Car_ID]->redraw();
		}
	}

	port = 0x02;

	if (mvb.get_ubit(port, 13, 0))
		vcm_1->label("VCM(M)");
	else
		vcm_1->label("VCM");

	if (mvb.get_ubit(port, 13, 1))
		vcm_6->label("VCM(M)");
	else
		vcm_6->label("VCM");

	vcm_1->redraw();
	vcm_6->redraw();

	// 1车
	if (mvb.get_ubit(port, 1, 0) == 1)
		vcm_1->color(FL_GREEN);
	else
		vcm_1->color(FL_RED);

	if (mvb.get_ubit(port, 1, 2) == 1)
		edrm_1->color(FL_GREEN);
	else
		edrm_1->color(FL_RED);

	if (mvb.get_ubit(port, 1, 3) == 1)
		dxm1_1->color(FL_GREEN);
	else
		dxm1_1->color(FL_RED);

	if (mvb.get_ubit(port, 1, 4) == 1)
		dxm2_1->color(FL_GREEN);
	else
		dxm2_1->color(FL_RED);

	if (mvb.get_ubit(port, 1, 5) == 1)
		dim_1->color(FL_GREEN);
	else
		dim_1->color(FL_RED);

	if (mvb.get_ubit(port, 1, 6) == 1)
		axm_1->color(FL_GREEN);
	else
		axm_1->color(FL_RED);

	if (mvb.get_ubit(port, 1, 7) == 1)
		hmi_1->color(FL_GREEN);
	else
		hmi_1->color(FL_RED);

	if (mvb.get_ubit(port, 0, 0) == 1)
		siv_1->color(FL_GREEN);
	else
		siv_1->color(FL_RED);

	if (mvb.get_ubit(port, 0, 1) == 1)
		pis_1->color(FL_GREEN);
	else
		pis_1->color(FL_RED);

	if (mvb.get_ubit(port, 0, 2) == 1)
		atc_1->color(FL_GREEN);
	else
		atc_1->color(FL_RED);

	if (mvb.get_ubit(port, 0, 3) == 1)
		hvac_1->color(FL_GREEN);
	else
		hvac_1->color(FL_RED);

	if (mvb.get_ubit(port, 0, 4) == 1)
		edcu1_1->color(FL_GREEN);
	else
		edcu1_1->color(FL_RED);

	if (mvb.get_ubit(port, 0, 5) == 1)
		edcu2_1->color(FL_GREEN);
	else
		edcu2_1->color(FL_RED);

	if (mvb.get_ubit(port, 0, 6) == 1)
		bcu_1->color(FL_GREEN);
	else
		bcu_1->color(FL_RED);

	vcm_1->redraw();
	edrm_1->redraw();
	dxm1_1->redraw();
	dxm2_1->redraw();
	dim_1->redraw();
	axm_1->redraw();
	hmi_1->redraw();
	siv_1->redraw();
	pis_1->redraw();
	atc_1->redraw();
	hvac_1->redraw();
	edcu1_1->redraw();
	edcu2_1->redraw();
	bcu_1->redraw();

	// 2车
	if (mvb.get_ubit(port, 3, 3) == 1)
		dxm1_2->color(FL_GREEN);
	else
		dxm1_2->color(FL_RED);

	if (mvb.get_ubit(port, 3, 4) == 1)
		dxm2_2->color(FL_GREEN);
	else
		dxm2_2->color(FL_RED);

	if (mvb.get_ubit(port, 2, 0) == 1)
		dcu_2->color(FL_GREEN);
	else
		dcu_2->color(FL_RED);

	if (mvb.get_ubit(port, 2, 3) == 1)
		hvac_2->color(FL_GREEN);
	else
		hvac_2->color(FL_RED);

	if (mvb.get_ubit(port, 2, 4) == 1)
		edcu1_2->color(FL_GREEN);
	else
		edcu1_2->color(FL_RED);

	if (mvb.get_ubit(port, 2, 5) == 1)
		edcu2_2->color(FL_GREEN);
	else
		edcu2_2->color(FL_RED);

	dxm1_2->redraw();
	dxm2_2->redraw();
	dcu_2->redraw();
	hvac_2->redraw();
	edcu1_2->redraw();
	edcu2_2->redraw();

	// 3车
	if (mvb.get_ubit(port, 5, 3) == 1)
		dxm1_3->color(FL_GREEN);
	else
		dxm1_3->color(FL_RED);

	if (mvb.get_ubit(port, 5, 4) == 1)
		dxm2_3->color(FL_GREEN);
	else
		dxm2_3->color(FL_RED);

	if (mvb.get_ubit(port, 4, 0) == 1)
		dcu_3->color(FL_GREEN);
	else
		dcu_3->color(FL_RED);

	if (mvb.get_ubit(port, 4, 3) == 1)
		hvac_3->color(FL_GREEN);
	else
		hvac_3->color(FL_RED);

	if (mvb.get_ubit(port, 4, 4) == 1)
		edcu1_3->color(FL_GREEN);
	else
		edcu1_3->color(FL_RED);

	if (mvb.get_ubit(port, 4, 5) == 1)
		edcu2_3->color(FL_GREEN);
	else
		edcu2_3->color(FL_RED);

	if (mvb.get_ubit(port, 4, 6) == 1)
		bcu_3->color(FL_GREEN);
	else
		bcu_3->color(FL_RED);

	dxm1_3->redraw();
	dxm2_3->redraw();
	dcu_3->redraw();
	hvac_3->redraw();
	edcu1_3->redraw();
	edcu2_3->redraw();
	bcu_3->redraw();

	// 4车
	if (mvb.get_ubit(port, 7, 3) == 1)
		dxm1_4->color(FL_GREEN);
	else
		dxm1_4->color(FL_RED);

	if (mvb.get_ubit(port, 7, 4) == 1)
		dxm2_4->color(FL_GREEN);
	else
		dxm2_4->color(FL_RED);

	if (mvb.get_ubit(port, 6, 0) == 1)
		dcu_4->color(FL_GREEN);
	else
		dcu_4->color(FL_RED);

	if (mvb.get_ubit(port, 6, 3) == 1)
		hvac_4->color(FL_GREEN);
	else
		hvac_4->color(FL_RED);

	if (mvb.get_ubit(port, 6, 4) == 1)
		edcu1_4->color(FL_GREEN);
	else
		edcu1_4->color(FL_RED);

	if (mvb.get_ubit(port, 6, 5) == 1)
		edcu2_4->color(FL_GREEN);
	else
		edcu2_4->color(FL_RED);

	if (mvb.get_ubit(port, 6, 6) == 1)
		bcu_4->color(FL_GREEN);
	else
		bcu_4->color(FL_RED);

	dxm1_4->redraw();
	dxm2_4->redraw();
	dcu_4->redraw();
	hvac_4->redraw();
	edcu1_4->redraw();
	edcu2_4->redraw();
	bcu_4->redraw();

	// 5车
	if (mvb.get_ubit(port, 9, 3) == 1)
		dxm1_5->color(FL_GREEN);
	else
		dxm1_5->color(FL_RED);

	if (mvb.get_ubit(port, 9, 4) == 1)
		dxm2_5->color(FL_GREEN);
	else
		dxm2_5->color(FL_RED);

	if (mvb.get_ubit(port, 8, 0) == 1)
		dcu_5->color(FL_GREEN);
	else
		dcu_5->color(FL_RED);

	if (mvb.get_ubit(port, 8, 3) == 1)
		hvac_5->color(FL_GREEN);
	else
		hvac_5->color(FL_RED);

	if (mvb.get_ubit(port, 8, 4) == 1)
		edcu1_5->color(FL_GREEN);
	else
		edcu1_5->color(FL_RED);

	if (mvb.get_ubit(port, 8, 5) == 1)
		edcu2_5->color(FL_GREEN);
	else
		edcu2_5->color(FL_RED);

	dxm1_5->redraw();
	dxm2_5->redraw();
	dcu_5->redraw();
	hvac_5->redraw();
	edcu1_5->redraw();
	edcu2_5->redraw();

	// 6车
	if (mvb.get_ubit(port, 11, 0) == 1)
		vcm_6->color(FL_GREEN);
	else
		vcm_6->color(FL_RED);

	if (mvb.get_ubit(port, 11, 2) == 1)
		edrm_6->color(FL_GREEN);
	else
		edrm_6->color(FL_RED);

	if (mvb.get_ubit(port, 11, 3) == 1)
		dxm1_6->color(FL_GREEN);
	else
		dxm1_6->color(FL_RED);

	if (mvb.get_ubit(port, 11, 4) == 1)
		dxm2_6->color(FL_GREEN);
	else
		dxm2_6->color(FL_RED);

	if (mvb.get_ubit(port, 11, 5) == 1)
		dim_6->color(FL_GREEN);
	else
		dim_6->color(FL_RED);

	if (mvb.get_ubit(port, 11, 6) == 1)
		axm_6->color(FL_GREEN);
	else
		axm_6->color(FL_RED);

	if (mvb.get_ubit(port, 11, 7) == 1)
		hmi_6->color(FL_GREEN);
	else
		hmi_6->color(FL_RED);

	if (mvb.get_ubit(port, 10, 0) == 1)
		siv_6->color(FL_GREEN);
	else
		siv_6->color(FL_RED);

	if (mvb.get_ubit(port, 10, 1) == 1)
		pis_6->color(FL_GREEN);
	else
		pis_6->color(FL_RED);

	if (mvb.get_ubit(port, 10, 2) == 1)
		atc_6->color(FL_GREEN);
	else
		atc_6->color(FL_RED);

	if (mvb.get_ubit(port, 10, 3) == 1)
		hvac_6->color(FL_GREEN);
	else
		hvac_6->color(FL_RED);

	if (mvb.get_ubit(port, 10, 4) == 1)
		edcu1_6->color(FL_GREEN);
	else
		edcu1_6->color(FL_RED);

	if (mvb.get_ubit(port, 10, 5) == 1)
		edcu2_6->color(FL_GREEN);
	else
		edcu2_6->color(FL_RED);

	if (mvb.get_ubit(port, 10, 6) == 1)
		bcu_6->color(FL_GREEN);
	else
		bcu_6->color(FL_RED);

	vcm_6->redraw();
	edrm_6->redraw();
	dxm1_6->redraw();
	dxm2_6->redraw();
	dim_6->redraw();
	axm_6->redraw();
	hmi_6->redraw();
	siv_6->redraw();
	pis_6->redraw();
	atc_6->redraw();
	hvac_6->redraw();
	edcu1_6->redraw();
	edcu2_6->redraw();
	bcu_6->redraw();
}
