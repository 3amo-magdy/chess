#include"menu.h"
//the function that takes mouse&keyboard input
int take_input(game*s,int moves[8][8],int *a,int *b,int*m,int*n,int who,SDL_Window*window){
    int taken=0; //a flag to check if the input was taken or not
    unsigned long long int u;
    int target_locked=0;//a flag = 1 when there's a piece that can move has just been clicked
    int can=1;//a flag = 0 if the piece can move
    int i,j;//for the king position
    //the waiting for certain events loop [does not stop until 'taken' = 1
    while(!taken){
        //make an SDL_Event q
        SDL_Event q;
        //if there is an event :
        while(SDL_PollEvent(&q)){
            //if it was a clock on the mouse:
            if(q.type == SDL_MOUSEBUTTONDOWN){
                //Get mouse position (with pixel units) and store it in x,y
                int x,y;
                //if the click was a left click:
                if(SDL_GetMouseState(&x,&y)==SDL_BUTTON_LEFT){
                    //divide y&x by 'slot = 69 = one square length' to know at which square of the board
                    //the mouse clicked on
                    //checking if it has a piece of the player 'who' using ascii manipulations:
                    if(x<558&&y<553){
                    if(s->board[y/slot][x/slot]>(97-(who*32))&&s->board[y/slot][x/slot]<(122-(who*32))){
                        //if so ,, check if the piece can move or not
                        //set all moves to zeros and can to 1:
                        for (int i=0;i<8;i++){
                            for(int j=0;j<8;j++){
                                moves[i][j]=0;
                            }
                        }
                        can=1;
                        //filling moves & can with get_possible_moves:
                        u=get_possible_moves(y/slot,x/slot,s,moves,&can);
                        int o=y/slot;
                        int p=x/slot;
                        //filling the missing puzzle ;) [please check page 6 of the report -> the sixth function]
                        if(!can){
                            if(!can_it_really(s,who,u,&o,&p)){
                                //if it's a sure thing that it has at-least a single valid move:
                                //we fill *a and *b with it's position on the board
                                *a=y/slot;
                                *b=x/slot;
                                target_locked=1;
                                //displaying the player's name on the console & the piece being targeted & its position on the board
                                screen_clear();
                                if(!who){
                                    printf("it's ");name(p1);printf("'s turn ...\n");
                                }
                                else{
                                    printf("it's ");name(p2);printf("'s turn ...\n");
                                }
                                printf("Piece controlled : %c[%c%d]\n",s->board[*a][*b],*b+65,*a+1);
                            }
                            else{
                                //if it has no valid moves : play the 'not valid move song'
                                //it's a wav file in the 'bmp' foldee loaded by SDL_LoadWav
                                SDL_LoadWAV("bmp/no.wav",&wavspec,&wavbuffer,&wavlength);
                                //opening the audiodevice
                                device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
                                //queuing the sound by SDL_QueueAudio
                                SDL_QueueAudio(device_id,wavbuffer,wavlength);
                                //playing the sound with second parameter 0 of SDL_PauseAudioDevice
                                SDL_PauseAudioDevice(device_id,0);
                                //waiting for the sound effect to end before closing the audiodevice
                                SDL_Delay(320);
                                SDL_CloseAudioDevice(device_id);
                                //freeing the pointer
                                SDL_FreeWAV(wavbuffer);
                            }
                        }
                        else{
                                //just as before we play the invalid move sound if it's not a valid move
                                SDL_LoadWAV("bmp/no.wav",&wavspec,&wavbuffer,&wavlength);
                                device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
                                SDL_QueueAudio(device_id,wavbuffer,wavlength);
                                SDL_PauseAudioDevice(device_id,0);
                                SDL_Delay(320);
                                SDL_CloseAudioDevice(device_id);
                                SDL_FreeWAV(wavbuffer);
                        }
                    }
                    else{
                        if(!target_locked){
                            //the same goes here(if the player clicked on a piece he doesn't control or an empty square).
                            SDL_LoadWAV("bmp/no.wav",&wavspec,&wavbuffer,&wavlength);
                            device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
                            SDL_QueueAudio(device_id,wavbuffer,wavlength);
                            SDL_PauseAudioDevice(device_id,0);
                            SDL_Delay(320);
                            SDL_CloseAudioDevice(device_id);
                            SDL_FreeWAV(wavbuffer);
                        }
                    }
                }
                //if there is a target locked:
                if((SDL_GetMouseState(&x,&y)==SDL_BUTTON_LEFT)&&target_locked){
                                            if(x<558&&y<553){

                    if((s->board[y/slot][x/slot]<65)||(s->board[y/slot][x/slot]>(97-((1-who)*32))&&s->board[y/slot][x/slot]<(122-((1-who)*32)))){
                        //store the king's position in i,j
                        where_is_my_king(s,who,&i,&j);
                        //check if the move from (*a,*b) to the clicked-on square is valid
                        //By using the moves 2D array & is_ok_to_move() :
                        if(moves[y/slot][x/slot]>0 && is_ok_to_move(s,*a,*b,y/slot,x/slot,i,j,who)){
                            *m=y/slot;
                            *n=x/slot;
                            return -1;
                            break;
                        }
                        else{
                            //if it's not a valid move : play the invalid move sound
                            SDL_LoadWAV("bmp/no.wav",&wavspec,&wavbuffer,&wavlength);
                            device_id=SDL_OpenAudioDevice(NULL,0,&wavspec,NULL,0);
                            SDL_QueueAudio(device_id,wavbuffer,wavlength);
                            SDL_PauseAudioDevice(device_id,0);
                            SDL_Delay(320);
                            SDL_CloseAudioDevice(device_id);
                            SDL_FreeWAV(wavbuffer);
                        }
                    }
                }
            }}}
            //if a keyboard key was pressed :
            else if(q.type == SDL_KEYDOWN){
                //if the key pressed was 'u':
                if(q.key.keysym.sym==SDLK_u){
                    if (s->turn>0){ //to not go off-limits
                        return 2;
                    }
                }
                //if the key pressed was 'r':
                else if(q.key.keysym.sym==SDLK_r){
                    if(s->turn<=max_turn){
                        return 3;
                    }
                }
                //if the key pressed was 's':
                else if(q.key.keysym.sym==SDLK_s){
                        //save and
                        //stay in the big while loop waiting for another input
                        MsgBox("Saved successfuly");
                        save();
                        break;
                }
                //if the key pressed was 'y':
                else if(q.key.keysym.sym==SDLK_y){
                        return 6;
                }
                //if any other key was pressed :
                else{
                    //keep waiting another event.
                    break;
                }
            }
            //the next events have become useless since the window has been changed to border-less
            /*
            else if(q.type==SDL_QUIT){
                return 6;
            }
            else if(q.type==SDL_WINDOWEVENT){
                if(q.window.event==SDL_WINDOW_MAXIMIZED){
                    SDL_RestoreWindow(window);
                }
                if(q.window.event==SDL_WINDOWEVENT_MINIMIZED){
                    SDL_MinimizeWindow(window);
                }
            }
            */
        }
    }
}
//please read the report
unsigned long long int who_is_attacking(game*s,int a,int b,int who,int*howmany){//put who=0 to know what small pieces are threatening the position:(a,b)
    unsigned long long int u=0;
    int trash[8][8];
    int can=1;
    //for white pieces "small letters in the char board"
    if(who==0){
        //looping through the board squares
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                //if it has a white piece in it:
                if(s->board[i][j]>96){
                    //get all its possible moves:
                    unsigned long long int d=get_possible_moves(i,j,s,trash,&can);
                    //if it can attack the square(a,b):
                    if(((one<<(a*8+b))&d)!=0){
                        //add it to u by bit-wise "or-ing" all of the positions that can attack (a,b)
                        u=u|(one<<(i*8+j));
                        //increase the threat count by one
                        (*howmany)++;
                    }
                }
            }
        }
    }
    //for black pieces "capital letters in the char board"
    else{
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                //if it's a black piece "capital" and the rest is same as before
                if(s->board[i][j]>65&&s->board[i][j]<96){
                    if(((one<<(a*8+b))&get_possible_moves(i,j,s,trash,&can))!=0){
                        u=u|(one<<(i*8+j));
                        (*howmany)++;
                    }
                }
            }
        }
    }
return u;
}
//calculates all the places that 'who' can go to :
unsigned long long int attack_zone(game *s,int who){
    unsigned long long int u=0;
    unsigned long long int d;
    int trash[8][8];
    int trashcan=1;
    // 0 for white (small)
    if(who==0){
        //looping through all the squares
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                //if it's white:
                if(s->board[i][j]>96){
                    //add all the places it can move-to to u by bit-wise or:
                    d=get_possible_moves(i,j,s,trash,&trashcan);
                    u=u|d;
                }
            }
        }
    }
    // else for black (capital)
    else{
        //looping through all the squares
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                //if it's black:
                if((s->board[i][j]>65)&&(s->board[i][j]<90)){
                    //add all the places it can move-to to u by bit-wise or:
                    d=get_possible_moves(i,j,s,trash,&trashcan);
                    u=u|d;
                }
            }
        }
    }
    return u;
}
//calculates all the places that 'who' can go to except for his king
unsigned long long int modified_attack_zone(game *s,int who){
    unsigned long long int u=0;
    unsigned long long int d;
    int trash[8][8];
    int trashcan=1;
    if(who==0){ // 0 for small
        //looping through all the squares
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                //if it's white but not a king :
                if(s->board[i][j]>96&&s->board[i][j]!='k'){
                    d=get_possible_moves(i,j,s,trash,&trashcan);
                    u=u|d;
                }
            }
        }
    }
    else{
        //looping through all the squares
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                //if it's black but not a king :
                if((s->board[i][j]>65)&&(s->board[i][j]<90&&s->board[i][j]!='K')){
                    d=get_possible_moves(i,j,s,trash,&trashcan);
                    u=u|d;
                }
            }
        }
    }
    return u;
}
//to check if a move is safe for the king or not:
int is_ok_to_move(game*s,int a,int b,int x,int y,int o,int p,int who){
    //from (a,b) to (x,y): king is in (o,p)
    int m=o,n=p;
    //make a temporary game where u can virtually perform the move and then see if the king is safe or not:
    game new_s={
    0,
    {{'r' , 'n' , 'b' , 'k' , 'q' , 'b' , 'n' , 'r' },
    { 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' },
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' },
    { 'R' , 'N' , 'B' , 'K' , 'Q' , 'B' , 'N' , 'R' }},
    0,0,0,
    0,
    0,
    0,{' '}
    };
    //the board is all what matters in this temporary game:
    //filling it as the current actual game (the one with address s):
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            new_s.board[i][j]=s->board[i][j];
        }
    }
    //performing the movement on the temporary game (x) according to it's type
    int moves[8][8]={
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}};
    int can=1;
    unsigned long long int z = get_possible_moves(a,b,s,moves,&can);
    //if it's a en-passant movement:
    if(moves[x][y]==8){
        if(who==0){
            new_s.board[x][y]=new_s.board[a][b];
            new_s.board[a][b]=colorboard[a][b];
            new_s.board[x+1][y]=colorboard[a][b];
        }
        else{
            new_s.board[x][y]=new_s.board[a][b];
            new_s.board[a][b]=colorboard[a][b];
            new_s.board[x-1][y]=colorboard[a][b];
        }
    }
     //if the king is the piece that moving:
    //we gotta set m,n to the destination position (the king's new position):
    else if(moves[x][y]==2||moves[x][y]==4){
        m=x;
        n=y;
        new_s.board[x][y]=new_s.board[a][b];
        new_s.board[a][b]=colorboard[a][b];
    }
    //if it was any other type of movement:
    else{
        new_s.board[x][y]=new_s.board[a][b];
        new_s.board[a][b]=colorboard[a][b];
    }
    //after performing the move, now we need to see what's the state of the king:
    //using attack zone():
    unsigned long long int u=0;
    //get the attack zone of the opponent:
    if(who==0){
        u=attack_zone(&new_s,1);
    }
    else{
        u=attack_zone(&new_s,0);
    }
    //if the king is in an threatened place:
    if (((one<<(m*8+n))&u)== 0){
        return 1;
    }
    //if it's a safe one:
    else{
        return 0;
    }
}
//to check if a particular position is currently threatened or not
//most useful for castling permission and that's why modified_attack_zone was made (to prevent an infinit recursion : move_k <-> attack_zone)
int is_it_checked(game*s,int m,int n,int who){
    unsigned long long int u=0;
    //get the attack zone of the opponent:
    if(who==0){
        u=modified_attack_zone(s,1);
    }
    else{
        u=modified_attack_zone(s,0);
    }
    //see if it's in it or not
    if (((one<<(m*8+n))&u)!=0){
        return 1;    //if yes
    }
    else{
        return 0;  //if no
    }
}
//a function to find the king of "who"
void where_is_my_king(game*s,int who,int*m,int*n){
    if(who==0){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(s->board[i][j]=='k'){
                    *m=i;
                    *n=j;
                }
            }
        }
    }
    else{
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(s->board[i][j]=='K'){
                    *m=i;
                    *n=j;
                }
            }
        }
    }
}
//takes a 64 bit representing all the squares the piece at (*a,*b) can move-to
//makes sure that at-least one of these moves is valid
int can_it_really(game*s,int who,unsigned long long u,int *a,int *b){
    int m,n;
    //get the king place
    where_is_my_king(s,who,&m,&n);
    //loop 64 times:
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            //once u find a 1 in u at (i,j)
            if(((one<<(8*i+j))&u)!=0){
                if(is_ok_to_move(s,*a,*b,i,j,m,n,who)){
                    return 0;
                }
            }
        }
    }
    return 1;
}
//if something can block the way between a threatening rook and a checked king :
void rook_defence(int i,int j,int y,int x,game* s,int who,int*dead){
    //uses the co-ordinates to loop through all the places:
    //if they share the same row:
    if(x==j){
        if(i>y){
            for(int k=y+1;k<i;k++){
                if((one<<(8*k+x))&attack_zone(s,who)){
                    int howmany=0;
                    //get all the pieces that can block the way (move in-between):
                    unsigned long long int w=who_is_attacking(s,k,x,who,&howmany);
                    //loop 64 times (representing the 64 bits):
                    for(int a=0;a<8;a++){
                        for(int b=0;b<8;b++){
                            //if there's a 1 representing (a,b) in the 64-bit:
                            if(((one<<(a*8+b))&w)!=0){
                                //and it's not the king:
                                if(s->board[a][b]=='k'||s->board[a][b]=='K'){continue;}
                                //check if it's valid or not:
                                if(is_ok_to_move(s,a,b,k,x,y,x,who)){
                                    //if yes then declare that it's not dead yet and return
                                    *dead=0;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
        else{
            for(int k=y-1;k>i;k--){
                if((one<<(8*k+x))& attack_zone(s,who)){
                    int howmany=0;
                    unsigned long long int w=who_is_attacking(s,k,x,who,&howmany);
                    for(int a=0;a<8;a++){
                        for(int b=0;b<8;b++){
                            if(((one<<(a*8+b))&w)!=0){
                                if(s->board[a][b]=='k'||s->board[a][b]=='K'){continue;}
                                if(is_ok_to_move(s,a,b,k,x,y,x,who)){
                                    *dead=0;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //if they share the same column:
    else if(y==i){
        if(j>x){
            for(int k=x+1;k<j;k++){
                if((one<<(8*y+k))& attack_zone(s,who)){
                    int howmany=0;
                    unsigned long long int w=who_is_attacking(s,y,k,who,&howmany);
                    for(int a=0;a<8;a++){
                        for(int b=0;b<8;b++){
                            if(((one<<(a*8+b))&w)!=0){
                                if(s->board[a][b]=='k'||s->board[a][b]=='K'){continue;}
                                if(is_ok_to_move(s,a,b,y,k,y,x,who)){
                                    *dead=0;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
        else{
            for(int k=j+1;k<x;k++){
                if((one<<(8*k+x))& attack_zone(s,who)){
                    int howmany=0;
                    unsigned long long int w=who_is_attacking(s,y,k,who,&howmany);
                    for(int a=0;a<8;a++){
                        for(int b=0;b<8;b++){
                            if(((one<<(a*8+b))&w)!=0){
                                if(s->board[a][b]=='k'||s->board[a][b]=='K'){continue;}
                                if(is_ok_to_move(s,a,b,y,k,y,x,who)){
                                    *dead=0;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
//the same as the previous function but here the threatening piece is a bishop:
void bishop_defence(int i,int j,int y,int x,game* s,int who,int*dead){
    if(i>y&&j>x){
        for(int a=y+1;a<i;a++){
            for(int b=x+1;b<j;b++){
                if(a-y==b-x){
                    if((one<<(8*b+a))& attack_zone(s,who)){
                        int howmany=0;
                        unsigned long long int w=who_is_attacking(s,a,b,who,&howmany);
                        for(int r=0;r<8;r++){
                            for(int t=0;t<8;t++){
                                if(((one<<(r*8+t))&w)!=0){
                                    if(s->board[a][b]=='k'||s->board[a][b]=='K'){continue;}
                                    if(is_ok_to_move(s,r,t,a,b,y,x,who)){
                                        *dead=0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(i<y&&j>x){
        for(int a=y-1;a>i;a--){
            for(int b=x+1;b<j;b++){
                if(y-a==b-x){
                    if((one<<(8*b+a))& attack_zone(s,who)){
                        int howmany=0;
                        unsigned long long int w=who_is_attacking(s,a,b,who,&howmany);
                        for(int r=0;r<8;r++){
                            for(int t=0;t<8;t++){
                                if(((one<<(r*8+t))&w)!=0){
                                    if(s->board[a][b]=='k'||s->board[a][b]=='K'){continue;}
                                    if(is_ok_to_move(s,r,t,a,b,y,x,who)){
                                        *dead=0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(i<y&&j<x){
        for(int a=y-1;a>i;a--){
            for(int b=x-1;b>j;b--){
                if(a-y==b-x){
                    if((one<<(8*b+a))& attack_zone(s,who)){
                        int howmany=0;
                        unsigned long long int w=who_is_attacking(s,a,b,who,&howmany);
                        for(int r=0;r<8;r++){
                            for(int t=0;t<8;t++){
                                if(((one<<(r*8+t))&w)!=0){
                                    if(s->board[a][b]=='k'||s->board[a][b]=='K'){continue;}
                                    if(is_ok_to_move(s,r,t,a,b,y,x,who)){
                                        *dead=0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(i>y&&j<x){
        for(int a=y+1;a<i;a++){
            for(int b=x-1;b>j;b--){
                if(y-a==b-x){
                    if((one<<(8*b+a))& attack_zone(s,who)){
                        int howmany=0;
                        unsigned long long int w=who_is_attacking(s,a,b,who,&howmany);
                        for(int r=0;r<8;r++){
                            for(int t=0;t<8;t++){
                                if(((one<<(r*8+t))&w)!=0){
                                    if(s->board[a][b]=='k'||s->board[a][b]=='K'){continue;}
                                    if(is_ok_to_move(s,r,t,a,b,y,x,who)){
                                        *dead=0;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
//the following function helps to prepare the new turns based on the previous one:
//s1 is the address of the previous game(turn)
//s2 is the address of the generated game(the following turn)
void inherit_games(game *s1,game *s2){
    s2->turn=(s1->turn)+1;
    //inherit the same board (note: there hasn't been any moves performed on s2 yet):
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            s2->board[i][j]=s1->board[i][j];
        }
    }
    //the same castle also
    s2->castle=s1->castle;
    //reset the en-passant switch
    s2->enpas.on=0;
    s2->enpas.x=0;
    s2->enpas.y=0;
    //increase the 50 moves draw counter
    s2->draw_50=(s1->draw_50)+1;
    //take the same captured array and count:
    for(int j=0;j<s1->cap_count;j++){
        s2->captured[j] = s1->captured[j];
    }
    s2->cap_count=s1->cap_count;
}
//decides to either inherit the turn from the previous one (the previous function) or making the very first turn:
void prepare_the_game(int turnn,game*x){
    //making the turn #0 :
    if(turnn==0){
        x->turn=0;
        // the castle starts with 15 : 0000 1111 (please read the report)
        x->castle=15;
        x->enpas.on=0;
        x->enpas.x=0;
        x->enpas.y=0;
        //setting the beginning board:
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                x->board[i][j]=beginning_board[i][j];
            }
        }
        //setting the counters to 0:
        x->draw_50=0;
        x->cap_count=0;
        //and captured pieces array to the beginning one {'e','e','e','e',...}
        for(int j=0;j<30;j++){
            x->captured[j]=beginning_cap[j];
        }
    //if it's not the turn #0 :
    }else{
        //get the address of the previous turn and pass it to inherit_games in the first parameter
        //to use it to fill x (the current turn getting prepared):
        inherit_games(get_that_game(turnn-1),x);
    }
}
void draw_prom(int who){
    //make a rectangle to use it's co-ordinates to draw on the screen:
    SDL_Rect M;
    M.x=139;
    M.y=181;
    //make a temporary surface:
    SDL_Surface* temp;
    //fill it with the current window surface:
    temp = SDL_GetWindowSurface(window);
    if(!who){//0 for white
        //blit the 'white_prom' surface on temp at M.x & M.y:
        SDL_BlitSurface(white_prom,NULL,temp,&M);
        printf("hi\n");
    }
    else{//else for black
        //blit the 'black_prom' surface on temp at M.x & M.y:
        SDL_BlitSurface(black_prom,NULL,temp,&M);
    }
    //display temp on the screen
    SDL_UpdateWindowSurface(window);
    //free the memory
    SDL_FreeSurface(temp);
    temp=NULL;
}

//do the moves (using the move_'int' functions:
void perform_move(game *s,int who,int a,int b,int *x,int *y,int moves[8][8]){
    if(moves[*x][*y]==1){
        move_1(s,a,b,*x,*y);
    }
    if(moves[*x][*y]==3){
        move_3(s,a,b,*x,*y);
    }
    if(moves[*x][*y]==2){
        move_2(s,a,b,*x,*y,who);
    }
    if(moves[*x][*y]==4){
        move_4(s,a,b,*x,*y,who);
    }
    if(moves[*x][*y]==5){
        move_5(s,a,b,*x,*y,who);
    }
    if(moves[*x][*y]==6){
        move_6(s,a,b,*x,*y,who);
    }
    if(moves[*x][*y]==7){
        move_7(s,a,b,*x,*y);
    }
    if(moves[*x][*y]==8){
        move_8(s,a,b,*x,*y,who);
    }
    if(moves[*x][*y]==9){
        move_9(s,a,b,*x,*y,who);
    }
    if(moves[*x][*y]==10){
        move_10(s,a,b,*x,*y,who);
    }
    if(moves[*x][*y]==11){
        //display the promotion picture on the screen
        draw_prom(who);
        move_11(s,a,b,*x,*y,who);
    }
    if(moves[*x][*y]==12){
        //display the promotion picture on the screen
        draw_prom(who);
        move_12(s,a,b,*x,*y,who);
    }
}
//after preparing the turn , taking the move command  & performing the move :
//the last thing to do before playing the following turn is to store it in saved[]:
void save_into_array(game*s,int index){
    //saving it a primitive element by another:
    saved[index].turn = index;
    saved[index].castle = s->castle;
    saved[index].enpas.on = s->enpas.on;
    saved[index].enpas.x = s->enpas.x;
    saved[index].enpas.y = s->enpas.y;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            saved[index].board[i][j] = s->board[i][j];
        }
    }
    saved[index].draw_50 = s->draw_50;
    for(int j=0;j<30;j++){
        saved[index].captured[j] = s->captured[j];
    }
    saved[index].cap_count = s->cap_count;
}
