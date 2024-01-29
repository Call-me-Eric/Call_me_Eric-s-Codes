#include<cstdio>
#include<cstdlib>
#include<cmath>
using namespace std;
int n, m;
int a[10001], k[10001];
bool flag = 1,book[10001];
int ans;
int t;
void dfs(int);
int main(){
	int t = 0;
	scanf("%d%d",&n, &m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&k[i]);
	}
	dfs(1);
	return 0;
}
void dfs(int step){
	if(t == 2) return;
	if(step == n + 1){
		ans++;
		if(ans == m + 1){
			for(int i = 1;i < n;i++){
				printf("%d ",a[i]);
			}
			printf("%d",a[n]);
			t = 2;
			return;
		}
	}
	for(int i = 1;i <= n;i++){
		if(ans == 0){
			i = k[step];
		} 
		if(book[i])continue;
			book[i] = 1;
			a[step] = i;
			dfs(step + 1);
			book[i] = a[step] = 0;
	}
	return;
}
