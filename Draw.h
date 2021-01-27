#include "save.h"
//to draw the board
void draw_board(game*s,int i,int j,SDL_Surface* screenSurface){
    SDL_Rect place;
    place.h=slot;
    place.w=slot;
    place.x=j*slot+6;
    place.y=i*slot+6;
    switch(s->board[i][j]){
        case 'k':
            SDL_BlitSurface(king,NULL,screenSurface,&place);
            break;
        case 'K':
            SDL_BlitSurface(KING,NULL,screenSurface,&place);
            break;
        case 'p':
            SDL_BlitSurface(pawn,NULL,screenSurface,&place);
            break;
        case 'P':
            SDL_BlitSurface(PAWN,NULL,screenSurface,&place);
            break;
        case 'q':
            SDL_BlitSurface(queen,NULL,screenSurface,&place);
            break;
        case 'Q':
            SDL_BlitSurface(QUEEN,NULL,screenSurface,&place);
            break;
        case 'n':
            SDL_BlitSurface(knight,NULL,screenSurface,&place);
            break;
        case 'N':
            SDL_BlitSurface(KNIGHT,NULL,screenSurface,&place);
            break;
        case 'b':
            SDL_BlitSurface(bishop,NULL,screenSurface,&place);
            break;
        case 'B':
            SDL_BlitSurface(BISHOP,NULL,screenSurface,&place);
            break;
        case 'r':
            SDL_BlitSurface(rook,NULL,screenSurface,&place);
            break;
        case 'R':
            SDL_BlitSurface(ROOK,NULL,screenSurface,&place);
            break;
        default:
            break;
    }
}
//to draw the captured
void draw_captured(game*s,int i,int j,SDL_Surface* screenSurface){
    SDL_Rect place;
    place.h=slot;
    place.w=slot;
    place.x=j*slot+6+552;
    place.y=(i/4)*slot+6;
    switch(s->captured[i]){
        case 'k':
            SDL_BlitSurface(king,NULL,screenSurface,&place);
            break;
        case 'K':
            SDL_BlitSurface(KING,NULL,screenSurface,&place);
            break;
        case 'p':
            SDL_BlitSurface(pawn,NULL,screenSurface,&place);
            break;
        case 'P':
            SDL_BlitSurface(PAWN,NULL,screenSurface,&place);
            break;
        case 'q':
            SDL_BlitSurface(queen,NULL,screenSurface,&place);
            break;
        case 'Q':
            SDL_BlitSurface(QUEEN,NULL,screenSurface,&place);
            break;
        case 'n':
            SDL_BlitSurface(knight,NULL,screenSurface,&place);
            break;
        case 'N':
            SDL_BlitSurface(KNIGHT,NULL,screenSurface,&place);
            break;
        case 'b':
            SDL_BlitSurface(bishop,NULL,screenSurface,&place);
            break;
        case 'B':
            SDL_BlitSurface(BISHOP,NULL,screenSurface,&place);
            break;
        case 'r':
            SDL_BlitSurface(rook,NULL,screenSurface,&place);
            break;
        case 'R':
            SDL_BlitSurface(ROOK,NULL,screenSurface,&place);
            break;
        default:
            break;
    }
}
//to draw a single digit (for displaying the turn):
void draw_digit(int x,int c,SDL_Surface*screenSurface){
    SDL_Rect place;
    place.x=697+c*23;
    place.y=559;
    if(x==0){
        SDL_BlitSurface(digit_0,NULL,screenSurface,&place);
    }
    else if(x==1){
        SDL_BlitSurface(digit_1,NULL,screenSurface,&place);

    }
    else if(x==2){
        SDL_BlitSurface(digit_2,NULL,screenSurface,&place);

    }
    else if(x==3){
        SDL_BlitSurface(digit_3,NULL,screenSurface,&place);

    }
    else if(x==4){
        SDL_BlitSurface(digit_4,NULL,screenSurface,&place);

    }
    else if(x==5){
        SDL_BlitSurface(digit_5,NULL,screenSurface,&place);

    }
    else if(x==6){
        SDL_BlitSurface(digit_6,NULL,screenSurface,&place);

    }
    else if(x==7){
        SDL_BlitSurface(digit_7,NULL,screenSurface,&place);

    }
    else if(x==8){
        SDL_BlitSurface(digit_8,NULL,screenSurface,&place);

    }
    else if(x==9){
        SDL_BlitSurface(digit_9,NULL,screenSurface,&place);

    }
}
//using the above function:
void draw_turn(game*s,SDL_Surface*screen){
    int a[5]={0,0,0,0,0};
    int i=0;
    int x=s->turn;
    while(x){
        a[i]=x%10;
        i++;
        x=x/10;
    }
    int j;
    int c=0;
    for(j=i-1;j>-1;j--){
        draw_digit(a[j],c,screen);
        c++;
    }

}
//the main draw function
void draw(SDL_Surface* screenSurface,game*x){
    screenSurface = SDL_GetWindowSurface(window);
    SDL_BlitSurface( back_ground, NULL, screenSurface, NULL );
    SDL_BlitSurface( board, NULL, screenSurface, NULL );
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(x->board[i][j]<64){continue;}
            draw_board(x,i,j,screenSurface);
        }
    }
    for(int i=0;i<x->cap_count;i++){
        draw_captured(x,i,i%4,screenSurface);
    }
    draw_turn(x,screenSurface);
    SDL_UpdateWindowSurface( window );
    SDL_FreeSurface(screenSurface);
}
//initialize the sdl_window
void init_window(SDL_Window*x){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_LoadWAV("bmp/open.wav",&wavspec,&wavbuffer,&wavlength);
    device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
    SDL_QueueAudio(device_id,wavbuffer,wavlength);
    SDL_PauseAudioDevice(device_id,0);
    SDL_Delay(4500);
    SDL_FreeWAV(wavbuffer);
    //Initialize SDL
    if(SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else{
        window=SDL_CreateWindow("Chess",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                win_width, win_height,
                                SDL_WINDOW_BORDERLESS|SDL_WINDOW_OPENGL);
        if( window == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {   x=window;
            SDL_Surface*icon=NULL;
            icon=SDL_LoadBMP("bmp/icon2.bmp");
            SDL_SetWindowIcon(window,icon);
            SDL_FreeSurface(icon);
            //Fill the surface white
            //SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            board= SDL_LoadBMP( "bmp/board2.bmp" );
            back_ground= SDL_LoadBMP( "bmp/bb.bmp" );
            KING = SDL_LoadBMP( "bmp/k2.bmp" );
            king = SDL_LoadBMP( "bmp/k.bmp" );
            QUEEN= SDL_LoadBMP( "bmp/q2.bmp" );
            queen= SDL_LoadBMP( "bmp/q.bmp" );
            BISHOP= SDL_LoadBMP( "bmp/b2.bmp" );
            bishop= SDL_LoadBMP( "bmp/b.bmp" );
            PAWN= SDL_LoadBMP( "bmp/p2.bmp" );
            pawn= SDL_LoadBMP( "bmp/p.bmp" );
            ROOK= SDL_LoadBMP( "bmp/r2.bmp" );
            rook= SDL_LoadBMP( "bmp/r.bmp" );
            KNIGHT= SDL_LoadBMP( "bmp/n2.bmp" );
            knight= SDL_LoadBMP( "bmp/n.bmp" );
            digit_0=SDL_LoadBMP("bmp/0.bmp");
            digit_1=SDL_LoadBMP("bmp/1.bmp");
            digit_2=SDL_LoadBMP("bmp/2.bmp");
            digit_3=SDL_LoadBMP("bmp/3.bmp");
            digit_4=SDL_LoadBMP("bmp/4.bmp");
            digit_5=SDL_LoadBMP("bmp/5.bmp");
            digit_6=SDL_LoadBMP("bmp/6.bmp");
            digit_7=SDL_LoadBMP("bmp/7.bmp");
            digit_8=SDL_LoadBMP("bmp/8.bmp");
            digit_9=SDL_LoadBMP("bmp/9.bmp");
            white_prom = SDL_LoadBMP("bmp/white_prom.bmp");
            black_prom = SDL_LoadBMP("bmp/black_prom.bmp");
        }
    }
}
//destroy, end & free the memory:
void end_window(){
    SDL_LoadWAV("bmp/close.wav",&wavspec,&wavbuffer,&wavlength);
    device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
    SDL_QueueAudio(device_id,wavbuffer,wavlength);
    SDL_PauseAudioDevice(device_id,0);
    SDL_FreeWAV(wavbuffer);
    SDL_Delay(600);
    SDL_CloseAudioDevice(device_id);

    SDL_FreeSurface(board);
    SDL_FreeSurface(KING);
    SDL_FreeSurface(king);
    SDL_FreeSurface(PAWN);
    SDL_FreeSurface(QUEEN);
    SDL_FreeSurface(queen);
    SDL_FreeSurface(KNIGHT);
    SDL_FreeSurface(knight);
    SDL_FreeSurface(BISHOP);
    SDL_FreeSurface(rook);
    SDL_FreeSurface(digit_0);
    SDL_FreeSurface(digit_1);
    SDL_FreeSurface(digit_2);
    SDL_FreeSurface(digit_3);
    SDL_FreeSurface(digit_4);
    SDL_FreeSurface(digit_5);
    SDL_FreeSurface(digit_6);
    SDL_FreeSurface(digit_7);
    SDL_FreeSurface(digit_8);
    SDL_FreeSurface(digit_9);
    SDL_FreeSurface(white_prom);
    SDL_FreeSurface(black_prom);
    SDL_FreeSurface(back_ground);

    SDL_DestroyWindow( window );
    SDL_Quit();
}
