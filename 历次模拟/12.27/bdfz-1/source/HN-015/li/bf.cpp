#include<bits/stdc++.h>
#define rg register
#define file(x)freopen(x".in","r",stdin);freopen(x".out","w",stdout)

using namespace std;

const int maxn=1e6+10;

int n,m;
vector<int>G[maxn];
inline void init()
{
    scanf("%d %d",&n,&m);
    for(rg int i=1;i<=m;i+=1)
    {
	int x,y;scanf("%d %d",&x,&y);
	G[x].emplace_back(y);
	G[y].emplace_back(x);
    }
}

inline void Tran()
{
    int nn=m;
    int mm=0;
    int tnt=0;
    map<pair<int,int>,int>MP;
    for(rg int i=1;i<=n;i+=1)
	for(auto Cur:G[i])
	    if(i<Cur)
		MP[make_pair(i,Cur)]=++tnt;
    vector<int>NG[maxn>>5];
    for(rg int i=1;i<=tnt;i+=1)NG[i].clear();
    n=nn;
    for(rg int i=1;i<=n;i+=1)
	for(auto Cur:G[i])
	    for(auto Cur2:G[i])
		if(Cur^Cur2)
		{
		    int id1=i<Cur?MP[make_pair(i,Cur)]:MP[make_pair(Cur,i)];
		    int id2=i<Cur2?MP[make_pair(i,Cur2)]:MP[make_pair(Cur2,i)];
		    if(id1>id2)continue;
		    NG[id1].emplace_back(id2);
		    NG[id2].emplace_back(id1);
		    ++mm;
		}
    m=mm;
    for(rg int i=1;i<=tnt;i+=1)G[i]=NG[i];
}

int main()
{
    init();
    for(rg int i=1;i<=10;i+=1,Tran())
	cerr<<n<<" "<<m<<endl;
    return 0;
}
