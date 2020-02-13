#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void beam(int a[100][100], int x, int y,int n)
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

void main() {
    
    int i,a[100][100],x,y,xbeam,ybeam;
    system("cls");
    printf("Enter size of board : ");
    scanf("%d",&i);
    
    for(x=0;x<i;x++)
        for(y=0;y<i;y++)
            a[x][y]=0;
    
    while(1) {
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
        //....
        printf("\nenter where you want to hit \nx : ");
        scanf("%d",&xbeam);
        printf("\ny : ");
        scanf("%d",&ybeam);
        beam(a,ybeam-1,xbeam-1,i);
    }
}