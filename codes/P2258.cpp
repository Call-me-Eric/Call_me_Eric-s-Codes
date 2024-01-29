#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int n, m, r, c;
int ans = 1e9, minn;//ansΪ���Ľ�,minnΪDP������ 
int line_score[20];
int difference[20][20];
int array[20][20];
int dp[20][20];//dp[i][j]��ʾ��ǰi����ѡ��j�� 
int q[20];//�洢ѡ�����ĸ��� 
void dfs(int a,int b){
	if(b == r + 1){
		for(int j = 1;j <= m;j++){
			line_score[j] = 0;
			for(int i = 2;i <= r;i++){
				line_score[j] += abs(array[q[i - 1]][j] - array[q[i]][j]);
			}
		}
		for(int j = 1;j <= m;j++){
			for(int k = 1;k <= m;k++){
				difference[j][k] = 0;
				for(int i = 1;i <= r;i++){
					difference[j][k] += abs(array[q[i]][j] - array[q[i]][k]);
				}	
			}
		}
		for(int i = 1;i <= 19;i++){
			memset(dp[i],1,sizeof(dp[i]));
		}
		for(int i = 1;i <= m;i++){//dp
			minn = min(i,c);
			for(int j = 1;j <= minn;j++){
				for(int k = j - 1;k < i;k++){//����һ������ĵ�0�п��Բ�������(����+N�д���) 
					dp[i][j] = min(dp[i][j],dp[k][j - 1] + line_score[i] + difference[k][i]);
				}
				if(j == c){
					ans = min(ans, dp[i][j]);
				}	
			}
		}
		return;
	}
	if(a > n)return;
	q[b] = a;
	dfs(a + 1,b + 1);
	dfs(a + 1,b);
}

int main(){
	scanf("%d%d%d%d",&n,&m,&r,&c);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d",&array[i][j]);
		}
	}
	dfs(1,1);
	printf("%d",ans);
	return 0;
}
