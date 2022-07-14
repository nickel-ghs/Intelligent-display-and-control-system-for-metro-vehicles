#include"head.h"
static char count_login=0;
char a[5];
char *b=new char[5];

void login_input_cb(Fl_Button*o,void*)
{
	if(count_login++<3)
	  login_input->insert(o->label(),0);
	a[count_login]=1;
	printf("a[%d]=%d\n",count_login,a[count_login]);
	a[4]='\0';
}

void login_input_del_cb(Fl_Button*,void*)
{
	printf("aaaaaaaaa=%s\n",a);
	memcpy(b,a,count_login);
	login_input->value(b);
	printf("aaaaaaaaa=%s\n",b);
	count_login--;
}

//登入界面密码确认
void login_confirm_cb(Fl_Button*,void*)
{
	FILE *fp;
	char buf[3];
	
	fp=fopen("password.txt","r+");
	fseek(fp,0,SEEK_SET);
	fread(buf,1,3,fp);
	fclose(fp);

	if(atoi(login_input->value())==atoi(buf))
	{
		if(!group_maintenance_window->visible())
		{
			group_maintenance_window->show();
			group_maintenance_top->hide();
			group_top->show();
      label_window->label("维护");
			if(tempwin==NULL)
				group_main_window->hide();
			else tempwin->hide();
			tempwin=group_maintenance_window;
			login_input->value("");
		}
	}
	else
	{
		login_input->value("");
	}
	count_login=0;
}
