/*
 * SSD1289.c
 *
 *  Created on: Jan 2, 2014
 *      Author: Timotet
 */

#include "SSD1289.h"
#include "shift.h"
#include "Delay.h"
#include "integer.h"
#include "font_5x7.h"

UINT bgColor = 0;
UINT Color = 0;


void Lcd_Write_Cmd(UINT CMD) {  //write CMD

	SSD1289_R_HI;
	SSD1289_CMD;
	SSD1289_WR_LO;
	SSD1289_CS_LO;         // lcd CS low  active low
	s595_Put(CMD);         // write CMD data
	//SSD1289_WR_LO;
	//SSD1289_WR_HI;
	SSD1289_CS_HI;
}

void Lcd_Write_Data(UINT DATA) {	//write data

	SSD1289_R_HI;
	SSD1289_DATA;
	SSD1289_WR_LO;
	SSD1289_CS_LO;           // lcd CS low
	s595_Put(DATA);          // write data
	//SSD1289_WR_LO;
	//SSD1289_WR_HI;
	SSD1289_CS_HI;
}

void Lcd_Write_Cmd_Data(UINT CMD, UINT DATA) {	// write Cmd and data

	Lcd_Write_Cmd(CMD);
	Lcd_Write_Data(DATA);
}

void Address_set(UINT x1, UINT y1, UINT x2, UINT y2) { //set active drawing area

	Lcd_Write_Cmd_Data(0x0044, (x2 << 8) + x1);   //horizontal start and end address end address is 1st 8bits start address is last 8bits
	Lcd_Write_Cmd_Data(0x0045, y1);               //vertical address start1
	Lcd_Write_Cmd_Data(0x0046, y2);               //vertical address end2
	Lcd_Write_Cmd_Data(0x004E, x1);               // x address write
	Lcd_Write_Cmd_Data(0x004F, y1);               // y address write
	Lcd_Write_Cmd(0x22);
}

void setColor(UINT color) {
	Color = color;
}

void setBackgroundColor(UINT color) {
	bgColor= color;
}

void putColor(UINT color) {
	int i, j;
	Address_set(0, 0, Lcd_Width - 1, Lcd_Height - 1);

	for (i = 0; i < 320; i++) {
		for (j = 0; j < 240; j++) {
			Lcd_Write_Data(color);
		}
	}
}

void Clear(UCHAR blackWhite) {
	Address_set(0, 0, Lcd_Width - 1, Lcd_Height - 1);
	const UINT totalPixels = Lcd_Width * Lcd_Height;
	setBackgroundColor(blackWhite ? 0x0000 : 0xFFFF);
	UINT c = 0;
	while (c < totalPixels) {
		Lcd_Write_Data(bgColor);
		c++;
	}
}
/*
void Clear(void) {
	int i, j;
	Address_set(0, 0, Lcd_Width - 1, Lcd_Height - 1);

	for (i = 0; i < 320; i++) {
		for (j = 0; j < 240; j++) {
			Lcd_Write_Data(0x0000);

		}
	}
}
*/

void drawPixel(UCHAR x, UCHAR y) {
	Address_set(x, y, x, y);
	Lcd_Write_Data(Color);
}

////////////////
// 5x7 font - this function draws background pixels
////////////////
void drawChar(UCHAR x, UCHAR y, char c) {
	UCHAR col = 0;
	UCHAR row = 0;
	UCHAR bit = 0x01;
	UCHAR oc = c - 0x20;
	Address_set(x, y, x + 4, y + 7); // if you want to fill column between chars, change x + 4 to x + 5

	while (row < 8) {
		while (col < 5) {
			if (font[oc][col] & bit) {
				//foreground
				Lcd_Write_Data(Color);
			}

			else {
				//background
				Lcd_Write_Data(bgColor);
			}
			col++;
		}
		// if you want to fill column between chars, writeData(bgColor) here
		col = 0;
		bit <<= 1;
		row++;
	}
}

void drawString(UCHAR x, UCHAR y, char *string) {
	UCHAR xs = x;
	while (*string) {
		drawChar(xs, y, *string++);
		xs += 6;
	}
}

void SSD1289_init(void) {

	Delay(20); // let system stabilize
	SSD1289_RST_HI;
	Delay(5);
	SSD1289_RST_LO;
	Delay(50);
	SSD1289_RST_HI;
	Delay(50);


	LCD_LED_HI;      //turn on lcd led back light
	//SSD1289_CS_LO;


	Lcd_Write_Cmd_Data(0x0007, 0x0021); //display control
	Lcd_Write_Cmd_Data(0x0000, 0x0001); //oscillator
	Lcd_Write_Cmd_Data(0x0007, 0x0023); //display control
	Lcd_Write_Cmd_Data(0x0010, 0x0000); //sleep mode off
	Delay(30);
	Lcd_Write_Cmd_Data(0x0007, 0x0033);   //display control
	Lcd_Write_Cmd_Data(0x0011, 0x6030);   //entry mode    262k color 0x4830 68k color 0x6030
	Lcd_Write_Cmd_Data(0x0002, 0x1000);   //driving waveform control
	//Lcd_Write_Cmd_Data(0x000f, 0x0000); //gate scan start position
	Lcd_Write_Cmd_Data(0x0002, 0x600);    //driving waveform control
	Lcd_Write_Cmd_Data(0x0001, 0x6B3f);   //driver output control 6b3f
	//Lcd_Write_Cmd_Data(0x0b, 0x5308);     // frame cycle control
	//Lcd_Write_Cmd_Data(0x0028, 0x0006); //VCOM OTP
	Lcd_Write_Cmd_Data(0x0025, 0x8000);   //frame frequency control was 0xE000


	Lcd_Write_Cmd_Data(0x0030, 0x7); //Gamma adjustments
	Lcd_Write_Cmd_Data(0x0031, 0x302);
	Lcd_Write_Cmd_Data(0x0032, 0x105);
	Lcd_Write_Cmd_Data(0x0033, 0x206);
	Lcd_Write_Cmd_Data(0x0034, 0x808);
	Lcd_Write_Cmd_Data(0x0035, 0x206);
	Lcd_Write_Cmd_Data(0x0036, 0x504);
	Lcd_Write_Cmd_Data(0x0037, 0x7);
	Lcd_Write_Cmd_Data(0x003A, 0x105);
	Lcd_Write_Cmd_Data(0x003B, 0x808);



/*
	Lcd_Write_Cmd_Data(0x0000, 0x0001);   //Start Crystal
	Lcd_Write_Cmd_Data(0x0003, 0x6664);   //power control 1 0x6664 was 6664
	Lcd_Write_Cmd_Data(0x000C, 0x0000);   //power control 2 0x0004 was 0
	Lcd_Write_Cmd_Data(0x000D, 0x800C);   //power control 3 0x0009 was 800C
	Lcd_Write_Cmd_Data(0x000E, 0x2B00);   //power control 4 0x3200 was 2B00
	Lcd_Write_Cmd_Data(0x001E, 0x00B7);   //power control 5 0x0029 was 00B7
	Lcd_Write_Cmd_Data(0x0001, 0x6B3F);   //driver output control 320*240 was 0x6B3F
	Lcd_Write_Cmd_Data(0x0002, 0x0600);   // driving waveform control
	Lcd_Write_Cmd_Data(0x0010, 0x0000);   //sleep mode 1 = sleep
	Lcd_Write_Cmd_Data(0x0011, 0x6070);   //entry mode 0x4030
	Lcd_Write_Cmd_Data(0x0005, 0x0000);     //compare register
	Lcd_Write_Cmd_Data(0x0006, 0x0000);     //compare register
	Lcd_Write_Cmd_Data(0x0015, 0x00D0);     //generic interface command 0x00D0
	Lcd_Write_Cmd_Data(0x0016, 0xEF1C);     //horizontal porch
	Lcd_Write_Cmd_Data(0x0017, 0x0103);     //vertical porch was 0x0003
	Lcd_Write_Cmd_Data(0x0007, 0x0023);     //display control was 0x0233
	Lcd_Write_Cmd_Data(0x000B, 0x5308);     //frame cycle control
	Lcd_Write_Cmd_Data(0x000F, 0x0000);     //gate scan start position
	Lcd_Write_Cmd_Data(0x0041, 0x0000);     //vertical scroll control 1
	Lcd_Write_Cmd_Data(0x0042, 0x0000);     //vertical scroll control 2
	Lcd_Write_Cmd_Data(0x0048, 0x0000);     //first window start
	Lcd_Write_Cmd_Data(0x0049, 0x013F);     //first window end
	Lcd_Write_Cmd_Data(0x004A, 0x0000);     //second window start
	Lcd_Write_Cmd_Data(0x004B, 0x013F);     //second window end
	Lcd_Write_Cmd_Data(0x0044, 0xEF00);     //horizontal ram address position
	Lcd_Write_Cmd_Data(0x0045, 0x0000);     //vertical ram address start position
	Lcd_Write_Cmd_Data(0x0046, 0x013F);     //vertical ram address end position


	Lcd_Write_Cmd_Data(0x0030, 0x0707); //Gamma adjustments
	Lcd_Write_Cmd_Data(0x0031, 0x0204);
	Lcd_Write_Cmd_Data(0x0032, 0x0204);
	Lcd_Write_Cmd_Data(0x0033, 0x0502);
	Lcd_Write_Cmd_Data(0x0034, 0x0507);
	Lcd_Write_Cmd_Data(0x0035, 0x0204);
	Lcd_Write_Cmd_Data(0x0036, 0x0204);
	Lcd_Write_Cmd_Data(0x0037, 0x0502);
	Lcd_Write_Cmd_Data(0x003A, 0x0302);
	Lcd_Write_Cmd_Data(0x003B, 0x0302);


	Lcd_Write_Cmd_Data(0x0023, 0x0000); //ram write data mask 1
	Lcd_Write_Cmd_Data(0x0024, 0x0000); //ram write data mask 1
	Lcd_Write_Cmd_Data(0x0025, 0x8000);
	Lcd_Write_Cmd_Data(0x004f, 0x0000);  //set GDDRAM x
	Lcd_Write_Cmd_Data(0x004e, 0x0000);  //set GDDRAM y
	Lcd_Write_Cmd(0x22);

	*/
	//SSD1289_CS_HI;

}

