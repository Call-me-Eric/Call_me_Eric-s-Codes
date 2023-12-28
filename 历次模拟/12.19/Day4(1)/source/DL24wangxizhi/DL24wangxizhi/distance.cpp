#include <bits/stdc++.h>
using namespace std;
const int maxn=1e3+10,top=510;

struct mytype
{
    bitset<top+4>B;
    int hb=-1;
}dis[maxn];
inline void Add(mytype&C,mytype&A,int x)
{
    C=A;
    for(int i=x;i<=top;i++)
        if(C.B[i]) C.B[i]=0;
        else{ C.B[i]=1; C.hb=max(C.hb,i); break; }
}
inline bool cmp(const mytype&X,const mytype&Y)
{
    for(int i=max(X.hb,Y.hb);i>=0;i--) if(X.B[i]!=Y.B[i])
        return X.B[i]>Y.B[i];
    return true;
}

int N,M,n,pre[maxn];
struct node{int x,y;}t[maxn];
bool ins[maxn];
inline int Dis(node A,node B){return max(abs(A.x-B.x),abs(A.y-B.y));}
inline void solve()
{
    cin>>N>>M>>n;
    for(int i=1;i<=n;i++) cin>>t[i].x>>t[i].y;
    for(int i=2;i<=n;i++) dis[i].B[top]=1,dis[i].hb=top;


    queue<int>q;q.push(1);ins[1]=1;
    while(!q.empty())
    {
        int x=q.front();q.pop();ins[x]=0;
        for(int y=1;y<=n;y++) if(y!=x)
        {
            int w=Dis(t[x],t[y]);
            mytype to; Add(to,dis[x],w);
            if(cmp(dis[y],to))
            {
                dis[y]=to,pre[y]=x;
                if(!ins[y]) q.push(y);ins[y]=1;
            }
        }
    }
    vector<int>vec;
    int x=n;
    while(x) vec.push_back(x),x=pre[x];
    reverse(vec.begin(),vec.end());
    cout<<vec.size()<<'\n';
    for(auto x:vec) cout<<x<<" ";cout<<'\n';
}

signed main()
{
    freopen("distance.in","r",stdin);
    freopen("distance.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(NULL);
    solve();
}