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
const int N = 1e3 + 10 , mod = 998244353 ;
void pls(int &x,int y){x += y ; if(x >= mod)x -= mod ;}
int fpow(int bas,int k){int res = 1 ; for( ; k ; k >>= 1 , bas = bas * bas % mod)if(k & 1)res = res * bas % mod ; return res ;}
int n,Q ;
int a[N][N],ta[N][N],p ;
void work(){
	for(ri i = 1 ; i <= n ; i++)for(ri j = 1 ; j <= n + 1 ; j++)a[i][j] = ta[i][j] ;
	for(ri k = 1 ; k <= n ; k++){
		for(ri i = k ; i <= n ; i++)if(a[i][k]){
			for(ri j = 1 ; j <= n + 1 ; j++)swap(a[i][j],a[k][j]) ;
			break ;
		}
			
		if(!a[k][k])continue ;
		for(ri i = 1 , div ; i <= n ; i++)if(i!=k){
			div = a[i][k] * fpow(a[k][k],mod - 2) % mod ;
			for(ri j = 1 ; j <= n + 1 ; j++)pls(a[i][j],mod-div*a[k][j]%mod) ;
		}
		//exit(0) ;
		/*cout<<"!!!"<<endl ;
		for(ri i = 1 ; i <= n ; i++){
			for(ri j = 1 ; j <= n + 1 ; j++)cout<<a[i][j]<<" " ; 
			cout<<endl ;
		}
		cout<<"!!!"<<endl ;*/
	}
	//exit(0) ;
	for(ri i = 1 ; i <= n ; i++)if(!a[i][i])return puts(a[i][n+1]?"No":"Many"),void() ;
	for(ri i = 1 ; i <= n ; i++)printf("%lld ",a[i][n+1]*fpow(a[i][i],mod-2)%mod) ; puts("") ;
}
bool m_ed ;
signed main(){
	freopen("eq.in","r",stdin) ; freopen("eq.out","w",stdout) ;
	read(n,Q) ;
	for(ri i = 1 ; i <= n ; i++)for(ri j = 1 ; j <= n + 1 ; j++)read(ta[i][j]) ;
	work() ;
	while(Q--){
		read(p) ; for(ri i = 1 ; i <= n + 1 ; i++)read(ta[p][i]) ;
		work() ;
	}
	return 0 ;
}
/*
3 3
1 1 0 2
1 0 1 2
0 1 1 2
1 1 0 0 1
2 0 1 1 2
3 0 1 1 1

*/

