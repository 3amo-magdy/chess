#include "Draw.h"
// take turn and screen surface to draw and window and t0 refer to previous moved piece char
//f3 & f4 refer to chosen piece position
//returns -1 if he commanded a valid move.
//returns 2 if the player command was to undo.
//returns 6 if it was to go back to main menu.
//returns 3 if it was to redo.
int play(int turn,SDL_Surface* screenSurface,SDL_Window* window,char* t0,int* f1,int* f2,int* f3,int* f4){
    game x;
    prepare_the_game(turn,&x);
    screen_clear();
    draw(screenSurface,&x);
    if(turn!=0){
        if(turn%2==0){
            name(p2);
        }
        else{
            name(p1);
        }
        printf(" has played : %c[%c%d] ---> [%c%d]\n\n",*t0,*f2+65,*f1+1,*f4+65,*f3+1);
    }
    if(turn%2==0){
        printf("it's ");name(p1);printf("'s turn ...\n");
    }
    else{
        printf("it's ");name(p2);printf("'s turn ...\n");
    }
    int checked=0;
    is_my_king_checked(&x,turn%2,&checked);
    if(!beSureKingIsDead(&x,checked,turn%2)){
        return 0;
    }
    if(!noleftpiece(&x)){
        return 0;
    }
    if(fiftymove(&x)){
        return 0;
    }
    if(checked==1){
        SDL_LoadWAV("bmp/check.wav",&wavspec,&wavbuffer,&wavlength);
        device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
        SDL_QueueAudio(device_id,wavbuffer,wavlength);
        SDL_PauseAudioDevice(device_id,0);
        SDL_Delay(300);
        SDL_CloseAudioDevice(device_id);
        SDL_FreeWAV(wavbuffer);
        MsgBox("check !");
    }

    int a,b,k,l,moves[8][8];
    int g=take_input(&x,moves,&a,&b,&k,&l,turn%2,window);
    if(g!=-1){return g;}
    *t0=x.board[a][b];*f1=a;*f2=b;*f3=k;*f4=l;

    perform_move(&x,turn%2,a,b,&k,&l,moves);
    SDL_LoadWAV("bmp/move.wav",&wavspec,&wavbuffer,&wavlength);
    device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
    SDL_QueueAudio(device_id,wavbuffer,wavlength);
    SDL_PauseAudioDevice(device_id,0);
    SDL_Delay(70);
    SDL_CloseAudioDevice(device_id);
    SDL_FreeWAV(wavbuffer);

    save_into_array(&x,turn);
    max_turn = turn;
    return 5;
}
//game loop it take screensurface and window to draw
//and turnn be 0 if start be  or be max numer of loaded game
//not end untill one payer chose back to main menu and he can undo after
//end of game
void gameplay(SDL_Surface*screenSurface,int turnn,SDL_Window*window){
    int state;
    int turn =turnn;
    while(1){
        int m,n;
        char t0;int f1,f2,f3,f4;
        state=play(turn,screenSurface,window,&t0,&f1,&f2,&f3,&f4);
        if(state==2){
            turn--;
        }
        else if(state==3){
            turn++;
        }
        else if(state==6){
            end_window();
            int turn =0;
            main_menu(&turn);

            init_window(window);
            SDL_Surface* screenSurface;

            gameplay(screenSurface,turn,window);

            end_window();
            return 0;
        }
        else if(state==0){
            printf("game ended, however you can undo, type:\n['u' to undo]\n['y' to go back]\n[any button else to quit]\n");
            SDL_Event event;
            int taken=0;
            while(!taken){
                while (SDL_PollEvent(&event)) {
                    switch( event.type ){
                    case SDL_KEYDOWN:
                        printf( "Key press detected\n" );
                        if(event.key.keysym.sym==SDLK_u){
                            if (turn>0){
                                turn--;
                                taken=1;
                            }
                        }
                        else if(event.key.keysym.sym==SDLK_s){
                                save();
                                end_window();
                                int turn =0;
                                main_menu(&turn);

                                init_window(window);
                                SDL_Surface *screenSurface;

                                gameplay(screenSurface,turn,window);

                                end_window();
                                return;
                        }
                        else if(event.key.keysym.sym==SDLK_y){
                            end_window();
                            int turn =0;
                            main_menu(&turn);

                            init_window(window);
                            SDL_Surface* screenSurface;

                            gameplay(screenSurface,turn,window);

                            end_window();
                            return;
                        }
                        else{
                            break;
                        }

                    case SDL_KEYUP:
                        printf( "Key release detected\n" );
                        break;
                    case SDL_QUIT:
                        return 6;
                    default:
                        break;
                    }
                }
            }
        }
        else{
            turn++;
        }
    }
}

