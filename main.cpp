#include <SDL.h>
#include <SDL_image.h>
#include "iostream"
#include <time.h>
#include <stdlib.h>
using namespace std;

int mapa[13][22];
void cuadrado (int x, int y, int color,SDL_Rect& windowRect ,SDL_Rect& textureRect, SDL_Renderer* renderer, SDL_Texture* spriteSheet)
{
    windowRect.x = x*18;
    windowRect.y = y*18;
textureRect.x = (color -1) * textureRect.w;
SDL_RenderCopy(renderer, spriteSheet, &textureRect, &windowRect);

}

void mostrar_mapa(SDL_Rect& windowRect ,SDL_Rect& textureRect, SDL_Renderer* renderer, SDL_Texture* spriteSheet)
{int tempcolor;
for (int i = 0; i < 20; i++)
    {
        for(int j = 1; j < 11; j++)
        {if (mapa[i][j] != 0)
        {tempcolor =mapa[i][j];
         cuadrado(j,i,tempcolor,windowRect,textureRect,renderer,spriteSheet);
         }}}
}
void limpiar_mapa()
{
    for (int i = 0; i < 21; i++)
    {
        for(int j = 0; j < 12; j++ )
        {
            if (j == 0 || j == 11 || i == 20)
                {mapa [i][j] = -1;
                 cout<< "-1";
                }
            else
                {mapa [i][j] = 0;
                 cout<< "*0";}
        }
        cout<<endl;
    }
}
struct bloque
{
    int x,y;
};


class pieza
{
    bloque b_principal;
    bloque b_anexo[3];
    int color;
public:
    pieza (bloque b_principal, bloque b_anexo[3],int color);
    void mostrarpieza(SDL_Rect& windowRect ,SDL_Rect& textureRect, SDL_Renderer* renderer, SDL_Texture* spriteSheet);
    void incrX(int incr){b_principal.x += incr;}
    void incrY(int incr){b_principal.y += incr;}
    bool colisionabajo();
    bool colisionderecha();
    bool colisionizquierda();
    void insertarmapa();
    void setPrincipal(bloque new_prin) {b_principal = new_prin;}
    void setAnexo(bloque new_anexo[3])
    {for (int i = 0; i<3;i++)
    b_anexo[i] = new_anexo[i];
    }
    void setColor(int newColor){color = newColor;}

};

pieza::pieza (bloque b_principal_, bloque b_anexo_[3],int color_)
{
    b_principal = b_principal_;
    for(int x = 0; x < 3;x++)
    {b_anexo[x] = b_anexo_[x];}
    color = color_;


}
void pieza::insertarmapa()
{
 int anexo_x, anexo_y;
mapa[b_principal.y][b_principal.x] = color;
for(int i = 0;i <3;i++)
{
anexo_x = b_principal.x + b_anexo[i].x;
anexo_y = b_principal.y + b_anexo[i].y;
mapa[anexo_y][anexo_x] = color;
}
}
void pieza::mostrarpieza(SDL_Rect& windowRect ,SDL_Rect& textureRect, SDL_Renderer* renderer, SDL_Texture* spriteSheet)
{
    int anexo_x, anexo_y;
cuadrado(b_principal.x,b_principal.y,color,windowRect,textureRect,renderer,spriteSheet);


for(int i = 0;i <3;i++)
{
anexo_x = b_principal.x + b_anexo[i].x;
anexo_y = b_principal.y + b_anexo[i].y;
cuadrado(anexo_x,anexo_y,color,windowRect,textureRect,renderer,spriteSheet);

}}

bool pieza::colisionabajo()
{
      int anexo_x, anexo_y;
    if (mapa[b_principal.y + 1][b_principal.x] != 0)
    return true;
    for(int i = 0;i <3;i++)
{
anexo_x = b_principal.x + b_anexo[i].x;
anexo_y = b_principal.y + b_anexo[i].y;
if (mapa[anexo_y +1][anexo_x] != 0)
    return true;
}
return false;
}

bool pieza::colisionizquierda()
{
      int anexo_x, anexo_y;
    if (mapa[b_principal.y][b_principal.x-1] != 0)
    return true;
    for(int i = 0;i <3;i++)
{
anexo_x = b_principal.x + b_anexo[i].x;
anexo_y = b_principal.y + b_anexo[i].y;
if (mapa[anexo_y][anexo_x -1] != 0)
    return true;
}
return false;
}

bool pieza::colisionderecha()
{
      int anexo_x, anexo_y;
    if (mapa[b_principal.y][b_principal.x + 1] != 0)
    return true;
    for(int i = 0;i <3;i++)
{
anexo_x = b_principal.x + b_anexo[i].x;
anexo_y = b_principal.y + b_anexo[i].y;
if (mapa[anexo_y][anexo_x + 1] != 0)
    return true;
}
return false;
}


int main(int argc, char** args)
{srand(time(0));
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Animating using Sprite Sheets", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event input;
    bool quit = false;
 limpiar_mapa();
    SDL_Texture* spriteSheet = NULL;
    SDL_Surface* temp = IMG_Load("C:/Users/darkx/Desktop/tetris/bin/Debug/images/tiles.png");
    spriteSheet = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    SDL_Rect windowRect;
    windowRect.x = 0;
    windowRect.y = 0;
    windowRect.w = 18;
    windowRect.h = 18;

    SDL_Rect textureRect;
    textureRect.x = 0;
    textureRect.y = 0;

    SDL_QueryTexture(spriteSheet, NULL, NULL, &textureRect.w, &textureRect.h);

    textureRect.w /= 8;
    textureRect.x = 0 * textureRect.w;
 //enteros

 int vcaida = 7, aux = 0, pb = 0;
 int vcolision = 70,aux2 = 0;
 int aleatorio;
 //booleanos
 bool colb = false;
 bool coli = false;
 bool cold = false;

    //piezas
    bloque principal = {5,2};
    bloque anexo1[3] = {{0,-1},{1,-1},{0,1}};
    bloque anexo2[3] = {{0,1},{1,0},{-1,0}};
    bloque anexo3[3] = {{0,-1},{-1,-1},{-1,0}};
    bloque anexo4[3] = {{0,-1},{0,1},{0,2}};
    bloque anexo5[3] = {{0,-1},{0,1},{1,1}};
    bloque anexo6[3] = {{-1,-1},{0,-1},{1,0}};
   //pieza aleatoria

    pieza Actual(principal,anexo2,1);

    aleatorio = 1 + rand()%6;
    if (aleatorio == 1) Actual.setAnexo(anexo1),Actual.setColor(1);
    else if (aleatorio == 2) Actual.setAnexo(anexo2),Actual.setColor(2);
   else if (aleatorio == 3) Actual.setAnexo(anexo3),Actual.setColor(3);
   else if (aleatorio == 4) Actual.setAnexo(anexo4),Actual.setColor(4);
   else if (aleatorio == 5) Actual.setAnexo(anexo5),Actual.setColor(5);
   else if (aleatorio == 6) Actual.setAnexo(anexo6),Actual.setColor(6);
unsigned int lastTime = 0, currentTime;
    while (!quit)
    {
        while (SDL_PollEvent(&input) > 0)
        {
            if (input.type == SDL_QUIT) quit = true;


        switch(input.type)
        {
        case SDL_KEYDOWN:

        if ((input.key.keysym.sym == SDLK_RIGHT) && !cold)
        {Actual.incrX(1);}
        if ((input.key.keysym.sym == SDLK_LEFT) && !coli)
        {Actual.incrX(-1);}
        if ((input.key.keysym.sym == SDLK_DOWN))
        {vcaida = 0;}
        break;


        }
        }

        colb = false;
        cold = false;
        coli = false;







        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
        SDL_RenderClear(renderer);

        mostrar_mapa(windowRect,textureRect,renderer,spriteSheet);
         if (Actual.colisionabajo()) colb = true;
         if (Actual.colisionizquierda()) coli = true;
         if (Actual.colisionderecha()) cold = true;
        Actual.mostrarpieza(windowRect,textureRect,renderer,spriteSheet);




currentTime = SDL_GetTicks();
  if (currentTime > lastTime + 50) {

 if (++aux >= 7){
        vcaida = 7;
        aux = 0;
        }
  if (pb++ >= vcaida && !colb)
        {
            pb = 0;
            Actual.incrY(1);
        }


        //colision abajo
         if (++aux2>= vcolision && colb){
            aux2 = 0;
            Actual.insertarmapa();
            principal = {5,2};
            Actual.setPrincipal(principal);

            aleatorio = 1 + rand() % 6;


    if (aleatorio == 1) Actual.setAnexo(anexo1),Actual.setColor(1);
    else if (aleatorio == 2) Actual.setAnexo(anexo2),Actual.setColor(2);
   else if (aleatorio == 3) Actual.setAnexo(anexo3),Actual.setColor(3);
   else if (aleatorio == 4) Actual.setAnexo(anexo4),Actual.setColor(4);
   else if (aleatorio == 5) Actual.setAnexo(anexo5),Actual.setColor(5);
   else if (aleatorio == 6) Actual.setAnexo(anexo6),Actual.setColor(6);

colb = false;
         }
    lastTime = currentTime;
  }


        SDL_RenderPresent(renderer);



    }

    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
