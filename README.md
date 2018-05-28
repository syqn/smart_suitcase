
# smart_suitcase

生活中行李箱已经成为每个人不缺少的生活工具。虽然市场上行李箱越来越轻便，但时时刻刻拖动行李箱行走对我们来说很不便利。智能行李箱这款设计就是针对这个问题开发的出来的作品——一种可以自动跟随使用者的智能行李箱。本作品以Sysnopsys公司的ARC EM系列处理器开发板作为智能行李箱的核心控制模块，L298N模块作为智能行李箱的供电模块，采用UWB定位系统，能够使行李箱在人群中精准跟随使用者，还原跟随。采用了超声波测距模块，感测非接触式距离，从而具有壁障功能，并针对防止行李箱被盗取的问题，添加了检测行李箱与使用者距离的功能，当超出预设的安全距离时，将自动发出警报，提示使用者行李箱已超出预设范围。这一款智能行李箱的设计就是为了给出行的人们带来便利，让我们一起看看他是如何做到的吧！

- [Introduction](#1)   
    - [Function](#1.1)
	- [System Architecture](#1.2)
- [HW/SW Setup](#2)
	- [Required Hardware](#2.1)
	- [Required Software](#2.2)
	- [Hardware Connection](#2.3)
- [User Manual](#3)
	- [Before Running This Application](#3.1)
	- [Run This Application](#3.2)
		- [Makefile](#3.2.1)
		- [Main Entry](#3.2.2)
		- [Driver](#3.2.3)
		- [Function Module](#3.2.4)


## <h2 id='1'> Introduction 


**“”智能行李箱**

本作品是一款可以自动跟随用户的智能行李箱。

### <h3 id='1.1'> Function 

- 自动跟随功能：当使用者行走时，行李箱会自动跟随使用者移动，并保持在一个安全的范围之内。
- 防盗报警功能：当行李箱与使用者之间的距离超出安全范围（被别人提走）或者行李箱遇到障碍无法移动时会发出警报提醒使用者。
- 避障功能：当行李箱行进路线上出现障碍物，如柱子，垃圾桶之类时，行李箱会自动绕开障碍。
- 测温功能：能够测量并显示环境温度
- 称重功能：能够测量行李的重量，以免出现超重的情况。
- 移动电源功能：能够当做移动电源供手机、平板等移动设备充电。
- 电量显示功能：能够显示电池电量以提示使用者及时充电。

<h3 id='1.2'> System Architecture


![这里写图片描述](https://img-blog.csdn.net/20180528222736927?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3N5cW55dWU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

<h2 id='2'> HW/SW Setup

### <h3 id='2.1'>Required Hardware

- EMSK开发板（主控板）
- 蜂鸣器
- UWB通信模块
- 超声波测距模块
- 温度传感器模块
- 锂电池

### <h3 id='2.2'>Required Software

- 参考软件包——embARC 201709
- 开发工具及编译工具——GNU Toolchain for ARC Processors,2017.09

### <h3 id='2.3'>Hardware Connection

EMSK开发板的PMOD接口数量非常多，如表1所示ARC与各模块的连接方式所示，可在本设计中，两个直流电机，过GPIO接口与ARC EMSK开发板相连，实现数据的采集和返回。

|ARC接口|	设备名称|	设备型号|	连接方式|
|---|--|---|---|
|PMOD3[4:1] PMOD4[4:1]	|直流电机\*2    |	L298N|	GPIO（PORTC[19:16]）|
|PMOD6[4:1]|	 UWB模块|	DWM1000	|SPI（CS0）|
|PMOD2[4:3]|	温度传感器模块	|TCN75	|I2C|
|PMOD5[10]	|蜂鸣器模块	|无源蜂鸣器	|GPIO（PORTA[27]）|
|PMOD5[9:7] PMOD6[9:7]	|超声波测距模块|	HC-SR04|	GPIO（PORTA[26:24]）GPIO（PORTA[30:28:]）|


<h2 id='3'>User manual
	
### <h3 id='3.1'>Before Running This Application



- Add this project to workspace
- Build project
- Run this application



