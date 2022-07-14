#include "../surface/train-ningbo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mvb.h>
#include <i2cfun.h>
#include <unistd.h>
#include <FL/Fl_Group.H>
#include <FL/Fl.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>

extern int tc_no;
extern char vcmflag;

extern Fl_Group *tempwin;
extern Fl_Group *tempwin_main; //主界面中各组的切换

/*------------------图标调用变量---------------------*/
extern Fl_PNG_Image *DriveCabBitmap[8]; //司机室占用和方向图标
extern Fl_PNG_Image *AirconditionBitmap[6];
extern Fl_PNG_Image *SivBitmap[6];
extern Fl_PNG_Image *DoorBitmap[6];
extern Fl_PNG_Image *PassengerBitmap[6];
extern Fl_PNG_Image *BrakeBitmap[6];
extern Fl_PNG_Image *TractionBitmap[6];
extern Fl_PNG_Image *FireBitmap[6];
extern Fl_PNG_Image *CompressorBitmap[6];
extern Fl_PNG_Image *PantoBitmap[6];
extern Fl_PNG_Image *Main_Airc_Status[8];      //空调状态
extern Fl_PNG_Image *Main_SIV_Status[10];      //辅变状态
extern Fl_PNG_Image *Main_Door_Status[8];      //门状态
extern Fl_PNG_Image *Main_Passenger_Status[4]; //乘客报警状态
extern Fl_PNG_Image *Main_ParkBrake_Status[2]; //停放制动状态
extern Fl_PNG_Image *Main_Brake_Status[6];     //制动状态
extern Fl_PNG_Image *Main_FDS_Status[3];       //烟火状态
extern Fl_PNG_Image *Main_CMP_Status[4];       //空压机状态
extern Fl_PNG_Image *Main_HSCB_Status[2];      // HSCB状态
extern Fl_PNG_Image *Main_Power_Status[2];     //车间电源状态
extern Fl_PNG_Image *Main_Panto_Status[5];     //受电弓状态
extern Fl_PNG_Image *Main_VVVF_Status[4];      //牵引状态
extern Fl_PNG_Image *Station_DaQi[2];          //站点显示中的大碶站
/*------------------图标调用变量---------------------*/

void image_deal_proccess(); //图标处理函数
void Door_Array_Initial();  //主运行界面门初始化函数
void Broadcast_Init();      //紧急广播界面初始化函数
void sleep_proccess();      //延时复位函数
void hmi_synchro();         //时间同步
void init_pit();            //初始化端口
void init_ver();            //初始化版本界面函数

/*------------------各界面函数调用---------------------*/
void Main_Proccess();
void net_proccess();
void ioA_proccess();
void ioB_proccess();
void ioC_proccess();
void Basedata_Proccess();
void Airc_Set_Proccess();
void BrakeCheck_proccess();
void transport_proccess();
void portdata_proccess();
void ver_process();
void total_proccess();
void line_proccess();
void station_set_proccess();
void DCU_Proccess();
void SIV_Proccess();
void diameter_proccess();
void acceleration_proccess();
void set_cab_proccess();
void get_wrong();
void wrong_show_cur();
void event_show_cur();
void wrong_prompt();
void DCUm_Proccess();
void Passby_Proccess();
void bright_auto_process();
/*------------------各界面函数调用---------------------*/

extern char AircSet_Fire_Flag;
extern char AircSet_Test_Flag;
extern char Air_Set_Flag;
extern char time_set_flag;
extern char time_update_flag;
extern short pit_num[200];
extern char pit_size[200];
extern char Broadcast_Speaker_Flag, Broadcast_Pre_Flag, Broadcast_Next_Flag, Broadcast_in_Flag, Broadcast_out_Flag;
extern char station_Set_Flag;
extern char Line_Select_Flag;
extern char Main_Door_Flag;
extern char diameter_set_flag;
extern char CarID_set_flag;
extern char time_set_flag;
extern int total_set_flag;
extern char BrakeCheck_Start_Flag;
extern long Buzzer_Switch_No; //蜂鸣器控制
extern char Broadcast_Confirm_Flag;
extern char Set_Cab_Flag;
extern char Brightness_Flag; //手动和自动模式变量控制
