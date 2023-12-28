#include<bits/stdc++.h>
#define For(i,n,r) for(register int i=(n);i<=(r);++i)
#define For_down(i,r,n) for(register int i=(r);i>=(n);--i)
using namespace std;
constexpr int n_MAX=200000+5,mod=998244353;
int norm(const int x){return ((x>=mod)?(x-mod):x);}
void add(int &x,const int y){((x+=y)>=mod)&&(x-=mod);}
constexpr char S[7]="014689";
constexpr int Trans[20][6]=
{
    { 0,  0,  0,  0,  0,  0},
    { 1,  0,  4,  1,  4,  1},
    { 4,  4,  4,  4,  4,  0},
    { 1,  4,  4,  1,  2,  1},
    { 4,  0,  4,  4,  4,  0},
    { 5,  4, 17, 15, 12,  8},
    { 4,  0,  4,  4,  4,  4},
    { 2,  4,  4,  4,  4,  0},
    { 3,  4, 14,  1,  7,  1},
    { 1,  0,  6,  1,  4,  1},
    { 4,  0,  4,  6,  4,  4},
    {16,  0,  6, 16,  4,  1},
    {12,  4,  4,  4,  4,  0},
    { 9,  0,  6,  1,  4,  1},
    { 4,  0,  4, 10,  4,  4},
    {18,  0,  6, 11,  4,  1},
    {13,  0,  6,  1,  4,  1},
    { 4,  0,  4, 17,  4,  4},
    {16,  0,  6,  1,  4,  1}
};
int F[2][20];
int calc(const char R[],const bool equal)
{
    const int n=strlen(R+1);
    memset(F,0,sizeof(F));
    int cur=5;
    For(i,1,n)
    {
        memset(F[i&1],0,sizeof(F[i&1]));
        For(u,1,18) For(j,0,5) add(F[i&1][Trans[u][j]],F[~i&1][u]);
        bool Flag=false;
        For(j,0,5)
        {
            if(S[j]<R[i]) add(F[i&1][Trans[cur][j]],1);
            else if(S[j]==R[i]) cur=Trans[cur][j],Flag=true;
        }
        if(!Flag) cur=0;
    }
    int ans=0;
    For(u,1,18) add(ans,F[n&1][u]);
    if(equal&&cur) add(ans,1);
    return ans;
}
char L[n_MAX],R[n_MAX];
int main()
{
    freopen("prime.in","r",stdin);
    freopen("prime.out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T; cin>>T;
    while(T--)
    {
        cin>>(L+1)>>(R+1);
        const int left=calc(L,0);
        const int right=calc(R,1);
        cout<<norm(right+(mod-left))<<'\n';
    }
    return 0;
}