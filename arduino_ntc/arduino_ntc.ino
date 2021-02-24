/***************************************************************************
  Description:为温度控制系统编写的基于Arduino UNO的下位机代码,上位机通过串口发送
    控制命令到下位机arduino上.下位机收到命令进行解析和执行相应的控制命令,这里
    下位机功能包括温度传感器数据获取反馈,加热器的控制等.
  Author: jiali_zhang
  History:
    20210224:init code;
****************************************************************************/
#include <string.h>
#include "sensors.h"
#include "commands.h"
#include "serialData.h"

/********************** USER  AREAR ***********************/
#define  VERSION   1.0  //当前arduino代码版本号

//可以更改串口输出端口号,更改这里后面的串口输出都会跟着修改
#define  SERIAL_OUT  Serial

#define  BAUDRATE  57600  //SERIAL_OUT串口通信的波特率
/********************** USER  END **************************/

/***************************************************************
  Description:  当从串口中解析出控制命令字符后，开始执行该命令.
    所有的命令字符定义都在commands.h文件中.
****************************************************************/
void runCommand()
{
  int i = 0;
  float out = 0.0;
  char *str = NULL;
  char *p = cmdDataObj.argv1;
  byte pid_args[12];

  if (cmdDataObj.cmd_chr != UPDATE_PID)
  {
    cmdDataObj.arg1 = atoi(cmdDataObj.argv1);
    cmdDataObj.arg2 = atoi(cmdDataObj.argv2);
    cmdDataObj.arg3 = atoi(cmdDataObj.argv3);
  }
  

  switch (cmdDataObj.cmd_chr) //根据控制命令字符来判断需要执行的命令
  {
    case ANALOG_READ:  //'a'-读取模拟引脚数据
      SERIAL_OUT.println(analogRead(cmdDataObj.arg1));
      break;

    case GET_BAUDRATE: //'b'-获取串口通信波特率
      {
        SERIAL_OUT.println(BAUDRATE);
        int baud = BAUDRATE;
      }
      break;

    case PIN_MODE:  //'c'-配置引脚的输入输出模式
      if (cmdDataObj.arg2 == 0)
      {
        pinMode(cmdDataObj.arg1, INPUT);
      }
      else if (cmdDataObj.arg2 == 1)
      {
        pinMode(cmdDataObj.arg1, OUTPUT);
      }
      SERIAL_OUT.println("OK");
      break;

    case DIGITAL_READ: //'d'-读取数字IO引脚上传感器的数据
      SERIAL_OUT.println(digitalRead(cmdDataObj.arg1));
      break;

    case ANALOG_WRITE: //'x'-模拟引脚上写入高低电平
      analogWrite(cmdDataObj.arg1, cmdDataObj.arg2);
      SERIAL_OUT.println("OK");
      break;

    case DIGITAL_WRITE: //'w'-数字引脚上写入高低电平
      if (cmdDataObj.arg2 == 0)
      {
        digitalWrite(cmdDataObj.arg1, LOW);
      }
      else if (cmdDataObj.arg2 == 1)
      {
        digitalWrite(cmdDataObj.arg1, HIGH);
      }
      SERIAL_OUT.println("OK");
      break;

    case CODE_VERSION: // 'v'-获取当前固件代码的版本号
      SERIAL_OUT.println(VERSION);
      break;

    case TEMP_GET: // 't'-获取当前温度传感器结果
      SERIAL_OUT.print(getTemperature(NTC));
      SERIAL_OUT.print("\n");
      break;

    default: //接收到错误的控制命令,该命令未在commands.h中定义
      SERIAL_OUT.println("Invalid Command");
      break;
  }
  
}

/**************************************************************
  Description:程序启动后,最开始运行的配置代码,该初始化函数只执行一次.
    在这里配置串口,各传感器等初始化信息.
 *************************************************************/
void setup()
{
  SERIAL_OUT.begin(BAUDRATE); //配置串口通信波特率
  cmdDataObj.resetCmdParam();

  initSensors();

}

/*******************************************************************
  Description:处理串口总线上获取到的字符数据,并从中解析出命令字符和有
  效参数. 所有的控制命令字符串结尾都需要以'\r'结尾,根据该字符判断是否收到
  一条完整命令.当收到该结束字符后,就开始执行接收到的指令.
*******************************************************************/
void procRecChar(char tmp_chr)
{
  if (tmp_chr == 13)  //判断是否收到了命令最后的结束字符'\r'
  {
    runCommand();
    cmdDataObj.resetCmdParam(); //在执行完命令后,可以将串口接收到的缓冲区参数重置清零
  }
  else if (tmp_chr == ' ') //使用空格来区分命令字符后面的各参数,遇到空格说明后面有新参数
  {
    cmdDataObj.argCnt++;
    cmdDataObj.argIndex = 0;
  }
  else //process single-letter command
  {
    if (cmdDataObj.argCnt == 0) //第一个字符都是命令字符
    {
      cmdDataObj.cmd_chr = tmp_chr;
    }
    else if (cmdDataObj.argCnt == 1) //开始保存第一个参数中所有字符到argv1缓冲区
    {
      cmdDataObj.argv1[cmdDataObj.argIndex] = tmp_chr;
      cmdDataObj.argIndex++;
    }
    else if (cmdDataObj.argCnt == 2)  //开始保存第二个参数中所有字符到argv2缓冲区
    {
      cmdDataObj.argv2[cmdDataObj.argIndex] = tmp_chr;
      cmdDataObj.argIndex++;
    }
    else if (cmdDataObj.argCnt == 3) //开始保存第三个参数中所有字符到argv3缓冲区
    {
      cmdDataObj.argv3[cmdDataObj.argIndex] = tmp_chr;
      cmdDataObj.argIndex++;
    }
  }
}

/**********************************************************************
  Description:该loop函数会不断的循环执行,除非arduino设备断电,否则该loop程序
    就会一直运行.在此函数内可以增加需要不断循环处理检测的函数.
 *********************************************************************/
void loop()
{
  while (SERIAL_OUT.available()) //判断串口中是否收到控制命令
  {
    char tmp_chr = SERIAL_OUT.read();  //读取串口缓冲区的一个字符
    procRecChar(tmp_chr); //处理该字符
  }

}
