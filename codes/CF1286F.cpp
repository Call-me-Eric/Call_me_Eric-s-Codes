#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 21, maxm = (1 << 20) + 1;
int f[maxm];
int n;ll a[maxn], b[maxn];
ll sl[maxm], sr[maxm];
ll X[maxm], Y[maxm];
void getque(int l,int r,ll *s){
	int m = 1;s[m] = 0;
	for(int i = l;i <= r;i++,m <<= 1){
		for(int j = 1;j <= m;j++){X[j] = s[j] - b[i];Y[j] = s[j] + b[i];}
		int x = 1, y = 1, k = 1;
		while(x <= m && y <= m){
			if(X[x] < Y[y]){s[k] = X[x++];}
			else s[k] = Y[y++];
			k++;
		}
		while(x <= m){s[k] = X[x++];k++;}
		while(y <= m){s[k] = Y[y++];k++;}
	}
}
bool check(int sta){
	int siz = 0;ll sum = 0;
	for(int i = 1;i <= n;i++){if((sta >> (i - 1)) & 1){b[++siz] = a[i];sum += a[i];}}
	if((sum - (siz - 1)) & 1)return false;
	getque(1,siz / 2,sl);getque(siz / 2 + 1,siz,sr);
	int L = 1 << (siz / 2), R = 1 << (siz - siz / 2),need = 1 + (abs(sum) < siz) * 2;
	for(int i = R, j = 1;i;i--){
		while(j <= L && sl[j] + sr[i] <= -siz)j++;
		for(int k = j;k <= L && need && sl[k] + sr[i] < siz;k++)need--;
//		if(!need)return true;
	}
	return !need;
}
signed main(){
	n = read();int m = 0;
	for(int i = 1;i <= n;i++){
		a[i] = read();
		if(a[i])a[++m] = a[i];
	}
	n = m;
	for(int i = 0;i < (1 << n);i++){
		if(!f[i] && check(i)){
			int rest = ((1 << n) - 1) ^ i;f[i] = 1;
			for(int s = rest;s;s = ((s - 1) & rest))
				f[i | s] = max(f[i | s],f[s] + 1);
		}
	}
	printf("%d\n",n - f[(1 << n) - 1]);
	return 0;
}
