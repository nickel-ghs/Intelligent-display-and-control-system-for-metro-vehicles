/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 16:51:38
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/SIV.h
 */
#ifndef SIV_DATA_H_
#define SIV_DATA_H_

static long SIV_Car_NO = 1;
char SIV_Buff[17][10];

void SIV_Clear();
void SIV_Proccess();

struct SIV_Data
{
   unsigned int SIV_Port;
   unsigned int SIV_Byte;
} SIV_Data_Struct[2][17] = {{{0xb, 26}, {0xb, 28}, {0xd, 0}, {0xd, 2}, {0xd, 4}, {0xd, 6}, {0xd, 8}, {0xd, 10}, {0xd, 12}, {0xd, 14}, {0xd, 16}, {0xd, 18}, {0xd, 20}, {0xd, 22}, {0xd, 24}, {0xd, 26}, {0xd, 28}},
                            {{0xc, 26}, {0xc, 28}, {0xe, 0}, {0xe, 2}, {0xe, 4}, {0xe, 6}, {0xe, 8}, {0xe, 10}, {0xe, 12}, {0xe, 14}, {0xe, 16}, {0xe, 18}, {0xe, 20}, {0xe, 22}, {0xe, 24}, {0xe, 26}, {0xe, 28}}};

struct SIV_Switch
{
   unsigned int Switch_Port;
   unsigned int Switch_Byte;
   unsigned int Switch_Bit;
} SIV_Switch_Struct[2][7] = {{{0xb, 19, 5}, {0xb, 19, 4}, {0xb, 19, 2}, {0xb, 19, 1}, {0xb, 23, 6}, {0xb, 23, 4}, {0xb, 25, 4}},
                             {{0xc, 19, 5}, {0xc, 19, 4}, {0xc, 19, 2}, {0xc, 19, 1}, {0xc, 23, 6}, {0xc, 23, 4}, {0xc, 25, 4}}};
#endif
