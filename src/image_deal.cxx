#include "head.h"
#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>

Fl_PNG_Image *DriveCabBitmap[8];     //司机室占用和方向图标
Fl_PNG_Image *AirconditionBitmap[6]; //空调图标
Fl_PNG_Image *SivBitmap[6];          //辅助电源图标
Fl_PNG_Image *DoorBitmap[6];         //门图标
Fl_PNG_Image *PassengerBitmap[6];    //乘客对讲图标
Fl_PNG_Image *BrakeBitmap[6];        //制动图标
Fl_PNG_Image *TractionBitmap[6];     //牵引图标
Fl_PNG_Image *FireBitmap[6];         //烟火图标
Fl_PNG_Image *CompressorBitmap[6];   //空压机图标
Fl_PNG_Image *PantoBitmap[6];        //受电弓图标

Fl_PNG_Image *Main_Airc_Status[8];      //空调状态
Fl_PNG_Image *Main_SIV_Status[10];      //辅变状态
Fl_PNG_Image *Main_Door_Status[8];      //门状态
Fl_PNG_Image *Main_Passenger_Status[4]; //乘客报警状态
Fl_PNG_Image *Main_ParkBrake_Status[2]; //停放制动状态
Fl_PNG_Image *Main_Brake_Status[6];     //制动状态
Fl_PNG_Image *Main_FDS_Status[3];       //烟火状态
Fl_PNG_Image *Main_CMP_Status[4];       //空压机状态
Fl_PNG_Image *Main_HSCB_Status[2];      // HSCB状态
Fl_PNG_Image *Main_Power_Status[2];     //车间电源状态
Fl_PNG_Image *Main_Panto_Status[5];     //受电弓状态
Fl_PNG_Image *Main_VVVF_Status[4];      //牵引状态

Fl_PNG_Image *Station_DaQi[2]; //站点显示中的大碶站

//图片选择显示
void image_deal_proccess()
{
  //站点显示中的大碶站
  Station_DaQi[0] = new Fl_PNG_Image("logo/station_daqi.png");       //顶部显示
  Station_DaQi[1] = new Fl_PNG_Image("logo/station_daqi_white.png"); //站点设置界面显示
  //司机室占有和方向
  DriveCabBitmap[0] = new Fl_PNG_Image("logo/chetou_L_0.png"); //无占有无方向
  DriveCabBitmap[1] = new Fl_PNG_Image("logo/chetou_L_1.png"); //无占有有方向
  DriveCabBitmap[2] = new Fl_PNG_Image("logo/chetou_L_2.png"); //有占有无方向
  DriveCabBitmap[3] = new Fl_PNG_Image("logo/chetou_L_3.png"); //有占有有方向
  DriveCabBitmap[4] = new Fl_PNG_Image("logo/chetou_R_0.png"); //无占有无方向
  DriveCabBitmap[5] = new Fl_PNG_Image("logo/chetou_R_1.png"); //无占有有方向
  DriveCabBitmap[6] = new Fl_PNG_Image("logo/chetou_R_2.png"); //有占有无方向
  DriveCabBitmap[7] = new Fl_PNG_Image("logo/chetou_R_3.png"); //有占有有方向

  //空调图标
  AirconditionBitmap[0] = new Fl_PNG_Image("logo/OpButton_1_2.png"); //非激活故障
  AirconditionBitmap[1] = new Fl_PNG_Image("logo/OpButton_1_3.png"); //激活故障
  AirconditionBitmap[2] = new Fl_PNG_Image("logo/OpButton_1_4.png"); //非激活警告
  AirconditionBitmap[3] = new Fl_PNG_Image("logo/OpButton_1_5.png"); //激活警告
  AirconditionBitmap[4] = new Fl_PNG_Image("logo/OpButton_1_6.png"); //非激活正常
  AirconditionBitmap[5] = new Fl_PNG_Image("logo/OpButton_1_7.png"); //激活正常

  //辅助电源图标
  SivBitmap[0] = new Fl_PNG_Image("logo/OpButton_2_2.png"); //非激活故障
  SivBitmap[1] = new Fl_PNG_Image("logo/OpButton_2_3.png"); //激活故障
  SivBitmap[2] = new Fl_PNG_Image("logo/OpButton_2_4.png"); //非激活警告
  SivBitmap[3] = new Fl_PNG_Image("logo/OpButton_2_5.png"); //激活警告
  SivBitmap[4] = new Fl_PNG_Image("logo/OpButton_2_6.png"); //非激活正常
  SivBitmap[5] = new Fl_PNG_Image("logo/OpButton_2_7.png"); //激活正常

  //门图标
  DoorBitmap[0] = new Fl_PNG_Image("logo/OpButton_4_2.png"); //非激活故障
  DoorBitmap[1] = new Fl_PNG_Image("logo/OpButton_4_3.png"); //激活故障
  DoorBitmap[2] = new Fl_PNG_Image("logo/OpButton_4_4.png"); //非激活警告
  DoorBitmap[3] = new Fl_PNG_Image("logo/OpButton_4_5.png"); //激活警告
  DoorBitmap[4] = new Fl_PNG_Image("logo/OpButton_4_6.png"); //非激活正常
  DoorBitmap[5] = new Fl_PNG_Image("logo/OpButton_4_7.png"); //激活正常

  //乘客对讲图标
  PassengerBitmap[0] = new Fl_PNG_Image("logo/OpButton_5_2.png"); //非激活故障
  PassengerBitmap[1] = new Fl_PNG_Image("logo/OpButton_5_3.png"); //激活故障
  PassengerBitmap[2] = new Fl_PNG_Image("logo/OpButton_5_4.png"); //非激活警告
  PassengerBitmap[3] = new Fl_PNG_Image("logo/OpButton_5_5.png"); //激活警告
  PassengerBitmap[4] = new Fl_PNG_Image("logo/OpButton_5_6.png"); //非激活正常
  PassengerBitmap[5] = new Fl_PNG_Image("logo/OpButton_5_7.png"); //激活正常

  //制动图标
  BrakeBitmap[0] = new Fl_PNG_Image("logo/OpButton_6_2.png"); //非激活故障
  BrakeBitmap[1] = new Fl_PNG_Image("logo/OpButton_6_3.png"); //激活故障
  BrakeBitmap[2] = new Fl_PNG_Image("logo/OpButton_6_4.png"); //非激活警告
  BrakeBitmap[3] = new Fl_PNG_Image("logo/OpButton_6_5.png"); //激活警告
  BrakeBitmap[4] = new Fl_PNG_Image("logo/OpButton_6_6.png"); //非激活正常
  BrakeBitmap[5] = new Fl_PNG_Image("logo/OpButton_6_7.png"); //激活正常

  //牵引图标
  TractionBitmap[0] = new Fl_PNG_Image("logo/OpButton_7_2.png"); //非激活故障
  TractionBitmap[1] = new Fl_PNG_Image("logo/OpButton_7_3.png"); //激活故障
  TractionBitmap[2] = new Fl_PNG_Image("logo/OpButton_7_4.png"); //非激活警告
  TractionBitmap[3] = new Fl_PNG_Image("logo/OpButton_7_5.png"); //激活警告
  TractionBitmap[4] = new Fl_PNG_Image("logo/OpButton_7_6.png"); //非激活正常
  TractionBitmap[5] = new Fl_PNG_Image("logo/OpButton_7_7.png"); //激活正常

  //烟火图标
  FireBitmap[0] = new Fl_PNG_Image("logo/OpButton_8_2.png"); //非激活故障
  FireBitmap[1] = new Fl_PNG_Image("logo/OpButton_8_3.png"); //激活故障
  FireBitmap[2] = new Fl_PNG_Image("logo/OpButton_8_4.png"); //非激活警告
  FireBitmap[3] = new Fl_PNG_Image("logo/OpButton_8_5.png"); //激活警告
  FireBitmap[4] = new Fl_PNG_Image("logo/OpButton_8_6.png"); //非激活正常
  FireBitmap[5] = new Fl_PNG_Image("logo/OpButton_8_7.png"); //激活正常

  //空压机图标
  CompressorBitmap[0] = new Fl_PNG_Image("logo/OpButton_9_2.png"); //非激活故障
  CompressorBitmap[1] = new Fl_PNG_Image("logo/OpButton_9_3.png"); //激活故障
  CompressorBitmap[2] = new Fl_PNG_Image("logo/OpButton_9_4.png"); //非激活警告
  CompressorBitmap[3] = new Fl_PNG_Image("logo/OpButton_9_5.png"); //激活警告
  CompressorBitmap[4] = new Fl_PNG_Image("logo/OpButton_9_6.png"); //非激活正常
  CompressorBitmap[5] = new Fl_PNG_Image("logo/OpButton_9_7.png"); //激活正常

  //受电弓图标
  PantoBitmap[0] = new Fl_PNG_Image("logo/OpButton_10_2.png"); //非激活故障
  PantoBitmap[1] = new Fl_PNG_Image("logo/OpButton_10_3.png"); //激活故障
  PantoBitmap[2] = new Fl_PNG_Image("logo/OpButton_10_4.png"); //非激活警告
  PantoBitmap[3] = new Fl_PNG_Image("logo/OpButton_10_5.png"); //激活警告
  PantoBitmap[4] = new Fl_PNG_Image("logo/OpButton_10_6.png"); //非激活正常
  PantoBitmap[5] = new Fl_PNG_Image("logo/OpButton_10_7.png"); //激活正常

  //空调状态
  Main_Airc_Status[0] = new Fl_PNG_Image("logo/TS_AirCon_1.png"); //故障
  Main_Airc_Status[1] = new Fl_PNG_Image("logo/TS_AirCon_2.png"); //警告
  Main_Airc_Status[2] = new Fl_PNG_Image("logo/TS_AirCon_3.png"); //紧急通风
  Main_Airc_Status[3] = new Fl_PNG_Image("logo/TS_AirCon_4.png"); //通风
  Main_Airc_Status[4] = new Fl_PNG_Image("logo/TS_AirCon_5.png"); //限制制冷
  Main_Airc_Status[5] = new Fl_PNG_Image("logo/TS_AirCon_6.png"); //运行
  Main_Airc_Status[6] = new Fl_PNG_Image("logo/TS_AirCon_7.png"); //关闭
  Main_Airc_Status[7] = new Fl_PNG_Image("logo/TS_AirCon_z.png"); //未知

  //辅助状态
  Main_SIV_Status[0] = new Fl_PNG_Image("logo/TS_HBU_1.png");   //辅助电源故障
  Main_SIV_Status[1] = new Fl_PNG_Image("logo/TS_HBU_2.png");   //辅助电源警告
  Main_SIV_Status[2] = new Fl_PNG_Image("logo/TS_HBU_4.png");   //辅助电源运行
  Main_SIV_Status[3] = new Fl_PNG_Image("logo/TS_HBU_5.png");   //辅助电源断开
  Main_SIV_Status[4] = new Fl_PNG_Image("logo/TS_HBU_z.png");   //辅助电源未知
  Main_SIV_Status[5] = new Fl_PNG_Image("logo/TS_HBUDC_1.png"); //充电机故障
  Main_SIV_Status[6] = new Fl_PNG_Image("logo/TS_HBUDC_2.png"); //充电机警告
  Main_SIV_Status[7] = new Fl_PNG_Image("logo/TS_HBUDC_4.png"); //充电机运行
  Main_SIV_Status[8] = new Fl_PNG_Image("logo/TS_HBUDC_5.png"); //充电机断开
  Main_SIV_Status[9] = new Fl_PNG_Image("logo/TS_HBUDC_z.png"); //充电机断开

  //门
  Main_Door_Status[0] = new Fl_PNG_Image("logo/door_1.png"); //紧急
  Main_Door_Status[1] = new Fl_PNG_Image("logo/door_2.png"); //切除
  Main_Door_Status[2] = new Fl_PNG_Image("logo/door_3.png"); //故障
  Main_Door_Status[3] = new Fl_PNG_Image("logo/door_4.png"); //警告
  Main_Door_Status[4] = new Fl_PNG_Image("logo/door_5.png"); //障碍物
  Main_Door_Status[5] = new Fl_PNG_Image("logo/door_6.png"); //开
  Main_Door_Status[6] = new Fl_PNG_Image("logo/door_7.png"); //关
  Main_Door_Status[7] = new Fl_PNG_Image("logo/door_z.png"); //未知

  //乘客报警
  Main_Passenger_Status[0] = new Fl_PNG_Image("logo/passenger_1.png"); //故障
  Main_Passenger_Status[1] = new Fl_PNG_Image("logo/passenger_2.png"); //呼叫
  Main_Passenger_Status[2] = new Fl_PNG_Image("logo/passenger_3.png"); //对讲
  Main_Passenger_Status[3] = new Fl_PNG_Image("logo/passenger_4.png"); //正常

  //停放制动
  Main_ParkBrake_Status[0] = new Fl_PNG_Image("logo/TS_Brake_1.png"); //施加
  Main_ParkBrake_Status[1] = new Fl_PNG_Image("logo/TS_Brake_0.png"); //缓解

  //空气制动
  Main_Brake_Status[0] = new Fl_PNG_Image("logo/TS_Brake_2.png"); //切除
  Main_Brake_Status[1] = new Fl_PNG_Image("logo/TS_Brake_4.png"); //故障
  Main_Brake_Status[2] = new Fl_PNG_Image("logo/TS_Brake_5.png"); //警告
  Main_Brake_Status[3] = new Fl_PNG_Image("logo/TS_Brake_6.png"); //施加
  Main_Brake_Status[4] = new Fl_PNG_Image("logo/TS_Brake_8.png"); //缓解
  Main_Brake_Status[5] = new Fl_PNG_Image("logo/TS_Brake_z.png"); //未知

  //烟火系统
  Main_FDS_Status[0] = new Fl_PNG_Image("logo/TS_FireDec_1.png"); //报警
  Main_FDS_Status[1] = new Fl_PNG_Image("logo/TS_FireDec_2.png"); //故障
  Main_FDS_Status[2] = new Fl_PNG_Image("logo/TS_FireDec_0.png"); //未检测到信息

  //空压机
  Main_CMP_Status[0] = new Fl_PNG_Image("logo/TS_Comp_1.png"); //故障
  Main_CMP_Status[1] = new Fl_PNG_Image("logo/TS_Comp_2.png"); //警告
  Main_CMP_Status[2] = new Fl_PNG_Image("logo/TS_Comp_3.png"); //运行
  Main_CMP_Status[3] = new Fl_PNG_Image("logo/TS_Comp_4.png"); //断开

  // HSCB
  Main_HSCB_Status[0] = new Fl_PNG_Image("logo/TS_HSCB_1.png"); //合上
  Main_HSCB_Status[1] = new Fl_PNG_Image("logo/TS_HSCB_2.png"); //断开

  //车间电源
  Main_Power_Status[0] = new Fl_PNG_Image("logo/TS_Wshop_1.png"); //供电
  Main_Power_Status[1] = new Fl_PNG_Image("logo/TS_Wshop_2.png"); //未供电

  //受电弓
  Main_Panto_Status[0] = new Fl_PNG_Image("logo/TS_Panto_1.png"); //本弓隔离
  Main_Panto_Status[1] = new Fl_PNG_Image("logo/TS_Panto_2.png"); //升弓故障
  Main_Panto_Status[2] = new Fl_PNG_Image("logo/TS_Panto_3.png"); //降弓故障
  Main_Panto_Status[3] = new Fl_PNG_Image("logo/TS_Panto_4.png"); //升弓
  Main_Panto_Status[4] = new Fl_PNG_Image("logo/TS_Panto_5.png"); //降弓
  Main_Panto_Status[5] = new Fl_PNG_Image("logo/TS_Panto_z.png"); //未知

  //牵引系统
  Main_VVVF_Status[0] = new Fl_PNG_Image("logo/TS_VVVF_1.png"); //故障
  Main_VVVF_Status[1] = new Fl_PNG_Image("logo/TS_VVVF_2.png"); //警告
  Main_VVVF_Status[2] = new Fl_PNG_Image("logo/TS_VVVF_3.png"); //激活
  Main_VVVF_Status[3] = new Fl_PNG_Image("logo/TS_VVVF_4.png"); //断开
}
