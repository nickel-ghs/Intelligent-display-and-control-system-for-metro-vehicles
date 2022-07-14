/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-24 11:16:09
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/BrakeCheck.h
 */
#ifndef BRAKE_CHECK_H_
#define BRAKE_CHECK_H_

void BrakeCheck_proccess();

char BrakeCheck_Start_Flag = 0;
static char BrakeCheck_Load_Buff[6][10]; //载荷临时存储量
char BrakeCheck_Array[4][10] = {"成功", "失败", "激活", "无法激活"};

//载重
struct Brake_Check_Load
{
   unsigned int Load_Port;
   unsigned int Load_Byte;
} Brake_Check_Load_Struct[6] = {{0x16, 20}, {0x16, 22}, {0x16, 24}, {0x16, 26}, {0x16, 28}, {0x16, 30}}; //

//自检结果
struct Brake_Check_Result
{
   unsigned int Result_Port;
   unsigned int Result_Byte;
   unsigned int Result_Bit; //成功、失败、激活、无法激活
} Brake_Check_Result_Struct[2][4] = {{{0x16, 11, 1}, {0x16, 11, 2}, {0x16, 11, 0}, {0x16, 11, 3}},
                                     {{0x16, 11, 5}, {0x16, 11, 6}, {0x16, 11, 4}, {0x16, 11, 7}}};

#endif
