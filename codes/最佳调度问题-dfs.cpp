#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int n, k;
long long ans = 99999999999;
long long a[1000001],b[1000001];
struct cmp{
	bool operator()(int a,int b){
		return a > b;
	}
};
inline void dfs(int step,long long res){
	if(step == 1 + n){
		ans = min(ans,res);
		return;
	}
	if(res >= ans)return; //×îÓÅ»¯1  
	for(int i = 1;i <= k;i++){
		if(b[i] == b[i - 1] && i > 1) continue;
		b[i] += a[step];
		
		dfs(step + 1,max(res, b[i]));
		b[i] -= a[step];
	}
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= n;i++){
		scanf("%lld",&a[i]);
	}
	sort(a + 1,a + 1 + n,cmp());
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}

