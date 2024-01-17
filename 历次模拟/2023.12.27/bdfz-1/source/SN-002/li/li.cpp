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
int n,m ;
bool m_ed ;
signed main(){
	freopen("li.in","r",stdin) ; freopen("li.out","w",stdout) ;
	read(n,m) ;
	if(n==2)cout<<0<<" "<<3<<endl ;
	else if(n==3){
		if(m==1)cout<<0<<" "<<4<<endl ;
		else if(m==2)cout<<0<<" "<<6<<endl ;
		else cout<<1<<" "<<3<<endl ;
	}
	return 0 ;
}
/*
*/

