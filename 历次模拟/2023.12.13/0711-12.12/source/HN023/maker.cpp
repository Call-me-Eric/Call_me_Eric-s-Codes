#include<bits/stdc++.h>
using namespace std;
char F[3]={'r','g','b'};
int main(){
    freopen("rgb.in","w",stdout);
    srand(time(0));
    int r,g,b,m;
    r=rand()%10+1;
    g=rand()%10+1;
    b=rand()%10+1;
    int n=r+g+b+1;
    m=rand()%(n*(n-1)/2-(n-1))+n-1;
    printf("%d %d %d %d\n",r,g,b,m);
    for(int i=2;i<=n;i++){
        int v=rand()%(i-1)+1;
        char c=F[rand()%3];
        printf("%d %d %c\n",v,i,c);
    }
    for(int i=n;i<=m;i++){
        int u=rand()%(n-1)+2;
        int v=rand()%(u-1)+1;
        char c=F[rand()%3];
        printf("%d %d %c\n",u,v,c);
    }
}