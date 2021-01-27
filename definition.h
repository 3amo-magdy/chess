#include <string.h>
#include<SDL2/SDL.h>
#include<stdio.h>
//defining MsgBox() according to the system, it's a system function:
//for windows:
#if defined(WIN32) || defined(WINDOWS)
#include <windows.h>
void MsgBox(char *s){
    MessageBox(0, s, "Message", 1);
}
#else
//for mac:
#include <unistd.h>
void MsgBox(char *s){
    char cmd[1024];
    sprintf(cmd, "xmessage -center \"%s\"", s);
    if(fork()==0){
        close(1); close(2);
        system(cmd);
        exit(0);
    }
}
#endif
//setting global SDL_Surfaces (to store the bitmaps of the chess board,pieces and background):
SDL_Window* window = NULL;
SDL_Window* back_ground = NULL;
SDL_Surface* board = NULL;
SDL_Surface* KING = NULL;
SDL_Surface* king = NULL;
SDL_Surface* PAWN = NULL;
SDL_Surface* pawn = NULL;
SDL_Surface* QUEEN = NULL;
SDL_Surface* queen = NULL;
SDL_Surface* KNIGHT = NULL;
SDL_Surface* knight = NULL;
SDL_Surface* BISHOP = NULL;
SDL_Surface* bishop = NULL;
SDL_Surface* ROOK = NULL;
SDL_Surface* rook = NULL;
SDL_Surface* digit_0 = NULL;
SDL_Surface* digit_1 = NULL;
SDL_Surface* digit_2 = NULL;
SDL_Surface* digit_3 = NULL;
SDL_Surface* digit_4 = NULL;
SDL_Surface* digit_5 = NULL;
SDL_Surface* digit_6 = NULL;
SDL_Surface* digit_7 = NULL;
SDL_Surface* digit_8 = NULL;
SDL_Surface* digit_9 = NULL;
SDL_Surface* white_prom = NULL;
SDL_Surface* black_prom = NULL;
//setting audio global variables:
SDL_AudioSpec wavspec;
Uint32 wavlength=0;
Uint8 *wavbuffer=NULL;
SDL_AudioDeviceID device_id;
//window dimensions:
#define win_height  645 //552+132
#define win_width   828 //552+276
//one square's length:
#define slot 69

const int   N = 8;

//this one is bit-shifted every where for bit-wise operations with other 64-bits U.L.Ls :
unsigned long long int one = 1;
//the color board: global constant   '.' for black | '-' for white
const int colorboard[8][8]={
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' }};
//global char arrays for the names of the players
char p1[12],p2[12];
//the en-passant structure
typedef struct {
    int on; //      on/off switch
    int x;  //      the column number of the piece that could be en-passed the following turn.
    int y;  //      it's row number
}enpassant;
//the max turn is crucial to control the possibility of re-doing and also to know how many turns have been played.
int max_turn=-1;
//the main structure : game check the report please
typedef struct{
    int turn;
    char board[8][8];
    enpassant enpas;
    int draw_50;
    char castle;
    int cap_count;
    char captured[30];  //  30 because that's the biggest possible number for the captured pieces.
}game;
//the global array that stores all the played turns.
game saved[3000];   //3000 would be more than enough as the The longest chess game ever played is 269 moves but still it's possible to go way far to more than 2 thousands moves
//initializing the captured array for the first turn (could be filled with any thing).
const char beginning_cap[30]={'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'};
//the board of the first turn: small = white & capital = black
const char beginning_board[8][8]={                          // white square = '-'  &   black square = '.'
{ 'r' , 'n' , 'b' , 'k' , 'q' , 'b' , 'n' , 'r' },
{ 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' },
{ '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
{ '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
{ '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
{ '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
{ 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' },
{ 'R' , 'N' , 'B' , 'K' , 'Q' , 'B' , 'N' , 'R' }
};
