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
const int N=305;
int n;
char s[N];
bitset<N> A[N],B[N],C;
struct matrix
{
    int f[N][N],m;
    matrix() {memset(f,0,sizeof(f));}
    friend matrix operator *(const matrix &a,const matrix &b)
    {
        matrix res; res.m=b.m;
        if(a.f[0][0]<0) return b;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) A[i][j]=a.f[i][j],B[j][i]=b.f[i][j];
        for(int i=0;i<n;i++)
            for(int j=0;j<b.m;j++) 
            {
                C=A[i]&B[j];
                res.f[i][j]=C.count()&1;
            }
        return res;
    }
}a,b;
il matrix qpow(matrix n,int k)
{
    matrix res; res.f[0][0]=-1;
    for(;k;n=n*n,k>>=1) if(k&1) res=res*n;
    return res;
}
int main()
{
    freopen("matrix.in","r",stdin);
    freopen("matrix.out","w",stdout);
    n=read();
    for(int i=0;i<n;i++) 
    {
        scanf("%s",s);
        for(int j=0;j<n;j++) a.f[i][j]=s[j]-'0';
    }
    scanf("%s",s);
    for(int i=0;i<n;i++) b.f[i][0]=s[i]-'0';
    a.m=n,b.m=1;
    int m=read();
    while(m--)
    {
        int x=read();
        matrix res=qpow(a,x)*b;
        for(int i=0;i<n;i++) printf("%d",res.f[i][0]); printf("\n");
    }
    return 0;
}
/*
3
110
011
111
101
2
0
2
*/