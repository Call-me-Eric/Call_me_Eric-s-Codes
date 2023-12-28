#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
const int maxm = 1.5e7 + 10,maxn = 3e5 + 10;
int n, pn, a[maxn],p[maxm],m[maxm];
bool book[maxm];
int cnt[maxm];
int gcd(int x,int y){return y == 0 ? x : gcd(y,x % y);}
int main(){
	scanf("%d",&n);
	scanf("%d",&a[1]);
	int mingcd = a[1],Max = -1;
	for(int i = 2;i <= n;i++){
		scanf("%d",&a[i]);
		mingcd = gcd(mingcd,a[i]);
	}
	for(int i = 1;i <= n;i++){
		a[i] /= mingcd;
		Max = max(Max,a[i]);
		cnt[a[i]]++;
	}
	for(int i = 2;i <= Max;i++){
		if(!book[i]){
			p[++pn] = i;
		}
		for(int j = 1;i * p[j] <= Max && j <= pn;j++){
			book[i * p[j]] = 1;
			if(i % p[j] == 0)break;
		}
	}
	int ans = 0;
	for(int i = 1;i <= pn;i++){
		int res = 0;
		for(int j = 1;j * p[i] <= Max;j++)res += cnt[j * p[i]];
		ans = max(ans,res);
	}
	if(ans == 0){
		puts("-1");
		return 0;
	}
	printf("%d\n",n - ans);
	return 0;
}
