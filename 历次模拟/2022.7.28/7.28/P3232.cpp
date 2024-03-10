#include<bits/stdc++.h>
using namespace std;
const int maxn = 501;
int nn, m, st[maxn * maxn], ed[maxn * maxn];
double a[maxn][maxn],ans[maxn],d[maxn * maxn],E[maxn * maxn];
vector<int> e[maxn];
void gauss(int n){
	for(int i = 1;i <= n;i++){
		int Max = i;
		for(int j = i + 1;j <= n;j++){
			if(a[j][i] > a[Max][i]){
				Max = j;
			}
		}
		if(Max != i)
			for(int j = 1;j <= n + 1;j++){
				swap(a[i][j],a[Max][j]);
			}
		if(!a[i][i]){
			puts("No Solution");
			return;
		}
		for(int j = 1 + i;j <= n;j++){
			if(a[i][j]){
				double tmp = a[j][i] / a[i][i];
				for(int k = 1;k <= n + 1;k++){
					a[j][k] -= (a[i][k] * tmp);
				}
			}
		}
	}
	for(int i = n;i > 0;i --){
		for(int j = i + 1;j <= n;j++){
			a[i][n + 1] -= a[i][j] * ans[j];
		}
		ans[i] = a[i][n + 1] / a[i][i];
	}
	return;
}
signed main(){
	scanf("%d%d",&nn,&m);
	int x, y;
	for(int i = 1;i <= m;i++){
		scanf("%d%d",&x,&y);
		e[x].push_back(y);
		e[y].push_back(x);
		d[x] += 1.0;d[y] += 1.0;
		st[i] = x;ed[i] = y;
	}
	for(int i = 1;i < nn;i++){
		a[i][i] = 1.0;
		for(int j = 0,len = e[i].size();j < len;j++){
			if(e[i][j] != nn){
				a[i][e[i][j]] = -1.0 / d[e[i][j]];
			}
		}
	}
	a[1][nn] = 1.0;
	gauss(nn - 1);
	for(int i = 1;i <= m;i++){
		E[i] = ans[st[i]] / d[st[i]] + ans[ed[i]] / d[ed[i]];
	}
	sort(E + 1,E + 1 + m);
	double res = 0;
	for(int i = 1;i <= m;i++){
		res += E[i] * (m + 1.0 - i);
	}
	printf("%.3lf\n",res);
	for(int i = 1;i <= nn;i++){
		printf("f[%d]=%lf\n",i,ans[i]);
	}
	return 0;
}

