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
const int N = 1e7 + 10 , _N = 1e7 ;
int vis[N],prm[N],pmn ;
void get_prime(){
	vis[0] = vis[1] = 1 ;
	for(ri i = 2 ; i <= _N ; i++){
		if(!vis[i])prm[++pmn] = i ;
		for(ri j = 1 ; j <= pmn && i * prm[j] <= _N ; j++){
			vis[i * prm[j]] = 1 ;
			if(i % prm[j] == 0)break ;
		}
	}
}
int T,l,r,ans,a[N] ;
int solve(int x){
	int t = x , n = 0 ; while(x)a[n++]=x%10,x/=10 ; x = t ;
	for(ri s = 1 , c = 0 , num = 0 ; s < (1 << n) ; s++){
		c = num = 0 ; for(ri i = 0 ; i < n ; i++)if(s>>i&1)num+=a[i]*pow(10,c),c++ ;
		if(!vis[num])return 0 ;
	}
	return 1 ;
}
bool m_ed ;
signed main(){
	freopen("prime.in","r",stdin) ; freopen("prime.out","w",stdout) ;
	get_prime() ; read(T) ; while(T--){
		read(l,r) ;
		for(ri i = l ; i <= r ; i++)ans+=solve(i) ; cout<<ans<<endl ;
		ans = 0 ;
	}
	return 0 ;
}
/*
*/
/*//El Psy Kongroo
#include<bits/stdc++.h>
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
const int N = 1e2 + 10 , mod = 998244353 , M = 1e8 + 10 ;
inline void pls(int &x,int y){x += y ; if(x >= mod)x -= mod ;}
int b[10]={0,1,4,6,8,9} ;
int f[N][2][3][3][2][2],a[N] ;
int dfs1(int c,int p1,int p2,int p3,int p4,int lim,int tg){
	int res = 0 ;
	if(c==0)return f[c][p1][p2][p3][p4][lim]=!tg ;
	if(f[c][p1][p2][p3][p4][lim]!=-1)return f[c][p1][p2][p3][p4][lim] ;
	for(ri i = 0 ; i < 6 ; i++){
		if(b[i]>a[c]&&lim)break ;
		if(p1&&b[i]==1)continue ;
		if((p2>=2||p3>=2)&&b[i]==1)continue ;
		if(p4&&b[i]==9)continue ;
		if(b[i]==0)pls(res,dfs1(c-1,p1,p2,p3,p4,lim&&b[i]==a[c],tg)) ;
		if(b[i]==1)pls(res,dfs1(c-1,1,p2,p3,1,lim&&b[i]==a[c],0)) ;
		if(b[i]==4)pls(res,dfs1(c-1,1,p2,p3,p4,lim&&b[i]==a[c],tg)) ;
		if(b[i]==6)pls(res,dfs1(c-1,1,p2,p3,p4,lim&&b[i]==a[c],tg)) ;
		if(b[i]==8)pls(res,dfs1(c-1,p1,p2+1,p3,1,lim&&b[i]==a[c],0)) ;
		if(b[i]==9)pls(res,dfs1(c-1,p1,p2,p3+1,p4,lim&&b[i]==a[c],tg)) ;
	}
	return f[c][p1][p2][p3][p4][lim]=res ;
}
bool vis[M] ;
int d[N],num[N]={0,409,449,499,6469,6949,9049,9649,9949,60649,666649,946669,60000049,66000049,66600049},pw[20] ;
int check(int n){
	while(!d[n])n-- ; if(!n)return 1 ;
	for(ri s = 1 , c = 0 , x = 0 ; s < (1 << n) ; s++){
		c = 0 , x = 0 ; for(ri i = 1 ; i <= n ; i++)if(s>>(i-1)&1)x+=pw[c]*d[i] ;
		if(vis[x])return 0 ;
	}
	return 1 ;
}
int dfs2(int c,int len,int lim){
	if(!c)return check(len) ; int res = 0 ;
	if(!lim){
		d[c] = 0 , pls(res,dfs2(c-1,len,0)) ;
		d[c] = 4 , pls(res,dfs2(c-1,len,0)) ;
		d[c] = 6 , pls(res,dfs2(c-1,len,0)) ;
		d[c] = 9 , pls(res,dfs2(c-1,len,0)) ;
	}
	else{
		if(a[c]>=0)d[c] = 0 , pls(res,dfs2(c-1,len,a[c]==0)) ;
		if(a[c]>=4)d[c] = 4 , pls(res,dfs2(c-1,len,a[c]==4)) ;
		if(a[c]>=6)d[c] = 6 , pls(res,dfs2(c-1,len,a[c]==6)) ;
		if(a[c]>=9)d[c] = 9 , pls(res,dfs2(c-1,len,a[c]==9)) ;
	}return res ;
}
char sl[N],sr[N] ; int cl,cr,ansl,ansr,T ;
bool m_ed ;
signed main(){
	pw[0] = 1 ; for(ri i = 1 ; i <= 9 ; i++)pw[i] = pw[i - 1] * 10 ;
	for(ri i = 1 ; i <= 100 ; i++)vis[num[i]] = 1 ;
	read(T) ; while(T--){
		scanf("%s",sl+1) ; cl = strlen(sl + 1) ; for(ri i = 1 ; i <= cl ; i++)a[i] = sl[cl-i+1]-'0' ;
		a[1]-- ; for(ri i = 1 ; i <= cl ; i++)if(a[i]<0)a[i+1]--,a[i]+=10 ; if(!a[cl])cl-- ;
		memset(f,-1,sizeof f) ; ansl = (dfs1(cl,0,0,0,0,1,1) + dfs2(cl,cl,1)) % mod ;
		scanf("%s",sr+1) ; cr = strlen(sr + 1) ; for(ri i = 1 ; i <= cr ; i++)a[i] = sr[cr-i+1]-'0' ;
		memset(f,-1,sizeof f) ; ansr = (dfs1(cr,0,0,0,0,1,1) + dfs2(cr,cr,1)) % mod ;
		printf("%d\n",(ansr+mod-ansl)%mod) ;
	}
	return 0 ;
}*/
/*
1
1 20
*/
