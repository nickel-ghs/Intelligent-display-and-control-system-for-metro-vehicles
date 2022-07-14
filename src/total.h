#include"head.h"
#include"total.h"
static char Total_Data_Buff[7][15];//临时存储值

void total_proccess()
{
	unsigned short port;
	port=0x28;
	
	for(int i=0;i<7;i++)
	{
		sprintf(Total_Data_Buff[i],"%d",mvb.get_uint(port,i*4));
		Total_Data[i]->label(Total_Data_Buff[i]);
		Total_Data[i]->redraw();
	}
}

void total_input_cb(Fl_Button*,long i)
{
	totalno=i;
	counttotal=0;
	Group_Total_Set->show();
	total_input->value("");
}

void totaln_input_cb(Fl_Button*o,void*)
{
	counttotal++;
	if(counttotal<=10)
		{
			total_input->insert(o->label(),0);
		}
}

void total_input_del_cb(Fl_Button*,void*)
{
	total_input->value("");
	counttotal=0;
}

void total_confirm_cb(Fl_Button*,void*)
{
		unsigned short port;
  	static char buf[10];
    if(total_set_flag==0)
    {
      FILE *fp;
      if(totalno==1)
	      fp=fopen("power_p.txt","rw+");
      else if(totalno==2)
	      fp=fopen("power_aux.txt","rw+");
      else if(totalno==3)
	      fp=fopen("power_r.txt","rw+");
      else if(totalno==6)
	      fp=fopen("power_dc.txt","rw+");
      else if(totalno==4)
	      fp=fopen("compressor_tc1.txt","rw+");
      else if(totalno==5)
	      fp=fopen("compressor_tc2.txt","rw+");

      for(int n=0;n<10;n++)
          buf[n]='\0';
	    sprintf(buf,"%s",total_input->value());

	    if(tc_no==1)
		  {
			  port=0x1b3;
			  fseek(fp,0,SEEK_SET);
			  fwrite(buf,1,10,fp);
        mvb.put_uint(port,(totalno-1)*4,atoi(total_input->value()));
			  mvb.put_ubit(port,31,totalno-1,1);
			  mvb.lp_put_alldata();
        total_set_flag=1;
      }
	    else
		  {
			  port=0x6b3;
			  fseek(fp,0,SEEK_SET);
			  fwrite(buf,1,10,fp);
        mvb.put_uint(port,(totalno-1)*4,atoi(total_input->value()));
			  mvb.put_ubit(port,31,totalno-1,1);
			  mvb.lp_put_alldata();
        total_set_flag=1;
		  }
	   fclose(fp);
	   counttotal=0;
	   total_input->value("");
    }	
}

void total_cancel_cb(Fl_Button*,void*)
{
	Group_Total_Set->hide();
	counttotal=0;
	total_input->value("");
	for(int i=1;i<=6;i++)
	{
		total_select_butt[i]->value(0);
	}
}
