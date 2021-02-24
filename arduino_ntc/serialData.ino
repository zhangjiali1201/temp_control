/*************************************************************
  Description:
    用于arduino从串口获得命令类中各函数的实现.
  Author: jiali_zhang
  History:
   20210224: initial this file.
*************************************************************/

/************************************************
 Description:将接收串口控制命令的缓冲区清零,
   开始准备存储新的控制命令数据.
 ***********************************************/
void serialData::resetCmdParam()
{
  this->cmd_chr = ENTER_CHAR;

  memset(this->argv1, ENTER_CHAR, sizeof(this->argv1));
  memset(this->argv2, ENTER_CHAR, sizeof(this->argv2));
  memset(this->argv3, ENTER_CHAR, sizeof(this->argv3));

  this->argCnt   = 0;
  this->argIndex = 0;
}
