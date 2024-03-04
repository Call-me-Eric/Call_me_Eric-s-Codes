#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define re register
#define int long long
#define rep(a,b,c)  for(re int a(b) ; a<=c ; ++a)
#define drep(a,b,c) for(re int a(b) ; a>=c ; --a)
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
const int M = 2e5+10;
const int mod = 4294967296;
char a[M];
int jishu1[M],jishu2[M];
int n,m,cnt,tot1,tot2;
inline int work(int x,int y){
	int res = 0;
	rep(i,x,y){
		if(a[i] == 'w'){
			cnt = 0;tot1 = 0;
			for(re int j(i-1) ; j>=x ; --j){
				if(a[j] == '0') cnt++;
				if(a[j] == '(') jishu1[++tot1] = cnt;
			}
			cnt = 0;tot2 = 0;
			for(re int j(i+1) ; j<=y ; ++j){
				if(a[j] == '0') cnt++;
				if(a[j] == ')') jishu2[++tot2] = cnt;
			}
			for(re int j(1) ; j<=tot1 ; ++j){
				for(re int k(1) ; k<=tot2 ; ++k){
					res = (res+jishu1[j]*jishu2[k])%mod;
				}
			}
		}
	}
	return res%mod;
}
signed main(){
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","r",stdout);
	n=read(),m=read();
	rep(i,1,n) cin >> a[i];
	while(m--){
		char xx;
		cin >> xx;
		if(xx == 'A'){
			int pos=read();
			char ch;
			cin >> ch;
			a[pos] = ch;
		}
		if(xx == 'B'){
			int x=read(),y=read();
			char ch;
			cin >> ch;
			rep(i,x,y) a[i] = ch;
		}
		if(xx == 'C'){
			int x=read(),y=read();
			printf("%lld\n",work(x,y)%mod);
		}
	}
	return 0;
}

/*
7 4
(0w0#))
C 1 6
B 5 6 w
A 6 0
C 1 7
*/
