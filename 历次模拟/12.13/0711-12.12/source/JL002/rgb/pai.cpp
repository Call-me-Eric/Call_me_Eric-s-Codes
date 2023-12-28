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
    ll cnt=0;
    while(true)
    {
        system("./gen");
        if(system("./rgb"))
            break;
        cerr<<(++cnt)<<endl;
    }
    exit(0);
}