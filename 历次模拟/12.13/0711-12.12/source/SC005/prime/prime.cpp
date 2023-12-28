#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint int
#define endl '\n'
int read(){
    int x=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c))x=x*10+c-48,c=getchar();
    return x*f;
}const int N=1e5+10,p=1e9;

int susu[N],cnt;
bool use[N];

void shai(int n=1e5)
{
    for(rint i=2;i<=n;i++)
    {
        if(!use[i]) susu[++cnt]=i;
        for(rint j=1;j<=cnt&&i*susu[j]<=n;j++)
        {
            use[i*susu[j]]=1;
            if(!(i%susu[j])) break;
        }
    }
}

bool check(int x)
{
    for(rint i=1;i<=cnt;i++)
    if(susu[i]<=x)
    {
        int now=1;
        for(rint j=1;j<=x;j*=10)
            if(susu[i]/now%10==x/j%10) now*=10;
        if(susu[i]/now==0) return 0;
    }
    return 1;
}

int can[N];
void init(int n=1e5)
{
    shai();
    for(rint i=1;i<=n;i++) can[i]=can[i-1]+check(i);
}

signed main()
{
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    
    init();
    int t=read();
    while(t--)
    {
        int l=read(),r=read();
        cout<<can[r]-can[l-1]<<endl;
    }
    
    return 0;
}