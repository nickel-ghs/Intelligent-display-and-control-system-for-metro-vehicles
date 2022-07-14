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
# Intelligent-display-and-control-system-for-metro-vehicles
# Intelligent-display-and-control-system-for-metro-vehicles
