#ifndef __OLED_H__

#define __OLED_H__

#include"ti_msp_dl_config.h"
#define Max_Column  128
#define Max_Row     64

void OLED_I2C_Init(void);
int I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteData(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x,unsigned char y);
void OLED_Fill(unsigned char Fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
uint32_t oled_pow(uint8_t m,uint8_t n);
void OLED_ShowChar(uint8_t line,uint8_t column,char ch,uint8_t TextSize);
void OLED_ShowString(uint8_t line, uint8_t column, char *String,uint8_t TextSize);
void OLED_ShowNum(uint8_t line,uint8_t column,uint32_t num,uint8_t len,uint8_t TextSize);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length,uint8_t TextSize);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t TextSize);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length,uint8_t TextSize);
void OLED_ShowFNum(uint8_t Line, uint8_t Column, float Number, uint8_t Length,uint8_t Flength,uint8_t TextSize);
#endif

