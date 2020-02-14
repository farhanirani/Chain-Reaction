#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void beam(int a[10][10], int x, int y,int n)
{
    if((x==0 && y==0)||(x==0 && y==n-1)||(x==n-1 && y==0)||(x==n-1 && y==n-1)) //for the corners, max 1 then burst
    {
        if(a[x][y]<1)
        {
            a[x][y]++;
        }
        else
        {
            a[x][y]=0;
            
            if(x+1<n)
                beam(a,x+1,y,n);
            if(y+1<n)
                beam(a,x,y+1,n);
            if(x!=0)
                beam(a,x-1,y,n);
            if(y!=0)
                beam(a,x,y-1,n);            
        }
        
    }
    else if((x==0)||(y==0)||(x==n-1)||(y==n-1))  //for the edges, max 2 then burst
    {
        if(a[x][y]<=1)
        {
            a[x][y]++;
        }
        else{
            a[x][y]=0;
            
            if(x+1<n)
                beam(a,x+1,y,n);
            if(y+1<n)
                beam(a,x,y+1,n);
            if(x!=0)
                beam(a,x-1,y,n);
            if(y!=0)
                beam(a,x,y-1,n);
        }
    }
    else  //normal case, max 4 then burst
    {
        if(a[x][y]<=3)
        {
            a[x][y]++;
        }
        else{
            a[x][y]=0;
            
            if(x+1<n)
                beam(a,x+1,y,n);
            if(y+1<n)
                beam(a,x,y+1,n);
            if(x!=0)
                beam(a,x-1,y,n);
            if(y!=0)
                beam(a,x,y-1,n);
        }
    }
    
}

//to get initial 2 values
void startvalues(int a[10][10], int i)
{
    int x,y,xbeam,ybeam;
    system("cls");
    //to display...
    
    printf("\tX\t");
    //print x axis
    for(x=0;x<i;x++)
        printf("%d\t",x+1);
    printf("\nY\t\t");
    for(x=0;x<i;x++)
        printf("--\t",x+1);
    printf("\n");

    for(x=0;x<i;x++)
    {
        //print y axis..
        printf("\n%d|\t\t",x+1);
        //print matrix
        for(y=0;y<i;y++)
        {
            printf("%d\t",a[x][y]);
        }
        printf("\n");
    }
    //to get the value of the target
    printf("\nenter where you want to hit \nx : ");
    scanf("%d",&xbeam);
    printf("\ny : ");
    scanf("%d",&ybeam);
    while(xbeam>i || ybeam>i){
        printf("enter values between %d and %d\n",i,i);
        printf("\nenter where you want to hit \nx : ");
        scanf("%d",&xbeam);
        printf("\ny : ");
        scanf("%d",&ybeam);
    }
    beam(a,ybeam-1,xbeam-1,i);
}

//main function...
void chainreaction(int a[10][10], int i)
{
    int x,y,xbeam,ybeam;
    while(1) 
    {
        system("cls");
        //to display....
        
        printf("\tX\t");
        //print x axis
        for(x=0;x<i;x++)
            printf("%d\t",x+1);
        printf("\nY\t\t");
        for(x=0;x<i;x++)
            printf("--\t",x+1);
        printf("\n");

        for(x=0;x<i;x++)
        {
            //print y axis..
            printf("\n%d|\t\t",x+1);
            //print matrix
            for(y=0;y<i;y++)
            {
                printf("%d\t",a[x][y]);
            }
            printf("\n");
        }
        //get the value of the target
        printf("\nenter where you want to hit \nx : ");
        scanf("%d",&xbeam);
        printf("\ny : ");
        scanf("%d",&ybeam);
        while(xbeam>i && ybeam>i){
            printf("enter values between %d and %d",i,i);
            printf("\nenter where you want to hit \nx : ");
            scanf("%d",&xbeam);
            printf("\ny : ");
            scanf("%d",&ybeam);
        }
        
        beam(a,ybeam-1,xbeam-1,i);
    }
}

void main() 
{    
    int i,a[10][10],x,y,xbeam,ybeam;
    system("cls");
    printf("Enter size of board : ");
    scanf("%d",&i);
    
    for(x=0;x<10;x++)
        for(y=0;y<10;y++)
            a[x][y]=0;

    startvalues(a,i);
    startvalues(a,i);
    chainreaction(a,i);
}