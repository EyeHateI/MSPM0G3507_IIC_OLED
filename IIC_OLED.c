//OLED IIC 4针脚 By EyeHateI
//              GND    电源地
//              VCC  接3.3v电源
//              SCL   PA31
//              SDA   PA28
//TextSize=2为两倍大小，占两行
#include "\oled\oled.h"
#include "ti_msp_dl_config.h"

int main(void) {
  SYSCFG_DL_init();
  OLED_Init();
  OLED_CLS();
  OLED_ShowChar(1,1,'A',2);//字符
  OLED_ShowNum(1,2,156,3,2);//无符号数
  OLED_ShowString(3, 1,"LP-MSPM0G3507", 2);//字符串
  OLED_ShowSignedNum(5,1,-99,2,1);//有符号整数
  OLED_ShowFNum(5,4,-3.95,3,2,1);//带符号浮点数
  OLED_ShowNum(6,4,15683842,8,2);//无符号整数
  OLED_ShowHexNum(8,1,33,4,1);//16进制
  OLED_ShowBinNum(8,6,15,4,1);//2进制
  while (1) {
  }
}
