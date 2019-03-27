#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "Game.h"



int main( int argc, char* args[] )
{
    game myGame;
    gameState state;
    font mFont;
    int myBool = 0 ;
    int myBool2 = 0 ;
    Mix_Music *myMusique;
    if(init("Lake View Hotel ",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame,&mFont)){

                state.g_bRunning=1;


    }else{

            return 1;//something's wrong

    }
    myMusique = Mix_LoadMUS("./Assets/son/Silent Hill Promise Extended.wav");
    while(state.g_bRunning){
        handleEvents(&state);
        if (myBool == 0){
            writeSDL(&myGame,mFont);
            MainScreen(&myGame,state);
            Mix_PlayMusic(myMusique, 1);
            myBool = 1;
        }
        if (state.g_bRunning == 2){
            if (myBool2==0){
                printf("Test");
                myBool2 = 1;
                Scene1(&myGame,state);
            }

        }

    }
	//Destroy window
	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();


	return 0;
}


int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame, font *mFont){


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);

            }

    }else{


        return 0;
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    mFont->g_font=TTF_OpenFont("./Fonts/verdana.ttf",65);

    if(!mFont->g_font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        SDL_Delay(5000);
        exit(EXIT_FAILURE);
    }

     SDL_Color fontColor={255,0,0};

     myGame->g_surface=TTF_RenderText_Blended(mFont->g_font, "Lake View Hotel", fontColor);//Charge la police

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
       printf("%s", Mix_GetError());
    }

    return 1;


}

void handleEvents(gameState *state){

    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT: printf("Left\n") ; break;
                                case SDLK_RIGHT: printf("right\n"); break;
                                case SDLK_UP: printf("up\n")   ; break;
                                case SDLK_DOWN:printf("down\n")  ; break;
                                case SDLK_SPACE:state->g_bRunning = 2;break;

                            }
                            break;
    SDL_WaitEvent(&event);

        }
    }
switch(event.type)

{

    case SDL_QUIT: state->g_bRunning=0;break;
    case SDL_MOUSEBUTTONUP:
        if ((event.button.button == SDL_BUTTON_RIGHT) && (state->g_bRunning==2)){
            SDL_WaitEvent(&event);
            printf("\nSourie en X : %d\n",event.button.x);
            printf("Sourie en Y : %d\n",event.button.y);
            if(((event.button.x > 100 ) && (event.button.x < 400))&& ((event.button.y > 150)&&(event.button.x <400))){
                    printf("Bite ! \n");
            }
        }
    break;

}

}
void MainScreen(game *myGame,gameState state){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;

        if (state.g_bRunning==1){
            myGame->g_surface = IMG_Load("./Assets/main.png");//Chargement de l'image png
            printf("1");
        }

        if (state.g_bRunning==2){
                myGame->g_surface = IMG_Load("./Assets/meme.png");//Chargement de l'image png
            printf("2");
        }



        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=800;//1 image = w:128 et h:82
                    rectangleSource.h=500;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=SCREEN_WIDTH/2-rectangleSource.w/2;//debut x
                    rectangleDest.y=150;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);


                    //SDL_FLIP_NONE
                    //SDL_FLIP_HORIZONTAL
                    //SDL_FLIP_VERTICAL



                    SDL_RenderPresent(myGame->g_pRenderer); // Affichage

                    SDL_RenderClear(myGame->g_pRenderer);


                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


    destroyTexture(myGame);

}
void Scene1(game *myGame,gameState state){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;
        game asset;

        if (state.g_bRunning==2){
            myGame->g_surface = IMG_Load("./Assets/meme.png");//Chargement de l'image png

            printf("2");
        }


        if(myGame->g_surface){


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    rectangleSource.x=0;
                    rectangleSource.y=-200;
                    rectangleSource.w=800;//1 image = w:128 et h:82
                    rectangleSource.h=500;

                    SDL_QueryTexture(myGame->g_texture,NULL,NULL,NULL,NULL);

                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=SCREEN_WIDTH/2-rectangleSource.w/2;//debut x
                    rectangleDest.y=150;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);


                    //SDL_FLIP_NONE
                    //SDL_FLIP_VERTICAL



                    SDL_RenderPresent(myGame->g_pRenderer); // Affichage

                    SDL_RenderClear(myGame->g_pRenderer);


                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }


    destroyTexture(myGame);

}
void writeSDL(game *myGame,font mFont) {




        if(myGame->g_surface){


                //Définition du rectangle dest pour blitter la chaine
                SDL_Rect rectangle;
                rectangle.x=SCREEN_WIDTH/2-300;//debut x
                rectangle.y=0;//debut y
                rectangle.w=600; //Largeur
                rectangle.h=150; //Hauteur


                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation de la texture pour la chaine
                // Libération de la ressource occupée par le sprite
                if(!myGame->g_surface)
                    SDL_FreeSurface(myGame->g_surface);


                 if(myGame->g_texture){

                        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,NULL,&rectangle); // Copie du sprite grâce au SDL_Renderer
                        SDL_RenderPresent(myGame->g_pRenderer); // Affichage
                        //TODO out of memory sdl texture
                 }
                 else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de creation surface pour chaine (%s)\n",SDL_GetError());
        }

        destroyTexture(myGame);


}
void destroy(game *myGame){

    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}

void destroyFont(font *mFont){
    if(mFont->g_font!=NULL){
        TTF_CloseFont(mFont->g_font);
        mFont->g_font=NULL;
    }

}

void destroyTexture(game *myGame){

    //Destroy texture
    if(myGame->g_texture!=NULL)
            SDL_DestroyTexture(myGame->g_texture);


}

