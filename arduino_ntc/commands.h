/***********************************************************************************
  Description:Define single-letter commands that will be sent by the PC over the
     serial link.
  Author: jiali_zhang
  History: 
    20210224:init this file
************************************************************************************/
#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define  ANALOG_READ     'a' //读取模拟引脚值
#define  GET_BAUDRATE    'b' //获取串口通信波特率
#define  PIN_MODE        'c' //配置引脚输入输出模式
#define  DIGITAL_READ    'd' //读取数字IO引脚值

#define  UPDATE_PID      'u' //更新所有电机的PID参数
#define  DIGITAL_WRITE   'w' //往数字IO引脚写入高低电平
#define  ANALOG_WRITE    'x' //往模拟IO引脚写入高低电平
#define  CODE_VERSION    'v' //返回当前固件代码的版本号

#define  TEMP_GET        't' //返回当前温度传感器结果

#endif
