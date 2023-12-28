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

vector<pii> calc2(const vector<Edge> &e){
	int c0=0,c1=0,all=0;
	d.init(n);
	for(auto cur:e){
		assert(cur.c!=2);
		all+=d.merge(cur.x,cur.y);
	}
	d.init(n);
	for(auto cur:e)
		if(cur.c==0) c0+=d.merge(cur.x,cur.y);
	d.init(n);
	for(auto cur:e)
		if(cur.c==1) c1+=d.merge(cur.x,cur.y);
	vector<pii> ret;
	for(int i=0;i<=c0;i++)
		for(int j=0;j<=min(c1,all-i);j++)
			ret.pb({i,j});
	return ret;
}

void construct(const vector<Edge> &e,int c0,int c1){
	d.init(n);
	for(auto cur:e)
		if(cur.c==0) d.merge(cur.x,cur.y);
	for(auto cur:e){
		if(!c1) break;
		if(cur.c==1&&d.merge(cur.x,cur.y))
			--c1,sel[cur.id]=1;
	}
	d.init(n);
	for(auto cur:e)
		if(cur.c==1) d.merge(cur.x,cur.y);
	for(auto cur:e){
		if(!c0) break;
		if(cur.c==0&&d.merge(cur.x,cur.y))
			--c0,sel[cur.id]=1;
	}
	d.init(n);
	for(auto cur:e)
		if(sel[cur.id]) d.merge(cur.x,cur.y);
	for(auto cur:e){
		if(c0&&cur.c==0&&d.merge(cur.x,cur.y))
			sel[cur.id]=1,--c0;
		if(c1&&cur.c==1&&d.merge(cur.x,cur.y))
			sel[cur.id]=1,--c1;
	}
}

using cp=vector<Edge>;

bool calc3(){
	d.init(n);
	for(int i=1;i<=m;i++)
		if(e[i].c==2) d.merge(e[i].x,e[i].y);
	static cp a[N];
	for(int i=1;i<=m;i++){
		if(e[i].c==2) continue;
		int x=e[i].x,y=e[i].y;
		if(d.find(x)!=d.find(y))
			a[n+1].pb({d.find(x),d.find(y),e[i].c,e[i].id});
		else
			a[d.find(x)].pb(e[i]);
	}

	static bitset<N> f[N][N];
	static vector<pii> vec[N];
	f[0][0][0]=1;
	for(int i=1;i<=n+1;i++){
		vec[i]=calc2(a[i]);
		for(auto cur:vec[i]){
			int x=cur.fi,y=cur.se;
			for(int j=x;j<=c[0];j++)
				f[i][j]|=f[i-1][j-x]<<y;
		}
	}

	int c0=c[0],c1=c[1];
	if(!f[n+1][c0][c1]) return false;
	for(int i=n+1;i>=1;i--){
		for(auto cur:vec[i]){
			int x=cur.fi,y=cur.se;
			if(c0>=x&&c1>=y&&f[i-1][c0-x][c1-y]){
				construct(a[i],x,y),c0-=x,c1-=y;
				break;
			}
		}
	}

	d.init(n);
	for(int i=1;i<=m;i++)
		if(sel[i]) d.merge(e[i].x,e[i].y);
	for(int i=1;i<=m;i++)
		if(e[i].c==2&&d.merge(e[i].x,e[i].y)) sel[e[i].id]=1;

	// checker
	for(int i=1;i<=m;i++)
		c[e[i].c]-=sel[i];
	if(c[2]) return false;
	assert(!c[0]&&!c[1]&&!c[2]);
	for(int i=1;i<=n;i++)
		assert(d.find(i)==d.find(1));
	return true;
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
	if(calc3()){
		puts("YES");
		for(int i=1;i<=m;i++)
			cout<<sel[i];
		cout<<'\n';
	}
	else puts("NO");
	return 0;
}
