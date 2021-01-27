#include "head.h"
//take game x and who refer to player  we wanna chick his moves
//Returns 1 if the player ‘who’ doesn’t have any valid move and 0 otherwise.
int nolegalmove(game *x,int who){
    int moves[8][8]={0};
    unsigned long long int u;
    if(who==0){
        for(int k=0;k<8;k++){
            for(int j=0;j<8;j++){
                int can=1;
                if(x->board[k][j] > 96){
                    u=get_possible_moves(k,j,x,moves,&can);
                    if(!can){
                        if(!(can_it_really(x,who,u,&k,&j))){
                            return 0;
                        }
                    }
                }
            }
        }
    }
    else{
        for(int k=0;k<8;k++){
            for(int j=0;j<8;j++){
                int can=1;
                if(x->board[k][j] > 64&&x->board[k][j]<96){
                    u=get_possible_moves(k,j,x,moves,&can);
                    if(!can){
                        if(!(can_it_really(x,who,u,&k,&j))){
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}
//Returns 1 if it’s a (50 moves draw) , 0 otherwise.
//take game x as argument
int fiftymove(game *x){
if(x->draw_50==100){
    MsgBox("Draw !");
    printf("draw : there have been no captures or pawn moves in the last fifty moves\n");
    return 1;
}
return 0;
}
//Returns 0 if it’s a dead position draw, 1 otherwise.
//take game x as input check if left piece can end game or not
int noleftpiece(game *s)
{
    int wht=-1;
    int bck=-1;
    int bownw=0;
    int knightw=0;
    int bownb=0;
    int knightb=0;
    if(s->cap_count==30)
    {
        MsgBox("Draw !");
        printf("draw :there's no enough pieces are left to perform a possible checkmate\n");
        return 0;
    }
    else if(s->cap_count>=28)
    {
        for(int k=0; k<8; k++)
        {
            for(int j=0; j<8; j++)
            {
                if(s->board[k][j] > 96)
                {
                    wht++;
                    if(s->board[k][j]=='b')
                    {
                        bownw++;
                    }
                    else if(s->board[k][j]=='n')
                    {
                        knightw++;
                    }
                }
                else if(s->board[k][j] > 64&&s->board[k][j]<96)
                {
                    bck++;
                    if(s->board[k][j]=='B')
                    {
                        bownb++;
                    }
                    else if(s->board[k][j]=='N')
                    {
                        knightb++;
                    }
                }
            }
        }
    }
    else{
        return 1;
    }
    if(wht==bck)
    {
        if(((knightb==1)&&(knightw==1))||((knightb==1)&&(bownw==1))||((bownb==1)&&(knightw==1))||((bownb==1)&&(bownw==1))){
            MsgBox("Draw !");
            printf("draw :there's no enough pieces are left to perform a possible checkmate\n");
            return 0;
        }
    }
    else if((wht==1)&&(bck==0))
    {
        if(knightw||bownw)
        {
            MsgBox("Draw !");
            printf("draw :there's no enough pieces are left to perform a possible checkmate\n");
            return 0;
        }
    }
    else if((bck==1)&&(wht==0))
    {
        if(knightb||bownb)
        {
            MsgBox("Draw !");
            printf("draw :there's no enough pieces are left to perform a possible checkmate\n");
            return 0;
        }
    }
    return 1;
}
//Designed to fill these three integer addressees :
//*checked= 1 if who’s king is checked,  0 otherwise.
//*wayout = 1 if the king has any valid move,  0 otherwise.
//*dead     = 1  if the king is checkmate,  0 other wise.
//it take game s and who refer king we want to check and way out and dead
void is_my_king_checked(game*s,int who,int* checked){// who = 0 for 'k',who = 1 for'K'
    int x=0;
    int y=0;
    //find king place
    if(who==0){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(s->board[i][j]=='k'){
                    y=i;
                    x=j;
                }
            }
        }
    }
    else{
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(s->board[i][j]=='K'){
                    y=i;
                    x=j;
                }
            }
        }
    }
    int w=who-1;
    unsigned long long int u=attack_zone(s,w);
    // check if it checked or not
    if (((one<<(y*8+x))&u) == 0){
        *checked=0;
    }
    else{
        *checked=1;
    }
}
//to be sure if king is dead or not
//take game s and checked as arguments and who refer to king we want check
//return 0 if game end otherwise return 120
int beSureKingIsDead(game *s,int checked,int who){
int d=nolegalmove(s,who);
if(d){
 if(checked){
    //play the checkmate sound
        SDL_LoadWAV("bmp/over.wav",&wavspec,&wavbuffer,&wavlength);
        device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
        SDL_QueueAudio(device_id,wavbuffer,wavlength);
        SDL_PauseAudioDevice(device_id,0);
        SDL_Delay(900);
        SDL_CloseAudioDevice(device_id);
        SDL_FreeWAV(wavbuffer);
        MsgBox("checkmate !");

        if(!(who)){
            printf("checkmate, ");name(p2);printf(" WINS !",p2);
        }
        else{
            printf("checkmate, ");name(p1);printf(" WINS !");
        }
        return 0;
}
    else{
            //draw
            SDL_LoadWAV("bmp/over.wav",&wavspec,&wavbuffer,&wavlength);
            device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
            SDL_QueueAudio(device_id,wavbuffer,wavlength);
            SDL_PauseAudioDevice(device_id,0);
            SDL_Delay(900);
            SDL_CloseAudioDevice(device_id);
            SDL_FreeWAV(wavbuffer);
            printf("Stalemate Draw : No legal moves available\n");
            MsgBox("DRAW !");
            return 0;
     }
}
return 120;
}
