#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h> //to use sleep() later on

int colorarray[5][5]; //player 1: 1
int playernumber = 1;  //start with player 1



void checkifgameover(int a[5][5])
{
    int p1=0,p2=0,i,j;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++)
        {
            if(colorarray[i][j]==1) p1++;
            else if(colorarray[i][j]==2) p2++;
        }
    
    if(p1==0){ 
        system("cls");
        // print final answer matrix............

        printf("\tX\t");
        //print x axis
        for(i=0;i<5;i++)
            printf("%d\t",i+1);
        printf("\nY\t\t");
        for(i=0;i<5;i++)
            printf("--\t",i+1);
        printf("\n");

        for(i=0;i<5;i++)
        {
            //print y axis..
            printf("\n%d|\t\t",i+1);
            //print matrix
            for(j=0;j<5;j++)
            {
                printf("%d %d\t",a[i][j],colorarray[i][j]);
            }
            printf("\n");
        }
        //..................
        printf("\n*********************************\nPLAYER 2 WINS THE GAME\n**********************************");
        exit(1);
    }
    else if(p2==0) {
        system("cls");
        // print final answer matrix...............

        printf("\tX\t");
        //print x axis
        for(i=0;i<5;i++)
            printf("%d\t",i+1);
        printf("\nY\t\t");
        for(i=0;i<5;i++)
            printf("--\t",i+1);
        printf("\n");

        for(i=0;i<5;i++)
        {
            //print y axis..
            printf("\n%d|\t\t",i+1);
            //print matrix
            for(j=0;j<5;j++)
            {
                printf("%d %d\t",a[i][j],colorarray[i][j]);
            }
            printf("\n");
        }
        //..................
        printf("\n*****************************\nPLAYER 1 WINS THE GAME\n*********************************");
        exit(1);
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
    printf("First digit of each slot : NUMBER \nSecond digit of each slot : PLAYER ID\n\n");
    printf("\tX\t");
    //print x axis
    for(x=0;x<5;x++)
        printf("%d\t",x+1);
    printf("\nY\t\t");
    for(x=0;x<5;x++)
        printf("--\t",x+1);
    printf("\n");

    for(x=0;x<5;x++)
    {
        //print y axis..
        printf("\n%d|\t\t",x+1);
        //print matrix
        for(y=0;y<5;y++)
        {
            printf("%d %d\t",a[x][y],colorarray[x][y]);
        }
        printf("\n");
    }
    //to get the value of the target
    printf("\nPLAYER %d : enter where you want to hit",color);
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
    int temp;
    int x,y,xbeam,ybeam;
    while(1) 
    {
        playernumber++;
        system("cls");
        //to display......
        
        printf("\tX\t");
        //print x axis
        for(x=0;x<5;x++)
            printf("%d\t",x+1);
        printf("\nY\t\t");
        for(x=0;x<5;x++)
            printf("--\t",x+1);
        printf("\n");

        for(x=0;x<5;x++)
        {
            //print y axis..
            printf("\n%d|\t\t",x+1);
            //print matrix
            for(y=0;y<5;y++)
            {
                printf("%d %d\t",a[x][y],colorarray[x][y]);
            }
            printf("\n");
        }

        //get the value of the target
        printf("\nPLAYER %d : enter where you want to hit \n",playernumber%2+1);
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
        checkifgameover(a);
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