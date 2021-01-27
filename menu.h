#include "moves.h"
//to clear the console:
void screen_clear()
{
  system ("CLS");
    printf(" .............                 _   _                ................ \n");
    printf("|             |               -  -  -              | made with love |\n");
    printf("|    Chess    |                -   -               |       in       |\n");
    printf("|             |                 - -                |      Egypt     |\n");
    printf(" .............                   -                  ................ \n");
}
//to display the name of a player:
void name(char p[12]){
    for(int i=0;i<12;i++){
        if(p[i]=='\n'||p[i]=='\0'){
            return;
        }
        printf("%c",p[i]);
    }
}

//ask for a console input (either 1 or 2),keep asking otherwise:
//returns 0 if they chose to load, 1 to start a new game
int ask(int*turn){
    char k;
    fflush(stdin);
    scanf("%c",&k);
    if(k=='2'){
        LOAD(turn);
        return 0;
    }
    else if(k=='1'){
        return 1;
    }
    else {
        MsgBox("u can either press '1' or '2'!");
        return(ask(turn));
    }
}
//the menu
//asks the players to choose either to play a new game, load a previous one or read info.
//if they chose info , they then are asked to choose between starting anew game or loading a previous one
//returns 0 if they chose to load, 1 to start a new game,
int menu(int*turn){
    screen_clear();
    char t;
    printf("\n[1] to start a new game\n[2] to load a previous game\n[3] for info\n");
    fflush(stdin);
    scanf("%c" ,&t);
    // setting turn && max_turn according to what was chosen : either [loaded game] OR [new game]
    if(t=='2'){
        LOAD(turn);
        return 0;
    }
    else if(t=='1'){
        return 1;
    }
    else if(t=='3'){
        printf("\nPlayer 1 plays with the white pieces and Player2 plays with the black ones\n\nHow to play our game?");
        printf("\nClick on the piece you wanna move then Click on the destination\nPress u to undo | s to save | r to redo | y to go back to main menu\n\nour game supports:\n-------------------\n");
        printf("\n1.castling\n2.en-passant\n3.pawn promotion\nDraw:\n------\n1.fiftymoves draw\n2.Stalemate draw\n3.Dead position draw\n our game supplies all check mate conditions\n");
        printf("\nChess is a two-player board game played on a chessboard,\na checkered game board (usually ");
        printf("black and white)\n");
        printf("with 64 squares arranged in an eight-by-eight grid\n Each player begins the");
        printf("game with 16 pieces\n");
        printf("one king, one queen, two rooks, two knights, two bishops, and eight pawns.\n");
        printf("Each of the six piece types moves differently. \nThe most powerful piece is the queenand the least powerful piece is the pawn.\n");
        printf("The objective is to checkmate the opponent’s king by placing it under an inescapable threat of capture.");
        printf("\nfor another information about game and rules visit Wikipedia\n");

        printf("\n[1] to start a new game\n[2] to load a previous game\n");
        return(ask(turn));
    }
    else {
        MsgBox("invalid option !");
        return(menu(turn));
    }
}
//displaying the menu & getting the players names if they chose to start a new game
int main_menu(int*turn){
    //if they chose to start a new game:
    if(menu(turn)){
        printf("\nhi there .. enter the names of the players in order [Max: 12 characters]:");
        printf("\nPlayer 1 : ");
        fflush(stdin);
        fgets(p1,12,stdin);
        //if they pressed enter proceeding without giving their name in,they would be called as"player_One":
        if(p1[0]=='\n'){
            p1[0]='p';p1[1]='l';p1[2]='a';p1[3]='y';p1[4]='e';p1[5]='r';p1[6]='_';p1[7]='O';p1[8]='n';p1[9]='e';
        }
        printf("\nPlayer 2 : ");
        fflush(stdin);
        fgets(p2,12,stdin);
        //if they pressed enter proceeding without giving their name in,they would be called as"player_Two":
        if(p2[0]=='\n'){
            p2[0]='p';p2[1]='l';p2[2]='a';p2[3]='y';p2[4]='e';p2[5]='r';p2[6]='_';p2[7]='T';p2[8]='w';p2[9]='o';
        }
        screen_clear();
        //asking them if they want to switch sides
        printf("\nFor ");name(p1);printf("\n----------------\nThey play with the upper side 'white pieces' of the board\n\n\n\nFor ");name(p2);printf("\n----------------\nThey play with the down side 'black pieces' of the board\n\nPress 's' to switch OR any other button to proceed\n",p1,p2);
        char w;
        fflush(stdin);
        scanf("%c",&w);
        //if they wanted to switch :
        if(w=='s'||w=='S'){
            char temp;
            //switch p1[] & p2[]
            for (int i=0;i<12;i++){
                temp=p2[i];
                p2[i]=p1[i];
                p1[i]=temp;
            }
        }
    }
}
