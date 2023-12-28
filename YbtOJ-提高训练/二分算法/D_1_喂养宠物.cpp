#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 3) + (x << 1) + ch - '0';ch = getchar();}
	return x * f;
}
int n,totalfood;
const int maxn = 55;
int a[maxn],greed[maxn], hunger[maxn];
bool check(int mid){
	for(int i = 1;i <= n;i++){a[i] = greed[i] * (mid - 1) + hunger[i];}
	sort(a + 1,a + 1 + n); int tot = 0;
	for(int i = 1;i <= mid;i++){
		tot += a[i];
	}
	return tot <= totalfood;
}
signed main(){
	n = read(); totalfood = read();
	for(int i = 1;i <= n;i++){
		hunger[i] = read();
	}
	for(int i = 1;i <= n;i++){
		greed[i] = read();
	}
	int l = 0, r = n,ans = 0;
	while(l + 1 < r){
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid;
		else r = mid;
	}
	printf("%d\n",l);
	return 0;
}
