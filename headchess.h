#include<stdio.h>
enum Type {EMPTY = 0, PAWN, ROOK, BISHOP, KNIGHT, QUEEN, KING};
enum Color {BLACK = 1, WHITE };
#define N 8
unsigned long long int one = 1;
const int colorboard[8][8]={
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' }};
typedef struct {
    enum Type type;
    enum Color color;
}Piece;
typedef struct {
    int on;
    int x;
    int y;
}enpassant;
int max_turn=-1;
typedef struct{
    int turn;
    char board[N][N];
    enpassant enpas;
    int draw_50;
    char castle;
    int cap_count;
    char captured[30];
}game;
game saved[3000];
const beginning_cap[30]={'e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'};
const char beginning_board[8][8]={// white = -  &   black = .
{ 'r' , 'n' , 'b' , 'k' , 'q' , 'b' , 'n' , 'r' },
{ 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' , 'p' },
{ '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
{ '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
{ '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
{ '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
{ 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' , 'P' },
{ 'R' , 'N' , 'B' , 'K' , 'Q' , 'B' , 'N' , 'R' }
};
void niniinin(){
for(int i=0;i<30;i++){
    saved[0].captured[i]='q';
}
}
void printBoard(game *s){
    printf("         A      B      C      D      E      F      G      H         \n" );

    for(int i=0;i<8;i++){
              if(i % 2 != 0)
                printf("             \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
            else
                printf("      \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \n");
        printf("%d     " ,i+1);
        for(int j=0;j<8;j++){
           for(j = 0; j < 8; j++)
                if((i + j) % 2 != 0){
                        if(s->board[i][j]=='.'){
                            printf("       ");
                        }
else{
                    printf("   %c   ",s->board[i][j]);}}
                else{
                        if(s->board[i][j]=='-'){printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb");}
                    else{printf("\xdb\xdb\xdb%c\xdb\xdb\xdb",s->board[i][j]);}}
        }
               if(i % 2 != 0){
                printf("\n             \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");}
            else{
                printf("\n      \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \xdb\xdb\xdb\xdb\xdb\xdb\xdb       \n");}

    }
    printf("         A      B      C      D      E      F      G      H         \n" );
}
void saveBoard(char c[8][8]){
    FILE *s;
    s=fopen("saveBoard.txt","a");
for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        fputc(c[i][j], s);
    }
}
fclose(s);
}
void saveEnpass(enpassant a){
FILE *s;
s=fopen("saveEn.txt","a");
fprintf(s," %d %d %d",a.on,a.x,a.y);
fclose(s);
}
void saveTurn(int turn){
FILE *s;
s=fopen("savedigt.txt","a");
fprintf(s,"%d ",turn);
fclose(s);
}
void savecapCount(int turn){
FILE *s;
s=fopen("savecap.txt","a");
fprintf(s,"%d ",turn);
fclose(s);
}
void save50move(int turn){
FILE *s;
s = fopen("save50move.txt","a");
fprintf(s,"%d ",turn);
fclose(s);
}
void saveCa(char c){
FILE *s;
s = fopen("saveCa.txt","a");
fputc(c, s);
fclose(s);
}
void saveCaput(char c[]){
FILE *s;
s = fopen("saveCaput.txt","a");
int j=0;
while(j<30){
printf("%c",c[j]);
fputc(c[j], s);
j++;
}
fclose(s);
}
void save(){
FILE *s;
s=fopen("savedigt.txt","w");
fprintf(s," %d ",max_turn);
fclose(s);
s=fopen("saveBoard.txt","w");
fclose(s);
s=fopen("saveEn.txt","w");
fclose(s);
s = fopen("saveCa.txt","w");
fclose(s);
s = fopen("savecap.txt","w");
fclose(s);
s = fopen("save50move.txt","w");
fclose(s);
s = fopen("saveCaput.txt","w");
fclose(s);
for(int i=0;i<=max_turn;i++){
    saveTurn(saved[i].turn);
}
for(int i=0;i<=max_turn;i++){
    saveBoard(saved[i].board);
}
for(int i=0;i<=max_turn;i++){
    saveEnpass(saved[i].enpas);
}
for(int i=0;i<=max_turn;i++){
    int u=saved[i].draw_50;
    printf("%d",u);
    save50move(u);
}
for(int i=0;i<=max_turn;i++){
    saveCa(saved[i].castle);
}
for(int i=0;i<=max_turn;i++){
    savecapCount(saved[i].cap_count);
}
for(int i=0;i<=max_turn;i++){
    saveCaput(saved[i].captured);
}
}
void changeCharTOnumber(char c,int *p1){
    while(c!='A'&&c!='B'&&c!='C'&&c!='D'&&c!='E'&&c!='F'&&c!='G'&&c!='H'){
        if(c=='\n'){
            scanf("%c",&c);
        }
        else{
            scanf("%c",&c);
        }
    }
    switch (c){
       case 'A':
           *p1=0;
           break;
       case 'B':
           *p1=1;
           break;
       case 'C':
           *p1=2;
           break;
       case 'D':
           *p1=3;
           break;
       case 'E':
           *p1=4;
           break;
       case 'F':
           *p1=5;
           break;
       case 'G':
           *p1=6;
           break;
       case 'H':
           *p1=7;
           break;
       default:
           printf("code break");
    }
}
int scanNumber(){
    int p;
    char o;
    scanf("%c",&o);
    while(o!='1'&&o!='2'&&o!='3'&&o!='4'&&o!='5'&&o!='6'&&o!='7'&&o!='8'){
        if(o=='\n'){
            scanf("%c",&o);
        }
    else{
        scanf("%c",&o);
    }
}
switch (o){
   case '1':
       p=0;
       break;

   case '2':
       p=1;
       break;

   case '3':
       p=2;
       break;

   case '4':
       p=3;
       break;

   case '5':
       p=4;
       break;

   case '6':
       p=5;
       break;

   case '7':
       p=6;
       break;

   case '8':
       p=7;
       break;
   default:
    printf("code break");
}
return p;
}
void get_position1(int*a,int*b,game *s){
    char c;
    do{
    printf("\nPlayer 1 turn:\nenter the position of a piece to control : ");
    scanf("\n%c",&c);
    changeCharTOnumber(c,b);
    *a=scanNumber();
    }
    while(s->board[*a][*b]!='r'&&s->board[*a][*b]!='n'&&s->board[*a][*b]!='b'&&s->board[*a][*b]!='k'&&s->board[*a][*b]!='q'&&s->board[*a][*b]!='p');
}
void get_position2(int*a,int*b,game *s){
    char c;
    do{
    printf("\nPlayer 2 turn:\nenter the position of a piece to control : ");
    scanf("\n%c",&c);
    changeCharTOnumber(c,b);
    *a=scanNumber();
    }
    while(s->board[*a][*b]!='R'&&s->board[*a][*b]!='N'&&s->board[*a][*b]!='B'&&s->board[*a][*b]!='K'&&s->board[*a][*b]!='Q'&&s->board[*a][*b]!='P');
}
void just_get_position(int*a,int*b){
    char c;
    printf("\ntype the destination position : ");
    scanf("%c",&c);
    changeCharTOnumber(c,b);
    *a=scanNumber();
}
unsigned long long int move_p(int a,int b,game*s,int moves[8][8],int*can){
    int x= b;
    int y= a;
    unsigned long long int u=0;
    if((y == 1) && (s->board[y+2][x] == '.'||s->board[y+2][x] == '-')&&(s->board[y+1][x] == '.'||s->board[y+1][x] == '-')){
         moves[3][x] = 7;
        u=u|(one<<(24+x));
        *can = 0;
       }
    if(y+1 <= 7){
       if(s->board[y+1][x] == '-'||s->board[y+1][x] =='.'){
            moves[y+1][x] = 1;
            u=u|(one<<(8*(y+1)+(x)));
            *can = 0;
            if(y+1==7){
                moves[y+1][x] = 11;
            }
        }
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
unsigned long long int move_r(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    for(int vec = -1; vec < 2; vec+=2){
        int mag = 1;
        while(1){
            if(x+(mag*vec) <= 7 && x+(mag*vec) >= 0){
                if(s->board[y][x+(mag*vec)] != '.'&&s->board[y][x+(mag*vec)] != '-'){
                    if(s->board[y][x+(mag*vec)] < 97){
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
unsigned long long int move_b(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    for(int xDir = -1; xDir < 2; xDir+=2){
        for(int yDir = -1; yDir < 2; yDir+=2){
            int mag = 1;
            while(1){
                if(x+(mag*xDir) <= 7 && x+(mag*xDir) >= 0 && y+(mag*yDir) <= 7 && y+(mag*yDir) >= 0){
                    if(s->board[y+(mag*yDir)][x+(mag*xDir)] != '.'&&s->board[y+(mag*yDir)][x+(mag*xDir)] != '-'){
                        if(s->board[y+(mag*yDir)][x+(mag*xDir)] < 97){
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
return u;
}

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
unsigned long long int move_n(int a,int b,game* s,int moves[8][8],int* can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    for(int i = -1; i < 2; i+=2){
        if(x+i <= 7 && x+i >= 0 && y+(2*i) >= 0 && y+(2*i) <= 7){
            if(s->board[y+(2*i)][x+i] == '.'||s->board[y+(2*i)][x+i] == '-'){
                moves[y+(2*i)][x+i] =1;
                u=u|(one<<(8*(y+2*i)+(x+i)));
                *can = 0;
            }
            else if(s->board[y+(2*i)][x+i] < 96){
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
            else if(s->board[y+i][x+(2*i)]<96){
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
            else if(s->board[y+(2*i)][x-i]<96){
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
            else if(s->board[y-i][x+(2*i)]<96){
                *can = 0;
                moves[y-i][x+(2*i)] = 3;
                u=u|(one<<(8*(y-i)+(x+2*i)));
            }
        }
    }
return u;}
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
unsigned long long int move_k(int a,int b,game*s,int moves[8][8],int*can){
    int x=b;
    int y=a;
    unsigned long long int u=0;
    for(int xDir = -1; xDir < 2; xDir++){
        for(int yDir = -1; yDir < 2; yDir++){
            if(xDir+x <= 7 && xDir+x >= 0 && y+yDir >= 0 && yDir+y <= 7 && !(xDir == 0 && yDir == 0)){
                if(s->board[yDir+y][xDir+x] != '.'&&s->board[yDir+y][xDir+x] != '-'){
                    if(s->board[yDir+y][xDir+x] < 96){
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
    if (((s->castle)&1)==1){
        if (s->board[0][1]<65&&s->board[0][2]<65&& !(is_it_checked(s,0,1,0)||is_it_checked(s,0,2,0)||is_it_checked(s,0,3,0))){
            moves[0][1]=9;
        }
    }
    if (((s->castle)&2)==2){
        if (s->board[0][4]<65&&s->board[0][5]<65&&s->board[0][6]<65&& !(is_it_checked(s,0,3,0)||is_it_checked(s,0,4,0)||is_it_checked(s,0,5,0))){
            moves[0][5]=10;
        }
    }
return u;}
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
    if (((s->castle)&4)==4){
        if (s->board[7][1]<65&&s->board[7][2]<65&& !(is_it_checked(s,7,3,1)||is_it_checked(s,7,2,1)||is_it_checked(s,7,1,1))){
            moves[7][1]=9;
        }
    }
    if (((s->castle)&8)==8){
        if (s->board[7][4]<65&&s->board[7][5]<65&&s->board[7][6]<65&& !(is_it_checked(s,7,3,1)||is_it_checked(s,7,4,1)||is_it_checked(s,7,5,1))){
            moves[7][5]=10;
        }
    }
return u;
}
unsigned long long int get_possible_moves(int x,int y,game*s,int moves[8][8],int*can_move){
    char piece = s->board[x][y];
    //int color = blackWhite[*x][*y];//0 if white
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
unsigned long long int attack_zone(game *s,int who){
    unsigned long long int u=0;
    unsigned long long int d;
    // 0 for small
    if(who==0){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(s->board[i][j]>96){
                    int trash[8][8];
                    int trashcan=1;
                    d=get_possible_moves(i,j,s,trash,&trashcan);
                    u=u|d;
                }
            }
        }
    }
    else{
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if((s->board[i][j]>65)&&(s->board[i][j]<90)){
                    int trash[8][8];
                    int trashcan=1;
                    d=get_possible_moves(i,j,s,trash,&trashcan);
                    u=u|d;
                }
            }
        }
    }
    return u;
}
unsigned long long int who_is_attacking(game*s,int a,int b,int who,int*howmany){//put who=0 to know what small pieces are threatening the position:(a,b)
    unsigned long long int u=0;
    int trash[8][8];
    int can=1;
    if(who==0){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(s->board[i][j]>96){
                    unsigned long long int d=get_possible_moves(i,j,s,trash,&can);
                    if(((one<<(a*8+b))&d)!=0){
                        u=u|(one<<(i*8+j));
                        (*howmany)++;
                    }
                }
            }
        }
    }
    else{
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
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
int is_ok_to_move(game*s,int a,int b,int x,int y,int m,int n,int who){//from (a,b) to (x,y): king is in (m,n)
    game new_s={
    0,
    {{'-' , 'n' , 'b' , 'k' , '.' , 'b' , 'n' , 'r' },
    { 'p' , 'p' , 'p' , '-' , 'p' , 'p' , 'p' , 'p' },
    { '-' , '.' , '-' , 'q' , '-' , '.' , '-' , '.' },
    { '.' , '-' , '.' , '-' , '.' , '-' , '.' , '-' },
    { '-' , 'p' , '-' , '.' , '-' , '.' , '-' , '.' },
    { '.' , '-' , 'p' , 'R' , '.' , '-' , '.' , '-' },
    { 'P' , 'P' , 'P' , '.' , '-' , 'P' , 'P' , 'P' },
    { 'R' , 'N' , 'B' , 'K' , 'Q' , 'B' , 'N' , 'R' }},
    0,0,0,
    0,
    0,
    0,{' '}
    };
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            new_s.board[i][j]=s->board[i][j];
        }
    }
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
    else{
    new_s.board[x][y]=new_s.board[a][b];
    new_s.board[a][b]=colorboard[a][b];
    }
    unsigned long long int u=0;
    if(who==0){
        u=attack_zone(&new_s,1);
    }
    else{
        u=attack_zone(&new_s,0);
    }
    if (((one<<(m*8+n))&u)== 0){
        return 1;
    }
    else{
        return 0;
    }
}
int is_it_checked(game*s,int m,int n,int who){
    unsigned long long int u=0;
    if(who==0){
        u=attack_zone(s,1);
    }
    else{
        u=attack_zone(s,0);
    }
    if (((one<<(m*8+n))&u)!=0){
        return 1;
    }
    else{
        return 0;
    }
}
void rook_defence(int i,int j,int y,int x,game* s,int who,int*dead){
    if(x==j){
        if(i>y){
            for(int k=y+1;k<i;k++){
                if((one<<(8*k+x))&attack_zone(s,who)){
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
void how_is_my_king(game*s,int who,int* checked,int*wayout,int*dead){// who = 0 for 'k',who = 1 for'K'
    int x=0;
    int y=0;
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
    unsigned long long int u=attack_zone(s,who-1);
    if (((one<<(y*8+x))&u) == 0){
        *checked=0;
        *dead=0;
    }
    else{
        *checked=1;
    }
    for(int xDir = -1; xDir < 2; xDir++){
        for(int yDir = -1; yDir < 2; yDir++){
            if(xDir+x <= 7 && xDir+x >= 0 && y+yDir >= 0 && yDir+y <= 7 && !(xDir == 0 && yDir == 0)){
                if(s->board[yDir+y][xDir+x] == '.'||s->board[yDir+y][xDir+x] == '-'){
                    if(((one<<((yDir+y)*8+(xDir+x)))&u)==0){
                        *wayout=1;
                        *dead=0;
                        break;
                    }
                }
            }
        }
        if(*wayout==1){
            break;
        }
    }
    if(*wayout==0&&*checked==1){
        *dead=1;
        int count=0;
        unsigned long long int q = who_is_attacking(s,y,x,who-1,&count);
        if(count>1){
            *dead=1;
            return;
        }
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(((one<<(i*8+j))&q)!=0){
                    if(((one<<(i*8+j))&attack_zone(s,who))!=0){
                        int howmany=0;
                        unsigned long long int w=who_is_attacking(s,i,j,who,&howmany);
                        for(int a=0;a<8;a++){
                            for(int b=0;b<8;b++){
                                if(((one<<(a*8+b))&w)!=0){
                                    if(s->board[a][b]=='k'||s->board[a][b]=='K'){
                                        if(is_ok_to_move(s,a,b,i,j,i,j,who)==1){
                                            *dead=0;
                                            return;
                                        }
                                    }
                                    else{
                                        if(is_ok_to_move(s,a,b,i,j,y,x,who)==1){
                                            *dead=0;
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(s->board[i][j]=='N'||s->board[i][j]=='n'){
                        *dead=1;
                        return;
                    }
                    if(s->board[i][j]=='P'||s->board[i][j]=='p'){
                        *dead=1;
                        return;
                    }
                    if(s->board[i][j]=='R'||s->board[i][j]=='r'){
                        rook_defence(i,j,y,x,s,who,dead);
                    }
                    if(s->board[i][j]=='B'||s->board[i][j]=='b'){
                        bishop_defence(i,j,y,x,s,who,dead);
                    }
                    if(s->board[i][j]=='Q'||s->board[i][j]=='q'){
                        rook_defence(i,j,y,x,s,who,dead);
                        if(*dead==0){return;}
                        bishop_defence(i,j,y,x,s,who,dead);
                    }
                }
            }
        }
    }
}
void convert(unsigned long long int n,int b,int a[],int *l,int *finished){
    if(*finished==1){return;}
    if(n==0){*finished=1;return;}
    a[*l]=n%b;
    *l+=1;
    convert(n/b,b,a,l,finished);
}
void print(int a[],int *l,int i,int *finished){
    if(*finished==1){return;}
    if(i==(*l)){*finished=1;return;}
    int e = a[i];
    if(i%8==0&&i!=0){
        printf("\n%d ",e);
    }
    else{
        printf("%d ",e);
    }

    print(a,l,i+1,finished);
}
/*int main()
{
game x ={
    0,
{{'-' , '.' , '-' , 'k' , '-' , 'b' , 'n' , 'r' },
{ 'p' , 'p' , 'p' , 'b' , 'p' , 'p' , 'p' , 'p' },
{ '-' , '.' , '-' , '.' , '-' , '.' , '-' , '.' },
{ '.' , '-' , '.' , 'R' , '.' , '-' , '.' , '-' },
{ '-' , 'p' , '-' , '.' , '-' , '.' , '-' , '.' },
{ '.' , '-' , 'p' , '-' , '.' , '-' , '.' , '-' },
{ 'P' , 'P' , 'P' , '.' , '-' , 'P' , 'P' , 'P' },
{ 'R' , 'N' , 'B' , 'K' , 'Q' , 'B' , 'N' , 'R' }},
0,0,0,
0,
0
};
int a, b;
printBoard(&x);
int move[8][8]={
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}};
get_position2(&a,&b,&x);
int can=1;
unsigned long long int U=get_possible_moves(a,b,&x,move,&can);
printf("\n");
for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        printf("%d ",move[i][j]);
    }
    printf("\n");
}
printf("%llu\n\n\n",U);
int k_checked=0;
int k_wayout=0;
int k_dead=1;
how_is_my_king(&x,0,&k_checked,&k_wayout,&k_dead);

unsigned long long int n=attack_zone(&x,1);
int finished_converting=0, finished_printing=0, l=0, kk[1000];
convert(n,2,kk,&l,&finished_converting);
print(kk,&l,0,&finished_printing);
printf("\n\nchecked?:%d\n",k_checked);
printf("there is way out ?:%d\n",k_wayout);
printf("k is dead ?:%d\n\n\n",k_dead);
int coco=0;
printf("\n\nis ok to move ? %d\n",is_ok_to_move(&x,1,3,2,2,0,3,0));


return 0;

}*/
        /*
        if he made a move == 7 --> a 2-step pawn :
        (*s).enpas.on = 1
        (*s).enpas.x  = x
        (*s).enpas.y  = y

        if he made a move == 8 --> enpassant :
        ...
        */
void move_1(game*s,int a,int b, int x, int y){
    s->board[x][y]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
}
void move_3(game*s,int a,int b, int x, int y){
    s->captured[s->cap_count]=s->board[x][y];
    s->cap_count=s->cap_count+1;
    s->board[x][y]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
}
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
void move_4(game*s,int a,int b, int x, int y,int who){
    s->captured[(s->cap_count)]=s->board[x][y];
    s->cap_count++;
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
void move_6(game*s,int a,int b, int x, int y,int who){
    s->captured[(s->cap_count)]=s->board[x][y];
    s->cap_count++;
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
void move_7(game*s,int a,int b, int m, int n){
    s->enpas.on=1;
    s->enpas.y=m;
    s->enpas.x=n;
    s->board[m][n]=s->board[a][b];
    s->board[a][b]=colorboard[a][b];
}
void move_8(game*s,int a,int b, int x, int y,int who){
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
void move_9(game*s,int a,int b, int x, int y,int who){
    move_2(s,a,b,x,y,who);
    move_1(s,x,y-1,x,y+1);
}
void move_10(game*s,int a,int b, int x, int y,int who){
    move_2(s,a,b,x,y,who);
    move_1(s,x,y+2,x,y-1);
}
void move_11(game* s,int a,int b, int x, int y,int who){
    move_1(s,a,b,x,y);
    char e;
    do{
        printf("choose what to promote to\n1 --> Queen || 2 --> Knight || 3 --> Rook || 4 --> Bishop\n");
        scanf("\n%c",&e);
    }
    while(!(e=='1'||e=='2'||e=='3'||e=='4'));
    if(e=='1'){
        s->board[x][y]=113-(32*who);
    }
    if(e=='2'){
        s->board[x][y]=110-(32*who);
    }
    if(e=='3'){
        s->board[x][y]=114-(32*who);
    }
    if(e=='4'){
        s->board[x][y]=98-(32*who);
    }
}
void move_12(game* s,int a,int b, int x, int y,int who){
    move_3(s,a,b,x,y);
    char e;
    do{
        printf("choose what to promote to\n            1 --> Queen   |   2 --> Knight   |   3 --> Rook   |   4 --> Bishop\n");
        scanf("\n%c",&e);
    }
    while(!(e=='1'||e=='2'||e=='3'||e=='4'));
    if(e=='1'){
        s->board[x][y]=113-(32*who);
    }
    if(e=='2'){
        s->board[x][y]=110-(32*who);
    }
    if(e=='3'){
        s->board[x][y]=114-(32*who);
    }
    if(e=='4'){
        s->board[x][y]=98-(32*who);
    }
}
game * get_that_game(int turn){
    game *p = &(saved[turn]);
    return p;
}
void inherit_games(game *s1,game *s2){
    s2->turn=(s1->turn)+1;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            s2->board[i][j]=s1->board[i][j];
        }
    }
    s2->castle=s1->castle;
    s2->enpas.on=0;
    s2->enpas.x=0;
    s2->enpas.y=0;
    s2->draw_50=(s1->draw_50)+1;
    for(int j=0;j<s1->cap_count;j++){
        s2->captured[j] = s1->captured[j];
    }
    s2->cap_count=s1->cap_count;
}
void prepare_the_game(int turnn,game*x){
    if(turnn==0){
        x->turn=0;
        x->castle=15;
        x->enpas.on=0;
        x->enpas.x=0;
        x->enpas.y=0;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                x->board[i][j]=beginning_board[i][j];
            }
        }
        x->draw_50=0;
        x->cap_count=0;
        for(int j=0;j<30;j++){
            x->captured[j]=beginning_cap[j];
        }
    }else{
        inherit_games(get_that_game(turnn-1),x);
    }
}
void pick(game*x){
    if((x->turn)%2==0){
        play(x,0);
    }
    else{
        play(x,1);
    }
}
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
int can_it_really(game*s,int who,unsigned long long u,int *a,int *b){
    int m,n;
    where_is_my_king(s,who,&m,&n);
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(((one<<(8*i+j))&u)!=0){
                if(is_ok_to_move(s,*a,*b,i,j,m,n,who)){
                    return 0;
                }
            }
        }
    }
    return 1;
}
void take_first_input(game* x,int who,int *a,int *b,int moves[8][8]){
    for (int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            moves[i][j]=0;
        }
    }
    int cannot=1;
    unsigned long long int u=0;
    if(!who){get_position1(a,b,x);}
    else{get_position2(a,b,x);}
    u=get_possible_moves(*a,*b,x,moves,&cannot);
    if(!cannot){
        cannot=can_it_really(x,who,u,a,b);
    }
    while(cannot){
        printf("the piece you chose can't move .. choose again please\n");
        unsigned long long int u=0;
        if(!who){get_position1(a,b,x);}
        else{get_position2(a,b,x);}
        u=get_possible_moves(*a,*b,x,moves,&cannot);
        if(cannot==0){
            cannot=can_it_really(x,who,u,a,b);
        }
    }
    for (int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            printf("%d ",moves[i][j]);
        }
        printf("\n");
    }
    return;
}
void take_second_input(game *s,int who,int a,int b,int *x,int *y,int moves[8][8],int checked){
    int m,n;//from (a,b) to (x,y)
    just_get_position(x,y);
    where_is_my_king(s,who,&m,&n);
    if(moves[*x][*y]>0 && is_ok_to_move(s,a,b,*x,*y,m,n,who)){
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
            move_11(s,a,b,*x,*y,who);
        }
        if(moves[*x][*y]==12){
            move_12(s,a,b,*x,*y,who);
        }
    }
    else{
        printf("invalid move! wisely pick another destination\n");
        take_second_input(s,who,a,b,&x,&y,moves,checked);
    }
}
void save_into_array(game*s,int index){
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
void print_captured(game*s){
if(s->turn==0){return;}
printf("captured pieces : ");
for(int i=0;i<s->cap_count;i++){//---------------------------------------------------------------> look here
    printf("[%c] ",s->captured[i]);
}
printf("\n");
}
int play(int turn){
    game x;
    prepare_the_game(turn,&x);
    printf("%d\n",x.castle);
    printf("%d\n",x.draw_50);
    printBoard(&x);
    print_captured(&x);
    if(turn<=max_turn&&max_turn){
        if(!turn){
            printf("type 'r' to redo ,'s' to save OR anything else to proceed\n");
        }
        else{
            printf("type 'u' to undo , 'r' to redo ,'s' to save OR anything else to proceed\n");
        }
        char q;
        scanf("\n %c",&q);
        if(q=='\n'){
            play(turn);
        }
        printf("----> %c\n",q);
        if (q =='u'&&turn>0){
            return 2;
        }
        else if(q=='r'&&turn<=max_turn){
            return 3;
        }
        else if (q =='s'&&turn>0){
            save();
        }
    }
    else if(turn>0){        char q;

        printf("type 'u' to undo ,'s' to save OR anything else to proceed\n");
        scanf("\n%c",&q);

        while(q=='\n'){scanf("\n %c " ,&q);}
        if (q =='u'&&turn>0){
            return 2;
        }
        else if(q=='r'&&turn<=max_turn){
            return 3;
        }
        else if (q =='s'&&turn>0){
            save();
        }
    }
    int checked=0,wayOut=0,dead=1;
    how_is_my_king(&x,turn%2,&checked,&wayOut,&dead);
    if(dead){
        printf("checkmate !\n");
        if(turn%2==0){
            printf("player 2 WINS !\n");
        }
        else{
            printf("player 1 WINS !\n");
        }
        return 0;
    }
    if(checked==1){
        printf("check !\n");
    }
    char c;
    int a,b,k,l,moves[8][8];
    take_first_input(&x,turn%2,&a,&b,moves);
    take_second_input(&x,turn%2,a,b,&k,&l,moves,checked);
    save_into_array(&x,turn);
    max_turn = turn;
    return 5;
}
void loadBoard(){
    FILE *lo;
lo = fopen("saveBoard.txt","r");
int i=0;
while(i<=max_turn){
for(int k=0;k<8;k++){
for(int j=0;j<8;j++){
        saved[i].board[k][j]=fgetc(lo);
}
}
i++;
}
fclose(lo);
}

void loaddigit(){
FILE *lo;
lo=fopen("savedigt.txt","r");
fscanf(lo,"%d",&max_turn);
for(int i=0; i<=max_turn;i++){
fscanf(lo,"%d",&saved[i].turn);
}
}
void loadenpass(){
    FILE *lo;
    lo=fopen("saveEn.txt","r");
for(int i=0;i<=max_turn;i++){
    fscanf(lo,"%d %d %d",&saved[i].enpas.on,&saved[i].enpas.x,&saved[i].enpas.y);
}
fclose(lo);
}
void load50move(){
   FILE *lo;
    lo=fopen("save50move.txt","r");
for(int i=0;i<=max_turn;i++){
    fscanf(lo,"%d",&saved[i].draw_50);
}
fclose(lo);
}
void loadCa(){
   FILE *lo;
    lo=fopen("saveCa.txt","r");
    int i=0;
while(i<=max_turn){
    saved[i].castle=fgetc(lo);
    i++;
}
fclose(lo);
}
void loadCaptured(){
FILE *lo;
lo = fopen("saveCaput.txt","r");
for(int i=0;i<=max_turn;i++){
for(int y=0;y<30;y++){
    saved[i].captured[y]=fgetc(lo);
}
}
fclose(lo);
}
void loadCap(){
FILE *lo;
lo = fopen("savecap.txt","r");
for(int i=0;i<=max_turn;i++){
fscanf(lo,"%d",&saved[i].cap_count);
}
fclose(lo);
}
void load(){
    printf("hello from load");
    loaddigit();
    loadBoard();
    loadenpass();
    load50move();
    loadCa();
    loadCaptured();
    loadCap();
}
void LOAD(int*turn){
    FILE *fp;
    fp=fopen("saveBoard.txt","r");
    int c = fgetc(fp);
    if (c == EOF) {
        /* file empty, error handling */
        fclose(fp);
        printf("the save file is empty\n");
        main();
    }
    else {
        ungetc(c, fp);
        fclose(fp);
        load();
        *turn =max_turn+1;
    }
}
void ask(int*turn){
    char k;
    scanf("\n%c",&k);
    if(k=='2'){
        LOAD(turn);
    }
    else if(k!='1'){
        printf("u can either press '1' or '2'!");
        ask(turn);
    }
}
void menu(int*turn){
    char t;
    printf("\n[1] to start a new game\n[2] to load a previous game\n[3] for info\n");
    scanf("%c" ,&t);
    if(t=='2'){
        LOAD(turn);
    }
    else if(t=='3'){
        printf("--------- INFO HERE ---------\n\n[1] start a new game\n[2] load a previous game\n");
        ask(turn);
    }
    else if(t!='1'){
        printf("invalid option !\n");
        // ---clear screen------
        menu(turn);
    }
}
