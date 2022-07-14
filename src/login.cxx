
#include "head.h"
static char count_login = 0; //用户输入密码位置数

//密码输入
void login_input_cb(Fl_Button *o, void *)
{
	if (count_login++ < 3) //密码最多3位
		login_input->insert(o->label(), 0);
}
//密码重新输入，直接删除所有输入
void login_input_del_cb(Fl_Button *, void *)
{
	login_input->value("");
	count_login = 0;
}

//登入界面密码确认
void login_confirm_cb(Fl_Button *, void *)
{
	FILE *fp;
	char buf[3];

	//密码放在password.txt中
	fp = fopen("password.txt", "r+");
	fseek(fp, 0, SEEK_SET);
	fread(buf, 1, 3, fp);
	fclose(fp);

	if (atoi(login_input->value()) == atoi(buf)) //判断密码是否正确
	{
		//界面跳转
		if (!group_maintenance_window->visible())
		{
			group_maintenance_window->show();
			group_maintenance_top->hide();
			group_top->show();
			label_window->label("维护");
			if (tempwin == NULL)
				group_main_window->hide();
			else
				tempwin->hide();
			tempwin = group_maintenance_window;
			//用户输入清零
			login_input->value("");
		}
	}
	else //密码错误
	{
		login_input->value("");
	}
	//用户输入密码位置数清零
	count_login = 0;
}
