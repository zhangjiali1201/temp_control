/*************************************************************************
  Description:各传感器代码的实现部分
  Author: jiali_zhang
  History: 
      20210224:增加温度传感器ntc
**************************************************************************/

/************************************************
  Description:初始化各传感器的引脚模式.
 ***********************************************/
void initSensors()
{
  pinMode(NTC, INPUT);
}

/**********************************************************************
  Description:获取指定的模拟引脚上红外测距传感器的值，输出单位是cm.这里需要注意
    输出的距离值范围需要在规定的4-30cm范围内,所有其他大于或小于的数据都需要限制.
    经过实际传感器插在板子上测试,发现读取的模拟引脚值比实际值小10左右,
    因此需要在计算电压的时候,读取值增加10后再计算电压.当得到正确电压后就
    可以计算距离了,这里的公式参考github上得到的,网址如下：
  https://github.com/guillaume-rico/SharpIR/blob/master/SharpIR.cpp
**********************************************************************/
int getTemperature(int sensor_pin)
{
  int temp = 0;
  temp = analogRead(sensor_pin);//读取模拟电压值
  temp = 245- temp/2;
        if(temp < 0)
          temp = 0;
  delay(100);//延时100ms
    
  return temp;
}
