#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + ch - '0'; ch = getchar();}
	return x * f;
}
int qpow(int x,int a,int mod){
	int res = 1;
	while(a){
		if(a & 1)res = (res * x) % mod;
		a >>= 1; x = (x * x) % mod;
	}
	return res;
}
const int maxm = 60;
int n, m;
int p[maxm], q[maxm];
int s, k;
bool check(){
	int ans = sqrt(s + n * k);
//	printf("ans = %lld\n",ans);
	for(int i = 1;i <= m;i++){
//		printf("check()%lld == %lld\n",qpow(ans,p[i],n),q[i]);
		if(qpow(ans,p[i],n) != q[i])return true;
	}
	return false;
}
signed main(){
	freopen("judgement.in","r",stdin);
	freopen("judgement.out","w",stdout);
int T = read();
for(int tes = 1;tes <= T;tes++){
	m = read();n = 1;bool flag = true;
	for(int i = 1;i <= m;i++){
		p[i] = read(); q[i] = read();
		n *= p[i];
	}
	s = qpow(q[1],n / p[1],n), k = 0;
	for(int i = 2;i <= m;i++){
		if(s != qpow(q[i],n / p[i],n)){flag = false;break;}
	}
//	printf("s = %lld\n",s);
	if(flag){
		while(((sqrt(s + n * k) * sqrt(s + n * k) != (s + n * k)) ? 1 : check()) && k <= 1e7 / T)k++;
		if(k >= 1e7 / T)puts("-1");
		else printf("%lld\n",(int)sqrt(s + n * k) % n);
//		printf("k = %lld\n",k);
	}
	else{
		puts("-1");
	}
}
	return 0;
}
