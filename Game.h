#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;


}game;

typedef struct gameState{

    int g_bRunning;


}gameState;

typedef struct font{

    TTF_Font *g_font;

}font;


typedef struct coordonnees{

    double x;
    double y;



}coordonnees;

typedef enum BOOL{true,false}BOOL;


int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame,font *mFont);
void handleEvents(gameState *state);
void MainScreen(game *myGame,gameState state);
void Scene1(game *myGame,gameState state);
void writeSDL(game *myGame,font mFont);
int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
void destroyTexture(game *myGame);
void destroyFont(font *mFont);
void destroy(game *myGame);

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

#endif // GAME_H_INCLUDED
