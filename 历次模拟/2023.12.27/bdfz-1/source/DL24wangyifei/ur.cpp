#include<bits/stdc++.h>
#define il inline
using namespace std;
il int read()
{
    int xr=0,F=1; char cr;
    while(cr=getchar(),cr<'0'||cr>'9') if(cr=='-') F=-1;
    while(cr>='0'&&cr<='9')
        xr=(xr<<3)+(xr<<1)+(cr^48),cr=getchar();
    return xr*F;
}
const int N=1e6+5;
const double pi=acos(-1),eps=1e-9;
struct Complex
{
    double x,y;
    friend Complex operator +(const Complex &a,const Complex &b) {return {a.x+b.x,a.y+b.y};}
    friend Complex operator *(Complex a,Complex b) {return {a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x};}
}a[N];
int n,k;
int main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    n=read(),k=read();
    if(k==n) {for(int i=1;i<=n;i++) printf("1");return 0;}
    if(k<=1) {for(int i=1;i<=n;i++) printf("0");return 0;}
    Complex Wn={cos(2*pi/n),sin(2*pi/n)};
    a[0]={1,0};
    for(int i=1;i<n;i++) a[i]=a[i-1]*Wn;
    // for(int i=0;i<n;i++)
    // {
    //     cout<<a[i].x<<" "<<a[i].y<<endl;
    // }
    int mx=0,qwq=0;
    for(int i=0;i<(1<<n);i++)
    {
        int cnt=0;
        for(int j=0;j<n;j++) if(i>>j&1) cnt++;
        if(cnt>k) continue;
        Complex ans={0,0};
        for(int j=0;j<n;j++) if(i>>j&1) ans=ans+a[j];
        if(fabs(ans.x)<eps&&fabs(ans.y)<eps) 
        {
            if(cnt>mx) mx=cnt,qwq=i;
        }
    }
    for(int i=0;i<n;i++) printf("%d",qwq>>i&1); printf("\n");
    return 0;
}