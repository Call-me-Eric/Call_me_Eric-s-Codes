#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
#define ll long long
using namespace std;
int n;
const int maxn = 1e5 + 10,maxc = 1e4 + 10;
int tot[maxc];
ll s[maxn],c[maxn],f[maxn];
/*int s[maxn],f[maxn];
vector<int> v[maxn];
*/
vector<int> stk[maxc];
inline ll Y(int i){return f[i - 1] + s[i] * c[i] * c[i] - 2 * s[i] * c[i];}
inline double slope(int i, int j){return 1.0 * (Y(i) - Y(j)) / (c[i] - c[j]);}//work out k
inline ll calc(int i, int j){return f[j - 1] + s[i] * (c[i] - c[j] + 1) * (c[i] - c[j] + 1);}

signed main(){
	scanf("%d",&n);
	/*90pts
	for(int i = 1;i <= n;i++){
		scanf("%lld",&s[i]);
		int len = v[s[i]].size();
		if(len){
			for(int j = 0;j < len;j++){
				f[i] = max(f[i],f[v[s[i]][j] - 1] + (long long)s[i] * (len - j + 1) *(len - j + 1));
			}
		}
		f[i] = max(f[i],f[i - 1] + s[i]);
		v[s[i]].push_back(i); 
	}*/
	//100pts
	for(int i = 1;i <= n;i++){
		scanf("%lld",&s[i]);
		c[i] = ++tot[s[i]];
	}
	for (int i = 1; i <= n; ++i) {
		int t = s[i];
		while(stk[t].size() >= 2 && slope(stk[t][stk[t].size() - 2], i) >= slope(stk[t][stk[t].size() - 2], stk[t][stk[t].size() - 1]))
					stk[t].pop_back();//cmp k:斜率优化 
		stk[t].push_back(i);
		while (stk[t].size() >= 2 && calc(i, stk[t][stk[t].size() - 1]) <= calc(i, stk[t][stk[t].size() - 2]))
					stk[t].pop_back();//cmp f[i]:合理性优化 
		f[i] = calc(i, stk[t][stk[t].size() - 1]);
	}
	printf("%lld\n",f[n]);
	return 0;
}

