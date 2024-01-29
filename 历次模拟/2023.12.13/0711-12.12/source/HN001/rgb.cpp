#include<cstdio>
#include<cctype>
#include<vector>
#include<ctime>
#include<random>
#include<algorithm>

#define maxn 333

bool Mbg;

template<class T>

inline T read(){
	T r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r*10)+(c^48),c=getchar();
	return f?-r:r;
}

inline char getc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}

int n,m,tot,f[maxn];

int lim[3],Min[3],Max[3];

std::vector<std::pair<int,int> > to[maxn];

struct Ed{
	int u,v,id,col;
}add[maxn];

std::vector<Ed> ed[3];

int find(int x){
	return x^f[x]?f[x]=find(f[x]):x;
}

inline int solve(std::vector<Ed> &vec,bool flg=0){
	int cnt=0;
	for(auto ed:vec){
		int u=find(ed.u);
		int v=find(ed.v);
		if(u==v)continue;
		f[v]=u,cnt++;
		if(flg)add[++tot]=ed;
	}
	return cnt;
}

inline bool check(){
	for(int o=0;o<3;o++){
		for(int i=1;i<=n;i++)f[i]=i;
		for(int i=0;i<3;i++)
			if(i^o)solve(ed[i]);
		Min[o]=solve(ed[o]);
		for(int i=1;i<=n;i++)f[i]=i;
		Max[o]=solve(ed[o]);
		if(lim[o]<Min[o]||lim[o]>Max[o])
			return false;
	}
	return true;
}

int fa[maxn],id[maxn];

void dfs(int u,int fa){
	::fa[u]=fa;
	for(auto P:to[u]){
		int v=P.first;
		if(v==fa)continue;
		id[v]=P.second,dfs(v,u);
	}
}

inline bool calc(){
	tot=0;
	static int cnt[3];
	static int lim[3];
	std::vector<Ed> vec[3];
	for(int i=1;i<=n;i++)f[i]=i;
	for(int o=0;o<3;o++){
		vec[o]=ed[o];
		lim[o]=vec[o].back().id;
		vec[o].pop_back();
		cnt[o]=solve(vec[o],1);
	}
	for(int o=0;o<3;o++){
		int now=o+1;
		if(cnt[o]<lim[o])return false;
		while(cnt[o]>lim[o]){
			if(vec[now].empty())now++;
			if(now>=3)return false;
			if(cnt[now]>=lim[now])now++;
			if(now>=3)return false;
			Ed ed=vec[now].back();
			vec[now].pop_back();
			if(ed.u==ed.v)continue;
			for(int i=1;i<=n;i++)
				to[i].clear();
			for(int i=1;i<n;i++){
				to[add[i].u].push_back({add[i].v,i});
				to[add[i].v].push_back({add[i].u,i});
			}
			dfs(ed.u,0);
			int x=ed.v;
			while(fa[x]){
				if(add[id[x]].col==o){
					add[id[x]]=ed;
					cnt[o]--,cnt[now]++;
					break;
				}
				x=fa[x];
			}
		}
	}
	return true;
}

bool Med;

int main(){
	double Mb=((&Mbg)-(&Med))/1e6;
	fprintf(stderr,"%.2lfMB\n",Mb=Mb<0?-Mb:Mb);
	if(Mb>1000)fprintf(stderr,"MLE!!!\n");
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	double st=clock();
	for(int o=0;o<3;o++)
		n+=(lim[o]=read<int>());
	n++,m=read<int>();
	static int id[3]={0,1,2},rk[3]={0,1,2};
	std::sort(id,id+3,[&](int x,int y){return lim[x]>lim[y];});
	std::sort(lim,lim+3),std::reverse(lim,lim+3);
	for(int i=0;i<3;i++)rk[id[i]]=i;
	for(int i=1;i<=m;i++){
		int u=read<int>();
		int v=read<int>();
		char c=getc();
		int col=rk[c=='r'?0:(c=='g'?1:2)];
		ed[col].push_back((Ed){u,v,i,col});
	}
	if(!check())return puts("NO"),0;
	for(int o=0;o<3;o++)
		ed[o].push_back((Ed){0,0,lim[o],o});
	std::mt19937 RAND(std::random_device{}());
	while(!calc()){
		if((clock()-st)/CLOCKS_PER_SEC>1.8)
			return puts("NO"),0;
		std::shuffle(ed,ed+3,RAND);
		for(int o=0;o<3;o++){
			for(auto &d:ed[o])d.col=o;
			std::shuffle(ed[o].begin(),ed[o].end()-1,RAND);
		}
	}
	puts("YES");
	static int ans[maxn*maxn];
	for(int i=1;i<n;i++)
		ans[add[i].id]=1;
	for(int i=1;i<=m;i++)
		putchar(ans[i]+'0');
	return 0;
}
