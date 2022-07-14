/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 10:27:25
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/wrong.h
 */

#ifndef WRONG_H_
#define WRONG_H_
#include <i2cfun.h>
#define WRONGBYTENO 400       //存储故障数组的最大字节数
#define MAXWRONGNO 3600       //故障最大条目数
#define wronginfo_offset 23   //故障内容偏移
#define wronginfo_length 109  //每行总文本长度
#define wronginfo_ReadLeng 72 //故障内容长度
#define grade_offset 5        //故障等级
#define prompt_offset 7       //故障提示
#define guide_length 82       //故障提示长度
#define YES 1                 //故障已确认
#define NO 0                  //故障未确认

struct WrongInfo
{
  unsigned short WrongCode;   //故障条目在文本中的行数
  unsigned short WrongLen;    //故障存储位置
  char WrongList[6];          //故障代码
  tm WrongTime, WrongTimeEnd; //故障出现与消失时间
  char WrongClass[2];         //故障等级
  unsigned char Confirmed;    //故障确认
  char WrongValue[80];        //故障数据
  char WrongPrompt[4][88];    //故障提示
};

void get_wrong();
static void search_wrong();                        //查询现有故障
static void analyse_wrong();                       //分析故障发生和消失
static void wrong_dispear(unsigned short wrongno); //故障消失处理函数
static void wrong_appear(unsigned short wrongno);  //新故障发生处理函数
static void record_wrong_s(WrongInfo *winfo);      //将故障信息存到event.bin文本
static void record_wrong_e(WrongInfo *winfo);
void wrong_show_cur();       //现存故障显示
void event_show_cur();       //故障履历显示
void wrongrecord_init();     //故障履历初始化
char get_cnum();             //统计轻微故障的数目
static void get_confirmno(); //显示中等和严重故障总数及已确认的数目
void wrong_prompt();         //中等和严重故障发生运行界面报警

struct stat statbuf;
unsigned char WrongStatus[WRONGBYTENO];    //故障状态
unsigned char OldWrongStatus[WRONGBYTENO]; //前一次得到的故障状态
unsigned short ListNo = 0;                 //现存故障总数
char Wrong_Page = 0, Event_Page = 0;
struct WrongInfo wrongrecordinfo[1010];
struct WrongInfo wronginfo[MAXWRONGNO]; //存放当前的所有故障信息
static char wrong_time[10][50];         //显示每行的时间存放
static char event_date[16][25];
static char event_time[16][25];
static char wrong_number[10][5];
static char event_number[16][5];
static char Wrong_Total_Number_Temp[5]; //总故障条数暂存
static char Wrong_Total_Page_Temp[4];   //总故障页数暂存
static char Wrong_NO_Page_Temp[4];      //总故障第几数暂存
long row = 1;                           //所选择的故障行数
static char count = 0;                  //主界面确认提示计数器
int ShowingWrongP;                      //用于定位主界面是否确认的故障条目位置
char Count_Medium = 0;                  //中等故障蜂鸣器响计数

#endif
