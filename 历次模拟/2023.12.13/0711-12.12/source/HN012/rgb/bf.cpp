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
	stack<int> st;
	void init(int n){
		iota(f+1,f+n+1,1);
	}
	int find(int x){
		return x==f[x]?x:find(f[x]);
	}
	bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y) return false;
		f[x]=y,st.push(x);return true;
	}
	void undo(){
		int x=st.top();st.pop();
		f[x]=x;
	}
}d;

void dfs(int id){
	if(id>m){
		if(!c[0]&&!c[1]&&!c[2]){
			puts("YES");
			exit(0);
		}
		return;
	}
	int co=e[id].c,x=e[id].x,y=e[id].y;
	if(c[co]&&d.merge(x,y))
		--c[co],dfs(id+1),++c[co],d.undo();
	dfs(id+1);
}

int main(){
	freopen("rgb.in","r",stdin);
	freopen("rgb.ans","w",stdout);
	for(int i=0;i<3;i++) c[i]=rdi(),n+=c[i];
	++n,m=rdi();
	for(int i=1;i<=m;i++){
		int x,y;char typ;
		scanf("%d%d %c",&x,&y,&typ);
		e[i]={x,y,(typ=='r'?0:1+(typ=='b')),i};
	}
	d.init(n),dfs(1);
	puts("NO");
	return 0;
}
