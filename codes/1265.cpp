#include <cstdio>
#include <cstring>
using namespace std;
char s1[1005], s2[1005];
int dp[1005][1005];
int max(int a, int b){return a > b ? a : b;}
int min(int a, int b){return a < b ? a : b;}
int main() {
	scanf("%s%s",s1,s2);
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	for(int i = 1;i <= len1;i++){
		for(int j = 1;j <= len2;j++){
			dp[i][j] = s1[i - 1] == s2[j - 1] ?
			dp[i - 1][j - 1] + 1 :
			max(dp[i][j - 1], dp[i - 1][j]);
		} 
	}
	printf("%d\n",dp[len1][len2]);
	return 0;
}

