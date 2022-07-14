#include<time.h>

#define WRONGBYTENO 500   //存储故障数组的最大下标数
#define MAXWRONGNO 3600   //故障最大条目数
#define YES 1  //故障已确认
#define NO 0   //故障未确认
#define MAXROW 10  //每页最多故障行数
extern unsigned short ListNo;   //现存故障总数目
void wrong_show_cur();  //在表格中显示当前存在的故障数据

struct  WrongInfo
{
  unsigned short WrongCode;//故障条目在文本中的行数
  unsigned short WrongLen;//故障存储位置
  char WrongList[6];//故障代码
  tm WrongTime,WrongTimeEnd;//故障出现与消失时间
  char WrongClass[2];//故障等级
  unsigned char Confirmed;//故障确认
  char WrongValue[80];//故障数据
  char WrongPrompt[4][80];//故障提示
};

/*在主界面上显示发生的故障及故障提示*/
void wrong_prompt();
