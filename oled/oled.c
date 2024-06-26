#include "oled.h"
#include "oled_font.h"
#include "ti_msp_dl_config.h"


#define OLED_ADDR 0x3C

void OLED_I2C_Init(void) {}

// 向OLED寄存器地址写一个byte的数据
int I2C_WriteByte(uint8_t addr, uint8_t data) {
  uint8_t buff[2] = {0};
  buff[0] = addr;
  buff[1] = data;
  /* Wait for I2C to be Idle */
  while (!(DL_I2C_getControllerStatus(I2C_OLED_INST) &
           DL_I2C_CONTROLLER_STATUS_IDLE))
    ;

  /* Send the packet to the controller.
   * This function will send Start + Stop automatically.
   */
  DL_I2C_startControllerTransfer(I2C_OLED_INST, OLED_ADDR,
                                 DL_I2C_CONTROLLER_DIRECTION_TX, 2);
  DL_I2C_fillControllerTXFIFO(I2C_OLED_INST, &buff[0], 2);
  /* Poll until the Controller writes all bytes */
  while (DL_I2C_getControllerStatus(I2C_OLED_INST) &
         DL_I2C_CONTROLLER_STATUS_BUSY_BUS)
    ;

  /* Trap if there was an error */
  if (DL_I2C_getControllerStatus(I2C_OLED_INST) &
      DL_I2C_CONTROLLER_STATUS_ERROR) {
    /* LED will remain high if there is an error */
    __BKPT(0);
  }
  return 0;
}

// 写指令
void WriteCmd(unsigned char I2C_Command) { I2C_WriteByte(0x00, I2C_Command); }

// 写数据
void WriteData(unsigned char I2C_Data) { I2C_WriteByte(0x40, I2C_Data); }

// 厂家初始化代码
void OLED_Init(void) {
  OLED_I2C_Init();
  delay_cycles(16000000);
  WriteCmd(0xAE); // display off
  WriteCmd(0x20); // Set Memory Addressing Mode
  WriteCmd(0x10); // 00,Horizontal Addressing Mode;01,Vertical Addressing
                  // Mode;10,Page Addressing Mode (RESET);11,Invalid
  WriteCmd(0xb0); // Set Page Start Address for Page Addressing Mode,0-7
  WriteCmd(0xc8); // Set COM Output Scan Direction
  WriteCmd(0x00); //---set low column address
  WriteCmd(0x10); //---set high column address
  WriteCmd(0x40); //--set start line address
  WriteCmd(0x81); //--set contrast control register
  WriteCmd(0xff); // áá?èμ÷?ú 0x00~0xff
  WriteCmd(0xa1); //--set segment re-map 0 to 127
  WriteCmd(0xa6); //--set normal display
  WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
  WriteCmd(0x3F); //
  WriteCmd(
      0xa4); // 0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  WriteCmd(0xd3); //-set display offset
  WriteCmd(0x00); //-not offset
  WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
  WriteCmd(0xf0); //--set divide ratio
  WriteCmd(0xd9); //--set pre-charge period
  WriteCmd(0x22); //
  WriteCmd(0xda); //--set com pins hardware configuration
  WriteCmd(0x12);
  WriteCmd(0xdb); //--set vcomh
  WriteCmd(0x20); // 0x20,0.77xVcc
  WriteCmd(0x8d); //--set DC-DC enable
  WriteCmd(0x14); //
  WriteCmd(0xaf); //--turn on oled panel
}

// 设置光标起始坐标（x,y）
void OLED_SetPos(unsigned char x, unsigned char y) {
  WriteCmd(0xb0 + y);
  WriteCmd((x & 0xf0) >> 4 | 0x10);
  WriteCmd((x & 0x0f) | 0x01);
}

// 填充整个屏幕
void OLED_Fill(unsigned char Fill_Data) {
  unsigned char m, n;

  for (m = 0; m < 8; m++) {
    WriteCmd(0xb0 + m);
    WriteCmd(0x00);
    WriteCmd(0x10);

    for (n = 0; n < 128; n++) {
      WriteData(Fill_Data);
    }
  }
}

// 清屏
void OLED_CLS(void) { OLED_Fill(0x00); }

// 将OLED从休眠中唤醒
void OLED_ON(void) {
  WriteCmd(0xAF);
  WriteCmd(0x8D);
  WriteCmd(0x14);
}

// 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
void OLED_OFF(void) {
  WriteCmd(0xAE);
  WriteCmd(0x8D);
  WriteCmd(0x10);
}
/**
  * @brief  OLED显示字符串
  * @param  line 起始行位置，范围：1~8(TextSize=1)1~4(TextSize=2)
  * @param  column 起始列位置，范围：1~21(TextSize=1)1~16(TextSize=2)<列超范围自动换行>
  * @param  String 要显示的字符串 
  * @param  TextSize 字号
  * @retval 无
  */
void OLED_ShowString(uint8_t line, uint8_t column, char *String,uint8_t TextSize)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(line, column + i, String[i],TextSize);
	}
}
/**
  * @brief  OLED显示字符
  * @param  line 起始行位置，范围：1~8(TextSize=1)1~4(TextSize=2)
  * @param  column 起始列位置，范围：1~21(TextSize=1)1~16(TextSize=2)<列超范围自动换行>
  * @param  ch 要显示的字符
  * @param  TextSize 字号
  * @retval 无
  */
void OLED_ShowChar(uint8_t line,uint8_t column,char ch,uint8_t TextSize)
{
    if(column>(26-5*TextSize))
    {
        column-=(26-5*TextSize);
        line+=TextSize;
    }
    uint8_t x=(column-1)*(2*TextSize+4);
    uint8_t y=line-1;
    uint8_t c=0,i=0;
    c=ch-' ';
    switch (TextSize)
    {
        case 1: 
        {
            OLED_SetPos(x,y);
            for(i=0;i<6;i++)
                WriteData(F6x8[c][i]);
            break;
        }
        case 2:
        {
            OLED_SetPos(x,y);
            for(i=0;i<8;i++)
                WriteData(F8X16[c*16+i]);
            OLED_SetPos(x,y+1);
            for(i=0;i<8;i++)
                WriteData(F8X16[c*16+i+8]);
            break;
        }
    }
}
uint32_t oled_pow(uint8_t m,uint8_t n)
{
    uint32_t result=1;
    while(n--)result*=m;
    return result;
}
/**
  * @brief  OLED显示数字（十进制，无符号数）
  * @param  line 起始行位置，范围：1~8(TextSize=1)1~4(TextSize=2)
  * @param  column 起始列位置，范围：1~21(TextSize=1)1~16(TextSize=2)
  * @param  num 要显示的数字，范围：-2147483648~2147483647
  * @param  len 要显示数字的长度
  * @param  TextSize 字号
  * @retval 无
  */
void OLED_ShowNum(uint8_t line,uint8_t column,uint32_t num,uint8_t len,uint8_t TextSize)
{
    uint8_t i;
	for (i = 0; i < len; i++)							
	{
		OLED_ShowChar(line, column + i, num / oled_pow(10, len - i - 1) % 10 + '0',TextSize);
	}
}
/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~8(TextSize=1)1~4(TextSize=2)
  * @param  Column 起始列位置，范围：1~21(TextSize=1)1~16(TextSize=2)
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @param  TextSize 字号
  * @retval 无
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length,uint8_t TextSize)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+',TextSize);
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-',TextSize);
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / oled_pow(10, Length - i - 1) % 10 + '0',TextSize);
	}
}

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~8(TextSize=1)1~4(TextSize=2)
  * @param  Column 起始列位置，范围：1~21(TextSize=1)1~16(TextSize=2)
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  TextSize 字号
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t TextSize)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / oled_pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0',TextSize);
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A',TextSize);
		}
	}
}
/**
  * @brief  OLED显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~8(TextSize=1)1~4(TextSize=2)
  * @param  Column 起始列位置，范围：1~21(TextSize=1)1~16(TextSize=2)
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @param  TextSize 字号
  * @retval 无
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t TextSize)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / oled_pow(2, Length - i - 1) % 2 + '0',TextSize);
	}
}
/**
  * @brief  OLED显示浮点数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~8(TextSize=1)1~4(TextSize=2)
  * @param  Column 起始列位置，范围：1~21(TextSize=1)1~16(TextSize=2)
  * @param  Number 要显示的数字
  * @param  Length 要显示数字的长度，范围：1~10
  * @param  Flength 要显示的小数点后几位
  * @param  TextSize 字号
  * @retval 无
  */
void OLED_ShowFNum(uint8_t Line, uint8_t Column, float Number, uint8_t Length,uint8_t Flength,uint8_t TextSize)
{
    uint8_t i;
    uint8_t flag = 1;
    float Number1;
    uint32_t Number2;
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+',TextSize);
        Number1 = Number;
    }
    else
    {
        OLED_ShowChar(Line, Column, '-',TextSize);
        Number1 = -Number;
    }
    //将浮点数转换成整数然后显示
    Number2 = (int)(Number1 * oled_pow(10,Flength));
    
    
    for (i = Length; i > 0; i--)                            
    {
        if(i == (Length - Flength))
        {
            OLED_ShowChar(Line,Column + i + flag,'.',TextSize);
            flag = 0;
            OLED_ShowChar(Line, Column + i + flag, Number2 / oled_pow(10, Length - i) % 10 + '0',TextSize);
        }
        else
        {
            OLED_ShowChar(Line, Column + i + flag, Number2 / oled_pow(10, Length - i) % 10 + '0',TextSize);
        }
        
    }    
        
}