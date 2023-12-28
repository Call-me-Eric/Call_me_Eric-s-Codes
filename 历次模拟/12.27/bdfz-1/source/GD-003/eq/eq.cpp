#include<bits/stdc++.h>
using namespace std;

const int p=998244353;

int n;

struct PairHash
{
    inline
    size_t operator () (const pair<int,int> &pr) const
    {
        return (size_t)pr.first*pr.first*19491001+(size_t)pr.second*19260817;
    }
};
unordered_map<pair<int,int>,int,PairHash> mem;

inline
int quickPow(int a,int k)
{
    int &m=mem[pair<int,int>(a,k)];
    if(m) return m;
    int res=1;
    for(int w=a;k!=0;k>>=1,w=1ll*w*w%p)
    {
        if(k&1) res=1ll*res*w%p;
    }
    return m=res;
}

struct Equation
{
    vector<int> a;
    int b;

    inline
    Equation(int n=0)
    {
        a=vector<int>(n,0);
        b=0;
    }
    inline
    Equation(vector<int> _a,int _b)
    {
        a=_a,b=_b;
    }
    inline
    void cp(const Equation &y,int i)
    {
        copy(y.a.begin(),y.a.begin()+i+1,a.begin());
        b=y.b;
    }
    inline
    void ad(const Equation &y,int k,int i)
    {
        for(int j=0;j<=i;j++)
        {
            a[j]=(a[j]+1ll*k*y.a[j]%p);
            if(a[j]>=p) a[j]-=p;
        }
        b=(b+1ll*k*y.b)%p;
    }
};
Equation tot_eq[1410];
vector<pair<int,int>> upd[710];
int tot_eq_cnt;

struct LinearBasis
{
    Equation *t;
    bool can;
    int siz;

    inline
    LinearBasis(int n=0)
    {
        t=new Equation[710];
        can=1,siz=0;
        fill(t,t+n,Equation(n));
    }
    inline
    int insert(int i)
    {
        if(can==0) return -1;

        Equation eq=tot_eq[i];
        for(int i=n-1;i>=0;i--)
        {
            if(eq.a[i]!=0)
            {
                if(t[i].a[i]==0)
                {
                    t[i].cp(eq,i),siz++;
                    return i;
                }
                else
                {
                    int l=1ll*eq.a[i]*quickPow(t[i].a[i],p-2)%p;
                    eq.ad(t[i],1ll*l*(p-1)%p,i);
                }
            }
        }

        if(eq.b!=0)
        {
            can=0;
        }
        return -1;
    }
    inline
    void clear(int x)
    {
        fill(t[x].a.begin(),t[x].a.begin()+x+1,0);
        t[x].b=0;
        siz--;
    }
    inline
    vector<int> solve()         //{-1} for many,{-2} for no
    {
        if(can==0) return vector<int>(1,-2);
        if(siz!=n) return vector<int>(1,-1);

        vector<int> x(n,0);
        for(int i=0;i<n;i++)
        {
            int b=t[i].b;
            for(int j=0;j<i;j++)
            {
                b=(b-1ll*x[j]*t[i].a[j]%p+p);
                if(b>=p) b-=p;
            }
            x[i]=1ll*b*quickPow(t[i].a[i],p-2)%p;
        }
        return x;
    }
    inline
    void print()
    {
        cout<<"Linear Basis **********"<<endl;
        cout<<"can = "<<can<<" , siz = "<<siz<<endl;
        for(int i=0;i<n;i++)
        {
            for(int x:t[i].a) cout<<x<<" ";
            cout<<"= "<<t[i].b<<endl;
        }
        cout<<"***********************"<<endl;
    }
};
LinearBasis lb;

vector<int> ans[710];

struct SegmentTree
{
    struct Node
    {
        vector<int> upd;
    };
    Node t[3010];

    #define ls (u<<1)
    #define rs ((u<<1)|1)

    inline
    void update(int u,int l,int r,int a,int b,int id)
    {
        if(a<=l&&b>=r)
        {
            t[u].upd.push_back(id);
            return;
        }

        int m=l+(r-l)/2;
        if(a<=m) update(ls,l  ,m,a,b,id);
        if(b >m) update(rs,m+1,r,a,b,id);
    }
    inline
    void solve(int u,int l,int r)
    {
        // cout<<"Solving at "<<u<<" [ "<<l<<" , "<<r<<" ]"<<endl;

        int pre_can=lb.can;
        vector<int> inr(0);
        for(int i=0;i<t[u].upd.size();i++)
        {
            // cout<<"Insert ";
            // for(int y:tot_eq[x].a) cout<<y<<" ";
            // cout<<"= "<<tot_eq[x].b<<endl;
            int r=lb.insert(t[u].upd[i]);
            if(r!=-1) inr.push_back(r);
        }
        // cout<<"Updated"<<endl;
        // lb.print();

        if(l==r)
        {
            ans[l]=lb.solve();
            // cout<<l<<" 's ans get : ";
            // for(int x:ans[l]) cout<<x<<" ";
            // cout<<endl;
        }
        else
        {
            int m=l+(r-l)/2;
            solve(ls,l  ,m);
            solve(rs,m+1,r);
        }

        lb.can=pre_can;
        for(int x:inr) lb.clear(x);
        // cout<<"Undo done"<<endl;
        // lb.print();
    }
    inline
    void print(int u,int l,int r)
    {
        cout<<"Node "<<u<<" : [ "<<l<<" , "<<r<<" ] : ";
        for(int x:t[u].upd) cout<<x<<" ";
        cout<<endl;

        if(l==r) return;

        int m=l+(r-l)/2;
        print(ls,l  ,m);
        print(rs,m+1,r);
    }
};
SegmentTree st;

int main()
{
    freopen("eq.in","r",stdin);
    freopen("eq.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    int q;
    cin>>n>>q;
    for(int i=1;i<=n;i++)
    {
        vector<int> a(n,0);
        int b=0;
        for(int &x:a) cin>>x;
        cin>>b;

        tot_eq[++tot_eq_cnt]=Equation(a,b);
        upd[i].push_back({0,tot_eq_cnt});
    }
    for(int _=1;_<=q;_++)
    {
        vector<int> a(n,0);
        int id,b=0;
        cin>>id;
        for(int &x:a) cin>>x;
        cin>>b;

        tot_eq[++tot_eq_cnt]=Equation(a,b);
        upd[id].push_back({_,tot_eq_cnt});
    }
    // cout<<"Upd got"<<endl;

    for(int i=1;i<=n;i++)
    {
        for(int j=0;j+1<upd[i].size();j++)
        {
            st.update(1,0,q,upd[i][j].first,upd[i][j+1].first-1,upd[i][j].second);
        }
        st.update(1,0,q,upd[i].back().first,q,upd[i].back().second);
    }
    // cout<<"Upd hanged"<<endl;
    // st.print(1,0,q);

    lb=LinearBasis(n);
    // cout<<"Pre lb"<<endl;
    // lb.print();
    // cout<<"Start solving"<<endl;
    st.solve(1,0,q);
    // cout<<"Solved"<<endl;

    for(int i=0;i<=q;i++)
    {
        if(ans[i][0]==-1)
        {
            cout<<"Many"<<'\n';
        }
        else if(ans[i][0]==-2)
        {
            cout<<"No"<<'\n';
        }
        else
        {
            for(int x:ans[i]) cout<<x<<" ";
            cout<<'\n';
        }
    }
}