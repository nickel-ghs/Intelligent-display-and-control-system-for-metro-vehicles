
#include "head.h"
static char count_password = 0;

//函数与login.cxx内容相似

//密码输入
void password_input_cb(Fl_Button *o, void *)
{
	if (count_password++ < 3)
		password_input->insert(o->label(), 0);
}

//密码输入错误删除
void password_input_del_cb(Fl_Button *, void *)
{
	password_input->value("");
	count_password = 0;
}

//登入界面密码确认
void password_confirm_cb(Fl_Button *, void *)
{
	FILE *fp;
	char password_buff[6];

	if (count_password == 3) //密码必须为3位
	{
		sprintf(password_buff, "%s", password_input->value());
		fp = fopen("password.txt", "w+");
		fseek(fp, 0, SEEK_SET);
		fwrite(password_buff, 1, 3, fp);
		fclose(fp);
		password_prompt_box->hide(); //错误提示信息窗口隐藏
	}
	else
	{
		password_prompt_box->show(); //错误提示信息窗口隐藏
	}
	password_input->value("");
	count_password = 0;
}

//维护界面切换至密码设置界面
void password_cb(Fl_Button *, void *)
{
	if (!group_password_window->visible())
	{
		group_password_window->show();
		group_top->hide();
		group_maintenance_top->show();
		maintenance_label->label("维护--密码设置");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_password_window;
		password_input->value("");
		password_prompt_box->hide();
		count_password = 0;
	}
}

//密码设置界面切换至维护界面
void password_return_cb(Fl_Button *, void *)
{
	if (!group_maintenance_window->visible())
	{
		group_maintenance_window->show();
		maintenance_label->label("维护");
		if (tempwin == NULL)
			group_maintenance_window->hide();
		else
			tempwin->hide();
		tempwin = group_maintenance_window;
	}
}
