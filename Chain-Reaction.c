#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>  
#define sizeOfBoard 5  //this is the size of the board, you can change it for a bigger board


void beam(int a[sizeOfBoard][sizeOfBoard], int x, int y, int pid);
void printBoard(int a[sizeOfBoard][sizeOfBoard]);
int playerIDarray[sizeOfBoard][sizeOfBoard]; //player 1: 1
int playernumber = 1;  //start with player 1



// HOW TO PLAY CHAIN REACTION:

// When a slot reached the maximum amount of balls it can hold, it will blast in all 4 surrounding directions.
// The color of the blasted balls will conquer the surrounding blast slots.

// The player with no color balls left loses the game.

// MAX BALLS BEFORE IT BLASTS INTO SURROUNDING SLOTS:
// 1. CORNER : 1 BALL
// 2. EDGE : 2 BALLS
// 3. OTHER : 4 BALLS





int isGameOver(int a[sizeOfBoard][sizeOfBoard])
{
    int p1=0,p2=0,x,y;
    for(x=0;x<sizeOfBoard;x++)
        for(y=0;y<sizeOfBoard;y++)
        {
            if(playerIDarray[x][y]==1) p1++;
            else if(playerIDarray[x][y]==2) p2++;
        }
    
    if(p1==0)
    { 
        return 2;   //meaning player 2 has won the game, because no player 1 ids are there
    }
    else if(p2==0) 
    {
        return 1;  //meaning player 1 has won the game, because no player 2 ids are there
    }
    else
    {
        return 0;  //means game not over yet
    }
}

void beamSurroundingSlots(int a[sizeOfBoard][sizeOfBoard], int x, int y, int pid)
{
    a[x][y]=0;
    playerIDarray[x][y]=0;

    if(x+1<sizeOfBoard)
        beam(a,x+1,y,pid);
    if(y+1<sizeOfBoard)
        beam(a,x,y+1,pid);
    if(x!=0)
        beam(a,x-1,y,pid);
    if(y!=0)
        beam(a,x,y-1,pid); 
}

void beam(int a[sizeOfBoard][sizeOfBoard], int x, int y, int pid)
{
    system("cls");
    printBoard(a);
    sleep(1);
    if(x%(sizeOfBoard-1)==0 && y%(sizeOfBoard-1)==0) //for the corners, max 1 then burst
    {
        if(a[x][y]<1)
        {
            a[x][y]++;
            playerIDarray[x][y] = pid;
        }
        else
        {
            beamSurroundingSlots(a,x,y,pid);      
        }
        
    }
    else if(x%(sizeOfBoard-1)==0 || y%(sizeOfBoard-1)==0)  //for the edges, max 2 then burst
    {
        if(a[x][y]<=1)
        {
            a[x][y]++;
            playerIDarray[x][y] = pid;
        }
        else
        {
            beamSurroundingSlots(a,x,y,pid);
        }
    }
    else  //normal case, max sizeOfBoard then burst
    {
        if(a[x][y]<=3)
        {
            a[x][y]++;
            playerIDarray[x][y] = pid;
        }
        else
        {
            beamSurroundingSlots(a,x,y,pid);
        }
    }
}


void printBoard(int a[sizeOfBoard][sizeOfBoard])
{
    int x,y;
    printf("\033[0m");        
    printf("\tX\t");

    //print x axis
    for(x=0;x<sizeOfBoard;x++)
        printf("%d\t",x+1);
    printf("\nY\t\t");
    for(x=0;x<sizeOfBoard;x++)
        printf("--\t");
    printf("\n");

    for(x=0;x<sizeOfBoard;x++)
    {
        //print y axis..
        printf("\033[0m"); 
        printf("\n%d|\t\t",x+1);
        //print matrix
        for(y=0;y<sizeOfBoard;y++)
        {
            if(playerIDarray[x][y]==1) printf("\033[1;34m"); else if(playerIDarray[x][y]==2) printf("\033[1;31m"); else printf("\033[0m");
            printf("%d \t",a[x][y]);
        }
        printf("\n");
    }
    //DISPLAY over........
}


//MAIN******************** function...
void chainReaction(int a[sizeOfBoard][sizeOfBoard])
{
    int temp,gameover;
    int x,y,xbeam,ybeam;
    while(1) 
    {
        gameover=0;
        playernumber++;
        system("cls");

        //print the board
        printBoard(a);

        //after the first two entries, it must start checking if someone has won the game,
        //eg if player 2 has no id left in the playerIDarray, then player 1 has won the game. 
        if(playernumber>3)
        {
            //to check if the game is over
            gameover = isGameOver(a);
            if(gameover == 1)
            {
                printf("\033[1;34m");
                printf("\n*****************************\nPLAYER 1/ BLUE WINS THE GAME\n*********************************");
                return;
            }
            else if(gameover == 2)
            {
                printf("\033[1;31m");
                printf("\n*****************************\nPLAYER 2/ RED WINS THE GAME\n*********************************");
                return;
            }
        }


        //get the value of the target slot
        if(playernumber%2+1==1) printf("\033[1;34m"); else if(playernumber%2+1==2) printf("\033[1;31m"); else printf("\033[0m");
        printf("\nPLAYER %d : enter where you want to hit \n",playernumber%2+1);
        printf("\033[0m");

        do{
            printf("x : ");
            scanf("%d",&xbeam);
            printf("y : ");
            scanf("%d",&ybeam);
            while(xbeam>sizeOfBoard || ybeam>sizeOfBoard || xbeam<1 || ybeam<1)
            {
                printf("\nPLEASE ENTER VALUES BETWEEN 1 & sizeOfBoard ");
                printf("\nenter values \nx : ");
                scanf("%d",&xbeam);
                printf("y : ");
                scanf("%d",&ybeam);
            }
            temp = (playernumber%2 == 0)?2:1;
            if(playerIDarray[ybeam-1][xbeam-1] == temp) 
            {
                printf("\nenter value at empty/0 slot or a slot with your number\n");
            }
        }while(playerIDarray[ybeam-1][xbeam-1] == temp);  //if player has played on other players slot, retake in values
        
        beam(a,ybeam-1,xbeam-1,playernumber%2+1);
    }
}


void main() 
{    
    int a[sizeOfBoard][sizeOfBoard],x,y,xbeam,ybeam;
    system("cls");
        
    for(x=0;x<sizeOfBoard;x++)
        for(y=0;y<sizeOfBoard;y++)
        {
            a[x][y]=0;
            playerIDarray[x][y]=0;
        }
        
    chainReaction(a);
}