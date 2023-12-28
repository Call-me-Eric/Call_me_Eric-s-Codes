#include<bits/stdc++.h>
#define N 2001001
#define MAX 2001
using namespace std;
typedef long long ll;
typedef double db;
inline void read(ll &ret)
{
    ret=0;char c=getchar();bool pd=false;
    while(!isdigit(c)){pd|=c=='-';c=getchar();}
    while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
    ret=pd?-ret:ret;
    return;
}
char s[3]={'r','g','b'};
signed main()
{
    freopen("rgb.in","w",stdout);
    ll r=82,g=82,b=82;
    ll n=r+g+b+1;
    ll m=n*(n-1)/2;
    cout<<r<<" "<<g<<" "<<b<<" "<<m<<endl;
    mt19937 rnd(time(NULL));
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            printf("%d %d %c\n",i,j,s[rnd()%3]);
    exit(0);
}