#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+7;
typedef long long LL;
typedef long double db;
const db Pi = acos(-1);
int n,k;
namespace task1
{
    const LL Mul = 1e12;
    inline LL Hash(db A,db B){return (A*Mul*131)+(B*Mul);}
    LL val[N];
    unordered_map<LL,int> state[50];
    int Ans[50],Now=0,L,R;
    void upd(int S,int T,int c)
    {
        if(c<=Now)return;
        Now=c;
        for(int i=0;i<L;i++)Ans[i]=((S>>i)&1);
        for(int i=0;i<R;i++)Ans[L+i]=((T>>i)&1);
    }
    void solve()
    {
        db A=(2.0*Pi)/(1.0*n);
        LL D=0;
        for(int i=1;i<=n;i++)
        {
            val[i]=Hash(sin(A*(i-1)),cos(A*(i-1)));
            D+=val[i];
        }
        L=(n/2),R=n-L;
        for(int S=0;S<(1<<L);S++)
        {
            int c=0;
            LL res=0;
            for(int i=0;i<L;i++)if((S>>i)&1)
            {
                c++;
                res+=val[i+1];
            }
            state[c][res]=S;
        }
        //for(int i=0;i<n;i++)cout<<Ans[i];cout<<endl;
        for(int S=0;S<(1<<R);S++)
        {
            int c=0;
            LL res=0;
            for(int i=0;i<R;i++)if((S>>i)&1)
            {
                c++;
                res+=val[L+i+1];
            }
            for(int d=k-c;d>=max(0,Now+1-c);d--)
            for(int v=-5;v<=5;v++)
            {
                if(state[d].find(-res+v)!=state[d].end())
                upd(state[d][-res+v],S,d+c);
            }
        }
        for(int i=0;i<n;i++)cout<<Ans[i];
        //out<<Now;
    }
}
namespace task2
{

    int calc(int n,int k)
    {
        int res=0,c=0;
        for(int i=2;i<=n;i++)
        if(n%i==0)
        {
            int v=(k/i)*i;
            if(v>res)
            {
                res=v;
                c=i;
            }
        }
        if(c==0)
        {
            for(int i=0;i<n;i++)cout<<0;
            exit(0);
        }
        return c;
    }
    void solve()
    {
        int D=calc(n,k),R=k/D,L=(n/D);
        for(int i=1;i<=n;i++)
        {
            int d=(i-1)%L+1;
            if(d<=R)putchar('1');
            else putchar('0');
        }
    }
}
int main()
{
    freopen("ur.in","r",stdin);
    freopen("ur.out","w",stdout);
    cin>>n>>k;
    if(n<=36)
    {
        task1::solve();
        return 0;
    }
    task2::solve();
    return 0;
}
