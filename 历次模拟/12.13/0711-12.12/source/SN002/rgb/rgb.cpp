//El Psy Kongroo
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ri int
#define TIME (1e3 * clock() / CLOCKS_PER_SEC)
using namespace std ;
template <typename T>
inline void read(T&x){
	x = 0 ; char c = getchar() ; bool flg = 1 ; while(c > '9' || c < '0'){if(c == '-')flg = 0 ; c = getchar() ;}
	while(c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48) ; c = getchar() ;} x = flg ? x : -x ;
}
template <typename T,typename ...Args>
inline void read(T&x,Args&...args){read(x),read(args...);}
bool m_bg ;
const int N = 1e5 + 10 ;
mt19937 rnd(time(0)) ;
char tc[5] ;
struct line{int u,v,c ;}L[N] ;
int r,g,b,n,m,ans[N] ;
namespace subtask1{
	int __fa[N],ht[N] ;
	int getf(int x){return x==__fa[x]?x:getf(__fa[x]) ;}
	void dfs(int cm,int cr,int cg,int cb){
		if(cr+cg+cb>cm||cr<0||cg<0||cb<0)return ;
		if(cr==0&&cg==0&&cb==0){
			puts("YES") ;
			for(ri i = 1 ; i <= m ; i++)putchar(ans[i]+'0') ; exit(0) ;
		}
		int u = getf(L[cm].u) , v = getf(L[cm].v) , k = 0 , c = L[cm].c ; 
		if(u==v)ans[cm]=0,dfs(cm-1,cr,cg,cb) ;
		else{
			if(ht[u]>ht[v])swap(u,v) ;
			k = (ht[u] == ht[v]) ; __fa[u] = v ; ht[v] += k ;
			ans[cm] = 1 ; dfs(cm-1,cr-(c==0),cg-=(c==1),cb-=(c==2)) ;
			__fa[u] = u , __fa[v] = v , ht[v] -= k ;
			ans[cm] = 0 ; dfs(cm-1,cr,cg,cb) ;
		}
	}
	signed main(){
		for(ri i = 1 ; i <= n ; i++)__fa[i]=i ; dfs(m,r,g,b) ;
		puts("NO") ; return 0 ;
	}
}
namespace subtask2{
	int id[N],__fa[N],cr,cg,cb ;
	int getf(int x){return x==__fa[x]?x:__fa[x]=getf(__fa[x]) ;}
	void merge(int i){
		int u = getf(L[i].u) , v = getf(L[i].v) , c = L[i].c ; ans[i] = 0 ;
		if(u==v||(c==0&&cr==0)||(c==1&&cg==0)||(c==2&&cb==0))return ;
		cr-=(c==0),cg-=(c==1),cb-=(c==2) ; __fa[u] = v ; ans[i] = 1 ;
	}
	signed main(){
		for(ri i = 1 ; i <= m ; i++)id[i] = i ;
		while(TIME<1900){
			for(ri i = 1 ; i <= n ; i++)__fa[i] = i ;
			shuffle(id+1,id+m+1,rnd) ; cr = r , cg = g , cb = b ;
			for(ri i = 1 ; i <= m ; i++)merge(id[i]) ;
			if(!cr&&!cg&&!cb){puts("YES") ; for(ri i = 1 ; i <= n ; i++)putchar(ans[i]+'0') ; exit(0) ;}
		}puts("NO") ;
		return 0 ;
	}
}
bool m_ed ;
signed main(){
	freopen("rgb.in","r",stdin) ; freopen("rgb.out","w",stdout) ;
	read(r,g,b,m) ; n = r + g + b + 1 ; for(ri i = 1 ; i <= m ; i++)read(L[i].u,L[i].v),scanf("%s",tc),L[i].c=(tc[0]=='r'?0:tc[0]=='g'?1:2) ;
	if(n<=5)subtask1::main() ;
	else subtask2::main() ;
	return 0 ;
}
/*
*/
