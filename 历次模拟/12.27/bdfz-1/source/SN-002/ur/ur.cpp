//El Psy Kongroo
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define pb push_back
#define ri int
using namespace std ;
template <typename T>
inline void read(T&x){
	x = 0 ; char c = getchar() ; bool flg = 1 ; while(c > '9' || c < '0'){if(c == '-')flg = 0 ; c = getchar() ;}
	while(c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48) ; c = getchar() ;} x = flg ? x : -x ;
}
template <typename T,typename ...Args>
inline void read(T&x,Args&...args){read(x),read(args...);}
bool m_bg ;
const int N = 1e6 + 10 , _N = 1e6 ;
#define db double
const db pi = acos(-1) , eps = 1e-8 ;
/*struct node{
	db x,y ;
	friend node operator + (node a,node b){return {a.x+b.x,a.y+b.y} ;}
	friend node operator - (node a,node b){return {a.x-b.x,a.y-b.y} ;}
}p[N] ;*/
//bool eq(db x,db y){return fabs(x-y)<=eps ;}
int vis[N],prm[N],pmn,las[N] ;
int n,k,ok[N] ; vector<int>p ;
void get_prime(){
	int x = n ; for(ri i = 2 ; i * i <= x ; i++)if(x%i==0){while(x%i==0)x/=i ; p.pb(i) ;} if(x!=1)p.pb(x) ;
	for(ri i = 2 ; i <= _N ; i++){
		if(!vis[i])prm[++pmn] = i ;
		for(ri j = 1 ; j <= pmn && i * prm[j] <= _N ; j++){
			vis[i * prm[j]] = 1 ; las[i * prm[j]] = prm[j] ;
			if(i % prm[j] == 0)break ;
		}
	}
}
#define pii pair<int,int>
map<pii,int>mp ; 
int mul(int s,int k1,int k2){
	int res = 0 ;
	for(ri i = 0 ; i < k1 ; i++)res|=(s<<(k2*i)) ;
	return res ;
}
int ans[N] ;
void dfs(int c,int s){
	if(mp.count({c,s}))return ; mp[{c,s}] = 1 ;
	if(c==(int)p.size())return ans[__builtin_popcountll(s)]=s,void() ; dfs(c+1,s) ;
	int pn = p[c] , U = (1 << (n / pn)) - 1 , S = ((U ^ s) & U) ;
	for(ri T = S ; T ; T = (S&(T-1))){
		if((s&(mul(T,pn,n/pn)))==0)dfs(c+1,s|mul(T,pn,n/pn)) ;
	}
}
bool m_ed ;
signed main(){
	//freopen("ur.in","r",stdin) ; freopen("ur.out","w",stdout) ;
	read(n,k) ; get_prime() ;
	if(k==n){
		for(ri i = 1 ; i <= n ; i++)printf("1") ; 
		printf("\n") ; return 0 ;
	}
	else if(k <= 1){
		for(ri i = 1 ; i <= n ; i++)printf("0") ;
		printf("\n") ; return 0 ;
	}
	else if(n <= 36){
		dfs(0,0) ; while(!ans[k])k-- ;
		for(ri i = 0 ; i < n ; i++)printf("%lld",(ans[k]>>i&1)) ; printf("\n") ; return 0 ;
	}
	else if(!vis[n]){
		for(ri i = 1 ; i <= n ; i++)printf("%d",k==n) ;
		printf("\n") ; return 0 ;
	}
	else if(las[n]&&las[n/las[n]]==0){
		int p1 = las[n] , p2 = n/las[n] , k1 = 0 , k2 = 0 ;
		for( ; k1 * p1 <= k ; k1++) ; if(k1*p1>k)k1-- ;
		for( ; k2 * p2 <= k ; k2++) ; if(k2*p2>k)k2-- ;
		if(p1*k1<p2*k2)swap(p1,p2),swap(k1,k2) ;
		//cout<<p1<<" "<<k1<<endl ;
		for(ri i = 1 ; i <= p1 ; i++){
			for(ri j = 1 ; j <= k1 ; j++)printf("1") ;
			for(ri j = k1 + 1 ; j <= n/p1 ; j++)printf("0") ;
		}
		printf("\n") ; return 0 ;
	}
	else if(p.size()==1){
		int p1 = las[n] , k1 = 0 ;
		for( ; k1 * p1 <= k ; k1++) ; if(k1*p1>k)k1-- ;
		for(ri i = 1 ; i <= p1 ; i++){
			for(ri j = 1 ; j <= k1 ; j++)printf("1") ;
			for(ri j = k1 + 1 ; j <= n/p1 ; j++)printf("0") ;
		}
		printf("\n") ; return 0 ;
	}
	else{
		
	}
	/*read(n) ; for(ri i = 0 ; i < n ; i++)p[i]={cos(2*pi/n*i),sin(2*pi/n*i)} ;
	for(ri s = 0 ; s < (1 << n) ; s++){
		//if(__builtin_popcount(s)!=5)continue ;
		node c = {0,0} ;
		for(ri i = 0 ; i < n ; i++)if(s>>i&1)c = c + p[i] ;
		//cout<<c.x<<" "<<c.y<<endl ;
		if(eq(c.x,0)&&eq(c.y,0)){
			//for(ri i = 0 ; i < n ; i++)cout<<(s>>i&1) ; cout<<endl ; exit(0) ;
			ok[__builtin_popcount(s)]=1 ;
		}
	}
	for(ri i = 1 ; i <= n ; i++)cout<<i<<" "<<ok[i]<<endl ;*/
	return 0 ;
}
/*
*/

