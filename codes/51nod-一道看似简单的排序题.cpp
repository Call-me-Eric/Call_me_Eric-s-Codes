#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const long long MOD = (1 << 16) - 1;//65536 = 2 ^ 16 
int n,m;
long long x,y,p;
long long a[10000010];
vector<long long> G[70000];
int main(){
	scanf("%d%d",&n,&m);
	scanf("%lld%lld%lld%lld",&a[0],&x,&y,&p);
	for(int i = 1;i <= n;i++)a[i] = (a[i - 1] * x % p + y) % p;
	int tot = 0;
	for(int i = 0;i < 65536;i++){
		G[i].clear();
	}
	for(int i = 1;i <= n;i++){
		G[(int)(a[i] & MOD)].push_back(a[i]);
	}
	for(int i = MOD;i >= 0;i--){
		for(int j = 0,len = G[i].size();j < len;j++){
			a[++tot] = G[i][j];
		}
		G[i].clear();
	}
	tot = 0;
	for(int i = 1;i <= n;i++){
		G[(int)(a[i] >> 16)].push_back(a[i]); 
	}
	for(int i = MOD;i >= 0;i--){
		for(int j = 0,len = G[i].size();j < len;j++){
			a[++tot] = G[i][j];
		}
		G[i].clear();
	}
	long long ans = 0;
	for(int i = 1;i <= m;i++)ans += a[i];
	printf("%lld",ans);
	return 0;
}
