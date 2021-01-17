#include "headchess.h"
int main(){
    printf(" .......                                ........\n");
    printf("|             |                              | made with love |\n");
    printf("|    Chess    |                              |       in       |\n");
    printf("|             |                              |      Egypt     |\n");
    printf(" .-.-.-.-.-.-.                                .-.-.-.-.-.-.-.-\n");
    int state;
    // set turn && max_turn according to what was chosen : either [loaded game] OR [new game]
    int turn =0;
    menu(&turn);
    while(1){
        state=play(turn);
        if(state==2){
            turn--;
        }
        else if(state==3){
            turn++;
        }
        else if(!state){
            char t;
            printf("game ended, however you can undo, type:\n['u' to undo]\n['y' to go back]\n[any button else to quit]\n");
            scanf("%c",&t);
            if(t=='u'){
                turn--;
            }
            else if(t=='y'){
                //go back to menu
            }
            else{
                break;
            }
        }
        if(state==5){
            turn++;
        }
    }
}
