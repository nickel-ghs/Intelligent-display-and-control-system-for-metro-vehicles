#ifndef MAIN_DATA_H_
#define MAIN_DATA_H_

void main_proccess();
void main_direction();
void Main_Butt_Switch_Function();
void Airc_Array_Initial();
void SIV_Array_Initial();
void Door_Array_Initial();
void Passenger_Array_Initial();
void ParkBrake_Array_Initial();
void Brake_Array_Initial();
void FDS_Array_Initial();
void CMP_Array_Initial();
void HSCB_Array_Initial();
void Power_Array_Initial();
void Panto_Array_Initial();

char Main_Aircondition_Flag = 0;
char Main_Siv_Flag = 0;
char Main_Broadcast_Flag = 0;
char Main_Door_Flag = 0;
char Main_Passenger_Flag = 0;
char Main_Brake_Flag = 0;
char Main_Traction_Flag = 0;
char Main_Fire_Flag = 0;
char Main_Compressor_Flag = 0;
char Main_Panto_Flag = 0;
char Main_Passenger_Status_Flag = 0; //用来判断正常状态显示 1:有过其他状态 0:没有过其他状态
char Main_Brake_Status_Flag = 0;
char Main_Airc_Status_Flag = 0;
char Main_SIV_Status_Flag = 0;
char Main_FDS_Status_Flag = 0;
char Main_CMP_Status_Flag = 0;
char Main_Power_Status_Flag = 0;
char Main_Panto_Status_Flag = 0;
char Main_VVVF_Status_Flag = 0;

Fl_Box *Main_Airc[2][6];
Fl_Box *Main_SIV[2][6];
Fl_Box *Main_Door[8][6];
Fl_Box *Main_Passenger[4][6];
Fl_Box *Main_ParkBrake[2][6];
Fl_Box *Main_Brake[2][6];
Fl_Box *Main_FDS[1][6];
Fl_Box *Main_CMP[1][6];
Fl_Box *Main_HSCB[1][6];
Fl_Box *Main_Power[1][6];
Fl_Box *Main_Panto[1][6];

static char Main_NetV_Buff[5];           //网压临时存储值
static char Main_Speed_Buff[5];          //速度临时存储值
static char Main_Restrict_Speed_Buff[5]; //限速临时存储值
static char Main_Number_Buff[6][10];     //车辆号临时存储值
static char Main_Level_Buff[6];          //级位临时存储值
static char Main_Jar_Buff[8];            //主风缸压力临时存储值

char Main_Station_Name[30][20] = {{"------ "}, {"高桥西"}, {"高桥"}, {"梁祝"}, {"芦港"}, {"徐家漕长乐"}, {"望春桥"}, {"泽民"}, {"大卿桥"}, {"西门口"}, {"鼓楼"}, {"东门口(天一广场)"}, {"江厦桥东"}, {"舟孟北路"}, {"樱花公园"}, {"福明路"}, {"世纪大道"}, {"海晏北路"}, {"福庆北路"}, {"盛莫路"}, {"东环南路"}, {"邱隘"}, {"五乡"}, {"宝幢"}, {"邬隘"}, {"大契"}, {"松花江路"}, {"中河路"}, {"长江路"}, {"霞浦"}};

//空调按钮
struct Main_Airc_Butt
{
   unsigned int Airc_Butt_Port;
   unsigned int Airc_Butt_Byte;
   unsigned int Airc_Butt_Bit;
} Main_Airc_Butt_Struct[3] = {{0x01, 19, 4}, {0x01, 19, 5}, {0x01, 19, 6}};

//门
struct Main_Door_Butt1
{
   unsigned int Door_Butt_Port;
   unsigned int Door_Butt_Byte;
   unsigned int Door_Butt_Bit;
} Main_Door_Butt_Struct[3] = {{0x01, 19, 0}, {0x01, 19, 1}, {0x01, 19, 2}};

//制动系统
struct Main_Brake_Butt
{
   unsigned int Brake_Butt_Port;
   unsigned int Brake_Butt_Byte;
   unsigned int Brake_Butt_Bit;
} Main_Brake_Butt_Struct[3] = {{0x01, 18, 3}, {0x01, 18, 4}, {0x01, 18, 5}};

//电网电压
struct Main_NetV
{
   unsigned int NetV_Port;
   unsigned int NetV_Byte;
} Main_NetV_Struct = {0x01, 8};

//速度
struct Main_Speed
{
   unsigned int Speed_Port;
   unsigned int Speed_Byte;
} Main_Speed_Struct = {0x01, 4};

//限速值
struct Main_Restrict_Speed
{
   unsigned int Restrict_Speed_Port;
   unsigned int Restrict_Speed_Byte;
} Main_Restrict_Speed_Struct = {0x01, 6};

//主风缸压力
struct Main_Jar
{
   unsigned int Jar_Port;
   unsigned int Jar_Byte;
} Main_Jar_Struct = {0x01, 14};

//模式
struct Main_Mode
{
   unsigned int Mode_Port;
   unsigned int Mode_Byte;
} Main_Mode_Struct = {0x01, 12};

//空转/打滑
struct Main_Slider
{
   unsigned int Slider_Port;
   unsigned int Slider_Byte;
} Main_Slider_Struct = {0x01, 26};

//工况
struct Main_Oper_Cond
{
   unsigned int Oper_Cond_Port;
   unsigned int Oper_Cond_Byte;
} Main_Oper_Cond_Struct = {0x01, 27};

//空调
struct Main_Airc //一维控制车厢数,二维控制设备个数，三维控制状态个数
{
   unsigned int Airc_Port;
   unsigned int Airc_Byte;
   unsigned int Airc_Bit; //严重故障,中等故障,紧急通风,通风,限制制冷,制冷,停机
} Main_Airc_Struct[6][2][7] = {
    {{{0x05, 25, 7}, {0x05, 24, 0}, {0x05, 11, 4}, {0x05, 11, 6}, {0x05, 11, 7}, {0x05, 15, 5}, {0x05, 10, 3}}, {{0x05, 24, 2}, {0x05, 24, 3}, {0x05, 11, 4}, {0x05, 11, 6}, {0x05, 11, 7}, {0x05, 15, 5}, {0x05, 10, 3}}},
    {{{0x06, 25, 7}, {0x06, 24, 0}, {0x06, 11, 4}, {0x06, 11, 6}, {0x06, 11, 7}, {0x06, 15, 5}, {0x06, 10, 3}}, {{0x06, 24, 2}, {0x06, 24, 3}, {0x06, 11, 4}, {0x06, 11, 6}, {0x06, 11, 7}, {0x06, 15, 5}, {0x06, 10, 3}}},
    {{{0x07, 25, 7}, {0x07, 24, 0}, {0x07, 11, 4}, {0x07, 11, 6}, {0x07, 11, 7}, {0x07, 15, 5}, {0x07, 10, 3}}, {{0x07, 24, 2}, {0x07, 24, 3}, {0x07, 11, 4}, {0x07, 11, 6}, {0x07, 11, 7}, {0x07, 15, 5}, {0x07, 10, 3}}},
    {{{0x08, 25, 7}, {0x08, 24, 0}, {0x08, 11, 4}, {0x08, 11, 6}, {0x08, 11, 7}, {0x08, 15, 5}, {0x08, 10, 3}}, {{0x08, 24, 2}, {0x08, 24, 3}, {0x08, 11, 4}, {0x08, 11, 6}, {0x08, 11, 7}, {0x08, 15, 5}, {0x08, 10, 3}}},
    {{{0x09, 25, 7}, {0x09, 24, 0}, {0x09, 11, 4}, {0x09, 11, 6}, {0x09, 11, 7}, {0x09, 15, 5}, {0x09, 10, 3}}, {{0x09, 24, 2}, {0x09, 24, 3}, {0x09, 11, 4}, {0x09, 11, 6}, {0x09, 11, 7}, {0x09, 15, 5}, {0x09, 10, 3}}},
    {{{0x0a, 25, 7}, {0x0a, 24, 0}, {0x0a, 11, 4}, {0x0a, 11, 6}, {0x0a, 11, 7}, {0x0a, 15, 5}, {0x0a, 10, 3}}, {{0x0a, 24, 2}, {0x0a, 24, 3}, {0x0a, 11, 4}, {0x0a, 11, 6}, {0x0a, 11, 7}, {0x0a, 15, 5}, {0x0a, 10, 3}}}};

//牵引
struct Main_VVVF //只有2、3、4、5车有
{
   unsigned int VVVF_Port;
   unsigned int VVVF_Byte;
   unsigned int VVVF_Bit; //故障,警告,激活,断开
} Main_VVVF_Struct[6][4] = {{{}, {}, {}, {}},
                            {{0x14, 8, 7}, {0x14, 8, 6}, {0x14, 8, 4}, {0x14, 8, 3}},
                            {{0x14, 20, 7}, {0x14, 20, 6}, {0x14, 20, 4}, {0x14, 20, 3}},
                            {{0x15, 8, 7}, {0x15, 8, 6}, {0x15, 8, 4}, {0x15, 8, 3}},
                            {{0x15, 20, 7}, {0x15, 20, 6}, {0x15, 20, 4}, {0x15, 20, 3}},
                            {{}, {}, {}, {}}};

//辅变
struct Main_SIV //只有1、6车有
{
   unsigned int SIV_Port;
   unsigned int SIV_Byte;
   unsigned int SIV_Bit; //严重故障,中等故障,运行,断开
} Main_SIV_Struct[6][2][4] = {{{{0x0b, 20, 7}, {0x0b, 20, 6}, {0x0b, 25, 4}, {0x0b, 21, 7}}, {{0x0b, 20, 4}, {0x0b, 20, 3}, {0x0b, 23, 4}, {0x0b, 20, 0}}},
                              {{{}, {}, {}, {}}, {{}, {}, {}, {}}},
                              {{{}, {}, {}, {}}, {{}, {}, {}, {}}},
                              {{{}, {}, {}, {}}, {{}, {}, {}, {}}},
                              {{{}, {}, {}, {}}, {{}, {}, {}, {}}},
                              {{{0x0c, 20, 7}, {0x0c, 20, 6}, {0x0c, 25, 4}, {0x0c, 21, 7}}, {{0x0c, 20, 4}, {0x0c, 20, 3}, {0x0c, 23, 4}, {0x0c, 20, 0}}}};

//门
struct Main_Door
{
   unsigned int Door_Port;
   unsigned int Door_Byte;
} Main_Door_Struct[8][6] = {
    {{0x19, 1}, {0x19, 9}, {0x19, 17}, {0x19, 25}, {0x20, 1}, {0x20, 9}},
    {{0x19, 0}, {0x19, 8}, {0x19, 16}, {0x19, 24}, {0x20, 0}, {0x20, 8}},
    {{0x19, 3}, {0x19, 11}, {0x19, 19}, {0x19, 27}, {0x20, 3}, {0x20, 11}},
    {{0x19, 2}, {0x19, 10}, {0x19, 18}, {0x19, 26}, {0x20, 2}, {0x20, 10}},
    {{0x19, 5}, {0x19, 13}, {0x19, 21}, {0x19, 29}, {0x20, 5}, {0x20, 13}},
    {{0x19, 4}, {0x19, 12}, {0x19, 20}, {0x19, 28}, {0x20, 4}, {0x20, 12}},
    {{0x19, 7}, {0x19, 15}, {0x19, 23}, {0x19, 31}, {0x20, 7}, {0x20, 15}},
    {{0x19, 6}, {0x19, 14}, {0x19, 22}, {0x19, 30}, {0x20, 6}, {0x20, 14}},
};

//乘客报警
struct Main_Passenger //一维控制车厢数,二维控制设备个数，三维控制状态个数
{
   unsigned int Passenger_Port;
   unsigned int Passenger_Byte;
   unsigned int Passenger_Bit;
} Main_Passenger_Struct[6][4][3] = {{{{0x27, 5, 2}, {0x27, 13, 0}, {0x27, 13, 1}}, {{0x27, 5, 3}, {0x27, 13, 2}, {0x27, 13, 3}}, {{0x27, 5, 4}, {0x27, 13, 4}, {0x27, 13, 5}}, {{0x27, 5, 5}, {0x27, 13, 6}, {0x27, 13, 7}}},
                                    {{{0x27, 5, 7}, {0x27, 12, 0}, {0x27, 12, 1}}, {{0x27, 4, 0}, {0x27, 12, 2}, {0x27, 12, 3}}, {{0x27, 4, 1}, {0x27, 12, 4}, {0x27, 12, 5}}, {{0x27, 4, 2}, {0x27, 12, 6}, {0x27, 12, 7}}},
                                    {{{0x27, 4, 4}, {0x27, 15, 0}, {0x27, 15, 1}}, {{0x27, 4, 5}, {0x27, 15, 2}, {0x27, 15, 3}}, {{0x27, 4, 6}, {0x27, 15, 4}, {0x27, 15, 5}}, {{0x27, 4, 7}, {0x27, 15, 6}, {0x27, 15, 7}}},
                                    {{{0x27, 6, 4}, {0x27, 14, 0}, {0x27, 14, 1}}, {{0x27, 6, 5}, {0x27, 14, 2}, {0x27, 14, 3}}, {{0x27, 6, 6}, {0x27, 14, 4}, {0x27, 14, 5}}, {{0x27, 6, 7}, {0x27, 14, 6}, {0x27, 14, 7}}},
                                    {{{0x27, 7, 7}, {0x27, 17, 0}, {0x27, 17, 1}}, {{0x27, 6, 0}, {0x27, 17, 2}, {0x27, 17, 3}}, {{0x27, 6, 1}, {0x27, 17, 4}, {0x27, 17, 5}}, {{0x27, 6, 2}, {0x27, 17, 6}, {0x27, 17, 7}}},
                                    {{{0x27, 7, 2}, {0x27, 16, 0}, {0x27, 16, 1}}, {{0x27, 7, 3}, {0x27, 16, 2}, {0x27, 16, 3}}, {{0x27, 7, 4}, {0x27, 16, 4}, {0x27, 16, 5}}, {{0x27, 7, 5}, {0x27, 16, 6}, {0x27, 16, 7}}}};

//停放制动
struct Main_ParkBrake //取每个设备的缓解位
{
   unsigned int ParkBrake_Port;
   unsigned int ParkBrake_Byte;
   unsigned int ParkBrake_Bit;
} Main_ParkBrake_Struct[6] = {{0x16, 1, 0}, {0x16, 1, 1}, {0x16, 1, 2}, {0x16, 1, 3}, {0x16, 1, 4}, {0x16, 1, 5}};

//空气制动
struct Main_Brake //一维控制车厢数,二维控制设备个数，三维控制状态个数
{
   unsigned int Brake_Port;
   unsigned int Brake_Byte;
   unsigned int Brake_Bit; //切除,故障,警告,施加,缓解
} Main_Brake_Struct[6][2][5] = {{{{0x16, 3, 3}, {0x16, 3, 2}, {0x16, 3, 4}, {0x16, 3, 0}, {0x16, 3, 1}}, {{0x16, 2, 0}, {0x16, 3, 7}, {0x16, 2, 1}, {0x16, 3, 5}, {0x16, 3, 6}}},
                                {{{0x16, 2, 5}, {0x16, 2, 4}, {0x16, 2, 6}, {0x16, 2, 2}, {0x16, 2, 3}}, {{0x16, 5, 2}, {0x16, 5, 1}, {0x16, 5, 3}, {0x16, 2, 7}, {0x16, 5, 0}}},
                                {{{0x16, 5, 7}, {0x16, 5, 6}, {0x16, 4, 0}, {0x16, 5, 4}, {0x16, 5, 5}}, {{0x16, 4, 4}, {0x16, 4, 3}, {0x16, 4, 5}, {0x16, 4, 1}, {0x16, 4, 2}}},
                                {{{0x16, 7, 1}, {0x16, 7, 0}, {0x16, 7, 2}, {0x16, 4, 6}, {0x16, 4, 7}}, {{0x16, 7, 6}, {0x16, 7, 5}, {0x16, 7, 7}, {0x16, 7, 3}, {0x16, 7, 4}}},
                                {{{0x16, 6, 3}, {0x16, 6, 2}, {0x16, 6, 4}, {0x16, 6, 0}, {0x16, 6, 1}}, {{0x16, 9, 0}, {0x16, 6, 7}, {0x16, 9, 1}, {0x16, 6, 5}, {0x16, 6, 6}}},
                                {{{0x16, 9, 5}, {0x16, 9, 4}, {0x16, 9, 6}, {0x16, 9, 2}, {0x16, 9, 3}}, {{0x16, 8, 2}, {0x16, 8, 1}, {0x16, 8, 3}, {0x16, 9, 7}, {0x16, 8, 0}}}};

//烟火
struct Main_FDS //一维控制车厢数,二维控制设备个数，三维控制状态个数
{
   unsigned int FDS_Port;
   unsigned int FDS_Byte;
   unsigned int FDS_Bit;
} Main_FDS_Struct[6][1][2] = {{{{0x16, 15, 0}, {0x16, 15, 6}}},
                              {{{0x16, 15, 1}, {0x16, 15, 7}}},
                              {{{0x16, 15, 2}, {0x16, 14, 0}}},
                              {{{0x16, 15, 3}, {0x16, 14, 1}}},
                              {{{0x16, 15, 4}, {0x16, 14, 2}}},
                              {{{0x16, 15, 5}, {0x16, 14, 3}}}};

//空压机
struct Main_CMP //一维控制车厢数,二维控制设备个数，三维控制状态个数
{
   unsigned int CMP_Port;
   unsigned int CMP_Byte;
   unsigned int CMP_Bit;
} Main_CMP_Struct[6][1][3] = {{{{}, {}, {}}},
                              {{{}, {}, {}}},
                              {{{0x16, 17, 0}, {0x16, 17, 1}, {0x16, 17, 2}}},
                              {{{0x16, 17, 3}, {0x16, 17, 4}, {0x16, 17, 5}}},
                              {{{}, {}, {}}},
                              {{{}, {}, {}}}};

// HSCB
struct Main_HSCB
{
   unsigned int HSCB_Port;
   unsigned int HSCB_Byte;
   unsigned int HSCB_Bit;
} Main_HSCB_Struct[6] = {{}, {0x10, 23, 5}, {0x11, 23, 5}, {0x12, 23, 5}, {0x13, 23, 5}, {}};

//车间电源
struct Main_Power //一维控制车厢数,二维控制设备个数，三维控制状态个数
{
   unsigned int Power_Port;
   unsigned int Power_Byte;
   unsigned int Power_Bit;
} Main_Power_Struct[6][1][2] = {{{{}, {}}},
                                {{{0x16, 19, 0}, {0x16, 19, 1}}},
                                {{{}, {}}},
                                {{{}, {}}},
                                {{{0x16, 19, 2}, {0x16, 19, 3}}},
                                {{{}, {}}}};

//受电弓
struct Main_Panto //一维控制车厢数,二维控制设备个数，三维控制状态个数
{
   unsigned int Panto_Port;
   unsigned int Panto_Byte;
   unsigned int Panto_Bit;
} Main_Panto_Struct[6][1][5] = {{{{}, {}, {}, {}, {}}},
                                {{{0x16, 19, 6}, {0x16, 18, 0}, {0x16, 18, 1}, {0x16, 18, 2}, {0x16, 18, 3}}},
                                {{{}, {}, {}, {}, {}}},
                                {{{}, {}, {}, {}, {}}},
                                {{{0x16, 19, 7}, {0x16, 18, 4}, {0x16, 18, 5}, {0x16, 18, 6}, {0x16, 18, 7}}},
                                {{{}, {}, {}, {}, {}}}};

//门回路左
struct Main_DoorLoop_L
{
   unsigned int DoorLoop_L_Port;
   unsigned int DoorLoop_L_Byte;
   unsigned int DoorLoop_L_Bit;
} Main_DoorLoop_L_Struct[6] = {{0x20, 19, 0}, {0x20, 19, 2}, {0x20, 19, 4}, {0x20, 19, 6}, {0x20, 18, 0}, {0x20, 18, 2}};

//门回路右
struct Main_DoorLoop_R
{
   unsigned int DoorLoop_R_Port;
   unsigned int DoorLoop_R_Byte;
   unsigned int DoorLoop_R_Bit;
} Main_DoorLoop_R_Struct[6] = {{0x20, 19, 1}, {0x20, 19, 3}, {0x20, 19, 5}, {0x20, 19, 7}, {0x20, 18, 1}, {0x20, 18, 3}};

#endif
