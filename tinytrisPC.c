//                              TINY_TRIS_PC v2.3
//                https://sites.google.com/view/tinytris
//                  (Dev) Daniel Champagne 2019-2021
//                 Contact EMAIL: phoenixbozo@gmail.com
/*
  TINY_TRIS_PC is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

DEPENDENCY
----------
0-STANDARD Libc (With GCC)
1-LIBSDL1.2
2-LIBSDL_mixer1.2

libsdl1.2
---------
sudo apt-get update
sudo apt-get install libsdl1.2-dev libsdl-mixer1.2-dev

Compile with command line on linux terminal:
gcc -o tinytrisPC tinytrisPC.c Widjet.c  -lSDL_mixer  `sdl-config --libs --cflags`

Compile with (GEANY) on linux:
gcc -Wall -o  "%e" "%f" -no-pie Widjet.c  -lSDL -lSDL_mixer
*/

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
//#include <windows.h> //For windows only
#include "Widjet.h"

#define delay(ZART)  SDL_Delay(ZART)
#define spin2 6
#define TINYJOYPAD_RIGHT widjet.Event.key[SDLK_RIGHT]
#define TINYJOYPAD_LEFT widjet.Event.key[SDLK_LEFT]
#define TINYJOYPAD_DOWN widjet.Event.key[SDLK_DOWN]
#define BUTTON_DOWN widjet.Event.key[SDLK_LCTRL]
#define BUTTON_UP !widjet.Event.key[SDLK_LCTRL]

uint8_t pgm_read_byte(uint8_t const *X_TAB){
return *X_TAB;
 }
	  
/**/
int timer=0;
uint8_t ByteX=0,ByteY=0;
int VideoBuff[64][128]={{0}};
/**/

uint8_t ColorChose=1;

//public var
uint8_t SOUND_BOX[10]={0};
uint8_t Grid_TTRIS[12][3]={{0}};
const uint8_t  MEM_TTTRIS[16]= {0,2,0,4,3,7,6,9,9,12,11,15,14,17,17,19,};
uint8_t Level_TTRIS;
uint8_t Level_Speed_ADJ_TTRIS;
uint16_t Scores_TTRIS;
uint8_t Nb_of_line_TTRIS[3];
uint16_t Nb_of_line_F_TTRIS;
uint8_t RND_VAR_TTRIS;
uint8_t LONG_PRESS_X_TTRIS;
uint8_t DOWN_DESACTIVE_TTRIS;
uint8_t DROP_SPEED_TTRIS;
uint8_t SPEED_x_trig_TTRIS;
uint8_t DROP_TRIG_TTRIS;
int8_t xx_TTRIS,yy_TTRIS;
uint8_t Piece_Mat2_TTRIS[5][5];
uint8_t Ripple_filter_TTRIS;
uint8_t PIECEs_TTRIS;
uint8_t PIECEs_TTRIS_PREVIEW;
uint8_t PIECEs_rot_TTRIS;
uint8_t DROP_BREAK_TTRIS;
int8_t OU_SUIS_JE_X_TTRIS;
int8_t OU_SUIS_JE_Y_TTRIS;
uint8_t OU_SUIS_JE_X_ENGAGED_TTRIS;
uint8_t OU_SUIS_JE_Y_ENGAGED_TTRIS;
int8_t DEPLACEMENT_XX_TTRIS;
int8_t DEPLACEMENT_YY_TTRIS;
uint8_t NumberofJoystick=0;

const uint8_t  H_Grid_TTTRIS[] = {
0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,
7,7,8,8,8,9,9,9,10,10,10,11,11,11,12,12,12,  
};

const uint8_t Pieces_TTRIS[] = {
//0
0b00000000,
0b00100000,
0b01110000,
0b00000000,
0b00000000,
//1
0b00000000,
0b00000000,
0b00110000,
0b00110000,
0b00000000,
//2
0b00000000,
0b00000000,
0b00110000,
0b01100000,
0b00000000,
//3
0b00000000,
0b00010000,
0b00110000,
0b00100000,
0b00000000,
//4
0b00100000,
0b00100000,
0b00100000,
0b00100000,
0b00000000,
//5
0b00000000,
0b00100000,
0b00100000,
0b01100000,
0b00000000,
//6
0b00000000,
0b00100000,
0b00100000,
0b00110000,
0b00000000,
};

const uint8_t  tiny_PREVIEW_block_TTTRIS[]= {
2,1,
0b11000000,
0b11000000,
};

const uint8_t  tinyblock_TTTRIS[] = {
3,1,
0x07,0x05,0x07,
};

const uint8_t  tinyblock2_TTTRIS[] = {
3,1,
0b11100000,
0b11100000,
0b11100000,
};

const uint8_t  police_TTRIS []= {
4,1,
0x1F,0x11,0x1F,0x00,
0x00,0x1F,0x00,0x00,
0x1D,0x15,0x17,0x00,
0x11,0x15,0x1F,0x00,
0x07,0x04,0x1F,0x00,
0x17,0x15,0x1D,0x00,
0x1F,0x15,0x1D,0x00,
0x01,0x1D,0x03,0x00,
0x1F,0x15,0x1F,0x00,
0x17,0x15,0x1F,0x00,
};

const uint8_t  start_button_1_TTRIS [] = {
30,1,
0xFE,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0xFE,
};

const uint8_t  start_button_2_TTRIS [] = {
30,1,
0x03,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x03,
};

const uint8_t  chateau_TTRIS [] = {
0xD5,0xF8,0xF4,0xEA,0x54,0x7A,0x55,0x68,0x74,0x7A,0x54,0x6A,0x55,0x78,0x74,0x6A,0x54,0x7A,0x55,0x68,
0x74,0x7A,0x54,0x6A,0x55,0x78,0x74,0x6A,0x54,0x7A,0x55,0x68,0xF4,0xFA,0xD4,0xEA,0xFF,0x01,0x00,0x02,
0x02,0x82,0xFE,0x82,0x02,0x02,0x88,0xFA,0x80,0x00,0xF8,0x10,0x08,0x08,0xF0,0x00,0x18,0x60,0xC0,0x38,
0x88,0xA0,0xA8,0xA8,0x28,0x28,0x28,0x08,0x08,0x08,0x01,0xFF,0xFF,0x00,0x04,0x04,0x04,0x14,0x14,0x14,
0x54,0x54,0x50,0x50,0x44,0x04,0x04,0xFC,0x04,0x04,0x04,0xF0,0x22,0x12,0x01,0x10,0xF4,0x00,0x00,0x20,
0x50,0x50,0x90,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x80,0x40,0x40,0x00,0x40,0x40,0xC0,
0x40,0x40,0x01,0x81,0x41,0x40,0x80,0x01,0x00,0xC0,0x40,0x41,0x81,0x01,0x40,0x41,0xC1,0x41,0x40,0x00,
0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x01,0x12,0x12,0x0C,0x00,0x00,0x1F,0x00,0x00,0x00,0x1F,
0x02,0x02,0x1F,0x00,0x00,0x1F,0x06,0x0A,0x11,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x00,0x00,0x00,0xF0,0xB0,0x50,0x88,0x88,0xC8,0x50,0x50,0x20,0x20,0x60,0x60,0xB0,0x90,0x10,0x18,
0x08,0x98,0x98,0xA4,0xE4,0x46,0xE4,0xE4,0xE8,0xF8,0xF0,0xF0,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
0x03,0x06,0x0D,0x1A,0x3F,0x6B,0xD6,0xAA,0x54,0xF8,0xFC,0xFC,0xFE,0xFE,0xAB,0x7F,0x7F,0x3F,0x3F,0x1F,
0x0F,0x0D,0x07,0x07,0x03,0x03,0x01,0x01,0x00,0x00,0x00,0xFF,0x1F,0x3C,0x38,0x38,0x30,0x30,0x30,0x30,
0x30,0x30,0x30,0x31,0x33,0x37,0x33,0x31,0x31,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
0x30,0x30,0x30,0x30,0x38,0x38,0x3C,0x1F,
};

const uint8_t  BACKGROUND_TTRIS []= {
0xFC,0x02,0xF9,0xF5,0x1D,0x0D,0x0D,0x0D,0x0D,0x0B,0x07,0x1F,0x3F,0x20,0x2F,0x2F,0x3F,0x22,0x3F,0x20,
0x39,0x33,0x20,0x3F,0x20,0x2A,0x2E,0x3F,0x2D,0x2A,0x2A,0x36,0x1F,0x07,0x0B,0x0D,0x0D,0x0D,0x0D,0x1D,
0xF5,0xF9,0x02,0xFC,0xF8,0x00,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,
0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,0x00,0x40,0x40,
0x00,0x40,0x00,0xF8,0xFC,0x02,0xF9,0xF5,0x1D,0x0D,0x0D,0x0B,0x07,0x1F,0x3F,0x2D,0x2A,0x2A,0x36,0x3F,
0x31,0x2E,0x2E,0x3F,0x31,0x2E,0x2E,0x31,0x3F,0x20,0x3A,0x32,0x2D,0x3F,0x20,0x2A,0x2E,0x3F,0x1F,0x07,
0x0B,0x0D,0x0D,0x1D,0xF5,0xF9,0x02,0xFC,0xFF,0x00,0x7F,0xBF,0xE0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xBF,0x7F,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x7F,0xBF,0xE0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xBF,0x7F,0x00,0xFF,0x00,0x01,0xFA,0x5A,
0x7A,0x5A,0xDA,0x5A,0x7A,0x5A,0xDA,0x5A,0x7A,0x5A,0xDA,0xDA,0x7A,0x5A,0xDA,0x5A,0x7A,0x5A,0xDA,0x5A,
0x7A,0x5A,0xDA,0x5A,0x7A,0x5A,0xDA,0x5A,0x7A,0x5A,0xDA,0x5A,0x7A,0x5A,0xDA,0x5A,0x7A,0xFA,0x01,0x00,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0x00,0x01,0xFA,0xFA,0x5A,0x5A,0x5A,0x7A,0x5A,0x5A,0x5A,0x7A,0x5A,0x5A,0x5A,0x7A,0x5A,0x5A,0x5A,0x7A,
0x5A,0x5A,0x5A,0x7A,0xDA,0xDA,0x5A,0x7A,0x5A,0xDA,0x5A,0x7A,0x5A,0xDA,0x5A,0x7A,0x5A,0xDA,0x5A,0x7A,
0x5A,0xFA,0x01,0x00,0x00,0x00,0xFF,0x55,0x77,0x55,0xDD,0x55,0x77,0x55,0xDD,0xF5,0xFF,0x3F,0x07,0xE0,
0xFC,0xBC,0xE0,0x81,0x07,0x1D,0x7D,0xD5,0x77,0x55,0xDD,0x55,0x77,0x55,0xDD,0x55,0x77,0x55,0xDD,0x55,
0x77,0x55,0xDD,0x55,0x77,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,0xFE,0xFD,0x07,0x03,0x03,0x03,0x03,0x03,
0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x07,0xFD,0xFE,0x00,0x01,0xFF,0xF7,0xD5,0xDD,0xD5,0xF7,
0xD5,0xDD,0xD5,0xF7,0xD5,0xDD,0xD5,0x77,0x55,0xFF,0x00,0x00,0x00,0x00,0xFF,0x55,0x77,0x55,0xDD,0xF5,
0x7F,0x3F,0x8F,0xC3,0xF0,0xDC,0xBF,0xF7,0xEF,0xFD,0xEA,0xD7,0xBC,0xF0,0x40,0x81,0x07,0x1D,0x75,0x3F,
0x87,0xF1,0x81,0x03,0x0F,0x35,0xDD,0x55,0x77,0x55,0xDD,0x55,0x77,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x00,
0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x7E,0xC2,0x5E,0x7E,
0x42,0x52,0x5A,0x7E,0x62,0x5E,0x62,0x7E,0x42,0x52,0x5A,0x7E,0xC2,0x5E,0xFC,0x01,0x03,0xFF,0x00,0x00,
0x00,0x00,0xFF,0x55,0x77,0x55,0xDF,0x57,0x7C,0xF8,0xE1,0x04,0x2A,0xEE,0xDA,0x4E,0x0A,0x0A,0x0E,0x1A,
0xAE,0x0A,0x05,0x01,0xC0,0x60,0x78,0x6F,0x5F,0x7E,0x75,0x6F,0x58,0x60,0xC0,0x03,0x0F,0x75,0xDD,0x55,
0x77,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xFF,0x00,0x00,0xFF,0x78,0x73,0xE5,0x67,0x66,0x66,0xE6,0x66,0x66,0x6E,0xFE,0xFE,0x0E,
0x06,0xC6,0x00,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0xFF,0xFF,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x0F,0x15,0x17,0x95,0x1D,0x15,0x97,0x1F,0x9F,0x00,
0x09,0xBF,0x3A,0x95,0x20,0x00,0x91,0x00,0xAA,0x00,0x00,0x80,0x02,0x85,0x37,0x2D,0x95,0x07,0x85,0x0D,
0x37,0x85,0x02,0x80,0x18,0x1C,0x9F,0x15,0x17,0x0F,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x0F,0x17,0x15,0x9D,0x15,0x17,
0x95,0x1D,0x95,0x17,0x15,0x7F,0x3F,0x80,0x00,0x1D,0x94,0x19,0x9A,0x13,0x13,0x93,0x13,0x93,0x13,0x17,
0x7F,0x3F,0x87,0x03,0x13,0x93,0x13,0x93,0x13,0x12,0x91,0x10,0x18,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,
0x06,0x0F,0x0D,0x1F,0x1D,0x16,0x1F,0x1D,0x1F,0x1D,0x36,0x3F,0x3D,0x7F,0x7D,0x76,0xFF,0xFD,0xFF,0xFD,
0x76,0x7F,0x7D,0x3F,0x3D,0x36,0x1F,0x1D,0x1F,0x1D,0x16,0x1F,0x1D,0x0F,0x0D,0x06,0x00,0x00,0x00,0x00,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,
0x00,0x00,0x00,0x00,0x06,0x0F,0x0D,0x1F,0x1D,0x16,0x1F,0x1D,0x1F,0x1D,0x36,0x3F,0x3D,0x7F,0x7D,0x76,
0xFF,0xFD,0xFF,0xFD,0x76,0x7F,0x7D,0x3F,0x3D,0x36,0x1F,0x1D,0x1F,0x1D,0x16,0x1F,0x1D,0x0F,0x0D,0x06,
0x00,0x00,0x00,0x00,
};



void ResetAllControl(Widjet *widjet);
int JoystickUpdateEvents(SDL_Joystick** joyst,Input* in);
void Tiny_Flip(void);
void pinMode(uint8_t pin,uint8_t inout);
void loop();
void digitalWrite(uint8_t pin,uint8_t highlow);
void setup();
void SSD1306_ssd1306_fillscreen(uint8_t value);
void SSD1306_ssd1306_draw_bmp(uint8_t x,uint8_t y,uint8_t wide, uint8_t height, const uint8_t picture[]);
uint8_t  digitalRead(uint8_t pin);
void SSD1306_ssd1306_send_command(uint8_t value);
void  SSD1306_ssd1306_send_data_start(void);
void SSD1306_ssd1306_send_byte(uint8_t value);
void SSD1306_ssd1306_send_data_stop();
void SDL_FlipBuffer(SDL_Surface *ren,config *CFG);
uint8_t recbit(uint8_t bitrec,uint8_t bit);

int JoystickUpdateEvents(SDL_Joystick** joyst,Input* in){
if (NumberofJoystick!=0) {SDL_JoystickUpdate();
in->JoyButton0=0;
in->JoyHatR=0;
in->JoyHatL=0;
in->JoyHatD=0;
if (NumberofJoystick!=0) {
//joystick
	if (SDL_JoystickGetButton(*joyst,0)) {in->JoyButton0=1;}
	if (SDL_JoystickGetButton(*joyst,2)) {in->JoyButton0=1;}
	if (SDL_JoystickGetButton(*joyst,1)) {in->JoyButton0=1;}
	if (SDL_JoystickGetButton(*joyst,3)) {in->JoyButton0=1;}

	if ((SDL_JoystickGetHat(*joyst,0))==SDL_HAT_RIGHT) {in->JoyHatR=1;}
	if ((SDL_JoystickGetHat(*joyst,0))==SDL_HAT_LEFT) {in->JoyHatL=1;}
	if ((SDL_JoystickGetHat(*joyst,0))==SDL_HAT_DOWN) {in->JoyHatD=1;}

	if ((SDL_JoystickGetHat(*joyst,0))==SDL_HAT_RIGHTUP) {in->JoyHatR=1;}
	if ((SDL_JoystickGetHat(*joyst,0))==SDL_HAT_LEFTUP) {in->JoyHatL=1;}
	if ((SDL_JoystickGetHat(*joyst,0))==SDL_HAT_LEFTDOWN) {in->JoyHatD=1;in->JoyHatL=1;}
	if ((SDL_JoystickGetHat(*joyst,0))==SDL_HAT_RIGHTDOWN) {in->JoyHatD=1;in->JoyHatR=1;}

if (SDL_JoystickGetAxis(*joyst,0)>10000) {in->JoyHatR=1;}
if (SDL_JoystickGetAxis(*joyst,0)<-10000) {in->JoyHatL=1;}
if (SDL_JoystickGetAxis(*joyst,1)>10000) {in->JoyHatD=1;}
//-32768 à 32768
}

if (in->JoyButton0!=0) {return 1;}
if (in->JoyHatR!=0) {return 1;}
if (in->JoyHatL!=0) {return 1;}
if (in->JoyHatD!=0) {return 1;}
}
return 0;
}

int main(int argc,char *argv[]){
uint32_t delay1=0,delay2=0,delay3=0;

SDL_Init(SDL_INIT_EVERYTHING);
SDL_JoystickEventState(SDL_DISABLE);
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,1024) ; 
Mix_AllocateChannels(7);
Mix_Volume(1, MIX_MAX_VOLUME);
Mix_VolumeMusic(MIX_MAX_VOLUME/3);
Mix_Music *music=Mix_LoadMUS("SND/Eternam2.wav");
Mix_Chunk *DROP;
Mix_Chunk *ROTATE;
Mix_Chunk *MOVE;
Mix_Chunk *LINE;
Mix_Chunk *START;
Mix_Chunk *NEXT_LEVEL;
Mix_Chunk *END;
DROP = Mix_LoadWAV("SND/DROP.wav");
ROTATE = Mix_LoadWAV("SND/ROTATE.wav");
MOVE = Mix_LoadWAV("SND/MOVE.wav");
LINE = Mix_LoadWAV("SND/LINE.wav");
START = Mix_LoadWAV("SND/START.wav");
NEXT_LEVEL = Mix_LoadWAV("SND/NEXT_LEVEL.wav");
END = Mix_LoadWAV("SND/END.wav");
Mix_VolumeChunk(DROP, MIX_MAX_VOLUME/3);
Mix_VolumeChunk(ROTATE, (MIX_MAX_VOLUME/6));
Mix_VolumeChunk(MOVE, (MIX_MAX_VOLUME/3));
Mix_VolumeChunk(LINE, MIX_MAX_VOLUME);
Mix_VolumeChunk(START, (MIX_MAX_VOLUME/2));
Mix_VolumeChunk(NEXT_LEVEL, MIX_MAX_VOLUME/2);
Mix_VolumeChunk(END, MIX_MAX_VOLUME);
//FreeConsole(); //efface le terminal pour windows
SDL_WM_SetCaption("Tiny tris v2.3 (2019-2021)", NULL);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); 
SDL_ShowCursor(SDL_DISABLE);
Widjet widjet={NULL}; 
config CFG={0,768,384};
LoadConfig(&CFG);
uint32_t FLAG=SDL_HWSURFACE;
if (CFG.FullScreen==1)    {FLAG=SDL_HWSURFACE|SDL_FULLSCREEN;}
widjet.render=SDL_SetVideoMode(CFG.resx,CFG.resy,8,FLAG);
WidjetInit(&widjet);
widjet.Event.w=CFG.resx;
widjet.Event.h=CFG.resy;
SDL_Joystick* Joyst=NULL;
NumberofJoystick=SDL_NumJoysticks();
if (NumberofJoystick>=1) {
Joyst=SDL_JoystickOpen(0);
if ( Joyst == NULL ){NumberofJoystick=0;fprintf(stderr,"Erreur joystick\n");
}else{
if (JoystickUpdateEvents(&Joyst,&widjet.Event)) {NumberofJoystick=0;}
}
}
SDL_JoystickEventState(SDL_DISABLE);
reset_Score_TTRIS();
Mix_PlayMusic(music, -1);
MENU:;
uint8_t Rot_TTRIS=0;
uint8_t SKIP_FRAME=0;
INIT_ALL_VAR_TTRIS();
Game_Play_TTRIS();
Ou_suis_Je_TTRIS(xx_TTRIS,yy_TTRIS);
uint8_t TIMER_1=0;
recupe_HIGHSCORE_TTRIS();
Convert_Nb_of_line_TTRIS();

while((!widjet.Event.key[SDLK_ESCAPE]) && (!widjet.Event.quit)){
UpdateEvents(&widjet.Event);
JoystickUpdateEvents(&Joyst,&widjet.Event); //récupération des evenement
PIECEs_TTRIS=PSEUDO_RND_TTRIS();
if ((widjet.Event.key[SDLK_LCTRL])||(widjet.Event.JoyButton0)) {reset_Score_TTRIS();break;}
delay(33);
TIMER_1=(TIMER_1<14)?TIMER_1+1:0;
Flip_intro_TTRIS(&TIMER_1);
SDL_FlipBuffer(widjet.render,&CFG);

}
SOUND_BOX[4]=1;

SETUP_NEW_PREVIEW_PIECE_TTRIS(&Rot_TTRIS);
Tiny_Flip_TTRIS(128);
SDL_Delay(100);
xx_TTRIS=55;yy_TTRIS=5;

while((!widjet.Event.key[SDLK_ESCAPE]) && (!widjet.Event.quit)){
	UpdateEvents(&widjet.Event);
JoystickUpdateEvents(&Joyst,&widjet.Event);
if (OU_SUIS_JE_X_ENGAGED_TTRIS==0) {
if  (SPEED_x_trig_TTRIS==0){
if ((TINYJOYPAD_RIGHT)||(widjet.Event.JoyHatR)) {
  if (LONG_PRESS_X_TTRIS==0) {SOUND_BOX[1]=1;}
  if ((LONG_PRESS_X_TTRIS==0)||(LONG_PRESS_X_TTRIS==20)) {
  DEPLACEMENT_XX_TTRIS=1;
  SPEED_x_trig_TTRIS=2;
  }
  if (LONG_PRESS_X_TTRIS<20) {LONG_PRESS_X_TTRIS++;}
  }
if ((TINYJOYPAD_LEFT)||(widjet.Event.JoyHatL)) {
  if (LONG_PRESS_X_TTRIS==0) {SOUND_BOX[1]=1;}
  if ((LONG_PRESS_X_TTRIS==0)||(LONG_PRESS_X_TTRIS==20)) {
    DEPLACEMENT_XX_TTRIS=-1;
    SPEED_x_trig_TTRIS=2;
    }
  if (LONG_PRESS_X_TTRIS<20) {LONG_PRESS_X_TTRIS++;}
  }
  
}else{
  SPEED_x_trig_TTRIS=(SPEED_x_trig_TTRIS>0)?SPEED_x_trig_TTRIS-1:0;}
  }
  
if ((TINYJOYPAD_RIGHT==0)&&(widjet.Event.JoyHatR==0)&&(TINYJOYPAD_LEFT==0)&&(widjet.Event.JoyHatL==0)) {
	LONG_PRESS_X_TTRIS=0;
	PSEUDO_RND_TTRIS();
	}
	
if ((BUTTON_UP)&&(widjet.Event.JoyButton0==0) ) {
  if ((OU_SUIS_JE_X_ENGAGED_TTRIS==0)&&(OU_SUIS_JE_Y_ENGAGED_TTRIS==0)) {Ripple_filter_TTRIS=0;}
  }
if (Ripple_filter_TTRIS==1) {CHECK_if_Rot_Ok_TTRIS(&Rot_TTRIS);Ripple_filter_TTRIS=2;}
if (OU_SUIS_JE_Y_ENGAGED_TTRIS==0){
  DROP_TRIG_TTRIS--;
  if (DROP_TRIG_TTRIS==0) {DEPLACEMENT_YY_TTRIS=1;DROP_TRIG_TTRIS=Level_Speed_ADJ_TTRIS;}
  }
if (DROP_SPEED_TTRIS>0) {
  DROP_SPEED_TTRIS--;
  }else{
    DROP_SPEED_TTRIS=Level_Speed_ADJ_TTRIS;
    }
if ((TINYJOYPAD_DOWN)||(widjet.Event.JoyHatD)){
	
if (OU_SUIS_JE_X_ENGAGED_TTRIS==0) {
DEPLACEMENT_XX_TTRIS=0;
LONG_PRESS_X_TTRIS=1;
}

  PSEUDO_RND_TTRIS();
  if (DOWN_DESACTIVE_TTRIS==0) {DEPLACEMENT_YY_TTRIS=1;DROP_SPEED_TTRIS=0;}
  }else{
    DOWN_DESACTIVE_TTRIS=0;
    } 
if (DROP_BREAK_TTRIS==6) {
	Mix_PlayChannel(0, DROP, 0);
  END_DROP_TTRIS(widjet.render,&CFG);
  SOUND_BOX[2]=1;
  if (End_Play_TTRIS()) {  Tiny_Flip_TTRIS(128); SDL_FlipBuffer(widjet.render,&CFG);delay(100);Mix_PlayChannel(2, END, 0);delay(2000);Check_NEW_RECORD();goto MENU;}
  yy_TTRIS=2;xx_TTRIS=55;
  PIECEs_TTRIS=PIECEs_TTRIS_PREVIEW;
  SETUP_NEW_PREVIEW_PIECE_TTRIS(&Rot_TTRIS);
  DOWN_DESACTIVE_TTRIS=1; 
  Tiny_Flip_TTRIS(128);
    SDL_FlipBuffer(widjet.render,&CFG);
  Game_Play_TTRIS();
  Tiny_Flip_TTRIS(128);
    SDL_FlipBuffer(widjet.render,&CFG);
  }  
  //déplacer cette ligne
if (((BUTTON_DOWN)||(widjet.Event.JoyButton0))&&(Ripple_filter_TTRIS==0)) {PSEUDO_RND_TTRIS();Ripple_filter_TTRIS=1;}

Move_Piece_TTRIS();
uint8_t SD;
for (SD=0;SD<10;SD++){
if (SOUND_BOX[SD]==1) {
	switch(SD){
		case 0:Mix_PlayChannel(6, ROTATE, 0);break;
		case 1:Mix_PlayChannel(1,MOVE , 0);break;
		case 3:Mix_PlayChannel(3,NEXT_LEVEL , 0);break;
		case 4:Mix_PlayChannel(4, START, 0);break;
		case 5:Mix_PlayChannel(5, LINE, 0);break;
		default:break;	
	}
	  SOUND_BOX[SD]=0;
}
}
  if (SKIP_FRAME==4) {
  Tiny_Flip_TTRIS(82);
  SDL_FlipBuffer(widjet.render,&CFG);
  SKIP_FRAME=0;
 }else{SKIP_FRAME++;}
delay2=SDL_GetTicks();
delay3=delay2-delay1;
if ((delay3<spin2)) {SDL_Delay(spin2-delay3);}
delay1=SDL_GetTicks();
}

Mix_FreeChunk(DROP);
DROP=NULL;
Mix_FreeChunk(ROTATE);
ROTATE=NULL;
Mix_FreeChunk(MOVE);
MOVE=NULL;
Mix_FreeChunk(LINE);
LINE=NULL;
Mix_FreeChunk(START);
START=NULL;
Mix_FreeChunk(NEXT_LEVEL);
NEXT_LEVEL=NULL;
Mix_FreeChunk(END);
END=NULL;
Mix_FreeMusic(music);
music=NULL;
SDL_FreeSurface(widjet.render);
WidjetFree(&widjet);
SDL_Quit();
return 0;
}

uint8_t recbit(uint8_t bitrec,uint8_t bit){
if ((bit&(1<<bitrec))==0){return 0;}else{ return 1;}
return 0;
}

 void  SSD1306_ssd1306_send_data_start(void){
ByteX=0;
ByteY=0;
 }

void SSD1306_ssd1306_send_byte(uint8_t value){
	
VideoBuff[ByteY*8][ByteX]=recbit(0,value);
VideoBuff[(ByteY*8)+1][ByteX]=recbit(1,value);
VideoBuff[(ByteY*8)+2][ByteX]=recbit(2,value);
VideoBuff[(ByteY*8)+3][ByteX]=recbit(3,value);
VideoBuff[(ByteY*8)+4][ByteX]=recbit(4,value);
VideoBuff[(ByteY*8)+5][ByteX]=recbit(5,value);
VideoBuff[(ByteY*8)+6][ByteX]=recbit(6,value);
VideoBuff[(ByteY*8)+7][ByteX]=recbit(7,value);
ByteX++;if (ByteX>127) {ByteY++;ByteX=0;}
}

void SDL_FlipBuffer(SDL_Surface *ren,config *CFG){
#define SQ 0
uint8_t xx,yy;
uint8_t COL_MAP;
uint8_t DividerX=CFG->resx/128;
uint8_t Dividery=CFG->resy/64;
	SDL_Rect rec;
rec.w=DividerX+SQ;
rec.h=Dividery+SQ;
for(yy=0;yy<64;yy++){
for(xx=0;xx<128;xx++){
rec.x=(xx*DividerX);
rec.y=(yy*Dividery);
if (((xx>43)&&(xx<84))) {
	COL_MAP=SDL_MapRGB(ren->format,200,230,255);
rec.x=(xx*DividerX)+rand()%2;
rec.y=(yy*Dividery)+rand()%2;
	}else{
		
	if (yy<19){	COL_MAP=SDL_MapRGB(ren->format,230,230,255);}else{
COL_MAP=SDL_MapRGB(ren->format,195-yy,195-yy,255-(yy-12));
		}
		}

SDL_FillRect(ren,&rec,(VideoBuff[yy][xx]*COL_MAP));
}}
SDL_Flip(ren);
}

void reset_Score_TTRIS(void){
for(uint8_t x=0;x<3;x++){Nb_of_line_TTRIS[x]=0;}
Level_TTRIS=0;
Scores_TTRIS=0;
Nb_of_line_F_TTRIS=0;
}

uint8_t PSEUDO_RND_TTRIS(void){
RND_VAR_TTRIS=(RND_VAR_TTRIS<6)?RND_VAR_TTRIS+1:0;
return RND_VAR_TTRIS;
}

void END_DROP_TTRIS(SDL_Surface *ren,config *CFG){
  uint8_t x,y;
  DROP_BREAK_TTRIS=0;
  for (y=0;y<5;y++){
  for (x=0;x<5;x++){
  if (Piece_Mat2_TTRIS[x][y]==1) {CHANGE_GRID_STAT_TTRIS(OU_SUIS_JE_X_TTRIS+(x),OU_SUIS_JE_Y_TTRIS+(y),1);}
  }}
  Scores_TTRIS=(OU_SUIS_JE_Y_TTRIS<9)?Scores_TTRIS+2:Scores_TTRIS+1;
  yy_TTRIS=0;
  xx_TTRIS=0;
  DELETE_LINE_TTRIS(ren,CFG);Convert_Nb_of_line_TTRIS();
}

void SETUP_NEW_PREVIEW_PIECE_TTRIS(uint8_t *Rot_TTRIS){
  PIECEs_TTRIS_PREVIEW=PSEUDO_RND_TTRIS();
  Select_Piece_TTRIS(PIECEs_TTRIS);
  *Rot_TTRIS=0;
  rotate_Matrix_TTRIS(*Rot_TTRIS);
  }


uint8_t MAP(uint8_t VAR,uint8_t st,uint8_t ed,uint8_t out_st,uint8_t out_rd){
	switch(VAR){
		case 0:return 11;
		case 1:return 11;
		case 2:return 10;
		case 3:return 10;
		case 4:return 9;
		case 5:return 9;
		case 6:return 8;
	    case 7:return 8;
	    case 8:return 7;
		case 9:return 7;
		case 10:return 6;
		case 11:return 6;
		case 12:return 5;
	    case 13:return 5;
		case 14:return 4;
	    case 15:return 4;
	    case 16:return 3;
		case 17:return 3;
		case 18:return 2;
		case 19:return 2;
		case 20:return 1;
	    default:return 1;
	}
}

void Game_Play_TTRIS(void){
uint8_t LEVEL_TMP=(Nb_of_line_F_TTRIS/20);
if (Level_TTRIS!=LEVEL_TMP) {Level_TTRIS=LEVEL_TMP;
	SOUND_BOX[0]=0;
	SOUND_BOX[1]=0;
	SOUND_BOX[2]=0;
	SOUND_BOX[3]=1;
	SOUND_BOX[4]=0;
    SOUND_BOX[5]=0;
	}
Level_Speed_ADJ_TTRIS=MAP(Level_TTRIS,0,20,11,1);
}

uint8_t End_Play_TTRIS(void){
for (uint8_t t=0;t<12;t++){
if (GRID_STAT_TTRIS(t,1)==1) {return 1;}
}
return 0;
}

void DELETE_LINE_TTRIS(SDL_Surface *ren,config *CFG){
uint8_t LOOP,SCAN_Line,ADDs_Block,OK_DELETE=0;
uint8_t LINE_MEM[19]={0}; 
uint8_t Nb_of_Line_temp=0;
for (LOOP=0;LOOP<19;LOOP++){
ADDs_Block=1;
for (SCAN_Line=0;SCAN_Line<12;SCAN_Line++){
if (GRID_STAT_TTRIS(SCAN_Line,LOOP)==0) {ADDs_Block=0;}
}
if (ADDs_Block) {
  LINE_MEM[LOOP]=1;
  OK_DELETE=1;
  }
}
if (OK_DELETE==1) {
  FLASH_LINE_TTRIS(&LINE_MEM[0],ren,CFG);
  Clean_Grid_TTRIS(&LINE_MEM[0]);
  }
for (LOOP=0;LOOP<19;LOOP++){
if (LINE_MEM[LOOP]==1) {Nb_of_Line_temp++;}
}
Nb_of_line_F_TTRIS=Nb_of_line_F_TTRIS+Nb_of_Line_temp;
Scores_TTRIS=(Scores_TTRIS+Calcul_of_Score_TTRIS(Nb_of_Line_temp));
}

uint8_t Calcul_of_Score_TTRIS(uint8_t Tmp_TTRIS){
switch(Tmp_TTRIS){
  case 0:return 0; break;
  case 1:return 2; break;
  case 2:return 5; break;
  case 3:return 8; break;
  case 4:return 12; break;
  default:return 0; break;
}}

void FLASH_LINE_TTRIS(uint8_t *PASS_LINE,SDL_Surface *ren,config *CFG){
uint8_t LOOP;
for (LOOP=0;LOOP<5;LOOP++){
PAINT_LINE_TTRIS(1,&PASS_LINE[0]);
Tiny_Flip_TTRIS(82);
    SDL_FlipBuffer(ren,CFG);
delay(30);
PAINT_LINE_TTRIS(0,&PASS_LINE[0]);
Tiny_Flip_TTRIS(82);
    SDL_FlipBuffer(ren,CFG);
delay(30);
}
SOUND_BOX[0]=0;
SOUND_BOX[1]=0;
SOUND_BOX[2]=0;
SOUND_BOX[3]=0;
SOUND_BOX[4]=0;
SOUND_BOX[5]=1;
}

void PAINT_LINE_TTRIS(uint8_t VISIBLE,uint8_t *PASS_LINE){
uint8_t LOOP,SCAN_Line;
for (LOOP=0;LOOP<19;LOOP++){
 if (PASS_LINE[LOOP]==1){
for (SCAN_Line=0;SCAN_Line<12;SCAN_Line++){ 
CHANGE_GRID_STAT_TTRIS(SCAN_Line,LOOP,VISIBLE);
}}}}

void Clean_Grid_TTRIS(uint8_t *PASS_LINE){
uint8_t GRID_2=18,GRID_1=18;
uint8_t x;
  while(1){
    if (PASS_LINE[GRID_1]==1) {GRID_2=GRID_1;GRID_2=(GRID_2>0)?GRID_2-1:0;break;}
    GRID_1=(GRID_1>0)?GRID_1-1:0;}
while(1){
  while(1){   
    if (PASS_LINE[GRID_2]==1) {GRID_2=(GRID_2>0)?GRID_2-1:0;}else{break;}
          } 
 for(x=0;x<12;x++){
CHANGE_GRID_STAT_TTRIS(x,GRID_1,(GRID_2>0)?GRID_STAT_TTRIS(x,GRID_2):0);
 }
GRID_1=(GRID_1>0)?GRID_1-1:0;
GRID_2=(GRID_2>0)?GRID_2-1:0;
if (GRID_1==0) {break;}
}}

uint8_t CHECK_if_Rot_Ok_TTRIS(uint8_t *Rot_TTRIS){
uint8_t Mem_rot=*Rot_TTRIS;
Ou_suis_Je_TTRIS(xx_TTRIS,yy_TTRIS);
*Rot_TTRIS=(*Rot_TTRIS<PIECEs_rot_TTRIS)?*Rot_TTRIS+1:0;
rotate_Matrix_TTRIS(*Rot_TTRIS);


if ((Check_collision_x_TTRIS(OU_SUIS_JE_X_ENGAGED_TTRIS)||(Check_collision_y_TTRIS(OU_SUIS_JE_Y_ENGAGED_TTRIS)))!=0) {
  *Rot_TTRIS=Mem_rot;
  rotate_Matrix_TTRIS(*Rot_TTRIS);
  return 1;
  }
SOUND_BOX[0]=1;
return 0;
}

uint8_t Check_collision_x_TTRIS(int8_t x_Axe){
uint8_t x,y;
for (y=0;y<5;y++){
for (x=0;x<5;x++){
if (Piece_Mat2_TTRIS[x][y]==1) {
  if (GRID_STAT_TTRIS((x+OU_SUIS_JE_X_TTRIS)+x_Axe,y+OU_SUIS_JE_Y_TTRIS)) {return 1;}
  } 
  }}
return 0; 
}

uint8_t Check_collision_y_TTRIS(int8_t y_Axe){
uint8_t x,y;
for (y=0;y<5;y++){
for (x=0;x<5;x++){
if (Piece_Mat2_TTRIS[x][y]==1) {
  if (GRID_STAT_TTRIS(x+OU_SUIS_JE_X_TTRIS,(y+OU_SUIS_JE_Y_TTRIS)+y_Axe)) {return 1;}} 
  }}
return 0; 
}

void Move_Piece_TTRIS(void){
Ou_suis_Je_TTRIS(xx_TTRIS,yy_TTRIS);
if (OU_SUIS_JE_X_ENGAGED_TTRIS==0){
  if (Check_collision_x_TTRIS(DEPLACEMENT_XX_TTRIS)) {DEPLACEMENT_XX_TTRIS=0;}
}
if (DEPLACEMENT_XX_TTRIS==1) {xx_TTRIS++;}
if (DEPLACEMENT_XX_TTRIS==-1) {xx_TTRIS--;}
Ou_suis_Je_TTRIS(xx_TTRIS,yy_TTRIS);
if (OU_SUIS_JE_X_ENGAGED_TTRIS==0) {DEPLACEMENT_XX_TTRIS=0;}

if (Check_collision_y_TTRIS(DEPLACEMENT_YY_TTRIS)) {
DEPLACEMENT_YY_TTRIS=0;LONG_PRESS_X_TTRIS=0;Ripple_filter_TTRIS=0;DROP_BREAK_TTRIS=6;}else{DROP_BREAK_TTRIS=0;}
if (DROP_SPEED_TTRIS==0){
if (DEPLACEMENT_YY_TTRIS==-1) {yy_TTRIS--;}
if (DEPLACEMENT_YY_TTRIS==1) {yy_TTRIS++;}
}
Ou_suis_Je_TTRIS(xx_TTRIS,yy_TTRIS);
if (OU_SUIS_JE_Y_ENGAGED_TTRIS==0) {DEPLACEMENT_YY_TTRIS=0;}
}

void Ou_suis_Je_TTRIS(int8_t xx_,int8_t yy_){
int8_t xx_t,yy_t;
xx_t=(((xx_)+9)-46);
yy_t=(((yy_)+9)-5);
OU_SUIS_JE_X_TTRIS=((xx_t/3)-3);
if ((xx_t%3)!=0) {
  OU_SUIS_JE_X_ENGAGED_TTRIS=1;
  }else{
    OU_SUIS_JE_X_ENGAGED_TTRIS=0;
    }
OU_SUIS_JE_Y_TTRIS=((yy_t/3)-3);
if ((yy_t)!=((OU_SUIS_JE_Y_TTRIS+3)*3)) {
  OU_SUIS_JE_Y_ENGAGED_TTRIS=1;
  }else{
    OU_SUIS_JE_Y_ENGAGED_TTRIS=0;
    }
}

void Select_Piece_TTRIS(uint8_t Piece_){
PIECEs_TTRIS =Piece_;
switch(Piece_){
  case 0:PIECEs_rot_TTRIS=3;break;
  case 1:PIECEs_rot_TTRIS=0;break;
  case 2:
  case 3:
  case 4:PIECEs_rot_TTRIS=1;break;
  case 5:
  case 6:PIECEs_rot_TTRIS=3;break;
  default:PIECEs_rot_TTRIS=0;break;
}}

void rotate_Matrix_TTRIS(uint8_t ROT){
uint8_t a_=0,b_=0;
for (uint8_t y=0;y<5;y++){
for (uint8_t x=0;x<5;x++){
switch(ROT){
  case 0:a_=x,b_=y;break;
  case 1:a_=4-y,b_=x;break;
  case 2:a_=4-x,b_=4-y;break;
  case 3:a_=y,b_=4-x;break;
  default:break;
}
Piece_Mat2_TTRIS[a_][b_]=Scan_Piece_Matrix_TTRIS(x,y+(PIECEs_TTRIS*5));
}}}

uint8_t Scan_Piece_Matrix_TTRIS(int8_t x_Mat,int8_t y_Mat){
uint8_t Result=(0b10000000>>x_Mat)&pgm_read_byte(&Pieces_TTRIS[y_Mat]);
if (Result) {return 1;}else{return 0;}
return 0;
}

uint8_t GRID_STAT_TTRIS(int8_t X_SCAN,int8_t Y_SCAN){
if (Y_SCAN<0) return 0;
if ((X_SCAN<0)||(X_SCAN>11)) {return 1;}
if (Y_SCAN>18) {return 1;}
uint8_t Y_VAR_SELECT=Y_SCAN>>3;
uint8_t Y_VAR_DECALAGE=RecupeDecalageY_TTRIS(Y_SCAN);
uint8_t COMP_BYTE_DECALAGE = (0b10000000>>Y_VAR_DECALAGE);
if ((COMP_BYTE_DECALAGE&Grid_TTRIS[X_SCAN][Y_VAR_SELECT])==0) {return 0;}else{return 1;}
return 0;
}

uint8_t CHANGE_GRID_STAT_TTRIS(int8_t X_SCAN,int8_t Y_SCAN,uint8_t VALUE){
if ((X_SCAN<0)||(X_SCAN>11)) return 0;
if ((Y_SCAN<0)||(Y_SCAN>18)) return 0;
uint8_t Y_VAR_SELECT=Y_SCAN>>3;
uint8_t Y_VAR_DECALAGE=RecupeDecalageY_TTRIS(Y_SCAN);
uint8_t COMP_BYTE_DECALAGE = (0b10000000>>Y_VAR_DECALAGE);
if (VALUE) {Grid_TTRIS[X_SCAN][Y_VAR_SELECT]=COMP_BYTE_DECALAGE|Grid_TTRIS[X_SCAN][Y_VAR_SELECT];}else{
Grid_TTRIS[X_SCAN][Y_VAR_SELECT]=(0xff-COMP_BYTE_DECALAGE)&Grid_TTRIS[X_SCAN][Y_VAR_SELECT];}
return 0;
}

uint8_t blitzSprite_TTRIS(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES){
uint8_t OUTBYTE;
uint8_t WSPRITE=pgm_read_byte(&SPRITES[0]);
uint8_t HSPRITE=pgm_read_byte(&SPRITES[1]);
uint8_t Wmax= (HSPRITE*WSPRITE)+1;
uint16_t PICBYTE=FRAME*(Wmax-1);
uint8_t RECUPELINEY=RecupeLineY_TTRIS(yPos);
if ((xPASS>((xPos+(WSPRITE-1))))||(xPASS<xPos)||((RECUPELINEY>yPASS)||((RECUPELINEY+(HSPRITE))<yPASS))) {return 0x00;}
uint8_t SPRITEyLINE=(yPASS-(RECUPELINEY));
uint8_t SPRITEyDECALAGE=(RecupeDecalageY_TTRIS(yPos));
uint8_t ScanA=(((xPASS-xPos)+(SPRITEyLINE*WSPRITE))+2);
uint8_t ScanB=(((xPASS-xPos)+((SPRITEyLINE-1)*WSPRITE))+2);
if (ScanA>Wmax) {OUTBYTE=0x00;}else{OUTBYTE=SplitSpriteDecalageY_TTRIS(SPRITEyDECALAGE,pgm_read_byte(&SPRITES[ScanA+(PICBYTE)]),1);}
if ((SPRITEyLINE>0)) {
uint8_t OUTBYTE2=SplitSpriteDecalageY_TTRIS(SPRITEyDECALAGE,pgm_read_byte(&SPRITES[ScanB+(PICBYTE)]),0);
if (ScanB>Wmax) {return OUTBYTE;}else{return OUTBYTE|OUTBYTE2;}
}else{return OUTBYTE;}
}

uint8_t H_grid_Scan_TTRIS(uint8_t xPASS){
return pgm_read_byte(&H_Grid_TTTRIS[xPASS-46]);  
}

uint8_t Recupe_TTRIS(uint8_t xPASS,uint8_t yPASS){
uint8_t BYTE_TTRIS=0;
uint8_t x=0;
for (uint8_t y=MEM_TTTRIS[(yPASS<<1)];y<MEM_TTTRIS[(yPASS<<1)+1];y++){
if ((xPASS>45)&&(xPASS<82)){
  x=H_grid_Scan_TTRIS(xPASS);
  }else{
    return 
    (RECUPE_BACKGROUND_TTRIS(xPASS,yPASS)|
    NEXT_BLOCK_TTRIS(xPASS,yPASS)|
    recupe_Nb_of_line_TTRIS(xPASS,yPASS)|
    recupe_SCORES_TTRIS(xPASS,yPASS)|
    recupe_LEVEL_TTRIS(xPASS,yPASS));}
if (GRID_STAT_TTRIS(x,y)==1) {BYTE_TTRIS=BYTE_TTRIS|blitzSprite_TTRIS(46+(x*3),5+(y*3),xPASS,yPASS,0,tinyblock_TTTRIS);}
}
return RECUPE_BACKGROUND_TTRIS(xPASS,yPASS)|BYTE_TTRIS|DropPiece_TTRIS(xPASS,yPASS);
}

uint8_t NEXT_BLOCK_TTRIS(uint8_t xPASS,uint8_t yPASS){
 if (xPASS>89){
uint8_t Byte_Mem=0;
uint8_t x_add=0;
uint8_t y_add=0;
switch(PIECEs_TTRIS_PREVIEW){
  case 0:x_add=1;y_add=1;break;
  case 1:y_add=-1;break;
  case 2:x_add=1;break;
  case 3:break;
  case 4:x_add=1;y_add=1;break;
  case 5:x_add=1;break;
  case 6:break;
  default:break;
}
for (uint8_t y=0;y<5;y++){
for (uint8_t x=0;x<5;x++){
if (Scan_Piece_Matrix_TTRIS(x,y+(PIECEs_TTRIS_PREVIEW*5))==1) {Byte_Mem|=blitzSprite_TTRIS(92+(x*2)+x_add,(27+(y*2))-5+y_add,xPASS,yPASS,0,tiny_PREVIEW_block_TTTRIS);}
}}
return Byte_Mem;
}
return 0;
}

uint8_t RECUPE_BACKGROUND_TTRIS(uint8_t xPASS,uint8_t yPASS){
return pgm_read_byte(&BACKGROUND_TTRIS[xPASS+(yPASS*128)]);
}

uint8_t DropPiece_TTRIS(uint8_t xPASS,uint8_t yPASS){
uint8_t Byte_Mem=0;
for (uint8_t y=0;y<5;y++){
for (uint8_t x=0;x<5;x++){
if (Piece_Mat2_TTRIS[x][y]==1) {Byte_Mem|=blitzSprite_TTRIS(xx_TTRIS+(x*3),(yy_TTRIS+(y*3))-5,xPASS,yPASS,0,tinyblock2_TTTRIS);}
}}
return Byte_Mem;
}

uint8_t SplitSpriteDecalageY_TTRIS(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN){
if (UPorDOWN) {return Input<<decalage;}
return Input>>(8-decalage);
}

uint8_t RecupeLineY_TTRIS(uint8_t Valeur){
return (Valeur>>3); 
}

uint8_t RecupeDecalageY_TTRIS(uint8_t Valeur){
return (Valeur-((Valeur>>3)<<3));
}

void Tiny_Flip_TTRIS(uint8_t HR_TTRIS){
uint8_t y,x; 
ByteX=0;
ByteY=0;
SSD1306_ssd1306_send_data_start();
for (y = 0; y < 8; y++){ 
for (x = 0; x < HR_TTRIS; x++){  
ByteX=x;
ByteY=y;
SSD1306_ssd1306_send_byte(Recupe_TTRIS(x,y));
}
}}

void Flip_intro_TTRIS(uint8_t *TIMER1){
uint8_t y,x; 
    SSD1306_ssd1306_send_data_start();
for (y = 0; y < 8; y++){ 
for (x = 0; x < 128; x++){SSD1306_ssd1306_send_byte(intro_TTRIS(x,y,TIMER1));}
}}

uint8_t intro_TTRIS(uint8_t xPASS,uint8_t yPASS,uint8_t *TIMER1){
return (RECUPE_BACKGROUND_TTRIS(xPASS,yPASS)|
  recupe_Chateau_TTRIS(xPASS,yPASS)|
  Recupe_Start_TTRIS(xPASS,yPASS,TIMER1)|
  recupe_SCORES_TTRIS(xPASS,yPASS)|
  recupe_Nb_of_line_TTRIS(xPASS,yPASS)|
  recupe_SCORES_TTRIS(xPASS,yPASS)|
  recupe_LEVEL_TTRIS(xPASS,yPASS)
  );
}

uint8_t Recupe_Start_TTRIS(uint8_t xPASS,uint8_t yPASS,uint8_t *TIMER1){
if (*TIMER1>7) {
  return blitzSprite_TTRIS(49,28,xPASS,yPASS,0,start_button_1_TTRIS)|blitzSprite_TTRIS(49,36,xPASS,yPASS,0,start_button_2_TTRIS);
  }else{
    return 0;
    }
}

uint8_t recupe_Chateau_TTRIS(uint8_t xPASS,uint8_t yPASS){
if (xPASS<46) return 0;
if (xPASS>81) return 0;
return pgm_read_byte(&chateau_TTRIS[(xPASS-46)+(yPASS*36)]); 
}

uint8_t recupe_SCORES_TTRIS(uint8_t xPASS,uint8_t yPASS){
if (xPASS<95) {return 0;}
if (xPASS>119){return 0;}
if (yPASS>1) {return 0;}
#define M10000 (Scores_TTRIS/10000)
#define M1000 (((Scores_TTRIS)-(M10000*10000))/1000)
#define M100 (((Scores_TTRIS)-(M1000*1000)-(M10000*10000))/100)
#define M10 (((Scores_TTRIS)-(M100*100)-(M1000*1000)-(M10000*10000))/10)
#define M1 ((Scores_TTRIS)-(M10*10)-(M100*100)-(M1000*1000)-(M10000*10000))
return 
(blitzSprite_TTRIS(95,8,xPASS,yPASS,M10000,police_TTRIS)|
 blitzSprite_TTRIS(99,8,xPASS,yPASS,M1000,police_TTRIS)|
 blitzSprite_TTRIS(103,8,xPASS,yPASS,M100,police_TTRIS)|
 blitzSprite_TTRIS(107,8,xPASS,yPASS,M10,police_TTRIS)|
 blitzSprite_TTRIS(111,8,xPASS,yPASS,M1,police_TTRIS)|
 blitzSprite_TTRIS(115,8,xPASS,yPASS,0,police_TTRIS));
}

void Convert_Nb_of_line_TTRIS(void){
Nb_of_line_TTRIS[2]= (Nb_of_line_F_TTRIS/100);
Nb_of_line_TTRIS[1]= ((Nb_of_line_F_TTRIS-(Nb_of_line_TTRIS[2]*100))/10);
Nb_of_line_TTRIS[0]= (Nb_of_line_F_TTRIS-(Nb_of_line_TTRIS[2]*100)-(Nb_of_line_TTRIS[1]*10));
}

uint8_t recupe_Nb_of_line_TTRIS(uint8_t xPASS,uint8_t yPASS){
if (xPASS<16) {return 0;}
if (xPASS>28){return 0;}
if (yPASS>1) {return 0;}
return 
(blitzSprite_TTRIS(16,8,xPASS,yPASS,Nb_of_line_TTRIS[2],police_TTRIS)|
 blitzSprite_TTRIS(20,8,xPASS,yPASS,Nb_of_line_TTRIS[1],police_TTRIS)|
 blitzSprite_TTRIS(24,8,xPASS,yPASS,Nb_of_line_TTRIS[0],police_TTRIS));
}

uint8_t recupe_LEVEL_TTRIS(uint8_t xPASS,uint8_t yPASS){
if (xPASS<109) {return 0;}
if (xPASS>118) {return 0;}
if (yPASS!=5)  {return 0;}
return 
(blitzSprite_TTRIS(109,41,xPASS,yPASS,(Level_TTRIS/10),police_TTRIS)|
 blitzSprite_TTRIS(114,41,xPASS,yPASS,(Level_TTRIS%10),police_TTRIS));
}

void INIT_ALL_VAR_TTRIS(void){
for(uint8_t y=0;y<3;y++){
for(uint8_t x=0;x<12;x++){
Grid_TTRIS[x][y]=0;}}
for(uint8_t y=0;y<5;y++){
for(uint8_t x=0;x<5;x++){
Piece_Mat2_TTRIS[x][y]=0;}}
LONG_PRESS_X_TTRIS=0;
DOWN_DESACTIVE_TTRIS=0;
DROP_SPEED_TTRIS=0;
SPEED_x_trig_TTRIS=0;
DROP_TRIG_TTRIS=1;
xx_TTRIS=0;
yy_TTRIS=0;
Ripple_filter_TTRIS=0;
PIECEs_TTRIS=0;
PIECEs_TTRIS_PREVIEW=0;
PIECEs_rot_TTRIS=0;
DROP_BREAK_TTRIS=0;
OU_SUIS_JE_X_TTRIS=0;
OU_SUIS_JE_Y_TTRIS=0;
OU_SUIS_JE_X_ENGAGED_TTRIS=0;
OU_SUIS_JE_Y_ENGAGED_TTRIS=0;
DEPLACEMENT_XX_TTRIS=0;
DEPLACEMENT_YY_TTRIS=0;
}

void recupe_HIGHSCORE_TTRIS(void){
if (FichierPresent("CONTROL.bmp")) {
SDL_Surface *TMP_=SDL_LoadBMP("CONTROL.bmp");
if ((getpixel(TMP_,412,262))==(0b10101010))  {
Level_TTRIS=(getpixel(TMP_,550,143));
Nb_of_line_F_TTRIS=(getpixel(TMP_,125,302));
Scores_TTRIS=(getpixel(TMP_,553,302));
}else{
Level_TTRIS=0;
Nb_of_line_F_TTRIS=0;
Scores_TTRIS=0;
	}
SDL_FreeSurface(TMP_);
}}

void save_HIGHSCORE_TTRIS(void){
if (FichierPresent("CONTROL.bmp")) {
SDL_Surface *TMP_=SDL_LoadBMP("CONTROL.bmp");
putpixel(TMP_,412,262,0b10101010);
putpixel(TMP_,550,143,Level_TTRIS);
putpixel(TMP_,125,302,Nb_of_line_F_TTRIS);
putpixel(TMP_,553,302,Scores_TTRIS);
SDL_SaveBMP(TMP_,"CONTROL.bmp");
SDL_FreeSurface(TMP_);
}}

void Check_NEW_RECORD(void){
uint8_t Save_=0;
if (FichierPresent("CONTROL.bmp")) {
SDL_Surface *TMP_=SDL_LoadBMP("CONTROL.bmp");
if ((getpixel(TMP_,412,262)!=((0b10101010))||(Scores_TTRIS>getpixel(TMP_,553,302))))  {
Save_=1;
}
SDL_FreeSurface(TMP_);
}
if (Save_==1) {save_HIGHSCORE_TTRIS(); }
}

void Sound_TTRIS(uint8_t freq,uint8_t dur){
}
