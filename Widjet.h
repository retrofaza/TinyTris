//                                         TINY_TRIS_PC
//                      https://sites.google.com/view/tinytris
//                       (Dev) Daniel Champagne 2019-2021
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

#ifndef WIDJET_H
#define WIDJET_H

//structure
typedef struct Input{
//clavier
char key[SDLK_LAST];
int w,h,MOVE,RESIZE;
char quit;
//joystick
char JoyHatL;
char JoyHatR;
char JoyHatD;
char JoyButton0;
} Input;


typedef struct config{
int FullScreen;
int resx;
int resy;
}config;

typedef struct Widjet{

SDL_Surface *render;

Input Event;

} Widjet;
//fin structure

//fonction interne
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);


// fonction d'initialisation widjet
void WidjetInit(Widjet *Structure);
void WidjetFree(Widjet *Structure);
void UpdateEvents(Input* in);

int LoadConfig(config *cfg);
int FichierPresent(const char* NomDuFichier);

void reset_Score_TTRIS(void);
uint8_t PSEUDO_RND_TTRIS(void);
void INTRO_MANIFEST_TTRIS(void);
void END_DROP_TTRIS(SDL_Surface *ren,config *CFG);
void SETUP_NEW_PREVIEW_PIECE_TTRIS(uint8_t *Rot_TTRIS);
void CONTROLE_TTRIS(uint8_t *Rot_TTRIS);
void Game_Play_TTRIS(void);
uint8_t End_Play_TTRIS(void);
void DELETE_LINE_TTRIS(SDL_Surface *ren,config *CFG);
uint8_t Calcul_of_Score_TTRIS(uint8_t Tmp_TTRIS);
void FLASH_LINE_TTRIS(uint8_t *PASS_LINE,SDL_Surface *ren,config *CFG);
void PAINT_LINE_TTRIS(uint8_t VISIBLE,uint8_t *PASS_LINE);
void Clean_Grid_TTRIS(uint8_t *PASS_LINE);
uint8_t CHECK_if_Rot_Ok_TTRIS(uint8_t *Rot_TTRIS);
uint8_t Check_collision_x_TTRIS(int8_t x_Axe);
uint8_t Check_collision_y_TTRIS(int8_t y_Axe);
void Move_Piece_TTRIS(void);
void Ou_suis_Je_TTRIS(int8_t xx_,int8_t yy_);
void Select_Piece_TTRIS(uint8_t Piece_);
void rotate_Matrix_TTRIS(uint8_t ROT);
uint8_t Scan_Piece_Matrix_TTRIS(int8_t x_Mat,int8_t y_Mat);
uint8_t GRID_STAT_TTRIS(int8_t X_SCAN,int8_t Y_SCAN);
uint8_t CHANGE_GRID_STAT_TTRIS(int8_t X_SCAN,int8_t Y_SCAN,uint8_t VALUE);
uint8_t blitzSprite_TTRIS(int8_t xPos,int8_t yPos,uint8_t xPASS,uint8_t yPASS,uint8_t FRAME,const uint8_t *SPRITES);
uint8_t H_grid_Scan_TTRIS(uint8_t xPASS);
uint8_t Recupe_TTRIS(uint8_t xPASS,uint8_t yPASS);
uint8_t NEXT_BLOCK_TTRIS(uint8_t xPASS,uint8_t yPASS);
uint8_t RECUPE_BACKGROUND_TTRIS(uint8_t xPASS,uint8_t yPASS);
uint8_t DropPiece_TTRIS(uint8_t xPASS,uint8_t yPASS);
uint8_t SplitSpriteDecalageY_TTRIS(uint8_t decalage,uint8_t Input,uint8_t UPorDOWN);
uint8_t RecupeLineY_TTRIS(uint8_t Valeur);
uint8_t RecupeDecalageY_TTRIS(uint8_t Valeur);
void Tiny_Flip_TTRIS(uint8_t HR_TTRIS);
void Tiny_FULLREC_TTRIS(void);
void Flip_intro_TTRIS(uint8_t *TIMER1);
uint8_t intro_TTRIS(uint8_t xPASS,uint8_t yPASS,uint8_t *TIMER1);
uint8_t Recupe_Start_TTRIS(uint8_t xPASS,uint8_t yPASS,uint8_t *TIMER1);
uint8_t recupe_Chateau_TTRIS(uint8_t xPASS,uint8_t yPASS);
uint8_t recupe_SCORES_TTRIS(uint8_t xPASS,uint8_t yPASS);
void Convert_Nb_of_line_TTRIS(void);
uint8_t recupe_Nb_of_line_TTRIS(uint8_t xPASS,uint8_t yPASS);
uint8_t recupe_LEVEL_TTRIS(uint8_t xPASS,uint8_t yPASS);
void INIT_ALL_VAR_TTRIS(void);
void recupe_HIGHSCORE_TTRIS(void);
void save_HIGHSCORE_TTRIS(void);
void Check_NEW_RECORD(void);
void Sound_TTRIS(uint8_t freq,uint8_t dur);

#endif

