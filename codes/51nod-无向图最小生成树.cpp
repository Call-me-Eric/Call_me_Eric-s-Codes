#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct edge_{
	int u,v,i;
	long long dis;
}e[51001];
int n, m;
long long ans;
int f[10001];
int getf(int x){
	if(x == f[x]){
		return x;
	}
	else {
		f[x] = getf(x);
		return f[x];
	}
}
struct cmp{
	bool operator()(edge_ a,edge_ b){
		return a.dis < b.dis;
	}
};
void merge(int x,int y,int i){
	int t1 = getf(x);
	int t2 = getf(y);	
	if(t2 != t1){
		f[t2] = t1;
		ans += e[i].dis;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= 1001;i++){
		f[i] = i;
	}
	for(int i = 1;i <= m;i++){
		scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].dis);
	}
	sort(e + 1,e + 1 + m,cmp());
	for(int i = 1;i <= m;i++){
		merge(e[i].u,e[i].v,i);
	}
	printf("%lld",ans);
	return 0;
}

