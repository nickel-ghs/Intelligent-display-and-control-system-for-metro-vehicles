/*
 * @Author: your name
 * @Date: 2022-06-12 19:12:08
 * @LastEditTime: 2022-06-25 10:25:50
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /ningbo/control/effort.h
 */

#ifndef _EFFORT_H_
#define _EFFORT_H_
/*----------------------------------------------------------------------------*/
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <string.h>
/*----------------------------------------------------------------------------*/

class Fl_Effort : public Fl_Widget
{
private:
    void draw(void);
    unsigned short v;
    unsigned short ff;

public:
    Fl_Effort(int x, int y, int w, int h = 0, const char *l = 0);
    ~Fl_Effort(void){};
    void Set_value(unsigned char m, unsigned char n);
};
/*------------------------------------------------------------------------------*/
#endif
