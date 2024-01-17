#include <bits/stdc++.h>

using namespace std;

using u32=unsigned int;
using i64=long long;
using u64=unsigned long long;
using db=double;
using vi=vector<int>;
using pii=pair<int,int>;

template<typename T>
T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f|=(c=='-'),c=getchar();
	while(isdigit(c)) x=x*10+(c-'0'),c=getchar();
	return f?-x:x;
}

#define rdi read<int>
#define rdi64 read<i64>
#define fi first
#define se second
#define pb push_back

const int N=255,M=N*N;

int c[3],n,m;
struct Edge{int x,y,c,id;}e[M];
int sel[M];

vector<pii> t[N];

void add_e(int id){
	assert(!sel[e[id].id]);
	int x=e[id].x,y=e[id].y;
	t[x].pb({y,id}),t[y].pb({x,id});
	--c[e[id].c],sel[e[id].id]=1;
}
void del_e(int id){
	assert(sel[e[id].id]);
	int x=e[id].x,y=e[id].y;
	t[x].erase(find_if(t[x].begin(),t[x].end(),[&](pii p){return p.se==id;}));
	t[y].erase(find_if(t[y].begin(),t[y].end(),[&](pii p){return p.se==id;}));
	++c[e[id].c],sel[e[id].id]=0;
}

struct Dsu{
	int f[N];
	void init(int n){
		iota(f+1,f+n+1,1);
	}
	int find(int x){
		return x==f[x]?x:f[x]=find(f[x]);
	}
	bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y) return false;
		f[x]=y;return true;
	}
}d;

int st[N],tp;
bool dfs(int x,int fa,int to){
	if(x==to) return true;
	for(auto tmp:t[x]){
		int y=tmp.fi;
		st[++tp]=tmp.se;
		if(y!=fa&&dfs(y,x,to)) return true;
		--tp;
	}
	return false;
}

bool construct(){
	d.init(n);
	for(int i=1;i<=n;i++)
		t[i].clear();
	for(int i=1;i<=m;i++)
		if(d.merge(e[i].x,e[i].y)) add_e(i);
	while(c[0]||c[1]||c[2]){
		bool fl=0;
		for(int i=1;i<=m;i++){
			if(!sel[i]&&c[e[i].c]>0){
				int x=e[i].x,y=e[i].y;
				tp=0,dfs(x,0,y);int flg=0;
				for(int j=1;j<=tp;j++){
					int k=st[j];
					if(c[e[k].c]<0){
						del_e(k),add_e(i),flg=1;
						break;
					}
				}
				/*
				if(!flg){
					for(int j=1;j<=tp;j++){
						int k=st[j];
						if(e[k].c!=e[i].c){
							del_e(k),add_e(i),i=0;
							break;
						}
					}
				}
				*/
				fl|=flg;
			}
		}
		if(!fl) break;
	}
	if(c[0]||c[1]||c[2]){
		for(int i=1;i<=m;i++)
			if(sel[e[i].id])
				sel[e[i].id]=0,++c[e[i].c];
		return false;
	}
	else return true;
}

void check(){
	d.init(n);
	for(int i=1;i<=m;i++)
		if(sel[i]) assert(d.merge(e[i].x,e[i].y));
	for(int i=1;i<=n;i++)
		assert(d.find(i)==d.find(1));
}

int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.out","w",stdout);
	for(int i=0;i<3;i++) c[i]=rdi(),n+=c[i];
	++n,m=rdi();
	for(int i=1;i<=m;i++){
		int x,y;char typ;
		scanf("%d%d %c",&x,&y,&typ);
		e[i]={x,y,(typ=='r'?0:1+(typ=='b')),i};
	}
	db st=clock();
	mt19937 rng(1983198);
	while(clock()-st<1.8*CLOCKS_PER_SEC){
		shuffle(e+1,e+m+1,rng);
		if(construct()){
			puts("YES");
			for(int i=1;i<=m;i++)
				cout<<sel[i];
			cout<<'\n';
			return 0;
		}
	}
	puts("NO");
	return 0;
}
