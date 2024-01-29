#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long a, b;
long long power10[20];
long long l[11], r[11];
void sum(long long n,long long* p){
	long long hpos,lpos,i,j,rest,all,tmp = 0;
	if(n == 0)return;
	for(i = 0;n >= power10[i];i++){
		rest = n % power10[i + 1];
		hpos = rest / power10[i] + 0;
		lpos = rest % power10[i] + 1;
		all += n / power10[i + 1] * power10[i];
		for(j = 0;j < hpos;j++)p[j] += power10[i];
		p[0] -= power10[i];
		p[hpos] += lpos;
	}
	for(j = 0;j < 10;j++)p[j] += all;
}
int main(){
	int i;
	for(power10[0] = 1,i = 1;i < 19;i++)power10[i] = power10[i - 1] * 10;
	power10[19] = power10[18] * 2;
	while(scanf("%lld%lld",&a,&b) != EOF){
		sum(a - 1,l);
		sum(b,r);
		for(int i = 0;i <= 9;i++){
			printf("%lld\n",r[i] - l[i]);
		}
	}
	return 0;
}

