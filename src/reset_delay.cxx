#include"head.h"

void sleep_proccess();
char AirSet_Count;//空调设置延时计数器
char Boradcast_Speaker_Count;//报站广播延时计数器
char Boradcast_Pre_Count;//上一站延时计数器
char Boradcast_Next_Count;//下一站延时计数器
char Boradcast_in_Count;//进站延时计数器
char Boradcast_out_Count;//出站延时计数器
char Station_Set_Count;//选站设置延时计数器
char Line_Set_Count;//线路设置延时计数器
char Broadcast_Set_Count;//紧急广播设置延时计数器
char Diameter_Set_Count;//轮径设置延时计数器
char CarID_Set_Count;//车号设置延时计数器
char Time_Set_Count;//时间设置延时计数器
char Total_Set_Count;//累计数据设置延时计数器
char BrakeCheck_Start_Count;//制动自检延时计数器
char Broadcast_Confirm_Count;//紧急广播确认延时计数器

void sleep_proccess()
{
	unsigned short port;

	//空调设置延时
	if(Air_Set_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		AirSet_Count++;
		if(AirSet_Count==6)
		{
			if(AircSet_Fire_Flag==1)
				mvb.put_ushort(port,26,1024);
			else if(AircSet_Test_Flag==1)
				mvb.put_ushort(port,26,2);
			else
				mvb.put_ushort(port,26,0);
			AirSet_Count=0;
			Air_Set_Flag=0;

			for(int i=1;i<=6;i++)
			{
				//AircSet_Butt[i]->value(0);
				//AircSet_Butt[i]->redraw();
			}
		}
	}

	//报站广播延时
	if(Broadcast_Speaker_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		Boradcast_Speaker_Count++;
		if(Boradcast_Speaker_Count==6)
		{
			mvb.put_ubit(port,13,3,0);
			Broadcast_Speaker_Flag=0;
			Boradcast_Speaker_Count=0;
		}
	}

	//上一站延时
	if(Broadcast_Pre_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		Boradcast_Pre_Count++;
		if(Boradcast_Pre_Count==6)
		{
			mvb.put_ubit(port,13,2,0);
			Broadcast_Pre_Flag=0;
			Boradcast_Pre_Count=0;
		}
	}   

	//下一站延时
	if(Broadcast_Next_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		Boradcast_Next_Count++;
		if(Boradcast_Next_Count==6)
		{
			mvb.put_ubit(port,13,1,0);
			Broadcast_Next_Flag=0;
			Boradcast_Next_Count=0;
		}
	}

	//进站延时
	if(Broadcast_in_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		Boradcast_in_Count++;
		if(Boradcast_in_Count==6)
		{
			mvb.put_ubit(port,13,3,0);
			Broadcast_in_Flag=0;
			Boradcast_in_Count=0;
		}
	}

	//出站延时
	if(Broadcast_out_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		Boradcast_out_Count++;
		if(Boradcast_out_Count==6)
		{
			mvb.put_ubit(port,13,4,0);
			Broadcast_out_Flag=0;
			Boradcast_out_Count=0;
		}
	}

	//选站延时
	if(station_Set_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		Station_Set_Count++;
		if(Station_Set_Count==6)
		{
			mvb.put_ubit(port,12,2,0);
			mvb.put_ubit(port,12,3,0);
			station_Set_Flag=0;
			Station_Set_Count=0;
		}
	}

	//线路延时
	if(Line_Select_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		Line_Set_Count++;
		if(Line_Set_Count==6)
		{
			mvb.put_ubit(port,12,4,0);
			Line_Select_Flag=0;
			Line_Set_Count=0;
		}
	}

	//轮径设置延时
	if(diameter_set_flag)
	{
		port=tc_no>1?0x6b1:0x1b1;

		Diameter_Set_Count++;
		if(Diameter_Set_Count==6)
		{
			for(int i=1;i<=6;i++)
			{
				diameter[i]->label("");
				mvb.put_ushort(port,12+(i-1)*2,0);
				mvb.put_ubit(port,0,i-1,0);
			}
			Diameter_Set_Count=0;
			diameter_set_flag=0;
		}
	}

	//车号设置延时
	if(CarID_set_flag)
	{
		port=tc_no>1?0x6b2:0x1b2;

		CarID_Set_Count++;
		if(CarID_Set_Count==6)
		{
			for(int i=1;i<=6;i++)
			{
				CarID[i]->label("");
				mvb.put_ushort(port,i*4+2,0);
				mvb.put_ushort(port,(i+1)*4,0);
				mvb.put_ubit(port,1,i+1,0);
			}
			CarID_Set_Count=0;
			CarID_set_flag=0;
		}
	}

	//时间设置延时
	if(diameter_set_flag)
	{
		port=tc_no>1?0x6b1:0x1b1;

		Time_Set_Count++;
		if(Time_Set_Count==6)
		{
			mvb.put_ubit(port,1,1,0);
			Time_Set_Count=0;
			time_set_flag=0;
		}
	}

	//累计数据设置延时
	if(total_set_flag)
	{
		port=tc_no>1?0x6b3:0x1b3;

		Total_Set_Count++;
		if(Total_Set_Count==6)
		{
			mvb.put_ubit(port,31,0,0);
			mvb.put_ubit(port,31,1,0);
			mvb.put_ubit(port,31,2,0);
			mvb.put_ubit(port,31,3,0);
			mvb.put_ubit(port,31,4,0);
			mvb.put_ubit(port,31,5,0);
			Total_Set_Count=0;
			total_set_flag=0;
		}
	}

	//制动自检延时
	if(BrakeCheck_Start_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		BrakeCheck_Start_Count++;
		if(BrakeCheck_Start_Count==6)
		{
			mvb.put_ubit(port,12,7,0);
			BrakeCheck_Start_Flag=0;
			BrakeCheck_Start_Count=0;
			BrakeCheck_Start_Butt->value(0);
		}
	}

	//紧急广播延时
	if(Broadcast_Confirm_Flag)
	{
		port=tc_no>1?0x6b0:0x1b0;
		Broadcast_Confirm_Count++;
		if(Broadcast_Confirm_Count==6)
		{
			mvb.put_ushort(port,2,0);
			Broadcast_Confirm_Flag=0;
			Broadcast_Confirm_Count=0;
		}
	}

	mvb.lp_put_alldata();
}
