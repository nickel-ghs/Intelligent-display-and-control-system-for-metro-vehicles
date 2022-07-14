#include "head.h"
#include "line.h"

//站点名称
char line_station_name[30][20] = {{"------ "}, {"高桥西"}, {"高桥"}, {"梁祝"}, {"芦港"}, {"徐家漕长乐"}, {"望春桥"}, {"泽民"}, {"大卿桥"}, {"西门口"}, {"鼓楼"}, {"东门口(天一广场)"}, {"江厦桥东"}, {"舟孟北路"}, {"樱花公园"}, {"福明路"}, {"世纪大道"}, {"海晏北路"}, {"福庆北路"}, {"盛莫路"}, {"东环南路"}, {"邱隘"}, {"五乡"}, {"宝幢"}, {"邬隘"}, {"大契"}, {"松花江路"}, {"中河路"}, {"长江路"}, {"霞浦"}};

unsigned int templine_num[10][2] = {
	{1, 20}, //表示路线1:高桥西为第一个，东环南路为第20个
	{20, 1}, //表示路线2:东环南路为第20个,高桥西为第一个，
	{1, 29},
	{29, 1},
	{6, 23},
	{23, 6},
	{6, 20},
	{20, 6}};
//选择站点，8个长条框按钮的回调函数
void Line_Select_cb(Fl_Button *, long i)
{
	Line_Select_No = i;
}

//线路设置确认
void Line_Confirm_cb(Fl_Button *, void *)
{
	unsigned short port;
	port = tc_no > 1 ? 0x6b0 : 0x1b0;
	//数据组装并发送
	mvb.put_ushort(port, 8, Line_Select_No);
	mvb.put_ushort(port, 4, templine_num[Line_Select_No - 1][0]); //起始点
	mvb.put_ushort(port, 6, templine_num[Line_Select_No - 1][1]); //目的点
	mvb.put_ubit(port, 12, 4, 1);
	Line_Select_Flag = 1;
	mvb.lp_put_alldata();
}

//界面处理函数，设置界面-->线路/车站选择-->选站
void line_proccess()
{
	//当前站
	if (mvb.get_ushort(0x01, 0) < 30 && mvb.get_ushort(0x01, 0) != 25) //从0x01端口取0位
	{
		Line_Current_Box->image(NULL);							  //图片设置为没
		Line_Current_Box->labelcolor(fl_rgb_color(87, 180, 227)); //选中的窗口变色--蓝紫色
		Line_Current_Box->label(line_station_name[mvb.get_ushort(0x01, 0)]);
	}
	else if (mvb.get_ushort(0x01, 0) == 25)
	{
		Line_Current_Box->label(NULL);
		Line_Current_Box->image(Station_DaQi[0]);
	}
	else
	{
		Line_Current_Box->labelcolor(fl_rgb_color(87, 180, 227));
		Line_Current_Box->label(" - - - - - ");
		Line_Current_Box->image(NULL);
	}

	//终点站
	if (mvb.get_ushort(0x01, 2) < 30 && mvb.get_ushort(0x01, 2) != 25) //从0x01端口取2位
	{
		Line_End_Box->image(NULL);
		Line_End_Box->labelcolor(fl_rgb_color(87, 180, 227));
		Line_End_Box->label(line_station_name[mvb.get_ushort(0x01, 2)]);
	}
	else if (mvb.get_ushort(0x01, 2) == 25)
	{
		Line_End_Box->label(NULL);
		Line_End_Box->image(Station_DaQi[0]);
	}
	else
	{
		Line_End_Box->labelcolor(fl_rgb_color(87, 180, 227));
		Line_End_Box->label(" - - - - - ");
		Line_End_Box->image(NULL);
	}

	Line_Current_Box->redraw();
	Line_End_Box->redraw();
}
