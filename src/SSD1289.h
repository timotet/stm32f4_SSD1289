/*
 * SSD1289.h
 *
 *  Created on: Jan 2, 2014
 *      Author: Timotet
 */

#ifndef SSD1289_H_
#define SSD1289__H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "integer.h"


/////these use port B /////
#define LCD_VCC          GPIO_Pin_1
#define LCD_VCC_HI       GPIO_SetBits(GPIOB,LCD_VCC)
#define LCD_VCC_LO       GPIO_ResetBits(GPIOB,LCD_VCC)

#define LCD_LED          GPIO_Pin_2
#define LCD_LED_HI       GPIO_SetBits(GPIOB,LCD_LED)
#define LCD_LED_LO       GPIO_ResetBits(GPIOB,LCD_LED)

#define SSD1289_R        GPIO_Pin_3
#define SSD1289_R_HI     GPIO_SetBits(GPIOB,SSD1289_R)
#define SSD1289_R_LO     GPIO_ResetBits(GPIOB,SSD1289_R)

#define SSD1289_WR       GPIO_Pin_4
#define SSD1289_WR_HI    GPIO_SetBits(GPIOB,SSD1289_WR)
#define SSD1289_WR_LO    GPIO_ResetBits(GPIOB,SSD1289_WR)

#define SSD1289_RST      GPIO_Pin_5
#define SSD1289_RST_HI   GPIO_SetBits(GPIOB,SSD1289_RST)
#define SSD1289_RST_LO   GPIO_ResetBits(GPIOB,SSD1289_RST)

#define SSD1289_REGSEL   GPIO_Pin_6
#define SSD1289_DATA     GPIO_SetBits(GPIOB,SSD1289_REGSEL)
#define SSD1289_CMD      GPIO_ResetBits(GPIOB,SSD1289_REGSEL)
#define SSD1289_REGSEL_LO       GPIO_ResetBits(GPIOB,SSD1289_REGSEL)

#define SSD1289_CS        GPIO_Pin_7
#define SSD1289_CS_HI     GPIO_SetBits(GPIOB,SSD1289_CS)
#define SSD1289_CS_LO     GPIO_ResetBits(GPIOB,SSD1289_CS)

#define Lcd_Width 240
#define Lcd_Height 320

#define Black   0x0000
#define Red     0xF800
#define Green   0x07E0
#define Blue    0x001F
#define White   0xFFFF
#define Purple  0xF11F
#define Yellow  0xFFE0
#define Cyan    0x07FF

//function prototypes
void Lcd_Write_Cmd(UINT CMD);
void Lcd_Write_Data(UINT DATA);
void Lcd_Write_Cmd_Data(UINT CMD, UINT DATA);
void Address_set(UINT x1,UINT y1,UINT x2,UINT y2);
void SSD1289_init(void);

void setColor(UINT color);
void setBackgroundColor(UINT color) ;
void putColor(UINT color);
void Clear(UCHAR blackWhite);
void drawPixel(UCHAR x, UCHAR y);
void drawChar(UCHAR x, UCHAR y, char c);
void drawString(UCHAR x, UCHAR y, char *string);

//#define Lcd_Write_Cmd_DATA  {Lcd_Write_Cmd(UINT CMD); Lcd_Write_DATA(UINT DATA);}



#ifdef	__cplusplus
}
#endif


#endif /* SSD1289_H_ */
