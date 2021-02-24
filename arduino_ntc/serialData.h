/**************************************************************** 
  Description: 用于从arduino的串口上获得上位机发送过来的命令
    的类，包含各种成员变量和函数声明.
  Author: jiali_zhang
  History:
    20210224: initial this file.
****************************************************************/
#ifndef _SERIAL_DATA_H_
#define _SERIAL_DATA_H_

#define  ENTER_CHAR  '\r'

/************************************************************
  Description:用于保存从串口上获取到的数据的类.
************************************************************/
class serialData
{
  public:
    void resetCmdParam(); //重置保存串口的类对象的各个数据

    byte argCnt;   //用来保存有几个参数
    byte argIndex; //用来记录参数保存到第几个字符

    char cmd_chr; //保存从串口接收到的单命令字符

    //保存命令字符后面的各字符
    char argv1[36];
    char argv2[4];
    char argv3[4];

    //将命令字符后的三个参数转换成整数后各保存在此三个变量中
    int arg1;
    int arg2;
    int arg3;
};

serialData cmdDataObj;
#endif
