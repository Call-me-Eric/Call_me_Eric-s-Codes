#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
int n, k;long long a[100001];
long long sum;
priority_queue<long long> t;
int main(){
	scanf("%d%d",&n,&k);
	int temp;
	for(int i = 1;i <= n;i++){
		scanf("%lld",&temp);
		t.push(temp);
	}
	long long min = t.top();
	for(int i = 1;i <= k;i++){
		a[i] = t.top();
		t.pop();
	}
	while(!t.empty()){
		min = t.top();
		for(int i = 1;i <= k;i++){
			if(a[i] < min){
				min = a[i];
			}
		}
		for(int i = 1;i <= k;i++){
			if(a[i] == min){
				a[i] = t.top();
				t.pop();
			}
			else a[i] -= min;
		}
		sum += min;
	}
	long long max = -9999;
	for(int i = 1;i <= k;i++){
		if(a[i] > max) max = a[i];
	}
	printf("%lld",sum + max);
	return 0;
}

