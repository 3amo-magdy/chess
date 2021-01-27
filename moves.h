#include "definition.h"
//please read the moves.h in the report first
//note: (0,0) is the most top left square of the board : going down increases y & going right increases x

//white pawn movements:
unsigned long long int move_p(int a,int b,game*s,int moves[8][8],int*can){
    int x= b;
    int y= a;
    unsigned long long int u=0;
    //checking the 2 square pawn jump:
    if((y == 1) && (s->board[y+2][x] == '.'||s->board[y+2][x] == '-')&&(s->board[y+1][x] == '.'||s->board[y+1][x] == '-')){
         moves[3][x] = 7;
        u=u|(one<<(24+x));
        *can = 0;
       }
    //checking the row ahead of the pawn:
    if(y+1 <= 7){
       //if it was empty:
       if(s->board[y+1][x] == '-'||s->board[y+1][x] =='.'){
            moves[y+1][x] = 1;
            u=u|(one<<(8*(y+1)+(x)));
            *can = 0;
            //if it was a promotion:
            if(y+1==7){
                moves[y+1][x] = 11;
            }
        }
        //checking the squares that thae pawn can capture at:
        if(x + 1 <= 7 && s->board[y+1][x+1] < 97 && s->board[y+1][x+1] != '-'&& s->board[y+1][x+1] != '.'){
            moves[y+1][x+1] = 3;
            u=u|(one<<(8*(y+1)+(x+1)));
            *can = 0;
            if(y+1==7){
                moves[y+1][x+1] = 12;
            }
        }
        if(x - 1 >= 0 && s->board[y+1][x-1] < 97 && s->board[y+1][x-1] != '-'&& s->board[y+1][x-1] != '.'){
            moves[y+1][x-1] = 3;
            u=u|(one<<(8*(y+1)+(x-1)));
            *can = 0;
            if(y+1==7){
                moves[y+1][x-1] = 12;
            }
        }
        //checking if there is a possible enpassant:
        if(s->turn >0){
            if(saved[(s->turn)-1].enpas.on){
                if((y==saved[(s->turn)-1].enpas.y)&&(x-saved[(s->turn)-1].enpas.x==1||x-saved[(s->turn)-1].enpas.x==-1)&&(s->board[y][(saved[(s->turn)-1].enpas.x)] < 97)){
                    moves[y+1][saved[(s->turn)-1].enpas.x] = 8;
                    u=u|(one<<(8*(y+1)+(saved[(s->turn)-1].enpas.x)));
                    u=u|(one<<((8*y)+(saved[(s->turn)-1].enpas.x)));
                    *can = 0;
                }
            }
        }
    }
return u;}
//the black pawn movements: the same as before but with opposite y directions
unsigned long long int move_P(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    if((y == 6) && (s->board[y-2][x] == '.'||s->board[y-2][x] == '-')&&(s->board[y-1][x] == '.'||s->board[y-1][x] == '-')){
        moves[4][x] = 7;
        u=u|(one<<(32+x));
       *can = 0;
       }
    if(y-1 >= 0){
       if(s->board[y-1][x] == '-'||s->board[y-1][x] =='.'){
            moves[y-1][x] = 1;
            u=u|(one<<(8*(y-1)+(x)));
            *can = 0;
            if(y-1==0){
                moves[y-1][x] = 11;
            }
        }
        if(x + 1 <= 7 && s->board[y-1][x+1] > 96 && s->board[y-1][x+1] != '-'&& s->board[y-1][x+1] != '.'){
            moves[y-1][x+1] = 3;
            u=u|(one<<(8*(y-1)+(x+1)));
            *can = 0;
            if(y-1==0){
                moves[y-1][x+1] = 12;
            }
        }
        if(x - 1 >= 0 && s->board[y-1][x-1] > 96 && s->board[y-1][x-1] != '-'&& s->board[y-1][x-1] != '.'){
            moves[y-1][x-1] = 3;
            u=u|(one<<(8*(y-1)+(x-1)));
            *can = 0;
            if(y-1==0){
                moves[y-1][x-1] = 12;
            }
        }
        if(saved[(s->turn)-1].enpas.on){
            if((y==saved[(s->turn)-1].enpas.y)&&(x-saved[(s->turn)-1].enpas.x==1||x-saved[(s->turn)-1].enpas.x==-1)&&(s->board[y][(saved[(s->turn)-1].enpas.x)] > 96)){
            moves[y-1][saved[(s->turn)-1].enpas.x] = 8;
            u=u|(one<<(8*(y-1)+(saved[(s->turn)-1].enpas.x)));
            u=u|(one<<(8*(y)+(saved[(s->turn)-1].enpas.x)));
            *can = 0;
            }
        }
    }
return u;}
//white rook movements:
unsigned long long int move_r(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    //stting a vector either -1 or 1 to check the full row and the full column it's in:
    for(int vec = -1; vec < 2; vec+=2){
        //multiplying a magnitude by the unit vector we can check all the squares in the 4 vectors -x , x, -y , y :
        int mag = 1;
        //checking all the squares in -x , x :
        while(1){
            if(x+(mag*vec) <= 7 && x+(mag*vec) >= 0){
                //if it's not empty:
                if(s->board[y][x+(mag*vec)] != '.'&&s->board[y][x+(mag*vec)] != '-'){
                    //if it has an opponent piece:
                    if(s->board[y][x+(mag*vec)] < 97){
                        moves[y][x+(mag*vec)] = 6;
                        u=u|(one<<(8*(y)+(x+mag*vec)));
                        *can = 0;
                    }
                    break;
                //if empty:
                }else{
                    moves[y][x+(mag*vec)] = 5;
                    u=u|(one<<(8*(y)+(x+mag*vec)));
                    *can = 0;
                }
            }else{
                break;
            }
            mag++;
        }
        mag = 1;
        //doing the same thing but this time with -y , y :
        while(1){
            if(y+(mag*vec) <= 7 && y+(mag*vec) >= 0){
                if(s->board[y+(mag*vec)][x] != '-'&&s->board[y+(mag*vec)][x] != '.'){
                    if(s->board[y+(mag*vec)][x] < 97){
                        moves[y+(mag*vec)][x] = 6;
                        u=u|(one<<(8*(y+mag*vec)+(x)));
                        *can = 0;
                    }
                    break;
                }else{
                    moves[y+(mag*vec)][x] = 5;
                    u=u|(one<<(8*(y+mag*vec)+(x)));
                    *can = 0;
                }
            }else{
                break;
            }
            mag++;
        }
    }
return u;}
//black Rook movements same idea as the white rock
unsigned long long int move_R(int a,int b,game*s,int moves[8][8],int*can){
    int x= b;
    int y= a;
    unsigned long long int u=0;
    for(int vec = -1; vec < 2; vec+=2){
        int mag = 1;
        while(1){
            if(x+(mag*vec) <= 7 && x+(mag*vec) >= 0){
                if(s->board[y][x+(mag*vec)] != '.'&&s->board[y][x+(mag*vec)] != '-'){
                    if(s->board[y][x+(mag*vec)] > 96){
                        moves[y][x+(mag*vec)] = 6;
                        u=u|(one<<(8*(y)+(x+mag*vec)));
                        *can = 0;
                    }
                    break;
                }else{
                    moves[y][x+(mag*vec)] = 5;
                    u=u|(one<<(8*(y)+(x+mag*vec)));
                    *can = 0;
                }
            }else{
                break;
            }
            mag++;
        }
        mag = 1;
        while(1){
            if(y+(mag*vec) <= 7 && y+(mag*vec) >= 0){
                if(s->board[y+(mag*vec)][x] != '.'&&s->board[y+(mag*vec)][x] != '-'){
                    if(s->board[y+(mag*vec)][x] > 96){
                        moves[y+(mag*vec)][x] = 6;
                        u=u|(one<<(8*(y+mag*vec))+(x));
                        *can = 0;
                    }
                    break;
                }else{
                    moves[y+(mag*vec)][x] = 5;
                    u=u|(one<<(8*(y+mag*vec))+(x));
                    *can = 0;
                }
            }else{
                break;
            }
            mag++;
        }
    }
return u;}
//white bishop movements:
unsigned long long int move_b(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    //setting a unit vector in the x direction : -1 & 1
    for(int xDir = -1; xDir < 2; xDir+=2){
        //setting a unit vector in the y direction : -1 & 1
        for(int yDir = -1; yDir < 2; yDir+=2){
            //initializing the increasing magnitude with 1
            int mag = 1;
            //the same idea as the rook but this time x&y both change with one to go diagonally in the 4 diagonal vectors.
            while(1){
                if(x+(mag*xDir) <= 7 && x+(mag*xDir) >= 0 && y+(mag*yDir) <= 7 && y+(mag*yDir) >= 0){
                    //if it's not empty
                    if(s->board[y+(mag*yDir)][x+(mag*xDir)] != '.'&&s->board[y+(mag*yDir)][x+(mag*xDir)] != '-'){
                        //if it has an opponent piece in it
                        if(s->board[y+(mag*yDir)][x+(mag*xDir)] < 97){
                            moves[y+(mag*yDir)][x+(mag*xDir)] = 3;
                            u=u|(one<<((8*(y+mag*yDir))+(x+mag*xDir)));
                            *can = 0;
                        }
                        break;
                    }else{
                        //if it's empty
                        moves[y+(mag*yDir)][x+(mag*xDir)] = 1;
                        u=u|(one<<((8*(y+mag*yDir))+(x+mag*xDir)));
                        *can = 0;
                    }
                }else{
                    break;
                }
                mag++;
            }
        }
    }
return u;
}
//black bishop movements : the same concept as the white bishop
unsigned long long int move_B(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    for(int xDir = -1; xDir < 2; xDir+=2){
        for(int yDir = -1; yDir < 2; yDir+=2){
            int mag = 1;
            while(1){
                if(x+(mag*xDir) <= 7 && x+(mag*xDir) >= 0 && y+(mag*yDir) <= 7 && y+(mag*yDir) >= 0){
                    if(s->board[y+(mag*yDir)][x+(mag*xDir)] != '.'&&s->board[y+(mag*yDir)][x+(mag*xDir)] != '-'){
                        if(s->board[y+(mag*yDir)][x+(mag*xDir)] > 96){
                            moves[y+(mag*yDir)][x+(mag*xDir)] = 3;
                            u=u|(one<<((8*(y+mag*yDir))+(x+mag*xDir)));
                            *can = 0;
                        }
                        break;
                    }else{
                        moves[y+(mag*yDir)][x+(mag*xDir)] = 1;
                        u=u|(one<<((8*(y+mag*yDir))+(x+mag*xDir)));
                        *can = 0;
                    }
                }else{
                    break;
                }
                mag++;
            }
        }
    }
return u;}
//white knight movements
unsigned long long int move_n(int a,int b,game* s,int moves[8][8],int* can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    //the knight has 8 squares at-most to check :
    //by setting i once as 1 and then as -1 we check 4 squares at a time:
    for(int i = -1; i < 2; i+=2){
        //when i = 1 : R-D-D : "one to the right and two down "
        //when i = -1 : L-U-U : "one to the left and two up"
        if(x+i <= 7 && x+i >= 0 && y+(2*i) >= 0 && y+(2*i) <= 7){
            //if empty
            if(s->board[y+(2*i)][x+i] == '.'||s->board[y+(2*i)][x+i] == '-'){
                moves[y+(2*i)][x+i] =1;
                u=u|(one<<(8*(y+2*i)+(x+i)));
                *can = 0;
            }
            //if not and has an opponent's piece in it
            else if(s->board[y+(2*i)][x+i] < 96){
                moves[y+(2*i)][x+i] =3;
                u=u|(one<<(8*(y+2*i)+(x+i)));
                *can = 0;
            }
        }
        //when i = 1 : D-R-R
        //when i = -1 : U-L-L
        if(y+i <= 7 && y+i >= 0 && x+(2*i) >= 0 && x+(2*i) <= 7){
            if(s->board[y+i][x+(2*i)]=='.'||s->board[y+i][x+(2*i)] == '-'){
                *can = 0;
                moves[y+i][x+(2*i)] = 1;
                u=u|(one<<(8*(y+i)+(x+2*i)));
            }
            else if(s->board[y+i][x+(2*i)]<96){
                *can = 0;
                moves[y+i][x+(2*i)] = 3;
                u=u|(one<<(8*(y+i)+(x+2*i)));
            }
        }
        //when i = 1 : L-D-D
        //when i = -1 : R-U-U
        if(x-i <= 7 && x-i >= 0 && y+(2*i) >= 0 && y+(2*i) <= 7){
            if(s->board[y+(2*i)][x-i]=='.'||s->board[y+2*i][x-i] == '-'){
                *can = 0;
                moves[y+(2*i)][x-i] = 1;
                u=u|(one<<(8*(y+2*i)+(x-i)));
            }
            else if(s->board[y+(2*i)][x-i]<96){
                *can = 0;
                moves[y+(2*i)][x-i] = 3;
                u=u|(one<<(8*(y+2*i)+(x-i)));
            }
        }
        //when i = 1 : U R R
        //when i = -1 : D-L-L
        if(y-i <= 7 && y-i >= 0 && x+(2*i) >= 0 && x+(2*i) <= 7){
           if(s->board[y-i][x+(2*i)]=='.'||s->board[y-i][x+(2*i)] == '-'){
                *can = 0;
                moves[y-i][x+(2*i)] = 1;
                u=u|(one<<(8*(y-i)+(x+2*i)));
            }
            else if(s->board[y-i][x+(2*i)]<96){
                *can = 0;
                moves[y-i][x+(2*i)] = 3;
                u=u|(one<<(8*(y-i)+(x+2*i)));
            }
        }
    }
return u;}
//black knight movements: same idea as before
unsigned long long int move_N(int a,int b,game*s,int moves[8][8],int*can){
    int x= b;
    int y= a;
    unsigned long long int u=0;
    for(int i = -1; i < 2; i+=2){
        if(x+i <= 7 && x+i >= 0 && y+(2*i) >= 0 && y+(2*i) <= 7){
            if(s->board[y+(2*i)][x+i] == '.'||s->board[y+(2*i)][x+i] == '-'){
                moves[y+(2*i)][x+i] =1;
                u=u|(one<<(8*(y+2*i)+(x+i)));
                *can = 0;
            }
            else if(s->board[y+(2*i)][x+i] > 96){
                moves[y+(2*i)][x+i] =3;
                u=u|(one<<(8*(y+2*i)+(x+i)));
                *can = 0;
            }
        }
        if(y+i <= 7 && y+i >= 0 && x+(2*i) >= 0 && x+(2*i) <= 7){
            if(s->board[y+i][x+(2*i)]=='.'||s->board[y+i][x+(2*i)] == '-'){
                *can = 0;
                moves[y+i][x+(2*i)] = 1;
                u=u|(one<<(8*(y+i)+(x+2*i)));
            }
            else if(s->board[y+i][x+(2*i)] > 96){
                *can = 0;
                moves[y+i][x+(2*i)] = 3;
                u=u|(one<<(8*(y+i)+(x+2*i)));
            }
        }
        if(x-i <= 7 && x-i >= 0 && y+(2*i) >= 0 && y+(2*i) <= 7){
            if(s->board[y+(2*i)][x-i]=='.'||s->board[y+2*i][x-i] == '-'){
                *can = 0;
                moves[y+(2*i)][x-i] = 1;
                u=u|(one<<(8*(y+2*i)+(x-i)));
            }
            else if(s->board[y+(2*i)][x-i] > 96){
                *can = 0;
                moves[y+(2*i)][x-i] = 3;
                u=u|(one<<(8*(y+2*i)+(x-i)));
            }
        }
        if(y-i <= 7 && y-i >= 0 && x+(2*i) >= 0 && x+(2*i) <= 7){
           if(s->board[y-i][x+(2*i)]=='.'||s->board[y-i][x+(2*i)] == '-'){
                *can = 0;
                moves[y-i][x+(2*i)] = 1;
                u=u|(one<<(8*(y-i)+(x+2*i)));
            }
            else if(s->board[y-i][x+(2*i)] > 96){
                *can = 0;
                moves[y-i][x+(2*i)] = 3;
                u=u|(one<<(8*(y-i)+(x+2*i)));
            }
        }
    }
return u;}
//white king movements:
unsigned long long int move_k(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    //setting a unit vector but this time with three values -1 & 0 & 1 in two directions enabling checking 8 squares
    //by excluding the king's positions (when both vectors are zero): we check the 7 squares around the king:
    for(int xDir = -1; xDir < 2; xDir++){
        for(int yDir = -1; yDir < 2; yDir++){
            //this last condition is the exclusion:
            if(xDir+x <= 7 && xDir+x >= 0 && y+yDir >= 0 && yDir+y <= 7 && !(xDir == 0 && yDir == 0)){
                //if not empty:
                if(s->board[yDir+y][xDir+x] != '.'&&s->board[yDir+y][xDir+x] != '-'){
                    //if it has an opponent's piece:
                    if(s->board[yDir+y][xDir+x] < 96){
                        moves[yDir+y][xDir+x] = 4;
                        u=u|(one<<(8*(yDir+y)+(xDir+x)));
                        *can = 0;
                    }
                }
                //if empty:
                else{
                    moves[yDir+y][xDir+x] = 2;
                    u=u|(one<<(8*(yDir+y)+(xDir+x)));
                    *can = 0;
                }
            }
        }
    }
    //checking the castling movements if possible:
    //the top left castling:
    if (((s->castle)&1)==1){
        if (s->board[0][1]<65&&s->board[0][2]<65&& !(is_it_checked(s,0,1,0)||is_it_checked(s,0,2,0)||is_it_checked(s,0,3,0))){
            moves[0][1]=9;
        }
    }
    // the top right castling:
    if (((s->castle)&2)==2){
        if (s->board[0][4]<65&&s->board[0][5]<65&&s->board[0][6]<65&& !(is_it_checked(s,0,3,0)||is_it_checked(s,0,4,0)||is_it_checked(s,0,5,0))){
            moves[0][5]=10;
        }
    }
return u;}
//the black king movements:
unsigned long long int move_K(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    for(int xDir = -1; xDir < 2; xDir++){
        for(int yDir = -1; yDir < 2; yDir++){
            if(xDir+x <= 7 && xDir+x >= 0 && y+yDir >= 0 && yDir+y <= 7 && !(xDir == 0 && yDir == 0)){
                if(s->board[yDir+y][xDir+x] != '.'&&s->board[yDir+y][xDir+x] != '-'){
                    if(s->board[yDir+y][xDir+x] > 96){
                        moves[yDir+y][xDir+x] = 4;
                        u=u|(one<<(8*(yDir+y)+(xDir+x)));
                        *can = 0;
                    }
                }
                else{
                    moves[yDir+y][xDir+x] = 2;
                    u=u|(one<<(8*(yDir+y)+(xDir+x)));
                    *can = 0;
                }
            }
        }
    }
    //the bottom left castling
    if (((s->castle)&4)==4){
        if (s->board[7][1]<65&&s->board[7][2]<65&& !(is_it_checked(s,7,3,1)||is_it_checked(s,7,2,1)||is_it_checked(s,7,1,1))){
            moves[7][1]=9;
        }
    }
    //the bottom right castling
    if (((s->castle)&8)==8){
        if (s->board[7][4]<65&&s->board[7][5]<65&&s->board[7][6]<65&& !(is_it_checked(s,7,3,1)||is_it_checked(s,7,4,1)||is_it_checked(s,7,5,1))){
            moves[7][5]=10;
        }
    }
return u;
}

//the next function takes a game, a position, fills an array 'moves' and an integer "can_move"
//the idea is better explained in the report.
unsigned long long int get_possible_moves(int x,int y,game*s,int moves[8][8],int*can_move){
    char piece = s->board[x][y];
    switch (piece){
        case 'p':
            return move_p(x,y,s,moves,can_move);
            break;
        case 'P':
            return move_P(x,y,s,moves,can_move);
            break;
        case 'n':
            return move_n(x,y,s,moves,can_move);
            break;
        case 'N':
            return move_N(x,y,s,moves,can_move);
            break;
        case 'r':
            return move_r(x,y,s,moves,can_move);
            break;
        case 'R':
            return move_R(x,y,s,moves,can_move);
            break;
        case 'b':
            return move_b(x,y,s,moves,can_move);
            break;
        case 'B':
            return move_B(x,y,s,moves,can_move);
            break;
        //for the queens :
        //the queen can move as a rook or as a bishop so ..
        case 'q':
            return (move_b(x,y,s,moves,can_move))|(move_r(x,y,s,moves,can_move));
            break;
        case 'Q':
            return (move_B(x,y,s,moves,can_move))|(move_R(x,y,s,moves,can_move));
            break;
        case 'k':
            return move_k(x,y,s,moves,can_move);
            break;
        case 'K':
            return move_K(x,y,s,moves,can_move);
            break;
        default :
            return 0;
    }
}
//movement types each movement is represented with a unique integer in the 2D moves array:

//basic movement to an empty square (1) ----- except for the kings & the rooks
void move_1(game*s,int a,int b, int x, int y){
    s->board[x][y]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
    if(s->board[x][y]=='p'||s->board[x][y]=='P'){s->draw_50=0;}
}
//move with a capture (3) ----- except for the kings & the rooks
void move_3(game*s,int a,int b, int x, int y){
    s->captured[s->cap_count]=s->board[x][y];
    s->cap_count=s->cap_count+1;
    s->board[x][y]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
    s->draw_50=0;
}
//basic movement to an empty square for the kings
void move_2(game*s,int a,int b, int x, int y,int who){
    s->board[x][y]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
    if(who == 0){
        s->castle^=1;
        s->castle^=2;
    }
    else{
        s->castle^=4;
        s->castle^=8;
    }
}
//move with a capture for kings
void move_4(game*s,int a,int b, int x, int y,int who){
    s->captured[(s->cap_count)]=s->board[x][y];
    s->cap_count++;
    s->draw_50=0;
    s->board[x][y]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
    if(who == 0){
        s->castle^=1;
        s->castle^=2;
    }
    else{
        s->castle^=4;
        s->castle^=8;
    }
}
//basic movement to an empty square for the rooks
void move_5(game*s,int a,int b, int x, int y,int who){
    s->board[x][y]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
    if(who == 0){
        if(b==0){
            s->castle^=1;
        }
        if(b==7){
            s->castle^=2;
        }
    }
    else{
        if(b==0){
            s->castle^=4;
        }
        if(b==7){
            s->castle^=8;
        }
    }
}
//move with a capture for rooks
void move_6(game*s,int a,int b, int x, int y,int who){
    s->captured[(s->cap_count)]=s->board[x][y];
    s->cap_count++;
    s->draw_50=0;
    s->board[x][y]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
    if(who == 0){
        if(b==0){
            s->castle^=1;
        }
        if(b==7){
            s->castle^=2;
        }
    }
    else{
        if(b==0){
            s->castle^=4;
        }
        if(b==7){
            s->castle^=8;
        }
    }
}
//the 2-squares pawn jump
void move_7(game*s,int a,int b, int m, int n){
    s->enpas.on=1;
    s->enpas.y=m;
    s->enpas.x=n;
    s->draw_50=0;
    s->board[m][n]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
}
//the en-passant movement
void move_8(game*s,int a,int b, int x, int y,int who){
    s->draw_50=0;
    if(who==0){
        s->board[x][y] = s->board[a][b];
        s->board[a][b] = colorboard[a][b];
        s->captured[s->cap_count]=s->board[x-1][y];
        s->cap_count+=1;
        s->board[x-1][y]=colorboard[x-1][y];
    }
    else{
        s->board[x][y]=s->board[a][b];
        s->board[a][b]=colorboard[a][b];
        s->captured[(s->cap_count)]=s->board[x+1][y];
        s->cap_count+=1;
        s->board[x+1][y]=colorboard[x+1][y];
    }
}
//castling with the near rook
void move_9(game*s,int a,int b, int x, int y,int who){
    move_2(s,a,b,x,y,who);
    move_1(s,x,y-1,x,y+1);
}
//castling with the far rook
void move_10(game*s,int a,int b, int x, int y,int who){
    move_2(s,a,b,x,y,who);
    move_1(s,x,y+2,x,y-1);
}
//pawn promotion
void move_11(game* s,int a,int b, int x, int y,int who){
    move_1(s,a,b,x,y);
    int taken=0;
    SDL_Event q;
    //taking the player's promotion choice
    while(!taken){
        while(SDL_PollEvent(&q)){
            if(q.type == SDL_MOUSEBUTTONDOWN){
                //Get mouse position
                int i,j;
                if(SDL_GetMouseState(&i,&j)==SDL_BUTTON_LEFT){
                    if(j>265&&j<313&&i>144&&i<404){
                        if(i<56+139){
                            s->board[x][y]=113-(32*who);
                            taken=1;
                        }
                        else if(i>84+139&&i<128+139){
                            s->board[x][y]=110-(32*who);
                            taken=1;
                        }
                        else if(i>155+139&&i<200+139){
                            s->board[x][y]=98-(32*who);
                            taken=1;
                        }
                        else if(i>227+139){
                            s->board[x][y]=114-(32*who);
                            taken=1;
                        }
                    }
                }
            }
        }
    }
}
//pawn promotion with a capture
void move_12(game* s,int a,int b, int x, int y,int who){
    move_3(s,a,b,x,y);
    int taken=0;
    SDL_Event q;
    //taking the player's promotion choice
    while(!taken){
        while(SDL_PollEvent(&q)){
            if(q.type == SDL_MOUSEBUTTONDOWN){
                //Get mouse position
                int i,j;
                if(SDL_GetMouseState(&i,&j)==SDL_BUTTON_LEFT){
                    if(j>265&&j<313&&i>144&&i<404){
                        if(i<56+139){
                            s->board[x][y]=113-(32*who);
                            taken=1;
                        }
                        else if(i>84+139&&i<128+139){
                            s->board[x][y]=110-(32*who);
                            taken=1;
                        }
                        else if(i>155+139&&i<200+139){
                            s->board[x][y]=98-(32*who);
                            taken=1;
                        }
                        else if(i>227+139){
                            s->board[x][y]=114-(32*who);
                            taken=1;
                        }
                    }
                }
            }
        }
    }
}
// to get the address of a game given the index (the turn) from saved[].
game * get_that_game(int turn){
    game *p = &(saved[turn]);
    return p;
}
