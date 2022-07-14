#ifndef AIRCONDITION_Set_H_
#define AIRCONDITION_Set_H_

char Air_Set_Flag,AircSet_Fire_Flag,AircSet_Test_Flag;
long AirSet_No;
static char AircSet_Number_Buff[6][10];//车辆号临时存储值
static char AircSet_Temp_Buff[6][15];//实际温度存储量
static char AircSet_Target_Buff[6][15];//目标温度存储量

void Airc_Set_Proccess();

//室内温度
struct AircSet_Indoor  
{
   unsigned int Indoor_Port;
   unsigned int Indoor_Byte;
}AircSet_Indoor_Struct[6]={{0x5,4},{0x6,4},{0x7,4},{0x8,4},{0x9,4},{0xa,4}};

//目标温度
struct AircSet_Target  
{
   unsigned int Target_Port;
   unsigned int Target_Byte;
}AircSet_Target_Struct[6]={{0x5,2},{0x6,2},{0x7,2},{0x8,2},{0x9,2},{0xa,2}};

#endif
