#include"play.h"
int main(int argc,char**argv){
    int turn=0;
    main_menu(&turn);
    //sdl initialization
    SDL_Window*x=NULL;
    init_window(x);

    SDL_Surface* screenSurface = NULL;
    gameplay(screenSurface,turn,x);

    //de-initialization
    end_window();
    return 0;
}
