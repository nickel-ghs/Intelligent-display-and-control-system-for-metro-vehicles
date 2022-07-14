杨铃老师的代码界面是由FLUID自动生成的

ningbo-20170629，一共38个文件，平均一个人12个文件

张庭东：FLUID编程，d3,i4,l2,m1,n1,v1 control/下effort.cxx /下main.cxx

刘尚宇：src/下文件头字母为p3,s3,t4,w2

吕嘉欣：a3,b6,c2,r1

```c
问题：

time.cxx:70
		//时间同步；仅在main.cxx中被调用一次
		void hmi_synchro();函数分析
main.cxx:325***
    	void init_pit();函数作用，pit是什么意思
brake_resistor.cxx:5
    	blower_contactor_m11->color(FL_GREEN); blower_contactor_m11没找到在哪里，隐藏了吗？
main.cxx:65
    ;0x1b0和0x6b0端口在协议文档上找不到
	if (tc_no == 1) //显示器版本号{
		mvb.put_ushort(0x1b0, 0, iddlife);
		mvb.lp_put_alldata();
	}
	else{
		mvb.put_ushort(0x6b0, 0, iddlife);
		mvb.lp_put_alldata();
	}
    
callback.cxx：27(解决)
        if (tempwin == NULL)//temwin-->temp window,表示当前目录，==NULL：group_main_window
            group_main_window->hide();
        else
            tempwin->hide();
main.cxx：267(解决)
	//取系统时间发送网络
	void init_time()
	{
	    time_t t;
	    struct tm *p;
	    time(&t);
	    unsigned short port;
        if (tc_no == 1)
	        port = 0x1b1;
	    else
	        port = 0x6b1;
	    p = localtime(&t);
    	//数据组装
	    mvb.put_uchar(port, 6, p->tm_year - 100);//将p->tm_year - 100放到port的第6个字节中
	    mvb.put_uchar(port, 7, p->tm_mon + 1);
	    mvb.put_uchar(port, 8, p->tm_mday);
	    mvb.put_uchar(port, 9, p->tm_hour);
	    mvb.put_uchar(port, 10, p->tm_min);
	    mvb.put_uchar(port, 11, p->tm_sec);
	    mvb.lp_put_alldata();//数据发送
	}
ver.cxx:148(解决)
    dt[2] = mvb.get_uchar(0x35, t1);//将0x35端口的第t1个uchar数据取出
ver.cxx:128(解决)
    vr_d[k1]->copy_label(buff); //将vr_d[k1]的label换为buff
test.cxx:160(解决)
    Ebrake_2_Butt->value(0);//Ebrake_2_Butt按钮释放
	Ebrake_2_Butt->value(1);//Ebrake_2_Butt按钮按下

错误：
    	1、时间设置不能更改系统时间
    	2、系统时间固定，不能记时
    	3、管理员界面version界面第二、三、四、五行应该为-----而不是v1.0.0.0
    	4、维护界面-->轮径设置界面:轮径数值无法改变
        5、设置界面-->运输模式:功能未完成；transport.cxx与ver.cxx完全一样，运输模式功能未完成

警告：
    	1、记数应该默认从0开始或从1开始，不应该混合写
        2、lcdbrightconfig.txt未使用
```



|         文件         |                   作用                   |     关键函数      |          函数作用           |                             注意                             |
| :------------------: | :--------------------------------------: | :---------------: | :-------------------------: | :----------------------------------------------------------: |
|       main.cxx       |       初始化一系列功能后，显示桌面       | Layout_Function() | 将界面打开与函数process关联 |      if (group_net_window->visible())  net_proccess();       |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|         FLTK         |                                          |                   |                             |                                                              |
|  tranin-ningbo.cxx   |              fluid自动生成               |                   |                             |                                                              |
|      effort.cxx      |                   画图                   |                   |                             |                                                              |
|     callback.cxx     |    fltk FLUID--按钮回调函数--界面跳转    |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|         其他         |                                          |                   |                             |                                                              |
|     basedata.cxx     |             所有界面头部显示             |                   |                             |                                                              |
|    main_data.cxx     |                主界面显示                |                   |                             |                                                              |
| auto_brightness.cxx  |                   亮度                   |                   |                             |                                                              |
|    image_deal.cxx    |                 图片显示                 |                   |                             |                                                              |
|   station_set.cxx    |         线路/车站选择界面初始化          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|        主界面        |                                          |                   |                             |                                                              |
| wrong.cxx&wrong1.cxx |               事件信息界面               |     [有问题]      |                             | file/event.bin：记录错误   wrong.txt:错误日志   guide.txt:错误解决方法,只读 |
|         none         |                 设置界面                 |                   |                             |                                                              |
|      login.cxx       |                 维护界面                 |                   |                             |                                                              |
|   network_data.cxx   |               网络拓扑界面               |                   |                             |                                                              |
|    Broadcast.cxx     | 主界面---进站广播&出站广播&上一站&下一站 |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|       设置界面       |                                          |                   |                             |                                                              |
|       line.cxx       |          设置界面线路/车站选择           |                   |                             |                                                              |
| aircondition_set.cxx |           设置界面---空调设置            |                   |                             |                                                              |
|    brightness.cxx    |  设置界面"亮度/声音"亮度调节的回调函数   |                   |                             |                                                              |
| Broadcast_Switch.cxx |           设置界面---广播设置            |                   |                             |                                                              |
|    BrakeCheck.cxx    |           设置界面---制动自检            |                   |                             |                                                              |
|    transport.cxx     |           设置界面---运输模式            |    【有错误】     |                             |      transport.cxx与ver.cxx完全一样，运输模式功能未完成      |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|       维护界面       |                                          |                   |                             |                                                              |
|      login.cxx       |     管理员登陆，登陆成功进入管理界面     |                   |                             |                  密码存在password.txt文件中                  |
|                      |                                          |                   |                             |                                                              |
|       time.cxx       |             时间日期管理界面             |                   |                             |                                                              |
|     password.cxx     |               密码设置界面               |                   |                             |                                                              |
|       ver.cxx        |               软件版本界面               |                   |                             |                                                              |
|      total.cxx       |             能耗/空压机信息              |                   |                             | power_p.txt power_aux.txt power_r.txt power_dc.txt power_tc.txt compressor_tc1.txt compressor_tc2.txt分别存储牵引能耗，辅助能耗，再生能耗，DC/DC能耗，C1车压缩机工作时间，C2车压缩机工作时间 |
|      wrong.cxx       |               事件记录查询               |                   |                             |                                                              |
|       SIV.cxx        |          SIV界面:辅助逆变器界面          |                   |                             |                                                              |
|       io_A.cxx       |             TC车DIM/DXM/AXM              |                   |                             |                                                              |
|       io_B.cxx       |                 Mp车DXM                  |                   |                             |                                                              |
|       io_C.cxx       |                  M车DXM                  |                   |                             |                                                              |
|  DCU.cxx&DCU_M.cxx   |       DCU界面:发动机的控制单元故障       |                   |                             |                                                              |
|     diameter.cxx     |               轮径设置界面               |                   |                             |      diameterlist.txt:存放TC1,TC2,Mp1,Mp2,M1,M2车的轮径      |
|     portdata.cxx     |                 端口数据                 |    【有问题】     |                             |                                                              |
|      CarID.cxx       |            维护界面的车号界面            |                   |                             |                                                              |
|   acceleration.cxx   |                加速度测试                |                   |                             |                                                              |
|     set_cab.cxx      |              操作端设置界面              |                   |                             | train.txt存放操作端为1/2端    Set_Cab.txt当"设置为1端"或"设置为2端"按钮锁定时为1,否则为0; |
|  brake_resistor.cxx  |             制动电阻例行实验             |                   |                             |                                                              |
|       test.cxx       |                 测试界面                 |                   |                             |                                                              |
|       reserved       |                   备用                   |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |
|                      |                                          |                   |                             |                                                              |



# Intelligent-display-and-control-system-for-metro-vehicles
# Intelligent-display-and-control-system-for-metro-vehicles
# Intelligent-display-and-control-system-for-metro-vehicles
# Intelligent-display-and-control-system-for-metro-vehicles
