#include "head.h"
#include "station_set.h"
char station_set_name[30][20] = {{"------ "}, {"高桥西"}, {"高桥"}, {"梁祝"}, {"芦港"}, {"徐家漕长乐"}, {"望春桥"}, {"泽民"}, {"大卿桥"}, {"西门口"}, {"鼓楼"}, {"东门口(天一广场)"}, {"江厦桥东"}, {"舟孟北路"}, {"樱花公园"}, {"福明路"}, {"世纪大道"}, {"海晏北路"}, {"福庆北路"}, {"盛莫路"}, {"东环南路"}, {"邱隘"}, {"五乡"}, {"宝幢"}, {"邬隘"}, {"大契"}, {"松花江路"}, {"中河路"}, {"长江路"}, {"霞浦"}};
//起始站向下翻页
void Station_Set_Start_Next_cb(Fl_Button *, void *)
{
	if (Station_Set_Start_Page < 3)
		Station_Set_Start_Page++;
	else
		Station_Set_Start_Page = 3;
	Station_Set_Start_Page_Name();
}

//起始站向上翻页
void Station_Set_Start_Pre_cb(Fl_Button *, void *)
{
	if (Station_Set_Start_Page > 0)
		Station_Set_Start_Page--;
	else
		Station_Set_Start_Page = 0;
	Station_Set_Start_Page_Name();
}

//终点站向下翻页
void Station_Set_End_Next_cb(Fl_Button *, void *)
{
	if (Station_Set_End_Page < 3)
		Station_Set_End_Page++;
	else
		Station_Set_End_Page = 3;
	Station_Set_End_Page_Name();
}

//终点站向上翻页
void Station_Set_End_Pre_cb(Fl_Button *, void *)
{
	if (Station_Set_End_Page > 0)
		Station_Set_End_Page--;
	else
		Station_Set_End_Page = 0;
	Station_Set_End_Page_Name();
}

void Station_Set_Start_Page_Name()
{
	for (int i = 1; i <= 8; i++)
	{
		if ((Station_Set_Start_Page * 8 + i) != 25)
		{
			StationSet_Start_Name[i]->image(NULL);
			StationSet_Start_Name[i]->label(station_set_name[Station_Set_Start_Page * 8 + i]);
			StationSet_Start_Name[i]->redraw();
		}
		else
		{
			StationSet_Start_Name[i]->label(NULL);
			StationSet_Start_Name[i]->image(Station_DaQi[1]);
			StationSet_Start_Name[i]->redraw();
		}
	}
	if (Station_Set_Start_Page == 3)
	{
		for (int j = 6; j <= 8; j++)
		{
			StationSet_Start_Name[j]->label(NULL);
			StationSet_Start_Name[j]->label("");
			StationSet_Start_Name[j]->redraw();
		}
	}
}

void Station_Set_End_Page_Name()
{
	for (int i = 1; i <= 8; i++)
	{
		if ((Station_Set_End_Page * 8 + i) != 25)
		{
			StationSet_End_Name[i]->image(NULL);
			StationSet_End_Name[i]->label(station_set_name[Station_Set_End_Page * 8 + i]);
			StationSet_End_Name[i]->redraw();
		}
		else
		{
			StationSet_End_Name[i]->label(NULL);
			StationSet_End_Name[i]->image(Station_DaQi[1]);
			StationSet_End_Name[i]->redraw();
		}
	}
	if (Station_Set_End_Page == 3)
	{
		for (int j = 6; j <= 8; j++)
		{
			StationSet_End_Name[j]->image(NULL);
			StationSet_End_Name[j]->label("");
			StationSet_End_Name[j]->redraw();
		}
	}
}

//选择起始站
void Station_Set_Start_No_cb(Fl_Button *, long i)
{
	Station_Set_Start_No = Station_Set_Start_Page * 8 + i;
}

//选择终点站
void Station_Set_End_No_cb(Fl_Button *, long i)
{
	Station_Set_End_No = Station_Set_End_Page * 8 + i;
}

//线路设置确认
void Station_Set_Confirm_cb(Fl_Button *, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;

	mvb.put_ushort(port, 4, Station_Set_Start_No);
	mvb.put_ushort(port, 6, Station_Set_End_No);
	mvb.put_ubit(port, 12, 2, 1);
	mvb.put_ubit(port, 12, 3, 1);
	station_Set_Flag = 1;
	mvb.lp_put_alldata();
}

void station_set_proccess()
{
	//当前站
	if (mvb.get_ushort(0x01, 0) < 30 && mvb.get_ushort(0x01, 0) != 25)
	{
		Station_Set_Current_Top->image(NULL);
		Station_Set_Current_Top->labelcolor(fl_rgb_color(87, 180, 227));
		Station_Set_Current_Top->label(station_set_name[mvb.get_ushort(0x01, 0)]);
	}
	else if (mvb.get_ushort(0x01, 0) == 25)
	{
		Station_Set_Current_Top->label(NULL);
		Station_Set_Current_Top->image(Station_DaQi[0]);
	}
	else
	{
		Station_Set_Current_Top->labelcolor(fl_rgb_color(87, 180, 227));
		Station_Set_Current_Top->label(" - - - - - ");
		Station_Set_Current_Top->image(NULL);
	}
	//终点站
	if (mvb.get_ushort(0x01, 2) < 30 && mvb.get_ushort(0x01, 2) != 25)
	{
		Station_Set_End_Top->image(NULL);
		Station_Set_End_Top->labelcolor(fl_rgb_color(87, 180, 227));
		Station_Set_End_Top->label(station_set_name[mvb.get_ushort(0x01, 2)]);
	}
	else if (mvb.get_ushort(0x01, 2) == 25)
	{
		Station_Set_End_Top->label(NULL);
		Station_Set_End_Top->image(Station_DaQi[0]);
	}
	else
	{
		Station_Set_End_Top->labelcolor(fl_rgb_color(87, 180, 227));
		Station_Set_End_Top->label(" - - - - - ");
		Station_Set_End_Top->image(NULL);
	}

	Station_Set_Current_Top->redraw();
	Station_Set_End_Top->redraw();
	Station_Set_Start_Page_Name();
	Station_Set_End_Page_Name();
}
