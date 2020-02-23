#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h> 

// HOW TO PLAY:

// When a slot reached the maximum amount of balls it can hold, it will blast in all 4 surrounding directions.
// The color of the blasted balls will conquer the surrounding blast slots.

// The player with no color balls left loses the game.

// MAX BALLS BEFORE IT BLASTS INTO SURROUNDING SLOTS:
// 1. CORNER : 1 BALL
// 2. EDGE : 2 BALLS
// 3. OTHER : 4 BALLS


void beam(int a[5][5], int x, int y, int pid);
int playerIDarray[5][5]; //player 1: 1
int playernumber = 1;  //start with player 1

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
      }
}

int isGameOver(int a[5][5])
{
    int p1=0,p2=0,x,y;
    for(x=0;x<5;x++)
        for(y=0;y<5;y++)
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

void beamSurroundingSlots(int a[5][5], int x, int y, int pid)
{
    a[x][y]=0;
    playerIDarray[x][y]=0;

    if(x+1<5)
        beam(a,x+1,y,pid);
    if(y+1<5)
        beam(a,x,y+1,pid);
    if(x!=0)
        beam(a,x-1,y,pid);
    if(y!=0)
        beam(a,x,y-1,pid); 
}

void beam(int a[5][5], int x, int y, int pid)
{
    if(x%(5-1)==0 && y%(5-1)==0) //for the corners, max 1 then burst
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
    else if(x%(5-1)==0 || y%(5-1)==0)  //for the edges, max 2 then burst
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
    else  //normal case, max 5 then burst
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


void printBoard(int a[5][5])
{
    int x,y;
    SetColor(7);        
    printf("\tX\t");

    //print x axis
    for(x=0;x<5;x++)
        printf("%d\t",x+1);
    printf("\nY\t\t");
    for(x=0;x<5;x++)
        printf("--\t");
    printf("\n");

    for(x=0;x<5;x++)
    {
        //print y axis..
        printf("\n%d|\t\t",x+1);
        //print matrix
        for(y=0;y<5;y++)
        {
            if(playerIDarray[x][y]==1) SetColor(1); else if(playerIDarray[x][y]==2) SetColor(4); else SetColor(7);
            printf("%d \t",a[x][y]);
        }
        printf("\n");
    }
    //DISPLAY over........
}


//MAIN******************** function...
void chainReaction(int a[5][5])
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
                SetColor(1);
                printf("\n*****************************\nPLAYER 1/ BLUE WINS THE GAME\n*********************************");
                return;
            }
            else if(gameover == 2)
            {
                SetColor(4);
                printf("\n*****************************\nPLAYER 2/ RED WINS THE GAME\n*********************************");
                return;
            }
        }


        //get the value of the target slot
        if(playernumber%2+1==1) SetColor(1); else if(playernumber%2+1==2) SetColor(4); else SetColor(7);
        printf("\nPLAYER %d : enter where you want to hit \n",playernumber%2+1);
        SetColor(7);

        do{
            printf("x : ");
            scanf("%d",&xbeam);
            printf("y : ");
            scanf("%d",&ybeam);
            while(xbeam>5 || ybeam>5 || xbeam<1 || ybeam<1)
            {
                printf("\nPLEASE ENTER VALUES BETWEEN 1 & 5 ");
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
    int a[5][5],x,y,xbeam,ybeam;
    system("cls");
        
    for(x=0;x<5;x++)
        for(y=0;y<5;y++)
        {
            a[x][y]=0;
            playerIDarray[x][y]=0;
        }
        
    chainReaction(a);
}