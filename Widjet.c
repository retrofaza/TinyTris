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

#include <SDL/SDL.h>
#include "Widjet.h"


int LoadConfig(config *cfg);
int FichierPresent(const char* NomDuFichier);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void WidjetInit(Widjet *Structure);
void WidjetFree(Widjet *Structure);

void UpdateEvents(Input* in);
// fonction d'initialisation widjet fin

void UpdateEvents(Input* in){
SDL_Event event;

while(SDL_PollEvent(&event))
{
switch (event.type)
{
case SDL_VIDEOEXPOSE:
in->MOVE=1;
break;
case  SDL_VIDEORESIZE: 
in->RESIZE=1;
in->w=event.resize.w;in->h=event.resize.h;
break;
case SDL_KEYDOWN:
in->key[event.key.keysym.sym]=1;
break;
case SDL_KEYUP:
in->key[event.key.keysym.sym]=0;
break;
case SDL_MOUSEMOTION:
break;
case SDL_MOUSEBUTTONDOWN:
break;
case SDL_MOUSEBUTTONUP:
break;
case SDL_QUIT:
in->quit = 1;
break;
default:
break;
}}
}
void WidjetInit(Widjet *Structure){
memset(&Structure->Event,0,sizeof(Structure->Event));
}


void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
if (((x<surface->w) && (x>=0)) &&((y<surface->h) && (y>=0))) {
 int Bytes=0;
Bytes = surface->format->BytesPerPixel;
Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * Bytes;
switch(Bytes) {
case 1:
*p = pixel;
break;
case 2:
*(Uint16 *)p = pixel;
break;
case 3:
if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
p[0] = (pixel >> 16) & 0xff;
p[1] = (pixel >> 8) & 0xff;
p[2] = pixel & 0xff;
} else {
p[0] = pixel & 0xff;
p[1] = (pixel >> 8) & 0xff;
p[2] = (pixel >> 16) & 0xff;
}
break;
case 4:
*(Uint32 *)p = pixel;
break;
}}
}

Uint32 getpixel(SDL_Surface *surface, int x, int y){
//overflow detect
if (((x<surface->w) && (x>=0)) &&((y<surface->h) && (y>=0))) {
int bpp = surface->format->BytesPerPixel;
Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0; 
    }
}else{return 0;}
}

void WidjetFree(Widjet *Structure){
SDL_FreeSurface(Structure->render);
}

//fichier present
int FichierPresent(const char* NomDuFichier){
FILE* FileTemp = fopen(NomDuFichier, "r");
if (FileTemp != NULL) {fclose(FileTemp);return 1;}
return 0;
}

//load config
int LoadConfig(config *cfg){
int t=0;
char suite[255]="";
char c[2]="";
if (FichierPresent("Config.ini")) {
FILE *fichier;
fichier = fopen("Config.ini" , "r");
//nombre d'élément de configuration
for(t=0;t<11;t++){
while(c[0]!=EOF) {
c[0] = fgetc(fichier);
if (c[0]=='\n') {break;}
if (c[0]=='0'||c[0]=='1'||c[0]=='2'||c[0]=='3'||c[0]=='4'||c[0]=='5'||c[0]=='6'||c[0]=='7'||c[0]=='8'||c[0]=='9') {
strcat(suite,&c[0]);}
}
if (t==0) {cfg->FullScreen=atoi(suite);}
if (t==1) {cfg->resx=atoi(suite);}
if (t==2) {cfg->resy=atoi(suite);}

strcpy(suite,"");
}
fclose(fichier);
}else{
cfg->FullScreen=0;
cfg->resx=768;
cfg->resy=384;

}
return 0;
}

