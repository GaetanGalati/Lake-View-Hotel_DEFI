#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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
int Text(game *myGame,font *mFont, char ctext[200]);
void handleEvents(gameState *state,game *myGame,font *mFont);
void MainScreen(game *myGame,gameState state);
void Scene1(game *myGame,gameState state);
void writeSDL(game *myGame,font mFont);
int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize);
void destroyTexture(game *myGame);
void destroyFont(font *mFont);
void destroy(game *myGame);

//Screen dimension constants


#endif // GAME_H_INCLUDED
