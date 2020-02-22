#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h> 

int colorarray[5][5]; //player 1: 1
int playernumber = 1;  //start with player 1

void SetColor(int ForgC){
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
    int p1=0,p2=0,i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
        {
            if(colorarray[i][j]==1) p1++;
            else if(colorarray[i][j]==2) p2++;
        }
    
    if(p1==0){ 
        return 2;   //meaning player 2 has won the game, because no player 1 ids are there
    }
    else if(p2==0) {
        return 1;  //meaning player 1 has won the game, because no player 2 ids are there
    }
    else
    {
        return 0;  //means game not over yet
    }
}


void beam(int a[5][5], int x, int y, int color)
{
    if(x%(5-1)==0 && y%(5-1)==0) //for the corners, max 1 then burst
    {
        if(a[x][y]<1)
        {
            a[x][y]++;
            colorarray[x][y] = color;
        }
        else
        {
            a[x][y]=0;
            colorarray[x][y]=0;
            
            if(x+1<5)
                beam(a,x+1,y,color);
            if(y+1<5)
                beam(a,x,y+1,color);
            if(x!=0)
                beam(a,x-1,y,color);
            if(y!=0)
                beam(a,x,y-1,color);            
        }
        
    }
    else if(x%(5-1)==0 || y%(5-1)==0)  //for the edges, max 2 then burst
    {
        if(a[x][y]<=1)
        {
            a[x][y]++;
            colorarray[x][y] = color;
        }
        else{
            a[x][y]=0;
            colorarray[x][y] = 0;
            
            if(x+1<5)
                beam(a,x+1,y,color);
            if(y+1<5)
                beam(a,x,y+1,color);
            if(x!=0)
                beam(a,x-1,y,color);
            if(y!=0)
                beam(a,x,y-1,color);
        }
    }
    else  //normal case, max 5 then burst
    {
        if(a[x][y]<=3)
        {
            a[x][y]++;
            colorarray[x][y] = color;
        }
        else{
            a[x][y]=0;
            colorarray[x][y] = 0;
            
            beam(a,x+1,y,color);
            beam(a,x,y+1,color);
            beam(a,x-1,y,color);
            beam(a,x,y-1,color);
        }
    }
    
}



//INITIALIZATION.......*********
void startvalues(int a[5][5], int color)
{
    int x,y,xbeam,ybeam;
    system("cls");
    //to display......
    
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
            if(colorarray[x][y]==1) SetColor(1); else if(colorarray[x][y]==2) SetColor(4); else SetColor(7);
            printf("%d \t",a[x][y]);
        }
        printf("\n");
    }
    //to get the value of the target

    if(color==1) SetColor(1); else if(color==2) SetColor(4); else SetColor(7);
    printf("\nPLAYER %d : enter where you want to hit",color);
    SetColor(7);
    label1: 
    printf("\nx : ");
    scanf("%d",&xbeam);
    printf("y : ");
    scanf("%d",&ybeam);
    while(xbeam>5 || ybeam>5 || xbeam<1 || ybeam<1){
        printf("\nPLEASE ENTER VALUES BETWEEN 1 & 5 ");
        printf("\nenter values \nx : ");
        scanf("%d",&xbeam);
        printf("y : ");
        scanf("%d",&ybeam);
    }
    if(colorarray[ybeam-1][xbeam-1] == 1) {
        printf("\nenter value at empty/0 slot or a slot with your number");
        goto label1;
    }

    beam(a,ybeam-1,xbeam-1,color);
}



//MAIN******************** function...
void chainreaction(int a[5][5])
{
    int temp,gameover;
    int x,y,xbeam,ybeam;
    while(1) 
    {
        gameover=0;
        playernumber++;
        system("cls");
        //to display......

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
                if(colorarray[x][y]==1) SetColor(1); else if(colorarray[x][y]==2) SetColor(4); else SetColor(7);
                printf("%d \t",a[x][y]);
            }
            printf("\n");
        }

        //display over........



        //to check if the game is over
        gameover = isGameOver(a);
        if(gameover == 1){
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



        //get the value of the target
        if(playernumber%2+1==1) SetColor(1); else if(playernumber%2+1==2) SetColor(4); else SetColor(7);
        printf("\nPLAYER %d : enter where you want to hit \n",playernumber%2+1);
        SetColor(7);
        label2:
        printf("x : ");
        scanf("%d",&xbeam);
        printf("y : ");
        scanf("%d",&ybeam);
        while(xbeam>5 || ybeam>5 || xbeam<1 || ybeam<1){
            printf("\nPLEASE ENTER VALUES BETWEEN 1 & 5 ");
            printf("\nenter values \nx : ");
            scanf("%d",&xbeam);
            printf("y : ");
            scanf("%d",&ybeam);
        }
        temp = (playernumber%2 == 0)?2:1;
        if(colorarray[ybeam-1][xbeam-1] == temp) {
            printf("\nenter value at empty/0 slot or a slot with your number\n");
            goto label2;
        }
        
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
            colorarray[x][y]=0;
        }

    startvalues(a,1); //red starts first
    startvalues(a,2);  //blue 2nd
    chainreaction(a);
}