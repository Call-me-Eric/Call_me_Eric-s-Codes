#include<bits/stdc++.h>
using namespace std;typedef long long ll;
const int maxn=255,maxm=4e4+10;
int n,m,a,b,c,x[maxm],y[maxm],ans[maxm],mc;vector<int>E[3];
struct BCJ{
    int rt[maxn];
    void init(){for(int i=1;i<=n;i++)rt[i]=i;}
    int fr(int p){if(p==rt[p])return p;return rt[p]=fr(rt[p]);}
    void mg(int x,int y){x=fr(x),y=fr(y);rt[y]=x;}
}B[3];
int main()
{
    freopen("rgb.in","r",stdin);
    freopen("rgb.out","w",stdout);
    scanf("%d%d%d%d",&a,&b,&c,&m);n=a+b+c+1;
    for(int i=1;i<=m;i++)
    {
        char* s=new char[5];char c;scanf("%d%d%s",x+i,y+i,s);c=s[0];int o=(c=='r'?0:(c=='g'?1:2));
        E[o].push_back(i);
    }
    B[0].init(),B[1].init();
    for(auto t:E[0])B[0].mg(x[t],y[t]),B[1].mg(x[t],y[t]),B[2].mg(x[t],y[t]);
    for(auto t:E[1])B[1].mg(x[t],y[t]);
    for(auto t:E[2])if(B[2].fr(x[t])!=B[2].fr(y[t]))B[2].mg(x[t],y[t]),mc++;
    for(auto t:E[2])
    {
        if(B[1].fr(x[t])!=B[1].fr(y[t]))c--,B[0].mg(x[t],y[t]),B[1].mg(x[t],y[t]),ans[t]=1;
    }
    if(c<0){puts("NO");return 0;}
    for(auto t:E[2])
    {
        if(c<=mc)break;
        if(B[1].fr(x[t])==B[1].fr(y[t]))continue;
        B[0].mg(x[t],y[t]),B[1].mg(x[t],y[t]);
        ans[t]=1;c--;
    }
    if(c>mc){puts("NO");return 0;}
    for(auto t:E[1])
    {
        if(B[0].fr(x[t])==B[0].fr(y[t]))continue;
        B[0].mg(x[t],y[t]);
        //cout<<x[t]<<" "<<y[t]<<endl;
        ans[t]=1;b--;
    }
    if(b<0){puts("NO");return 0;}
    //cout<<"*"<<endl;
    B[1].init();for(int i=1;i<=m;i++)if(ans[i])B[1].mg(x[i],y[i]);
    for(auto t:E[2])B[1].mg(x[t],y[t]);
    for(auto t:E[1])
    {
        //cout<<x[t]<<" "<<y[t]<<" "<<B[1].fr(x[t])<<" "<<B[1].fr(y[t])<<endl;
        if(B[1].fr(x[t])==B[1].fr(y[t]))continue;
        B[1].mg(x[t],y[t]);
        ans[t]=1;b--;
    }
    if(b<0){puts("NO");return 0;}
    //cout<<"*"<<endl;
    B[0].init();for(int i=1;i<=m;i++)if(ans[i])B[0].mg(x[i],y[i]);
    for(auto t:E[1])
    {
        if(!b)break;
        if(B[0].fr(x[t])==B[0].fr(y[t]))continue;
        B[0].mg(x[t],y[t]);
        ans[t]=1;b--;
    }
    for(auto t:E[2])
    {
        if(!c)break;
        if(B[0].fr(x[t])==B[0].fr(y[t]))continue;
        B[0].mg(x[t],y[t]);
        ans[t]=1;c--;
    }
    for(auto t:E[0])
    {
        if(!a)break;
        if(B[0].fr(x[t])==B[0].fr(y[t]))continue;
        B[0].mg(x[t],y[t]);
        ans[t]=1;a--;
    }
    //cout<<a<<" "<<b<<" "<<c<<endl;
    if(a||b||c){puts("NO");return 0;}
    puts("YES");
    for(int i=1;i<=m;i++)putchar(ans[i]+'0');
    return 0;
}