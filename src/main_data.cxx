#include "head.h"
#include "main_data.h"
#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include "../control/effort.h"

extern Fl_Effort *Effort_dd;

//主界面初始化
void Main_Proccess()
{
	//当前站和终点站显示
	{
		//当前站
		if (mvb.get_ushort(0x01, 0) < 30 && mvb.get_ushort(0x01, 0) != 25)
		{
			basedata_station_current->image(NULL);
			basedata_station_current->labelcolor(fl_rgb_color(87, 180, 227));
			basedata_station_current->label(Main_Station_Name[mvb.get_ushort(0x01, 0)]);
		}
		else if (mvb.get_ushort(0x01, 0) == 25)
		{
			basedata_station_current->label(NULL);
			basedata_station_current->image(Station_DaQi[0]);
		}
		else
		{
			basedata_station_current->labelcolor(fl_rgb_color(87, 180, 227));
			basedata_station_current->label(" - - - - - ");
			basedata_station_current->image(NULL);
		}
		//终点站
		if (mvb.get_ushort(0x01, 2) < 30 && mvb.get_ushort(0x01, 2) != 25)
		{
			basedata_station_end->image(NULL);
			basedata_station_end->labelcolor(fl_rgb_color(87, 180, 227));
			basedata_station_end->label(Main_Station_Name[mvb.get_ushort(0x01, 2)]);
		}
		else if (mvb.get_ushort(0x01, 2) == 25)
		{
			basedata_station_end->label(NULL);
			basedata_station_end->image(Station_DaQi[0]);
		}
		else
		{
			basedata_station_end->labelcolor(fl_rgb_color(87, 180, 227));
			basedata_station_end->label(" - - - - - ");
			basedata_station_end->image(NULL);
		}

		basedata_station_current->redraw();
		basedata_station_end->redraw();
	}

	//主按钮图标显示
	Main_Butt_Switch_Function();
	//电网电压
	{
		sprintf(Main_NetV_Buff, "%d", mvb.get_ushort(Main_NetV_Struct.NetV_Port, Main_NetV_Struct.NetV_Byte));
		Main_NetV_Box->label(Main_NetV_Buff);
		Main_NetV_Box->redraw();
	}
	//速度
	{
		sprintf(Main_Speed_Buff, "%0.1f", mvb.get_ushort(Main_Speed_Struct.Speed_Port, Main_Speed_Struct.Speed_Byte) * 0.1);
		Main_Speed_Box->label(Main_Speed_Buff);
		Main_Speed_Box->redraw();
	}
	//限速值
	{
		if (mvb.get_ushort(Main_Restrict_Speed_Struct.Restrict_Speed_Port, Main_Restrict_Speed_Struct.Restrict_Speed_Byte) != 0)
		{
			sprintf(Main_Restrict_Speed_Buff, "%0.1f", mvb.get_ushort(Main_Restrict_Speed_Struct.Restrict_Speed_Port, Main_Restrict_Speed_Struct.Restrict_Speed_Byte) * 0.1);
			Main_Restrict_Speed_Box->label(Main_Restrict_Speed_Buff);
			Main_Restrict_Speed_Box->redraw();
		}
		else
		{
			Main_Restrict_Speed_Box->label("");
			Main_Restrict_Speed_Box->redraw();
		}
	}
	//主风缸压力
	{
		sprintf(Main_Jar_Buff, "%0.2f", mvb.get_ushort(Main_Jar_Struct.Jar_Port, Main_Jar_Struct.Jar_Byte) * 0.01);
		Main_Jar_Box->label(Main_Jar_Buff);
		Main_Jar_Box->redraw();
	}
	//模式
	{
		if (mvb.get_ushort(Main_Mode_Struct.Mode_Port, Main_Mode_Struct.Mode_Byte) == 128)
			Main_Mode->label("零位");
		else if (mvb.get_ushort(Main_Mode_Struct.Mode_Port, Main_Mode_Struct.Mode_Byte) == 64)
			Main_Mode->label("ATP保护人工驾驶模式");
		else if (mvb.get_ushort(Main_Mode_Struct.Mode_Port, Main_Mode_Struct.Mode_Byte) == 32)
			Main_Mode->label("ATO模式");
		else if (mvb.get_ushort(Main_Mode_Struct.Mode_Port, Main_Mode_Struct.Mode_Byte) == 16)
			Main_Mode->label("人工驾驶模式");
		else if (mvb.get_ushort(Main_Mode_Struct.Mode_Port, Main_Mode_Struct.Mode_Byte) == 8)
			Main_Mode->label("慢行牵引");
		else if (mvb.get_ushort(Main_Mode_Struct.Mode_Port, Main_Mode_Struct.Mode_Byte) == 4)
			Main_Mode->label("拖拉牵引");
		else if (mvb.get_ushort(Main_Mode_Struct.Mode_Port, Main_Mode_Struct.Mode_Byte) == 2)
			Main_Mode->label("紧急牵引");
		else
			Main_Mode->label("");
		Main_Mode->redraw();
	}
	//空转/打滑
	{
		if (mvb.get_ubit(Main_Slider_Struct.Slider_Port, Main_Slider_Struct.Slider_Byte, 5))
			Main_Slider->label("打滑");
		else if (mvb.get_ubit(Main_Slider_Struct.Slider_Port, Main_Slider_Struct.Slider_Byte, 4))
			Main_Slider->label("空转");
		else if (mvb.get_ubit(Main_Slider_Struct.Slider_Port, Main_Slider_Struct.Slider_Byte, 3))
			Main_Slider->label("退行");
		else if (mvb.get_ubit(Main_Slider_Struct.Slider_Port, Main_Slider_Struct.Slider_Byte, 6))
			Main_Slider->label("联挂好");
		else
			Main_Slider->label("");
		Main_Slider->redraw();
	}
	//工况
	{
		if (mvb.get_ubit(Main_Oper_Cond_Struct.Oper_Cond_Port, Main_Oper_Cond_Struct.Oper_Cond_Byte, 6))
			Main_Oper_Cond->label("紧急停车按钮按下");
		else if (mvb.get_ubit(Main_Oper_Cond_Struct.Oper_Cond_Port, Main_Oper_Cond_Struct.Oper_Cond_Byte, 0))
			Main_Oper_Cond->label("紧急制动");
		else if (mvb.get_ubit(Main_Oper_Cond_Struct.Oper_Cond_Port, Main_Oper_Cond_Struct.Oper_Cond_Byte, 1))
			Main_Oper_Cond->label("快速制动");
		else if (mvb.get_ubit(Main_Oper_Cond_Struct.Oper_Cond_Port, Main_Oper_Cond_Struct.Oper_Cond_Byte, 2))
			Main_Oper_Cond->label("停放制动");
		else if (mvb.get_ubit(Main_Oper_Cond_Struct.Oper_Cond_Port, Main_Oper_Cond_Struct.Oper_Cond_Byte, 3))
			Main_Oper_Cond->label("保持制动");
		else if (mvb.get_ubit(Main_Oper_Cond_Struct.Oper_Cond_Port, Main_Oper_Cond_Struct.Oper_Cond_Byte, 4))
			Main_Oper_Cond->label("常用制动");
		else if (mvb.get_ubit(Main_Oper_Cond_Struct.Oper_Cond_Port, Main_Oper_Cond_Struct.Oper_Cond_Byte, 5))
			Main_Oper_Cond->label("牵引");
		else
			Main_Oper_Cond->label("");
		Main_Oper_Cond->redraw();
	}
	int Main_Car_ID = 0;
	for (Main_Car_ID = 0; Main_Car_ID < 6; Main_Car_ID++)
	{
		//空调
		if (group_aircondition_window->visible())
		{
			for (int i = 0; i < 2; i++) //控制每车厢设备个数
			{
				Main_Airc_Status_Flag = 0;
				for (int j = 0; j < 7; j++) //控制每个设备状态
				{
					Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[7]);
					if (mvb.get_ubit(Main_Airc_Struct[Main_Car_ID][i][j].Airc_Port, Main_Airc_Struct[Main_Car_ID][i][j].Airc_Byte, Main_Airc_Struct[Main_Car_ID][i][j].Airc_Bit))
					{
						switch (j)
						{
						case 0:
							Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[0]); //严重故障
							Main_Airc_Status_Flag = 1;
							break;
						case 1:
							Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[1]); //中等故障
							Main_Airc_Status_Flag = 1;
							break;
						case 2:
							Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[2]); //紧急通风
							Main_Airc_Status_Flag = 1;
							break;
						case 3:
							Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[3]); //通风
							Main_Airc_Status_Flag = 1;
							break;
						case 4:
							Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[6]); //停机
							Main_Airc_Status_Flag = 1;
							break;
						case 5:
							Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[4]); //限制制冷
							Main_Airc_Status_Flag = 1;
							break;
						case 6:
							Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[5]); //制冷
							Main_Airc_Status_Flag = 1;
							break;
						default:
							Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[7]); //未知
							Main_Airc_Status_Flag = 1;
							break;
						}
						Main_Airc[i][Main_Car_ID]->redraw();
						if (Main_Airc_Status_Flag == 1)
							break;
					}
				}
				if (Main_Airc_Status_Flag == 0)
				{
					Main_Airc[i][Main_Car_ID]->image(Main_Airc_Status[7]); //未知
					Main_Airc[i][Main_Car_ID]->redraw();
				}
			}
		}
		//门
		if (group_door_window->visible())
		{
			for (int i = 0; i < 8; i++) //控制每车厢设备个数
			{
				if (mvb.get_ubit(Main_Door_Struct[i][Main_Car_ID].Door_Port, Main_Door_Struct[i][Main_Car_ID].Door_Byte, 4)) //紧急情况下门从里面或外面打开
					Main_Door[i][Main_Car_ID]->image(Main_Door_Status[0]);
				else if (mvb.get_ubit(Main_Door_Struct[i][Main_Car_ID].Door_Port, Main_Door_Struct[i][Main_Car_ID].Door_Byte, 3)) //门切除
					Main_Door[i][Main_Car_ID]->image(Main_Door_Status[1]);
				else if (mvb.get_ubit(Main_Door_Struct[i][Main_Car_ID].Door_Port, Main_Door_Struct[i][Main_Car_ID].Door_Byte, 6)) //门故障
					Main_Door[i][Main_Car_ID]->image(Main_Door_Status[2]);
				else if (mvb.get_ubit(Main_Door_Struct[i][Main_Car_ID].Door_Port, Main_Door_Struct[i][Main_Car_ID].Door_Byte, 5)) //门警告
					Main_Door[i][Main_Car_ID]->image(Main_Door_Status[3]);
				else if (mvb.get_ubit(Main_Door_Struct[i][Main_Car_ID].Door_Port, Main_Door_Struct[i][Main_Car_ID].Door_Byte, 2)) //门检测到障碍物
					Main_Door[i][Main_Car_ID]->image(Main_Door_Status[4]);
				else if (mvb.get_ubit(Main_Door_Struct[i][Main_Car_ID].Door_Port, Main_Door_Struct[i][Main_Car_ID].Door_Byte, 1)) //门开
					Main_Door[i][Main_Car_ID]->image(Main_Door_Status[5]);
				else if (mvb.get_ubit(Main_Door_Struct[i][Main_Car_ID].Door_Port, Main_Door_Struct[i][Main_Car_ID].Door_Byte, 0)) //门关
					Main_Door[i][Main_Car_ID]->image(Main_Door_Status[6]);
				else
					Main_Door[i][Main_Car_ID]->image(Main_Door_Status[7]); //未知
				Main_Door[i][Main_Car_ID]->redraw();
			}
		}
		//乘客报警
		if (group_passenger_window->visible())
		{
			for (int i = 0; i < 4; i++) //控制每车厢设备个数
			{
				Main_Passenger_Status_Flag = 0;
				for (int j = 0; j < 3; j++) //控制每个设备状态
				{
					if (mvb.get_ubit(Main_Passenger_Struct[Main_Car_ID][i][j].Passenger_Port, Main_Passenger_Struct[Main_Car_ID][i][j].Passenger_Byte, Main_Passenger_Struct[Main_Car_ID][i][j].Passenger_Bit))
					{
						switch (j)
						{
						case 0:
							Main_Passenger[i][Main_Car_ID]->image(Main_Passenger_Status[0]); //故障
							Main_Passenger_Status_Flag = 1;
							break;
						case 1:
							Main_Passenger[i][Main_Car_ID]->image(Main_Passenger_Status[1]); //呼叫
							Main_Passenger_Status_Flag = 1;
							break;
						case 2:
							Main_Passenger[i][Main_Car_ID]->image(Main_Passenger_Status[2]); //对讲
							Main_Passenger_Status_Flag = 1;
							break;
						default:
							Main_Passenger[i][Main_Car_ID]->image(Main_Passenger_Status[3]); //正常
							Main_Passenger_Status_Flag = 1;
							break;
						}
						Main_Passenger[i][Main_Car_ID]->redraw();
						if (Main_Passenger_Status_Flag == 1)
							break;
					}
				}
				if (Main_Passenger_Status_Flag == 0)
				{
					Main_Passenger[i][Main_Car_ID]->image(Main_Passenger_Status[3]);
					Main_Passenger[i][Main_Car_ID]->redraw();
				}
			}
		}
		//制动系统
		if (group_brake_window->visible())
		{
			//停放制动
			if (mvb.get_ubit(Main_ParkBrake_Struct[Main_Car_ID].ParkBrake_Port, Main_ParkBrake_Struct[Main_Car_ID].ParkBrake_Byte, Main_ParkBrake_Struct[Main_Car_ID].ParkBrake_Bit))
			{
				Main_ParkBrake[0][Main_Car_ID]->image(Main_ParkBrake_Status[1]); //缓解
				Main_ParkBrake[1][Main_Car_ID]->image(Main_ParkBrake_Status[1]);
			}
			else
			{
				Main_ParkBrake[0][Main_Car_ID]->image(Main_ParkBrake_Status[0]); //施加
				Main_ParkBrake[1][Main_Car_ID]->image(Main_ParkBrake_Status[0]);
			}
			Main_ParkBrake[0][Main_Car_ID]->redraw();
			Main_ParkBrake[1][Main_Car_ID]->redraw();
			//空气制动
			{
				for (int i = 0; i < 2; i++) //控制每车厢设备个数
				{
					Main_Brake_Status_Flag = 0;
					for (int j = 0; j < 5; j++) //控制每个设备状态
					{
						if (mvb.get_ubit(Main_Brake_Struct[Main_Car_ID][i][j].Brake_Port, Main_Brake_Struct[Main_Car_ID][i][j].Brake_Byte, Main_Brake_Struct[Main_Car_ID][i][j].Brake_Bit))
						{
							switch (j)
							{
							case 0:
								Main_Brake[i][Main_Car_ID]->image(Main_Brake_Status[0]); //切除
								Main_Brake_Status_Flag = 1;
								break;
							case 1:
								Main_Brake[i][Main_Car_ID]->image(Main_Brake_Status[1]); //故障
								Main_Brake_Status_Flag = 1;
								break;
							case 2:
								Main_Brake[i][Main_Car_ID]->image(Main_Brake_Status[2]); //警告
								Main_Brake_Status_Flag = 1;
								break;
							case 3:
								Main_Brake[i][Main_Car_ID]->image(Main_Brake_Status[3]); //施加
								Main_Brake_Status_Flag = 1;
								break;
							case 4:
								Main_Brake[i][Main_Car_ID]->image(Main_Brake_Status[4]); //缓解
								Main_Brake_Status_Flag = 1;
								break;
							default:
								Main_Brake[i][Main_Car_ID]->image(Main_Brake_Status[5]); //未知
								Main_Brake_Status_Flag = 1;
								break;
							}
							Main_Brake[i][Main_Car_ID]->redraw();
							if (Main_Brake_Status_Flag == 1)
								break;
						}
					}
					if (Main_Brake_Status_Flag == 0)
					{
						Main_Brake[i][Main_Car_ID]->image(Main_Brake_Status[5]);
						Main_Brake[i][Main_Car_ID]->redraw();
					}
				}
			}
		}
		//烟火系统
		if (group_fire_window->visible())
		{
			for (int i = 0; i < 1; i++) //控制每车厢设备个数
			{
				Main_FDS_Status_Flag = 0;
				for (int j = 0; j < 2; j++) //控制每个设备状态
				{
					if (mvb.get_ubit(Main_FDS_Struct[Main_Car_ID][i][j].FDS_Port, Main_FDS_Struct[Main_Car_ID][i][j].FDS_Byte, Main_FDS_Struct[Main_Car_ID][i][j].FDS_Bit))
					{
						switch (j)
						{
						case 0:
							Main_FDS[i][Main_Car_ID]->image(Main_FDS_Status[0]); //报警
							Main_FDS_Status_Flag = 1;
							break;
						case 1:
							Main_FDS[i][Main_Car_ID]->image(Main_FDS_Status[1]); //故障
							Main_FDS_Status_Flag = 1;
							break;
						default:
							Main_FDS[i][Main_Car_ID]->image(Main_FDS_Status[2]); //未检测到信息
							Main_FDS_Status_Flag = 1;
							break;
						}
						Main_FDS[i][Main_Car_ID]->redraw();
						if (Main_FDS_Status_Flag == 1)
							break;
					}
				}
				if (Main_FDS_Status_Flag == 0)
				{
					Main_FDS[i][Main_Car_ID]->image(Main_FDS_Status[2]);
					Main_FDS[i][Main_Car_ID]->redraw();
				}
			}
		}
		//空压机
		if (group_compressor_window->visible())
		{
			if (Main_Car_ID == 2 || Main_Car_ID == 3)
			{
				for (int i = 0; i < 1; i++) //控制每车厢设备个数
				{
					Main_CMP_Status_Flag = 0;
					for (int j = 0; j < 3; j++) //控制每个设备状态
					{
						if (mvb.get_ubit(Main_CMP_Struct[Main_Car_ID][i][j].CMP_Port, Main_CMP_Struct[Main_Car_ID][i][j].CMP_Byte, Main_CMP_Struct[Main_Car_ID][i][j].CMP_Bit))
						{
							switch (j)
							{
							case 0:
								Main_CMP[i][Main_Car_ID]->image(Main_CMP_Status[0]); //故障
								Main_CMP_Status_Flag = 1;
								break;
							case 1:
								Main_CMP[i][Main_Car_ID]->image(Main_CMP_Status[1]); //警告
								Main_CMP_Status_Flag = 1;
								break;
							case 2:
								Main_CMP[i][Main_Car_ID]->image(Main_CMP_Status[2]); //运行
								Main_CMP_Status_Flag = 1;
								break;
							default:
								Main_CMP[i][Main_Car_ID]->image(Main_CMP_Status[3]); //断开
								Main_CMP_Status_Flag = 1;
								break;
							}
							Main_CMP[i][Main_Car_ID]->redraw();
							if (Main_CMP_Status_Flag == 1)
								break;
						}
					}
					if (Main_CMP_Status_Flag == 0)
					{
						Main_CMP[i][Main_Car_ID]->image(Main_CMP_Status[3]);
						Main_CMP[i][Main_Car_ID]->redraw();
					}
				}
			}
		}
		// HSCB
		if (group_panto_window->visible())
		{
			if (Main_Car_ID > 0 && Main_Car_ID < 5)
			{
				if (mvb.get_ubit(Main_HSCB_Struct[Main_Car_ID].HSCB_Port, Main_HSCB_Struct[Main_Car_ID].HSCB_Byte, Main_HSCB_Struct[Main_Car_ID].HSCB_Bit))
					Main_HSCB[0][Main_Car_ID]->image(Main_HSCB_Status[0]);
				else
					Main_HSCB[0][Main_Car_ID]->image(Main_HSCB_Status[1]);
				Main_HSCB[0][Main_Car_ID]->redraw();
			}
		}
		//车间电源
		if (group_panto_window->visible())
		{
			if (Main_Car_ID == 1 || Main_Car_ID == 4)
			{
				for (int i = 0; i < 1; i++) //控制每车厢设备个数
				{
					Main_Power_Status_Flag = 0;
					for (int j = 0; j < 2; j++) //控制每个设备状态
					{
						if (mvb.get_ubit(Main_Power_Struct[Main_Car_ID][i][j].Power_Port, Main_Power_Struct[Main_Car_ID][i][j].Power_Byte, Main_Power_Struct[Main_Car_ID][i][j].Power_Bit))
						{
							switch (j)
							{
							case 0:
								Main_Power[i][Main_Car_ID]->show();
								Main_Power[i][Main_Car_ID]->image(Main_Power_Status[0]); //供电
								Main_Power_Status_Flag = 1;
								break;
							case 1:
								Main_Power[i][Main_Car_ID]->show();
								Main_Power[i][Main_Car_ID]->image(Main_Power_Status[1]); //未供电
								Main_Power_Status_Flag = 1;
								break;
							default:
								break;
							}
							Main_Power[i][Main_Car_ID]->redraw();
							if (Main_Power_Status_Flag == 1)
								break;
						}
					}
					if (Main_Power_Status_Flag == 0)
					{
						// Main_Power[i][Main_Car_ID]->image(Main_Power_Status[1]);
						Main_Power[i][Main_Car_ID]->hide();
						Main_Power[i][Main_Car_ID]->redraw();
					}
				}
			}
		}

		//受电弓
		if (group_panto_window->visible())
		{
			if (Main_Car_ID == 1 || Main_Car_ID == 4)
			{
				for (int i = 0; i < 1; i++) //控制每车厢设备个数
				{
					Main_Panto_Status_Flag = 0;
					for (int j = 0; j < 5; j++) //控制每个设备状态
					{
						if (mvb.get_ubit(Main_Panto_Struct[Main_Car_ID][i][j].Panto_Port, Main_Panto_Struct[Main_Car_ID][i][j].Panto_Byte, Main_Panto_Struct[Main_Car_ID][i][j].Panto_Bit))
						{
							switch (j)
							{
							case 0:
								Main_Panto[i][Main_Car_ID]->image(Main_Panto_Status[0]); //本弓隔离
								Main_Panto_Status_Flag = 1;
								break;
							case 1:
								Main_Panto[i][Main_Car_ID]->image(Main_Panto_Status[1]); //升弓故障
								Main_Panto_Status_Flag = 1;
								break;
							case 2:
								Main_Panto[i][Main_Car_ID]->image(Main_Panto_Status[2]); //降弓故障
								Main_Panto_Status_Flag = 1;
								break;
							case 3:
								Main_Panto[i][Main_Car_ID]->image(Main_Panto_Status[3]); //升弓
								Main_Panto_Status_Flag = 1;
								break;
							case 4:
								Main_Panto[i][Main_Car_ID]->image(Main_Panto_Status[4]); //降弓
								Main_Panto_Status_Flag = 1;
								break;
							default:
								break;
							}
							Main_Panto[i][Main_Car_ID]->redraw();
							if (Main_Panto_Status_Flag == 1)
								break;
						}
					}
					if (Main_Panto_Status_Flag == 0)
					{
						Main_Panto[i][Main_Car_ID]->image(Main_Panto_Status[4]); //未知
						Main_Panto[i][Main_Car_ID]->redraw();
					}
				}
			}
		}

		//车辆号
		{
			if ((mvb.get_ushort(0x3A, Main_Car_ID * 4) * 65536 + mvb.get_ushort(0x3A, Main_Car_ID * 4 + 2)) > 0)
			{
				sprintf(Main_Number_Buff[Main_Car_ID], "%06d", mvb.get_ushort(0x3A, Main_Car_ID * 4) * 65536 + mvb.get_ushort(0x3A, Main_Car_ID * 4 + 2));
				Main_Number[Main_Car_ID]->label(Main_Number_Buff[Main_Car_ID]);
			}
			else
			{
				Main_Number[Main_Car_ID]->label("000000");
			}
			Main_Number[Main_Car_ID]->redraw();
		}

		//门回路
		{
			//左
			if (mvb.get_ubit(Main_DoorLoop_L_Struct[Main_Car_ID].DoorLoop_L_Port, Main_DoorLoop_L_Struct[Main_Car_ID].DoorLoop_L_Byte, Main_DoorLoop_L_Struct[Main_Car_ID].DoorLoop_L_Bit))
				Main_Door_L[Main_Car_ID]->show();
			else
				Main_Door_L[Main_Car_ID]->hide();
			//右
			if (mvb.get_ubit(Main_DoorLoop_R_Struct[Main_Car_ID].DoorLoop_R_Port, Main_DoorLoop_R_Struct[Main_Car_ID].DoorLoop_R_Byte, Main_DoorLoop_R_Struct[Main_Car_ID].DoorLoop_R_Bit))
				Main_Door_R[Main_Car_ID]->show();
			else
				Main_Door_R[Main_Car_ID]->hide();
		}
	}
	//因SIV和充电机的警告包括中等和轻微故障
	if (group_auxiliary_window->visible())
	{
		// 1车SIV
		if (mvb.get_ubit(0x0b, 20, 7)) //严重故障
		{
			Main_SIV[0][0]->image(Main_SIV_Status[0]);
			Main_SIV[0][0]->redraw();
		}
		else if (mvb.get_ubit(0x0b, 20, 6) || mvb.get_ubit(0x0b, 20, 5)) //警告
		{
			Main_SIV[0][0]->image(Main_SIV_Status[1]);
			Main_SIV[0][0]->redraw();
		}
		else if (mvb.get_ubit(0x0b, 25, 4)) //运行无故障
		{
			Main_SIV[0][0]->image(Main_SIV_Status[2]);
			Main_SIV[0][0]->redraw();
		}
		else if (mvb.get_ubit(0x0b, 21, 7)) //断开无故障
		{
			Main_SIV[0][0]->image(Main_SIV_Status[3]);
			Main_SIV[0][0]->redraw();
		}
		else //未知
		{
			Main_SIV[0][0]->image(Main_SIV_Status[4]);
			Main_SIV[0][0]->redraw();
		}
		// 6车SIV
		if (mvb.get_ubit(0x0c, 20, 7)) //严重故障
		{
			Main_SIV[0][5]->image(Main_SIV_Status[0]);
			Main_SIV[0][5]->redraw();
		}
		else if (mvb.get_ubit(0x0c, 20, 6) || mvb.get_ubit(0x0c, 20, 5)) //警告
		{
			Main_SIV[0][5]->image(Main_SIV_Status[1]);
			Main_SIV[0][5]->redraw();
		}
		else if (mvb.get_ubit(0x0c, 25, 4)) //运行无故障
		{
			Main_SIV[0][5]->image(Main_SIV_Status[2]);
			Main_SIV[0][5]->redraw();
		}
		else if (mvb.get_ubit(0x0c, 21, 7)) //断开无故障
		{
			Main_SIV[0][5]->image(Main_SIV_Status[3]);
			Main_SIV[0][5]->redraw();
		}
		else //未知
		{
			Main_SIV[0][5]->image(Main_SIV_Status[4]);
			Main_SIV[0][5]->redraw();
		}
		// 1车充电机
		if (mvb.get_ubit(0x0b, 20, 4)) //严重故障
		{
			Main_SIV[1][0]->image(Main_SIV_Status[5]);
			Main_SIV[1][0]->redraw();
		}
		else if (mvb.get_ubit(0x0b, 20, 3) || mvb.get_ubit(0x0b, 20, 2)) //警告
		{
			Main_SIV[1][0]->image(Main_SIV_Status[6]);
			Main_SIV[1][0]->redraw();
		}
		else if (mvb.get_ubit(0x0b, 23, 4)) //运行无故障
		{
			Main_SIV[1][0]->image(Main_SIV_Status[7]);
			Main_SIV[1][0]->redraw();
		}
		else if (mvb.get_ubit(0x0b, 20, 0)) //断开无故障
		{
			Main_SIV[1][0]->image(Main_SIV_Status[8]);
			Main_SIV[1][0]->redraw();
		}
		else //未知
		{
			Main_SIV[1][0]->image(Main_SIV_Status[9]);
			Main_SIV[1][0]->redraw();
		}
		// 6车充电机
		if (mvb.get_ubit(0x0c, 20, 4)) //严重故障
		{
			Main_SIV[1][5]->image(Main_SIV_Status[5]);
			Main_SIV[1][5]->redraw();
		}
		else if (mvb.get_ubit(0x0c, 20, 3) || mvb.get_ubit(0x0c, 20, 2)) //警告
		{
			Main_SIV[1][5]->image(Main_SIV_Status[6]);
			Main_SIV[1][5]->redraw();
		}
		else if (mvb.get_ubit(0x0c, 23, 4)) //运行无故障
		{
			Main_SIV[1][5]->image(Main_SIV_Status[7]);
			Main_SIV[1][5]->redraw();
		}
		else if (mvb.get_ubit(0x0c, 20, 0)) //断开无故障
		{
			Main_SIV[1][5]->image(Main_SIV_Status[8]);
			Main_SIV[1][5]->redraw();
		}
		else //未知
		{
			Main_SIV[1][5]->image(Main_SIV_Status[9]);
			Main_SIV[1][5]->redraw();
		}
	}
	if (group_vvvf_window->visible())
	{
		// 2车
		if (mvb.get_ubit(0x14, 8, 7)) //故障
		{
			Main_VVVF[1]->image(Main_VVVF_Status[0]);
			Main_VVVF[1]->redraw();
		}
		else if (mvb.get_ubit(0x14, 8, 5) || mvb.get_ubit(0x14, 8, 6)) //警告
		{
			Main_VVVF[1]->image(Main_VVVF_Status[1]);
			Main_VVVF[1]->redraw();
		}
		else if (mvb.get_ubit(0x14, 8, 4)) //激活
		{
			Main_VVVF[1]->image(Main_VVVF_Status[2]);
			Main_VVVF[1]->redraw();
		}
		else if (mvb.get_ubit(0x14, 8, 3)) //断开
		{
			Main_VVVF[1]->image(Main_VVVF_Status[3]);
			Main_VVVF[1]->redraw();
		}
		else
		{
			Main_VVVF[1]->image(Main_SIV_Status[4]); //未知,共用辅助电源的未知图标
			Main_VVVF[1]->redraw();
		}
		// 3车
		if (mvb.get_ubit(0x14, 20, 7)) //故障
		{
			Main_VVVF[2]->image(Main_VVVF_Status[0]);
			Main_VVVF[2]->redraw();
		}
		else if (mvb.get_ubit(0x14, 20, 5) || mvb.get_ubit(0x14, 20, 6)) //警告
		{
			Main_VVVF[2]->image(Main_VVVF_Status[1]);
			Main_VVVF[2]->redraw();
		}
		else if (mvb.get_ubit(0x14, 20, 4)) //激活
		{
			Main_VVVF[2]->image(Main_VVVF_Status[2]);
			Main_VVVF[2]->redraw();
		}
		else if (mvb.get_ubit(0x14, 20, 3)) //断开
		{
			Main_VVVF[2]->image(Main_VVVF_Status[3]);
			Main_VVVF[2]->redraw();
		}
		else
		{
			Main_VVVF[2]->image(Main_SIV_Status[4]); //未知,共用的辅助电源的图标
			Main_VVVF[2]->redraw();
		}
		// 4车
		if (mvb.get_ubit(0x15, 8, 7)) //故障
		{
			Main_VVVF[3]->image(Main_VVVF_Status[0]);
			Main_VVVF[3]->redraw();
		}
		else if (mvb.get_ubit(0x15, 8, 5) || mvb.get_ubit(0x15, 8, 6)) //警告
		{
			Main_VVVF[3]->image(Main_VVVF_Status[1]);
			Main_VVVF[3]->redraw();
		}
		else if (mvb.get_ubit(0x15, 8, 4)) //激活
		{
			Main_VVVF[3]->image(Main_VVVF_Status[2]);
			Main_VVVF[3]->redraw();
		}
		else if (mvb.get_ubit(0x15, 8, 3)) //断开
		{
			Main_VVVF[3]->image(Main_VVVF_Status[3]);
			Main_VVVF[3]->redraw();
		}
		else
		{
			Main_VVVF[3]->image(Main_SIV_Status[4]); //未知,共用的辅助电源的图标
			Main_VVVF[3]->redraw();
		}
		// 5车
		if (mvb.get_ubit(0x15, 20, 7)) //故障
		{
			Main_VVVF[4]->image(Main_VVVF_Status[0]);
			Main_VVVF[4]->redraw();
		}
		else if (mvb.get_ubit(0x15, 20, 5) || mvb.get_ubit(0x15, 20, 6)) //警告
		{
			Main_VVVF[4]->image(Main_VVVF_Status[1]);
			Main_VVVF[4]->redraw();
		}
		else if (mvb.get_ubit(0x15, 20, 4)) //激活
		{
			Main_VVVF[4]->image(Main_VVVF_Status[2]);
			Main_VVVF[4]->redraw();
		}
		else if (mvb.get_ubit(0x15, 20, 3)) //断开
		{
			Main_VVVF[4]->image(Main_VVVF_Status[3]);
			Main_VVVF[4]->redraw();
		}
		else
		{
			Main_VVVF[4]->image(Main_SIV_Status[4]); //未知,共用的辅助电源的图标
			Main_VVVF[4]->redraw();
		}
	}
	//司机室占有与方向
	main_direction();
	//牵引制动级位
	if (mvb.get_ushort(0x01, 10) == 0)
	{
		Effort_dd->Set_value(1, mvb.get_ushort(0x01, 10));
		Effort_d->copy_label("0");
	}
	else if (mvb.get_ushort(0x01, 10) <= 100)
	{
		if (mvb.get_ubit(0x01, 27, 5))
		{
			Effort_dd->Set_value(1, mvb.get_ushort(0x01, 10));
			sprintf(Main_Level_Buff, "＋%d", mvb.get_ushort(0x01, 10));
			Effort_d->copy_label(Main_Level_Buff);
		}
		else
		{
			Effort_dd->Set_value(0, mvb.get_ushort(0x01, 10));
			sprintf(Main_Level_Buff, "-%d", mvb.get_ushort(0x01, 10));
			Effort_d->copy_label(Main_Level_Buff);
		}
	}
	Effort_dd->redraw();
	Effort_d->redraw();
	//旁路按钮
	if (mvb.get_ushort(0x01, 20))
	{
		Main_Passby_butt->show();
	}
	else
	{
		Main_Passby_butt->hide();
	}
	Main_Passby_butt->redraw();
}

//司机室占有与方向
void main_direction()
{
	{
		if (mvb.get_ubit(0x01, 26, 0)) // 1车占有
		{
			if (mvb.get_ubit(0x01, 26, 2)) //方向向前
			{
				tc1_cab->image(DriveCabBitmap[3]);
				aircondition_cab1->image(DriveCabBitmap[3]);
				auxiliary_cab1->image(DriveCabBitmap[3]);
				passenger_cab1->image(DriveCabBitmap[3]);
				brake_cab1->image(DriveCabBitmap[3]);
				compressor_cab1->image(DriveCabBitmap[3]);
				vvvf_cab1->image(DriveCabBitmap[3]);
				fire_cab1->image(DriveCabBitmap[3]);
				panto_cab1->image(DriveCabBitmap[3]);
				if (mvb.get_ubit(0x01, 26, 1))
				{
					tc2_cab->image(DriveCabBitmap[6]);
					aircondition_cab2->image(DriveCabBitmap[6]);
					auxiliary_cab2->image(DriveCabBitmap[6]);
					passenger_cab2->image(DriveCabBitmap[6]);
					brake_cab2->image(DriveCabBitmap[6]);
					compressor_cab2->image(DriveCabBitmap[6]);
					vvvf_cab2->image(DriveCabBitmap[6]);
					fire_cab2->image(DriveCabBitmap[6]);
					panto_cab2->image(DriveCabBitmap[6]);
				}
				else
				{
					tc2_cab->image(DriveCabBitmap[4]);
					aircondition_cab2->image(DriveCabBitmap[4]);
					auxiliary_cab2->image(DriveCabBitmap[4]);
					passenger_cab2->image(DriveCabBitmap[4]);
					brake_cab2->image(DriveCabBitmap[4]);
					compressor_cab2->image(DriveCabBitmap[4]);
					vvvf_cab2->image(DriveCabBitmap[4]);
					fire_cab2->image(DriveCabBitmap[4]);
					panto_cab2->image(DriveCabBitmap[4]);
				}
			}
			else if (mvb.get_ubit(0x01, 26, 3)) //向后
			{
				tc1_cab->image(DriveCabBitmap[2]);
				aircondition_cab1->image(DriveCabBitmap[2]);
				auxiliary_cab1->image(DriveCabBitmap[2]);
				passenger_cab1->image(DriveCabBitmap[2]);
				brake_cab1->image(DriveCabBitmap[2]);
				compressor_cab1->image(DriveCabBitmap[2]);
				vvvf_cab1->image(DriveCabBitmap[2]);
				fire_cab1->image(DriveCabBitmap[2]);
				panto_cab1->image(DriveCabBitmap[2]);
				if (mvb.get_ubit(0x01, 26, 1))
				{
					tc2_cab->image(DriveCabBitmap[7]);
					aircondition_cab2->image(DriveCabBitmap[7]);
					auxiliary_cab2->image(DriveCabBitmap[7]);
					passenger_cab2->image(DriveCabBitmap[7]);
					brake_cab2->image(DriveCabBitmap[7]);
					compressor_cab2->image(DriveCabBitmap[7]);
					vvvf_cab2->image(DriveCabBitmap[7]);
					fire_cab2->image(DriveCabBitmap[7]);
					panto_cab2->image(DriveCabBitmap[7]);
				}
				else
				{
					tc2_cab->image(DriveCabBitmap[5]);
					aircondition_cab2->image(DriveCabBitmap[5]);
					auxiliary_cab2->image(DriveCabBitmap[5]);
					passenger_cab2->image(DriveCabBitmap[5]);
					brake_cab2->image(DriveCabBitmap[5]);
					compressor_cab2->image(DriveCabBitmap[5]);
					vvvf_cab2->image(DriveCabBitmap[5]);
					fire_cab2->image(DriveCabBitmap[5]);
					panto_cab2->image(DriveCabBitmap[5]);
				}
			}
			else
			{
				tc1_cab->image(DriveCabBitmap[2]);
				aircondition_cab1->image(DriveCabBitmap[2]);
				auxiliary_cab1->image(DriveCabBitmap[2]);
				passenger_cab1->image(DriveCabBitmap[2]);
				brake_cab1->image(DriveCabBitmap[2]);
				compressor_cab1->image(DriveCabBitmap[2]);
				vvvf_cab1->image(DriveCabBitmap[2]);
				fire_cab1->image(DriveCabBitmap[2]);
				panto_cab1->image(DriveCabBitmap[2]);
				if (mvb.get_ubit(0x01, 26, 1))
				{
					tc2_cab->image(DriveCabBitmap[6]);
					aircondition_cab2->image(DriveCabBitmap[6]);
					auxiliary_cab2->image(DriveCabBitmap[6]);
					passenger_cab2->image(DriveCabBitmap[6]);
					brake_cab2->image(DriveCabBitmap[6]);
					compressor_cab2->image(DriveCabBitmap[6]);
					vvvf_cab2->image(DriveCabBitmap[6]);
					fire_cab2->image(DriveCabBitmap[6]);
					panto_cab2->image(DriveCabBitmap[6]);
				}
				else
				{
					tc2_cab->image(DriveCabBitmap[4]);
					aircondition_cab2->image(DriveCabBitmap[4]);
					auxiliary_cab2->image(DriveCabBitmap[4]);
					passenger_cab2->image(DriveCabBitmap[4]);
					brake_cab2->image(DriveCabBitmap[4]);
					compressor_cab2->image(DriveCabBitmap[4]);
					vvvf_cab2->image(DriveCabBitmap[4]);
					fire_cab2->image(DriveCabBitmap[4]);
					panto_cab2->image(DriveCabBitmap[4]);
				}
			}
		}
		else if (mvb.get_ubit(0x01, 26, 1)) // 6车占有
		{
			if (mvb.get_ubit(0x01, 26, 2)) //方向向前
			{
				tc2_cab->image(DriveCabBitmap[7]);
				aircondition_cab2->image(DriveCabBitmap[7]);
				auxiliary_cab2->image(DriveCabBitmap[7]);
				passenger_cab2->image(DriveCabBitmap[7]);
				brake_cab2->image(DriveCabBitmap[7]);
				compressor_cab2->image(DriveCabBitmap[7]);
				vvvf_cab2->image(DriveCabBitmap[7]);
				fire_cab2->image(DriveCabBitmap[7]);
				panto_cab2->image(DriveCabBitmap[7]);
				if (mvb.get_ubit(0x01, 26, 0))
				{
					tc1_cab->image(DriveCabBitmap[2]);
					aircondition_cab1->image(DriveCabBitmap[2]);
					auxiliary_cab1->image(DriveCabBitmap[2]);
					passenger_cab1->image(DriveCabBitmap[2]);
					brake_cab1->image(DriveCabBitmap[2]);
					compressor_cab1->image(DriveCabBitmap[2]);
					vvvf_cab1->image(DriveCabBitmap[2]);
					fire_cab1->image(DriveCabBitmap[2]);
					panto_cab1->image(DriveCabBitmap[2]);
				}
				else
				{
					tc1_cab->image(DriveCabBitmap[0]);
					aircondition_cab1->image(DriveCabBitmap[0]);
					auxiliary_cab1->image(DriveCabBitmap[0]);
					passenger_cab1->image(DriveCabBitmap[0]);
					brake_cab1->image(DriveCabBitmap[0]);
					compressor_cab1->image(DriveCabBitmap[0]);
					vvvf_cab1->image(DriveCabBitmap[0]);
					fire_cab1->image(DriveCabBitmap[0]);
					panto_cab1->image(DriveCabBitmap[0]);
				}
			}
			else if (mvb.get_ubit(0x01, 26, 3)) //向后
			{
				tc2_cab->image(DriveCabBitmap[6]);
				aircondition_cab2->image(DriveCabBitmap[6]);
				auxiliary_cab2->image(DriveCabBitmap[6]);
				passenger_cab2->image(DriveCabBitmap[6]);
				brake_cab2->image(DriveCabBitmap[6]);
				compressor_cab2->image(DriveCabBitmap[6]);
				vvvf_cab2->image(DriveCabBitmap[6]);
				fire_cab2->image(DriveCabBitmap[6]);
				panto_cab2->image(DriveCabBitmap[6]);
				if (mvb.get_ubit(0x01, 26, 0))
				{
					tc1_cab->image(DriveCabBitmap[3]);
					aircondition_cab1->image(DriveCabBitmap[3]);
					auxiliary_cab1->image(DriveCabBitmap[3]);
					passenger_cab1->image(DriveCabBitmap[3]);
					brake_cab1->image(DriveCabBitmap[3]);
					compressor_cab1->image(DriveCabBitmap[3]);
					vvvf_cab1->image(DriveCabBitmap[3]);
					fire_cab1->image(DriveCabBitmap[3]);
					panto_cab1->image(DriveCabBitmap[3]);
				}
				else
				{
					tc1_cab->image(DriveCabBitmap[1]);
					aircondition_cab1->image(DriveCabBitmap[1]);
					auxiliary_cab1->image(DriveCabBitmap[1]);
					passenger_cab1->image(DriveCabBitmap[1]);
					brake_cab1->image(DriveCabBitmap[1]);
					compressor_cab1->image(DriveCabBitmap[1]);
					vvvf_cab1->image(DriveCabBitmap[1]);
					fire_cab1->image(DriveCabBitmap[1]);
					panto_cab1->image(DriveCabBitmap[1]);
				}
			}
			else
			{
				tc2_cab->image(DriveCabBitmap[6]);
				aircondition_cab2->image(DriveCabBitmap[6]);
				auxiliary_cab2->image(DriveCabBitmap[6]);
				passenger_cab2->image(DriveCabBitmap[6]);
				brake_cab2->image(DriveCabBitmap[6]);
				compressor_cab2->image(DriveCabBitmap[6]);
				vvvf_cab2->image(DriveCabBitmap[6]);
				fire_cab2->image(DriveCabBitmap[6]);
				panto_cab2->image(DriveCabBitmap[6]);
				if (mvb.get_ubit(0x01, 26, 0))
				{
					tc1_cab->image(DriveCabBitmap[2]);
					aircondition_cab1->image(DriveCabBitmap[2]);
					auxiliary_cab1->image(DriveCabBitmap[2]);
					passenger_cab1->image(DriveCabBitmap[2]);
					brake_cab1->image(DriveCabBitmap[2]);
					compressor_cab1->image(DriveCabBitmap[2]);
					vvvf_cab1->image(DriveCabBitmap[2]);
					fire_cab1->image(DriveCabBitmap[2]);
					panto_cab1->image(DriveCabBitmap[2]);
				}
				else
				{
					tc1_cab->image(DriveCabBitmap[0]);
					aircondition_cab1->image(DriveCabBitmap[0]);
					auxiliary_cab1->image(DriveCabBitmap[0]);
					passenger_cab1->image(DriveCabBitmap[0]);
					brake_cab1->image(DriveCabBitmap[0]);
					compressor_cab1->image(DriveCabBitmap[0]);
					vvvf_cab1->image(DriveCabBitmap[0]);
					fire_cab1->image(DriveCabBitmap[0]);
					panto_cab1->image(DriveCabBitmap[0]);
				}
			}
		}
		else
		{
			tc1_cab->image(DriveCabBitmap[0]);
			tc2_cab->image(DriveCabBitmap[4]);
			aircondition_cab1->image(DriveCabBitmap[0]);
			aircondition_cab2->image(DriveCabBitmap[4]);
			auxiliary_cab1->image(DriveCabBitmap[0]);
			auxiliary_cab2->image(DriveCabBitmap[4]);
			passenger_cab1->image(DriveCabBitmap[0]);
			passenger_cab2->image(DriveCabBitmap[4]);
			brake_cab1->image(DriveCabBitmap[0]);
			brake_cab2->image(DriveCabBitmap[4]);
			compressor_cab1->image(DriveCabBitmap[0]);
			compressor_cab2->image(DriveCabBitmap[4]);
			vvvf_cab1->image(DriveCabBitmap[0]);
			vvvf_cab2->image(DriveCabBitmap[4]);
			fire_cab1->image(DriveCabBitmap[0]);
			fire_cab2->image(DriveCabBitmap[4]);
			panto_cab1->image(DriveCabBitmap[0]);
			panto_cab2->image(DriveCabBitmap[4]);
		}
		tc1_cab->redraw();
		tc2_cab->redraw();
		aircondition_cab1->redraw();
		aircondition_cab2->redraw();
		auxiliary_cab1->redraw();
		auxiliary_cab2->redraw();
		passenger_cab1->redraw();
		passenger_cab2->redraw();
		brake_cab1->redraw();
		brake_cab2->redraw();
		compressor_cab1->redraw();
		compressor_cab2->redraw();
		vvvf_cab1->redraw();
		vvvf_cab1->redraw();
		fire_cab1->redraw();
		fire_cab1->redraw();
		panto_cab1->redraw();
		panto_cab2->redraw();
	}
}

//主按钮图标显示
void Main_Butt_Switch_Function()
{
	{
		//空调
		// if(main_aircondition_butt->value())
		if (Main_Aircondition_Flag == 1)
		{
			main_door_butt->value(0);
			if (mvb.get_ubit(Main_Airc_Butt_Struct[0].Airc_Butt_Port, Main_Airc_Butt_Struct[0].Airc_Butt_Byte, Main_Airc_Butt_Struct[0].Airc_Butt_Bit))
			{
				main_aircondition_butt->image(AirconditionBitmap[1]); //激活故障
			}
			else if (mvb.get_ubit(Main_Airc_Butt_Struct[1].Airc_Butt_Port, Main_Airc_Butt_Struct[1].Airc_Butt_Byte, Main_Airc_Butt_Struct[1].Airc_Butt_Bit))
			{
				main_aircondition_butt->image(AirconditionBitmap[3]); //激活警告
			}
			else // if(mvb.get_ubit(Main_Airc_Butt_Struct[2].Airc_Butt_Port,Main_Airc_Butt_Struct[2].Airc_Butt_Byte,Main_Airc_Butt_Struct[2].Airc_Butt_Bit))
			{
				main_aircondition_butt->image(AirconditionBitmap[5]); //激活正常
			}
		}
		else
		{
			if (mvb.get_ubit(Main_Airc_Butt_Struct[0].Airc_Butt_Port, Main_Airc_Butt_Struct[0].Airc_Butt_Byte, Main_Airc_Butt_Struct[0].Airc_Butt_Bit))
			{
				main_aircondition_butt->image(AirconditionBitmap[0]); //激活故障
			}
			else if (mvb.get_ubit(Main_Airc_Butt_Struct[1].Airc_Butt_Port, Main_Airc_Butt_Struct[1].Airc_Butt_Byte, Main_Airc_Butt_Struct[1].Airc_Butt_Bit))
			{
				main_aircondition_butt->image(AirconditionBitmap[2]); //激活警告
			}
			else // if(mvb.get_ubit(Main_Airc_Butt_Struct[2].Airc_Butt_Port,Main_Airc_Butt_Struct[2].Airc_Butt_Byte,Main_Airc_Butt_Struct[2].Airc_Butt_Bit))
			{
				main_aircondition_butt->image(AirconditionBitmap[4]); //激活正常
			}
		}
		main_aircondition_butt->redraw();
		//门
		// if(main_door_butt->value())
		if (Main_Door_Flag == 1)
		{
			if (mvb.get_ubit(Main_Door_Butt_Struct[0].Door_Butt_Port, Main_Door_Butt_Struct[0].Door_Butt_Byte, Main_Door_Butt_Struct[0].Door_Butt_Bit))
			{
				main_door_butt->image(DoorBitmap[1]); //激活故障
			}
			else if (mvb.get_ubit(Main_Door_Butt_Struct[1].Door_Butt_Port, Main_Door_Butt_Struct[1].Door_Butt_Byte, Main_Door_Butt_Struct[1].Door_Butt_Bit))
			{
				main_door_butt->image(DoorBitmap[3]); //激活警告
			}
			else // if(mvb.get_ubit(Main_Door_Butt_Struct[2].Door_Butt_Port,Main_Door_Butt_Struct[2].Door_Butt_Byte,Main_Door_Butt_Struct[2].Door_Butt_Bit))
			{
				main_door_butt->image(DoorBitmap[5]); //激活正常
			}
		}
		else
		{
			if (mvb.get_ubit(Main_Door_Butt_Struct[0].Door_Butt_Port, Main_Door_Butt_Struct[0].Door_Butt_Byte, Main_Door_Butt_Struct[0].Door_Butt_Bit))
			{
				main_door_butt->image(DoorBitmap[0]); //非激活故障
			}
			else if (mvb.get_ubit(Main_Door_Butt_Struct[1].Door_Butt_Port, Main_Door_Butt_Struct[1].Door_Butt_Byte, Main_Door_Butt_Struct[1].Door_Butt_Bit))
			{
				main_door_butt->image(DoorBitmap[2]); //非激活警告
			}
			else // if(mvb.get_ubit(Main_Door_Butt_Struct[2].Door_Butt_Port,Main_Door_Butt_Struct[2].Door_Butt_Byte,Main_Door_Butt_Struct[2].Door_Butt_Bit))
			{
				main_door_butt->image(DoorBitmap[4]); //非激活正常
			}
		}
		main_door_butt->redraw();
		//制动
		// if(main_brake_butt->value())
		if (Main_Brake_Flag == 1)
		{
			if (mvb.get_ubit(Main_Brake_Butt_Struct[0].Brake_Butt_Port, Main_Brake_Butt_Struct[0].Brake_Butt_Byte, Main_Brake_Butt_Struct[0].Brake_Butt_Bit))
			{
				main_brake_butt->image(BrakeBitmap[1]); //激活故障
			}
			else if (mvb.get_ubit(Main_Brake_Butt_Struct[1].Brake_Butt_Port, Main_Brake_Butt_Struct[1].Brake_Butt_Byte, Main_Brake_Butt_Struct[1].Brake_Butt_Bit))
			{
				main_brake_butt->image(BrakeBitmap[3]); //激活警告
			}
			else // if(mvb.get_ubit(Main_Brake_Butt_Struct[2].Brake_Butt_Port,Main_Brake_Butt_Struct[2].Brake_Butt_Byte,Main_Brake_Butt_Struct[2].Brake_Butt_Bit))
			{
				main_brake_butt->image(BrakeBitmap[5]); //激活正常
			}
		}
		else
		{
			if (mvb.get_ubit(Main_Brake_Butt_Struct[0].Brake_Butt_Port, Main_Brake_Butt_Struct[0].Brake_Butt_Byte, Main_Brake_Butt_Struct[0].Brake_Butt_Bit))
			{
				main_brake_butt->image(BrakeBitmap[0]); //非激活故障
			}
			else if (mvb.get_ubit(Main_Brake_Butt_Struct[1].Brake_Butt_Port, Main_Brake_Butt_Struct[1].Brake_Butt_Byte, Main_Brake_Butt_Struct[1].Brake_Butt_Bit))
			{
				main_brake_butt->image(BrakeBitmap[2]); //非激活警告
			}
			else // if(mvb.get_ubit(Main_Brake_Butt_Struct[2].Brake_Butt_Port,Main_Brake_Butt_Struct[2].Brake_Butt_Byte,Main_Brake_Butt_Struct[2].Brake_Butt_Bit))
			{
				main_brake_butt->image(BrakeBitmap[4]); //非激活正常
			}
		}
		main_brake_butt->redraw();
		//辅助
		// if(main_siv_butt->value())
		if (Main_Siv_Flag == 1)
		{
			if (mvb.get_ubit(0xb, 20, 7) || mvb.get_ubit(0xc, 20, 7) || mvb.get_ubit(0xb, 20, 4) || mvb.get_ubit(0xc, 20, 4))
				main_siv_butt->image(SivBitmap[1]); //激活故障
			else if (mvb.get_ubit(0xb, 20, 6) || mvb.get_ubit(0xc, 20, 6) || mvb.get_ubit(0xb, 20, 3) || mvb.get_ubit(0xc, 20, 3) || mvb.get_ubit(0xb, 20, 5) || mvb.get_ubit(0xc, 20, 5) || mvb.get_ubit(0xb, 20, 2) || mvb.get_ubit(0xc, 20, 2))
				main_siv_butt->image(SivBitmap[3]); //激活警告
			else
				main_siv_butt->image(SivBitmap[5]); //激活正常
		}
		else
		{
			if (mvb.get_ubit(0xb, 20, 7) || mvb.get_ubit(0xc, 20, 7) || mvb.get_ubit(0xb, 20, 4) || mvb.get_ubit(0xc, 20, 4))
				main_siv_butt->image(SivBitmap[0]); //非激活故障
			else if (mvb.get_ubit(0xb, 20, 6) || mvb.get_ubit(0xc, 20, 6) || mvb.get_ubit(0xb, 20, 3) || mvb.get_ubit(0xc, 20, 3) || mvb.get_ubit(0xb, 20, 5) || mvb.get_ubit(0xc, 20, 5) || mvb.get_ubit(0xb, 20, 2) || mvb.get_ubit(0xc, 20, 2))
				main_siv_butt->image(SivBitmap[2]); //非激活警告
			else
				main_siv_butt->image(SivBitmap[4]); //非激活正常
		}
		main_siv_butt->redraw();
		//乘客对讲
		// if(main_passenger_butt->value())
		if (Main_Passenger_Flag == 1)
		{
			if (mvb.get_ubit(0x01, 18, 0))
				main_passenger_butt->image(PassengerBitmap[1]); //激活故障
			else												// if(mvb.get_ubit(0x01,18,1))
				main_passenger_butt->image(PassengerBitmap[5]); //激活正常
																/*else
																  main_passenger_butt->image(PassengerBitmap[3]);//激活警告*/
		}
		else
		{
			if (mvb.get_ubit(0x01, 18, 0))
				main_passenger_butt->image(PassengerBitmap[0]); //非激活故障
			else												// if(mvb.get_ubit(0x01,18,1))
				main_passenger_butt->image(PassengerBitmap[4]); //非激活正常
																/*else
																  main_passenger_butt->image(PassengerBitmap[2]);//非激活警告*/
		}
		main_passenger_butt->redraw();
		//牵引
		// if(main_traction_butt->value())
		if (Main_Traction_Flag == 1)
		{
			if (mvb.get_ubit(0x14, 8, 7) || mvb.get_ubit(0x14, 20, 7) || mvb.get_ubit(0x15, 8, 7) || mvb.get_ubit(0x15, 20, 7))
				main_traction_butt->image(TractionBitmap[1]); //激活故障
			else if (mvb.get_ubit(0x14, 8, 6) || mvb.get_ubit(0x14, 20, 6) || mvb.get_ubit(0x15, 8, 6) || mvb.get_ubit(0x15, 20, 6) || mvb.get_ubit(0x14, 8, 5) || mvb.get_ubit(0x14, 20, 5) || mvb.get_ubit(0x15, 8, 5) || mvb.get_ubit(0x15, 20, 5))
				main_traction_butt->image(TractionBitmap[3]); //激活警告
			else
				main_traction_butt->image(TractionBitmap[5]); //激活正常
		}
		else
		{
			if (mvb.get_ubit(0x14, 8, 7) || mvb.get_ubit(0x14, 18, 7) || mvb.get_ubit(0x15, 8, 7) || mvb.get_ubit(0x15, 18, 7))
				main_traction_butt->image(TractionBitmap[0]); //非激活故障
			else if (mvb.get_ubit(0x14, 8, 6) || mvb.get_ubit(0x14, 18, 6) || mvb.get_ubit(0x15, 8, 6) || mvb.get_ubit(0x15, 18, 6) || mvb.get_ubit(0x14, 8, 5) || mvb.get_ubit(0x14, 18, 5) || mvb.get_ubit(0x15, 8, 5) || mvb.get_ubit(0x15, 18, 5))
				main_traction_butt->image(TractionBitmap[2]); //非激活警告
			else
				main_traction_butt->image(TractionBitmap[4]); //非激活正常
		}
		main_traction_butt->redraw();
		//烟火
		// if(main_fire_butt->value())
		if (Main_Fire_Flag == 1)
		{
			if (mvb.get_ushort(0x16, 14) & 0x0fc0)
				main_fire_butt->image(FireBitmap[1]); //激活故障
			else if (mvb.get_ushort(0x16, 14) & 0x003f)
				main_fire_butt->image(FireBitmap[3]); //激活警告
			else
				main_fire_butt->image(FireBitmap[5]); //激活正常
		}
		else
		{
			if (mvb.get_ushort(0x16, 14) & 0x0fc0)
				main_fire_butt->image(FireBitmap[0]); //非激活故障
			else if (mvb.get_ushort(0x16, 14) & 0x003f)
				main_fire_butt->image(FireBitmap[2]); //非激活警告
			else
				main_fire_butt->image(FireBitmap[4]); //非激活正常
		}
		main_fire_butt->redraw();
		//空压机
		// if(main_compressor_butt->value())
		if (Main_Compressor_Flag == 1)
		{
			if (mvb.get_ubit(0x16, 17, 0) || mvb.get_ubit(0x16, 17, 3))
				main_compressor_butt->image(CompressorBitmap[1]); //激活故障
			else if (mvb.get_ubit(0x16, 17, 1) || mvb.get_ubit(0x16, 17, 4))
				main_compressor_butt->image(CompressorBitmap[3]); //激活警告
			else
				main_compressor_butt->image(CompressorBitmap[5]); //激活正常
		}
		else
		{
			if (mvb.get_ubit(0x16, 17, 0) || mvb.get_ubit(0x16, 17, 3))
				main_compressor_butt->image(CompressorBitmap[0]); //非激活故障
			else if (mvb.get_ubit(0x16, 17, 1) || mvb.get_ubit(0x16, 17, 4))
				main_compressor_butt->image(CompressorBitmap[2]); //非激活警告
			else
				main_compressor_butt->image(CompressorBitmap[4]); //非激活正常
		}
		main_compressor_butt->redraw();
		//受电弓
		// if(main_panto_butt->value())
		if (Main_Panto_Flag == 1)
		{
			if (mvb.get_uchar(0x16, 18) & 0x0303)
				main_panto_butt->image(PantoBitmap[1]); //激活故障
			else
				main_panto_butt->image(PantoBitmap[5]); //激活正常
		}
		else
		{
			if (mvb.get_uchar(0x16, 18) & 0x0303)
				main_panto_butt->image(PantoBitmap[0]); //非激活故障
			else
				main_panto_butt->image(PantoBitmap[4]); //非激活正常
		}
		main_panto_butt->redraw();
	}
}

//切换至空调组
void main_aircondition_cb(Fl_Button *, void *)
{
	if (!group_aircondition_window->visible())
	{
		group_aircondition_window->show();
		label_window->label("空调");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_aircondition_window;
		Main_Aircondition_Flag = 1;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Door_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;
		Airc_Array_Initial();
	}
}

//切换至辅助电源组
void main_auxiliary_cb(Fl_Button *, void *)
{
	if (!group_auxiliary_window->visible())
	{
		group_auxiliary_window->show();
		label_window->label("辅助电源");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_auxiliary_window;
		Main_Siv_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Door_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;
		SIV_Array_Initial();
	}
}

//紧急广播界面切回主界面
void emergency_return_cb(Fl_Button *, void *)
{
	group_maintenance_top->hide();
	group_top->show();
	if (!group_main_window->visible())
	{
		group_main_window->show();
		label_window->label("车门");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_main_window;
	}
	if (!group_door_window->visible())
	{
		group_door_window->show();
		label_window->label("车门");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_door_window;
		Main_Door_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;

		main_aircondition_butt->value(0);
		main_emergency_butt->value(0);
		main_siv_butt->value(0);
		main_passenger_butt->value(0);
		main_brake_butt->value(0);
		main_traction_butt->value(0);
		main_fire_butt->value(0);
		main_compressor_butt->value(0);
		main_panto_butt->value(0);
	}
}

//登录界面返回主运行界面
void login_cancel_cb(Fl_Button *, void *)
{
	group_maintenance_top->hide();
	group_top->show();
	if (!group_main_window->visible())
	{
		group_main_window->show();
		label_window->label("车门");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_main_window;
	}
	if (!group_door_window->visible())
	{
		group_door_window->show();
		label_window->label("车门");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_door_window;
		Main_Door_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;

		main_aircondition_butt->value(0);
		main_emergency_butt->value(0);
		main_siv_butt->value(0);
		main_passenger_butt->value(0);
		main_brake_butt->value(0);
		main_traction_butt->value(0);
		main_fire_butt->value(0);
		main_compressor_butt->value(0);
		main_panto_butt->value(0);
	}
}

//切换至车门界面
void main_door_cb(Fl_Button *, void *)
{
	if (!group_door_window->visible())
	{
		group_door_window->show();
		label_window->label("车门");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_door_window;
		Main_Door_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;
		Door_Array_Initial();
	}
}

//切换至紧急对讲界面
void main_passenger_cb(Fl_Button *, void *)
{
	if (!group_passenger_window->visible())
	{
		group_passenger_window->show();
		label_window->label("紧急对讲");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_passenger_window;
		Main_Passenger_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Door_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;
		Passenger_Array_Initial();
	}
}

//切换至制动界面
void main_brake_cb(Fl_Button *, void *)
{
	if (!group_brake_window->visible())
	{
		group_brake_window->show();
		label_window->label("制动");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_brake_window;
		Main_Brake_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Door_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;
		ParkBrake_Array_Initial();
		Brake_Array_Initial();
	}
}

//切换至牵引界面
void main_traction_cb(Fl_Button *, void *)
{
	if (!group_vvvf_window->visible())
	{
		group_vvvf_window->show();
		label_window->label("牵引");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_vvvf_window;
		Main_Traction_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Door_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;
	}
}

//切换至烟火界面
void main_firesmoke_cb(Fl_Button *, void *)
{
	if (!group_fire_window->visible())
	{
		group_fire_window->show();
		label_window->label("火/烟");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_fire_window;
		Main_Fire_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Door_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;
		FDS_Array_Initial();
	}
}

//切换至空压机界面
void main_aircomp_cb(Fl_Button *, void *)
{
	if (!group_compressor_window->visible())
	{
		group_compressor_window->show();
		label_window->label("空气压缩机");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_compressor_window;
		Main_Compressor_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Door_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Panto_Flag = 0;
		CMP_Array_Initial();
	}
}

//切换至受电弓界面
void main_panto_cb(Fl_Button *, void *)
{
	if (!group_panto_window->visible())
	{
		group_panto_window->show();
		label_window->label("受电弓");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_panto_window;
		Main_Panto_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Door_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		HSCB_Array_Initial();
		Power_Array_Initial();
		Panto_Array_Initial();
	}
}

//切换至主界面
void main_cb(Fl_Button *, void *)
{
	group_maintenance_top->hide();
	group_top->show();
	if (!group_main_window->visible())
	{
		group_main_window->show();
		label_window->label("车门");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_main_window;
	}
	if (!group_door_window->visible())
	{
		group_door_window->show();
		label_window->label("车门");
		if (tempwin_main == NULL)
			group_door_window->hide();
		else
			tempwin_main->hide();
		tempwin_main = group_door_window;
		Main_Door_Flag = 1;
		Main_Aircondition_Flag = 0;
		Main_Siv_Flag = 0;
		Main_Broadcast_Flag = 0;
		Main_Passenger_Flag = 0;
		Main_Brake_Flag = 0;
		Main_Traction_Flag = 0;
		Main_Fire_Flag = 0;
		Main_Compressor_Flag = 0;
		Main_Panto_Flag = 0;

		main_aircondition_butt->value(0);
		main_emergency_butt->value(0);
		main_siv_butt->value(0);
		main_passenger_butt->value(0);
		main_brake_butt->value(0);
		main_traction_butt->value(0);
		main_fire_butt->value(0);
		main_compressor_butt->value(0);
		main_panto_butt->value(0);
	}
}

void Airc_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_Airc[0][i] = Main_Airc1[i];
		Main_Airc[1][i] = Main_Airc2[i];
	}
}

void SIV_Array_Initial()
{
	Main_SIV[0][0] = Main_SIV1[0];
	Main_SIV[0][5] = Main_SIV1[5];
	Main_SIV[1][0] = Main_SIV2[0];
	Main_SIV[1][5] = Main_SIV2[5];
}

void Door_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_Door[0][i] = Main_Door1[i];
		Main_Door[1][i] = Main_Door2[i];
		Main_Door[2][i] = Main_Door3[i];
		Main_Door[3][i] = Main_Door4[i];
		Main_Door[4][i] = Main_Door5[i];
		Main_Door[5][i] = Main_Door6[i];
		Main_Door[6][i] = Main_Door7[i];
		Main_Door[7][i] = Main_Door8[i];
	}
}

void Passenger_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_Passenger[0][i] = Main_Passenger1[i];
		Main_Passenger[1][i] = Main_Passenger2[i];
		Main_Passenger[2][i] = Main_Passenger3[i];
		Main_Passenger[3][i] = Main_Passenger4[i];
	}
}

void ParkBrake_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_ParkBrake[0][i] = Main_ParkBrake1[i];
		Main_ParkBrake[1][i] = Main_ParkBrake2[i];
	}
}

void Brake_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_Brake[0][i] = Main_Brake1[i];
		Main_Brake[1][i] = Main_Brake2[i];
	}
}

void FDS_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_FDS[0][i] = Main_FDS1[i];
	}
}

void CMP_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_CMP[0][i] = Main_CMP1[i];
	}
}

void HSCB_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_HSCB[0][i] = Main_HSCB1[i];
	}
}

void Power_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_Power[0][i] = Main_Power1[i];
	}
}

void Panto_Array_Initial()
{
	for (int i = 0; i < 6; i++)
	{
		Main_Panto[0][i] = Main_Panto1[i];
	}
}
