#include<bits/stdc++.h>
#define il inline
using namespace std;
il long long read()
{
    long long xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9')
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
int n,k,q;
namespace baoli
{
    const int N=105,M=1e5+15;
    int a[N][M],tot;
    int main()
    {
        tot=k;
        for(int i=1;i<=k;i++) for(int j=1;j<=n;j++) a[i][j]=read();
        while(q--)
        {
            int op=read(),x=read(),y=read();
            if(op==1)
            {
                tot++;
                for(int i=1;i<=n;i++) a[tot][i]=max(a[x][i],a[y][i]);
            }
            else if(op==2)
            {
                tot++;
                for(int i=1;i<=n;i++) a[tot][i]=min(a[x][i],a[y][i]);
            }
            else printf("%d\n",a[x][y]);
        }
        return 0;
    }
}
namespace opt1
{
    const int N=15,M=1e5+15;
    int a[N][M],bl[M],tot;
    int main()
    {
        tot=k;
        for(int i=1;i<=k;i++) for(int j=1;j<=n;j++) a[i][j]=read();
        for(int i=1;i<=k;i++) bl[i]=1<<i;
        while(q--)
        {
            int op=read(),x=read(),y=read();
            if(op==1)
            {
                tot++;
                bl[tot]=bl[x]|bl[y];
            }
            else 
            {
                int res=0;
                for(int i=1;i<=12;i++) if(bl[x]>>i&1) res=max(res,a[i][y]);
                printf("%d\n",res);
            }
        }
        return 0;
    }
}
int main()
{
    freopen("compose.in","r",stdin);
    freopen("compose.out","w",stdout);
    n=read(),k=read(),q=read();
    if(n<=100) return baoli::main();
    else return opt1::main();
}
/*

*/