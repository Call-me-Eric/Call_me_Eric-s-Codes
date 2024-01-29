#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 200;
int out[maxn];
int in[maxn];
bool book[maxn][maxn];
int mp[maxn][maxn];
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&out[i]);
	}
	for(int i = 1;i <= n;i++){
		int tmp = out[i];
		for(int j = 1;tmp && j <= n;j++){
			if(i == j){
				continue;
			}
			if(!book[i][j] && n - 1 - in[j] - out[j] > 0){
				in[j]++;
				tmp--;
				book[i][j] = book[j][i] = 1;
				mp[i][j] = 1;
			}
		}
	}
	for(int i = 1;i <= n;i++){
		mp[i][i] = 1;
	}
	for(int k = 1;k <= n;k++){
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				if(mp[i][k] && mp[k][j]){
					mp[i][j] = 1;
				}
			}
		}
	}
	int ans = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			ans += mp[i][j];
		}
	}
	printf("%d\n",ans);
	return 0;
}