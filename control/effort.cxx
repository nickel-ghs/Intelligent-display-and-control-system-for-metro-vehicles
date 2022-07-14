/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 10:25:42
 * @LastEditors: ubuntu
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/control/effort.cxx
 */

#include "effort.h"
#include "stdio.h"
/*----------------------------------------------------------------------------------*/

Fl_Effort ::Fl_Effort(int x, int y, int w, int h, const char *l) : Fl_Widget(x, y, w, h, l)
{
  v = 0;
  ff = 0;
}
/*----------------------------------------------------------------------------------*/
void Fl_Effort ::draw(void) //画图
{
  unsigned short i, j;
  fl_color(FL_BLACK);
  fl_rectf(x(), y(), w(), h());
  fl_color((Fl_Color)49);
  fl_rectf(x() + 1, y() + 1, w() - 2, h() - 2);
  fl_color(FL_GREEN);
  if (v == 0)
  {
    return;
  }
  if (ff == 0)
  {
    fl_color(FL_RED);
    j = (unsigned short)(y() + -2 + h() * 0.5);
    for (i = 0; i < v; i++)
    {
      fl_xyline(x() + 1, j + i, x() + w() - 2, j + i);
    }
  }
  else
  {
    j = (unsigned short)(y() + 1 + h() * 0.5);
    for (i = 0; i < v; i++)
    {
      fl_xyline(x() + 1, j - i, x() + w() - 2, j - i);
    }
  }
}
/*------------------------------------------------------------------------------*/
void Fl_Effort ::Set_value(unsigned char m, unsigned char n) //画图
{
  v = (unsigned short)((h() - 2) * 0.5 * n * 0.01);
  ff = m;
}
/*------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
