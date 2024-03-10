#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
int n, m, v, e;
const int maxn = 2020;
double dis[maxn][maxn];
double dp[maxn][maxn][2];
int c[maxn], d[maxn];
double k[maxn];
int main(){
	int x, y;
	double z;
	scanf("%d%d%d%d",&n,&m,&v,&e);
	for(int i = 1;i <= n;i++)scanf("%d",&c[i]);
	for(int i = 1;i <= n;i++)scanf("%d",&d[i]);
	for(int i = 1;i <= n;i++)scanf("%lf",&k[i]);
	for(int i = 1;i <= v;i++){
		dis[i][i] = 0;
		for(int j = 1;j < i;j++){
			dis[i][j] = dis[j][i] = 0x3f3f3f3f;
		}
	}
	for(int i = 1;i <= e;i++){
		scanf("%d%d%lf",&x,&y,&z);
		dis[x][y] = min(dis[x][y],z);
		dis[y][x] = dis[x][y];
	}
	for(int kk = 1;kk <= v;kk++){
		for(int i = 1;i <= v;i++){
			for(int j = 1;j < i;j++){
				if(dis[i][j] > dis[i][kk] + dis[kk][j]){
					dis[i][j] = dis[i][kk] + dis[kk][j];
					dis[j][i] = dis[i][j];
				}
			}
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 0;j <= m;j++){
			for(int k = 0;k <= 1;k++){
				dp[i][j][k] = 0x3f3f3f3f;
			}
		}
	}
	dp[1][0][0] = 0.0;dp[1][1][1] = 0.0;
	for(int i = 2;i <= n;i++){
		for(int j = 0;j <= m && j <= i;j++){
			dp[i][j][0] = min(dp[i - 1][j][0]
						    + dis[c[i - 1]][c[i]]
			 				 ,dp[i - 1][j][1]
						    + dis[c[i - 1]][c[i]] * (1.0 - k[i - 1])
						    + dis[d[i - 1]][c[i]] * k[i - 1]);
			 if(j >= 1){
			 	dp[i][j][1] = min(dp[i - 1][j - 1][0]
				 			    + dis[c[i - 1]][d[i]] * k[i]
							    + dis[c[i - 1]][c[i]] * (1.0 - k[i]),
				 				  dp[i - 1][j - 1][1] + 
								  dis[d[i - 1]][d[i]] * k[i] * k[i - 1]
							    + dis[d[i - 1]][c[i]] * k[i - 1] * (1.0 - k[i])
							    + dis[c[i - 1]][d[i]] * (1.0 - k[i - 1]) * k[i]
							    + dis[c[i - 1]][c[i]] * (1.0 - k[i - 1]) * (1.0 - k[i]));
			 }
		}
	}
	double ans = 0x3f3f3f3f;
	for(int i = 0;i <= m;i++){
		for(int j = 0;j <= 1;j++){
			ans = min(dp[n][i][j],ans);
		}
	}
	printf("%.2lf\n",ans);
	return 0;
}

