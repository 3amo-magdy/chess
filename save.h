#include "over.h"
//save the boards
void saveBoard(char c[8][8])
{
    //declaring a pointer to a file
    FILE *s;
    //opening the file
    s=fopen("saveBoard.txt","a");
    //looping through all the board individual elements
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            //saving each character in the file
            fputc(c[i][j], s);
        }
    }
    //saving the file
    fclose(s);
}
//save en-passant info
void saveEnpass(enpassant a)
{
    FILE *s;
    s=fopen("saveEn.txt","a");
    fprintf(s," %d %d %d",a.on,a.x,a.y);
    fclose(s);
}
//saving the turn number
void saveTurn(int turn)
{
    FILE *s;
    s=fopen("savedigt.txt","a");
    fprintf(s,"%d ",turn);
    fclose(s);
}
//saving the count of captured of a single turn
void savecapCount(int turn)
{
    FILE *s;
    s=fopen("savecap.txt","a");
    fprintf(s,"%d ",turn);
    fclose(s);
}
// saving 50 moves counter of a single turn
void save50move(int turn)
{
    FILE *s;
    s = fopen("save50move.txt","a");
    fprintf(s,"%d ",turn);
    fclose(s);
}
// saving the castling char of a single turn
void saveCa(char c)
{
    FILE *s;
    s = fopen("saveCa.txt","a");
    fputc(c, s);
    fclose(s);
}
// saving the captured pieces of a single turn
void saveCaput(char c[])
{
    FILE *s;
    s = fopen("saveCaput.txt","a");
    int j=0;
    while(j<30)
    {
        fputc(c[j], s);
        j++;
    }
    fclose(s);
}
//saving the names of the players
void saveNames()
{
    FILE *s;
    s=fopen("saveNames.txt","w");
    for(int i=0; i<12; i++)
    {
        fputc(p1[i],s);
    }
    for(int i=0; i<12; i++)
    {
        fputc(p2[i],s);
    }
    fclose(s);
}
//saving the whole saved[] array:
void save()
{
    //making sure the files exist, if not using "w" would create them :
    FILE *s;
    s=fopen("savedigt.txt","w");
    fprintf(s,"%d ",max_turn);
    fclose(s);
    s=fopen("saveBoard.txt","w");
    fclose(s);
    s=fopen("saveEn.txt","w");
    fclose(s);
    s = fopen("saveCa.txt","w");
    fclose(s);
    s = fopen("save50move.txt","w");
    fclose(s);
    s = fopen("saveCaput.txt","w");
    fclose(s);
    s=fopen("savecap.txt","w");
    fclose(s);
    //looping through saved[] and using the functions from above:
    for(int i=0; i<=max_turn; i++)
    {
        saveTurn(saved[i].turn);
    }
    for(int i=0; i<=max_turn; i++)
    {
        saveBoard(saved[i].board);
    }
    for(int i=0; i<=max_turn; i++)
    {
        saveEnpass(saved[i].enpas);
    }
    for(int i=0; i<=max_turn; i++)
    {
        save50move(saved[i].draw_50);
    }
    for(int i=0; i<=max_turn; i++)
    {
        saveCa(saved[i].castle);
    }
    for(int i=0; i<=max_turn; i++)
    {
        savecapCount(saved[i].cap_count);
    }
    for(int i=0; i<=max_turn; i++)
    {
        saveCaput(saved[i].captured);
    }
    saveNames();
}
//load the board of a single turn:
void loadBoard()
{
    FILE *lo;
    lo = fopen("saveBoard.txt","r");
    int i=0;
    while(i<=max_turn)
    {
        for(int k=0; k<8; k++)
        {
            for(int j=0; j<8; j++)
            {
                saved[i].board[k][j]=fgetc(lo);
            }
        }
        i++;
    }
    fclose(lo);
}
//load the turns into the saved[] array
void loaddigit()
{
    FILE *lo;
    lo=fopen("savedigt.txt","r");
    fscanf(lo,"%d",&max_turn);
    for(int i=0; i<=max_turn; i++)
    {
        fscanf(lo,"%d",&saved[i].turn);
    }
}
//load the enpassant-s information of all the turns
void loadenpass()
{
    FILE *lo;
    lo=fopen("saveEn.txt","r");
    for(int i=0; i<=max_turn; i++)
    {
        fscanf(lo,"%d %d %d",&saved[i].enpas.on,&saved[i].enpas.x,&saved[i].enpas.y);
    }
    fclose(lo);
}
//load the 50-moves counters of all the turns
void load50move()
{
    FILE *lo;
    lo=fopen("save50move.txt","r");
    for(int i=0; i<=max_turn; i++)
    {
        fscanf(lo,"%d",&saved[i].draw_50);
    }
    fclose(lo);
}
//load the castling information of all the turns
void loadCa()
{
    FILE *lo;
    lo=fopen("saveCa.txt","r");
    int i=0;
    while(i<=max_turn)
    {
        saved[i].castle=fgetc(lo);
        i++;
    }
    fclose(lo);
}
//load the captured arrays of all the turns
void loadCaptured()
{
    FILE *lo;
    lo = fopen("saveCaput.txt","r");
    for(int i=0; i<=max_turn; i++)
    {
        for(int y=0; y<30; y++)
        {
            saved[i].captured[y]=fgetc(lo);
        }
    }
    fclose(lo);
}
//load the captured count of every loaded turn
void loadCap()
{
    FILE *lo;
    lo = fopen("savecap.txt","r");
    for(int i=0; i<=max_turn; i++)
    {
        fscanf(lo,"%d",&saved[i].cap_count);
    }
    fclose(lo);
}
//load the names of the players
void loadNames()
{
    FILE *lo;
    lo=fopen("saveNames.txt","r");
    for(int i=0; i<12; i++)
    {
        p1[i]=fgetc(lo);
    }
    for(int i=0; i<12; i++)
    {
        p2[i]=fgetc(lo);
    }
    fclose(lo);
}
//just do all the previous loading functions
void load()
{
    loaddigit();
    loadBoard();
    loadenpass();
    load50move();
    loadCa();
    loadCaptured();
    loadCap();
    loadNames();
}

void LOAD(int*turn)
{
    FILE *fp;
    //choose any file to open to make sure that some thing was saved:
    fp=fopen("saveBoard.txt","r");
    //get the first character of the file:
    int c = fgetc(fp);
    if (c == EOF)         //EOF means 'end of file' charachter
    {
        //if the file's empty:
        fclose(fp);
        MsgBox("the save file is empty\n");
        main_menu(turn);
    }
    else
    {
        ungetc(c, fp);
        fclose(fp);
        load();
        *turn =max_turn+1;      //setting them to play just from the moment they saved
        //greeting them:
        printf("welcome back ");
        name(p1);
        printf(" and ");
        name(p2);
        MsgBox("loaded successfully");
    }
}
