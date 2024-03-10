#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=3e6+10;
int n,m;
int scnt;
struct edge{
	int nt,to,w;
}e[N<<1];
int p[N],cnt;
inline void add(int x,int y,int z){
	e[++cnt]={p[x],y,z};p[x]=cnt;
}
int tp,dfn[N],low[N],tim,ans=INT_MAX;
vector<int> vec;
pii stk[N];
void tarjan(int x,int fa,int W){
	dfn[x]=low[x]=++tim;
	stk[++tp]={x,W};
	for(int i=p[x];i;i=e[i].nt){
		int v=e[i].to,w=e[i].w;
		if(!dfn[v]){
			tarjan(v,x,w);
			low[x]=min(low[x],low[v]);
			if(low[v]>=dfn[x]){
				int sz=1;
				vec.clear();
				while(stk[tp+1].fr!=v){
					sz++;
					vec.push_back(stk[tp].sc);
					tp--;
				}
				sort(vec.begin(),vec.end());
				if(sz>2)vec.push_back(w);
				if(vec.size()==1)ans=min(ans,vec[0]);
				else if(vec.size()==2)ans=min(ans,vec[0]+vec[1]);
				else{
					ans=min(ans,min(vec[0]+vec[1],vec[2]));
				}
			}
		}
		else{
			if(v!=fa){
				low[x]=min(low[x],dfn[v]);
			}	
		}
	}
}
struct edge_to_one{
	int u,v,w;
	inline bool operator <(const edge_to_one &o)const{
		if(u==o.u)return v<o.v;
		return u<o.u;
	}
}a[N];
signed main(){
	freopen("inazuma.in","r",stdin);
	freopen("inazuma.out","w",stdout);
	n=rd();m=rd();
	for(int i=1;i<=m;i++){
		a[i].u=rd();a[i].v=rd();a[i].w=rd();
	}
	sort(a+1,a+1+m);
	for(int i=1,res=0;i<=m;i++){
		if(a[i].u==a[i+1].u&&a[i].v==a[i+1].v){
			res+=a[i].w;
		}else{
			res+=a[i].w;
			add(a[i].u,a[i].v,res);
			res=0;
		}
	}
	tarjan(1,0,0);
	cout<<ans<<endl;
	return 0;
}

