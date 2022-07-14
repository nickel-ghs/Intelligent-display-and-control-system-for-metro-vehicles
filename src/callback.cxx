
#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <i2cfun.h>

Fl_Group *tempwin_main; //主界面中各组的切换
Fl_Group *tempwin;		//主菜单间的界面切换，temp存储当前是哪一个界面

//切换至设置界面
void main_set_cb(Fl_Button *, void *)
{
	if (!group_set_window->visible()) //如果设置界面不可见则执行
	{
		group_set_window->show();	   //设置界面显示
		group_maintenance_top->hide(); //主界面隐藏
		group_top->show();			   //界面顶部继续显示
		label_window->label("设置");   //界面顶部的lable继续显示当前为哪一个界面

		if (tempwin == NULL) //如果是在主界面切换设置界面
			group_main_window->hide();
		else //如果是在其他界面切换设置界面
			tempwin->hide();

		tempwin = group_set_window; //标志切换到了设置界面
	}
}

//切换至旁路信息界面
void Main_Passby_cb(Fl_Button *, void *)
{
	if (!group_passby_window->visible())
	{
		group_passby_window->show();
		group_top->show();
		label_window->label("旁路信息");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_passby_window;
	}
}

//切换至维护界面
void main_maintenance_cb(Fl_Button *, void *)
{
	if (!group_login_window->visible())
	{
		group_login_window->show();
		// group_maintenance_top->hide();
		group_top->show();
		label_window->label("维护");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_login_window;
	}
}

//切换至网络拓扑界面
void main_net_cb(Fl_Button *, void *)
{
	if (!group_net_window->visible())
	{
		group_net_window->show();
		group_maintenance_top->hide();
		group_top->show();
		label_window->label("网络拓扑");
		if (tempwin == NULL)
			group_main_window->hide();
		else
			tempwin->hide();
		tempwin = group_net_window;
	}
}

//设置界面切换至线路设置界面
void line_station_cb(Fl_Button *, void *)
{
	if (!group_line_window->visible())
	{
		group_line_window->show();
		label_window->label("线路/车站选择");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_line_window;
	}
}

//线路设置界面切换至设置界面
void line_return_cb(Fl_Button *, void *)
{
	if (!group_set_window->visible())
	{
		group_set_window->show();
		label_window->label("设置");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_set_window;
	}
}

//线路界面切换至线路/车站选择界面
void select_station_cb(Fl_Button *, void *)
{
	if (!group_station_set_window->visible())
	{
		group_station_set_window->show();
		label_window->label("线路/车站选择");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_station_set_window;
	}
}

//设置界面切换至线路设置界面
void select_station_return_cb(Fl_Button *, void *)
{
	if (!group_line_window->visible())
	{
		group_line_window->show();
		label_window->label("线路/车站选择");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_line_window;
	}
}

//设置界面切换至亮度界面
void brightness_cb(Fl_Button *, void *)
{
	if (!group_brightness_window->visible())
	{
		group_brightness_window->show();
		label_window->label("亮度设置");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_brightness_window;
	}
}

//亮度界面切换至设置界面
void brightness_return_cb(Fl_Button *, void *)
{
	if (!group_set_window->visible())
	{
		group_set_window->show();
		label_window->label("设置");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_set_window;
	}
}

//设置界面切换至广播设置界面
void broadcast_set_cb(Fl_Button *, void *)
{
	if (!group_broadcast_set_window->visible())
	{
		group_broadcast_set_window->show();
		label_window->label("广播设置");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_broadcast_set_window;
	}
}

//广播设置界面切换至设置界面
void broadcast_set_return_cb(Fl_Button *, void *)
{
	if (!group_set_window->visible())
	{
		group_set_window->show();
		label_window->label("设置");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_set_window;
	}
}

//设置界面切换至制动自检界面
void brake_check_cb(Fl_Button *, void *)
{
	if (!group_brakecheck_window->visible())
	{
		group_brakecheck_window->show();
		label_window->label("制动自检");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_brakecheck_window;
	}
}

//制动自检界面切换至设置界面
void brakecheck_return_cb(Fl_Button *, void *)
{
	if (!group_set_window->visible())
	{
		group_set_window->show();
		label_window->label("设置");
		if (tempwin == NULL)
			group_set_window->hide();
		else
			tempwin->hide();
		tempwin = group_set_window;
	}
}

//维护界面切换至软件版本界面
void version_cb(Fl_Button *, void *)
{
	if (!group_version_window->visible())
	{
		group_version_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--软件版本");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_version_window;
		init_ver();
	}
}

//软件版本界面切换至维护界面
void version_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

//维护界面切换至能耗/空压机信息界面
void total_cb(Fl_Button *, void *)
{
	if (!group_total_window->visible())
	{
		group_total_window->show();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--能耗/空压机信息");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_total_window;
	}
}

//能耗界面切换至维护界面
void total_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

//维护界面切换至SIV界面
void siv_cb(Fl_Button *, void *)
{
	if (!group_siv_window->visible())
	{
		group_siv_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--SIV数据");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_siv_window;
	}
}

// SIV界面切换至维护界面
void siv_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

//维护界面切换至DCU界面
void dcu_cb(Fl_Button *, void *)
{
	if (!group_dcu_window->visible())
	{
		group_dcu_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--DCU数据");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_dcu_window;
	}
}

// DCU界面切换至维护界面
void dcu_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

//维护界面切换至操作端设置界面
void Operation_cb(Fl_Button *, void *)
{
	if (!group_set_cab->visible())
	{
		group_set_cab->show();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--操作端设置");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_set_cab;
	}
}

//操作端设置界面切换至维护界面
void operation_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

//维护界面切换至A车IO界面
void ioA_cb(Fl_Button *, void *)
{
	if (!group_ioA_window->visible())
	{
		group_ioA_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("TC车输入输出数据");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_ioA_window;
	}
}

// A车IO界面界面切换至维护界面
void ioA_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

//维护界面切换至B车IO界面
void ioB_cb(Fl_Button *, void *)
{
	if (!group_ioB_window->visible())
	{
		group_ioB_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("Mp车输入输出数据");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_ioB_window;
	}
}

// B车IO界面界面切换至维护界面
void ioB_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

//维护界面切换至C车IO界面
void ioC_cb(Fl_Button *, void *)
{
	if (!group_ioC_window->visible())
	{
		group_ioC_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("M车输入数据");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_ioC_window;
	}
}

// C车IO界面界面切换至维护界面
void ioC_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

//维护界面切换至端口数据界面
void portdata_cb(Fl_Button *, void *)
{
	if (!group_portdata_window->visible())
	{
		group_portdata_window->show();
		group_main_butt->hide();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--端口数据");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_portdata_window;
	}
}

//端口数据界面切换至维护界面
void portdata_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		group_main_butt->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}

void brake24_confirm_cb(Fl_Button *, void *)
{
	brake24_window->hide();
}

void brake26_confirm_cb(Fl_Button *, void *)
{
	brake26_window->hide();
}
