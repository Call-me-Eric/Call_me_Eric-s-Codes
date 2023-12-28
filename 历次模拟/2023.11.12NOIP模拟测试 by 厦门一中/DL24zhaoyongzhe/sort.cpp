#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e5 + 10;
int n, a[maxn], b[maxn];
signed main(){
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	n = read();for(int i = 1;i <= n;i++)a[i] = read();
	int ans = 0;
	for(int l = 1;l <= n;l++)
		for(int r = l + 1;r <= n;r++){
			for(int i = l;i <= r;i++)b[i] = a[i];
			sort(b + l,b + r + 1);
			int suma = 0, sumb = 0;
			for(int i = l;i <= r;i++){
				suma += a[i]; sumb += b[i];
				if(suma != sumb || a[i] != b[i])ans++;
			}
//			printf("l = %lld, r = %lld, ans = %lld\n",l,r,ans);
//			for(int i = l;i <= r;i++)printf("%lld ",b[i]);
//			puts("");
		}
	printf("%lld\n",ans);
	return 0;
}
