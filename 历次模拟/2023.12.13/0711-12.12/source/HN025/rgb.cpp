#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
mt19937 rg(random_device{}());
int n,m,a[3],b[3],mp[155],p[N],f[N];
int gf(int x){
    return x==f[x]?x:f[x]=gf(f[x]);
}
int U[N],V[N],C[N],vs[N];
int main(){
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    ios::sync_with_stdio(false);
    cin>>a[0]>>a[1]>>a[2]>>m;
    mp['r']=0,mp['g']=1,mp['b']=2;
    n=a[0]+a[1]+a[2]+1;
    int i,j,k,l,r,x,y;
    string s;
    for(i=1;i<=m;++i)
        cin>>U[i]>>V[i]>>s,p[i]=i,C[i]=mp[s[0]];
    int ed=1.8*CLOCKS_PER_SEC;
    while(clock()<ed)
        for(int _i=1;_i<=100;++_i){
            shuffle(p+1,p+m+1,rg);
            b[0]=a[0],b[1]=a[1],b[2]=a[2];
            for(x=1;x<=n;++x)f[x]=x;
            for(i=1;i<=m;++i)vs[i]=0;
            for(i=1;i<=m;++i)
                if(b[C[p[i]]]&&(x=gf(U[p[i]]))!=(y=gf(V[p[i]])))
                    --b[C[p[i]]],vs[p[i]]=1,f[x]=y;
            if(b[0]||b[1]||b[2])continue;
            puts("YES");
            for(i=1;i<=m;++i)putchar(vs[i]+'0');
            putchar('\n');
            return 0;
        }
    puts("NO");
    return 0;
}