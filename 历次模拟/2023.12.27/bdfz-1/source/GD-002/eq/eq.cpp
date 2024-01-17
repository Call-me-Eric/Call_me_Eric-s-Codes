/*
往一组消好的方程中插入一个方程是 O(n^2)。
线段树分治。
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int md=998244353;
int mod(int x)
{
    return x+(x<0)*md-(x>=md)*md;
}
int quickPow(int x,int k)
{
    int ans=1;
    for(;k;k>>=1,x=x*x%md)
    {
        if(k&1)
            ans=ans*x%md;
    }
    return ans;
}
int n,q;
struct Equation
{
    int v[710];
    friend istream& operator>>(istream &is,Equation &e)
    {
        for(int i=1;i<=n+1;i++)
            is>>e.v[i];
        return is;
    }
    friend ostream& operator<<(ostream &os,Equation e)
    {
        for(int i=1;i<=n+1;i++)
            os<<(i==n+1?"v=":"")<<e.v[i]<<" ";
        return os;
    }
    void maintain(int x)
    {
        int t=quickPow(v[x],md-2);
        for(int i=1;i<=n+1;i++)
            v[i]=(v[i]*t)%md;
    }
    friend Equation operator*(Equation a,int x)
    {
        for(int i=1;i<=n+1;i++)
            a.v[i]=a.v[i]*x%md;
        return a;
    }
    friend Equation operator+(Equation a,Equation b)
    {
        for(int i=1;i<=n+1;i++)
            a.v[i]=mod(a.v[i]+b.v[i]);
        return a;
    }
    friend Equation operator-(Equation a,Equation b)
    {
        for(int i=1;i<=n+1;i++)
            a.v[i]=mod(a.v[i]-b.v[i]);
        return a;
    }
    void operator-=(Equation b)
    {
        for(int i=1;i<=n+1;i++)
            v[i]=mod(v[i]-b.v[i]);
    }
};
struct Equations
{
    bool many,none;
    Equation eq[710];
    Equations()
    {
        many=none=0;
        for(int i=0;i<=n+1;i++)
        {
            for(int j=0;j<=n+1;j++)
                eq[i].v[j]=0;
        }
    }
    void insert(Equation e)
    {
        for(int i=1;i<=n;i++)
        {
            if(e.v[i])
            {
                if(!eq[i].v[i])
                {
                    eq[i]=e;
                    eq[i].maintain(i);
                    for(int j=i+1;j<=n;j++)
                    {
                        if(eq[i].v[j]&&eq[j].v[j])
                            eq[i]-=eq[j]*eq[i].v[j];
                    }
                    // cout<<"Maintain "<<e<<" = "<<eq[i]<<endl;
                    for(int j=1;j<i;j++)
                    {
                        if(eq[j].v[i])
                            eq[j]-=eq[i]*eq[j].v[i];
                    }
                    return;
                }
                else
                    e-=eq[i]*e.v[i];
            }
        }
        many=1;
        if(e.v[n+1])
            none=1;
    }
};
vector<Equation> ins[3100];
#define ls (u<<1)
#define rs ((u<<1)|1)
void insert(int u,int l,int r,int a,int b,Equation e)
{
    // cout<<"Insert u="<<u<<" ["<<l<<","<<r<<"] ["<<a<<","<<b<<"] eq = "<<e<<endl;
    if(a<=l&&r<=b)
    {
        ins[u].push_back(e);
        return;
    }
    int mid=(l+r)>>1;
    if(a<=mid) insert(ls,l,mid,a,b,e);
    if(b>mid) insert(rs,mid+1,r,a,b,e);
}
void solve(int u,int l,int r,Equations eq)
{
    // cout<<"Solve ["<<l<<","<<r<<"] :"<<endl;
    // cout<<"many="<<eq.many<<" none="<<eq.none<<endl;
    // for(int i=1;i<=n;i++)
    //     cout<<eq.eq[i]<<endl;
    for(Equation e:ins[u])
    {
        // cout<<"Insert "<<e<<endl;
        eq.insert(e);
    }
    // cout<<"Inserted :"<<endl;
    // cout<<"many="<<eq.many<<" none="<<eq.none<<endl;
    // for(int i=1;i<=n;i++)
    //     cout<<eq.eq[i]<<endl;
    if(l==r)
    {
        if(eq.none)
            cout<<"No\n";
        else if(eq.many)
            cout<<"Many\n";
        else
        {
            for(int i=1;i<=n;i++)
                cout<<eq.eq[i].v[n+1]<<" ";
            cout<<'\n';
        }
        return;
    }
    int mid=(l+r)>>1;
    solve(ls,l,mid,eq);
    solve(rs,mid+1,r,eq);
}
#undef ls
#undef rs
vector<pair<int,Equation>> upd[710];
signed main()
{
	freopen("eq.in","r",stdin);
	freopen("eq.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        Equation e;
        cin>>e;
        upd[i].push_back(make_pair(0,e));
    }
    for(int i=1;i<=q;i++)
    {
        int p;
        Equation e;
        cin>>p>>e;
        upd[p].push_back(make_pair(i,e));
    }
    for(int i=1;i<=n;i++)
    {
        // cout<<"i="<<i<<endl;
        for(int j=0;j<(int)upd[i].size()-1;j++)
            insert(1,0,q,upd[i][j].first,upd[i][j+1].first-1,upd[i][j].second);
        insert(1,0,q,upd[i].back().first,q,upd[i].back().second);
    }
    solve(1,0,q,Equations());
}
/*
3 3
1 1 0 2
1 0 1 2
0 1 1 2
1 1 0 0 1
2 0 1 1 2
3 0 1 1 1

3 0
1 1 0 2
1 0 1 2
0 1 1 3
*/