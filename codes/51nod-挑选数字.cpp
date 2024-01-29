#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n, m;
int a[41];
int b[41];
int total;
bool flag = false;
void dfs(int pos,int sum,int choosed,int not_cho){
	if(flag == true)return;
	if(sum == m){
		flag = true;
		for(int i = 1;i < choosed;i++){
			printf("%d ",b[i]);
		}
		return;
	}
	if(pos > n)return;
	if(sum > m || total - not_cho < m)return;
	for(int i = pos;i <= n;i++){
		b[choosed] = a[i];
		dfs(i + 1,sum + a[i],choosed + 1,not_cho);
		not_cho += a[i];
	}
	return;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		total += a[i];
	}
	sort(a + 1,a + 1 + n);
	dfs(1,0,1,0);
	if(!flag)printf("No Solution");
	return 0;
}

