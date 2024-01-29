//此程序时间复杂度为O(n * log n)(n为加油站数目) 
#include<cstdio>
#include<queue>
#include<algorithm>
#define LL long long
using namespace std;
priority_queue<LL> que;
LL n, l, p;
LL k, ans;
LL t1, t2, a[10000001], b[100001];
//对于在i点的加油站,a[i] = 汽油量 b[序号] = i 
int main(){
	k = 0;
	scanf("%lld%lld%lld",&l,&p,&n);
	for(int i = 1;i <= n;i++){
		scanf("%lld%lld",&t1,&t2);
		a[t1] = t2;
		b[i] = t1;
	}
	sort(b + 1,b + 1 + n);
	for(int i = 1;i <= n;i++){
		if(p < b[i] - k){
			//如果油不够到下一个加油站
			if(que.empty()){
				printf("-1");
				return 0;
				//还不可加油就结束程序 
			}
			else {
				while(p < b[i] - k){//可加油就加到足够为止 
					p += que.top();
					que.pop();
					ans++;
				}
				p = p - b[i] + k;
				k = b[i];
				que.push(a[b[i]]);
			}
		}
		else{//油够的话 
			p = p - b[i] + k;
			k = b[i];
			que.push(a[b[i]]);
		}
	}
	if(k < l){
		k += p;
		p = 0;
		while(k < l && (!que.empty())){
			k += que.top();
			que.pop();
			ans++;
		}
		if(k < l && que.empty()){
			printf("-1");
			return 0;
		}
	}
	printf("%lld",ans);
	return 0;
}
