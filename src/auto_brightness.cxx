/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 10:27:55
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/src/auto_brightness.cxx
 */

#include "head.h"
#include <i2cfun.h>

void bright_auto_process()
{
   int i = 0;
   unsigned short EVbrightvalue = 0;
   unsigned char bright_value[10] = {248, 240, 230, 200, 160, 130, 90, 50, 25, 5};
   unsigned short ev_bright_value[10] = {4, 10, 20, 40, 60, 100, 300, 600, 800, 1000};

   if ((GetEnvBright(&EVbrightvalue) == 1) && (Brightness_Flag == 0))
   {
      //选择ev_bright_value刚好比当前环境亮度亮一点的亮度
      for (i = 0; i < 10; i++)
      {
         if (EVbrightvalue > ev_bright_value[i]) //当前环境亮度
            continue;
         else
            break;
      }

      if (i == 10)
         i = 9;

      SetLcdBright(bright_value[i]);
   }
}
