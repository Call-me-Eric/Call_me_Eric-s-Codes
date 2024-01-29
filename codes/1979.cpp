#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int n;
long long a[100001];
long long m, p1, s1, s2;
long long p2;
long long sum1, sum2;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
	}
	scanf("%lld%lld%lld%lld",&m,&p1,&s1,&s2);
	a[p1] += s1;
	
	for(int i = 1;i <= n;i++){
		if(i < m)sum1 += a[i] * (m - i);
		else if(i == m)continue;
		else sum2 += a[i] * (i - m);
	}
	long long cha = abs(sum1 - sum2);
	bool flag = true;
	if(sum1 > sum2){
		for(int i = n;i >= m + 1;i--){
			if(abs( (sum2 + s2 * (i - m) - sum1) ) < cha){
				p2 = i;
				cha = abs((sum2 + s2 * (i - m) - sum1));
				flag = false; 
			}
		}
	}
	else if(sum2 > sum1){
		for(int i = m - 1;i >= 1;i--){
			if(abs( (sum1 + s2 * (m - i) - sum2) ) < cha){
				p2 = i;
				cha = abs((sum2 + s2 * (i - m) - sum1));
				flag = false;
			}
		}
	}
	if(sum1 == sum2 || flag)p2 = m;
	printf("%lld",p2);
	return 0;
}
