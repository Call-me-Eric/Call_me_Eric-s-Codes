#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x = 0, f=  1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f  =-1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 2100;
int f[maxn][maxn];
struct node{
	int first, second;
	node(int f = 0,int s = 0):first(f),second(s){}
	friend bool operator < (node a,node b){return a.first != b.first ? a.first < b.first : a.second < b.second;}
	friend bool operator > (node a,node b){return a.first != b.first ? a.first > b.first : a.second > b.second;}
}a[maxn];
int sum[maxn], n, t;
int x[maxn];
signed main(){
	freopen("distanced.in","r",stdin);
	freopen("distanced.out","w",stdout);
	n = read(); t = read();
	for(int i = 1;i <= n;i++){x[i] = read();}
	for(int i = 1;i <= n;i++){a[i] = node(x[i],read());}
	sort(a + 1,a + 1 + n); memset(f,-0x3f,sizeof(f));for(int i = 0;i <= n;i++){f[i][0] = 0;}
	for(int i = 1;i <= n;i++)sum[i] = sum[i - 1] + a[i].second;
	for(int s = 1;s <= n;s++)
	for(int i = 1;i <= n;i++){
		for(int j = i;j >= 1 && (a[i].first - a[j].first <= t);j--){
			for(int k = j - 1;k >= 0;k--){
				if(a[j].first - a[k].first <= t){
					f[i][s] = max(f[i][s],f[k][s] + sum[i] - sum[j - 1]);
					f[i][s] = max(f[i][s],f[k][s - 1] + sum[i] - sum[j - 1]);
				}else{
					f[i][s] = max(f[i][s],f[k][s - 1] + sum[i] - sum[j - 1]);
				}
			}
		}
	}
	int ans = -0x3f3f3f3f3f3f3f3f;
	for(int s = 1;s <= n;s++){
		for(int i = 1;i <= n;i++){ans = max(ans,f[i][s]);}
		printf("%lld ",ans);
	}
	return 0;
}
