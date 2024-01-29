#include<cstring>
#include<cstdio>
using namespace std;
const int maxn = 10000000;
const int maxs = 10000;

int n;
int a[maxn], b[maxn], res[maxn], ord[maxn];
int cnt[maxs + 1];

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d%d", &a[i], &b[i]);
	}
	memset(cnt,0,sizeof(cnt));
	for(int i = 0;i < n;i++){
		++cnt[b[i]];//1
	}
	for(int i = 0;i < maxs;i++){
		cnt[i + 1] += cnt[i];
	}
	for(int i = 0;i < n;i++){
		ord[--cnt[b[i]]] = i;//2
	}
	
	
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0;i < n;i++){
		++cnt[a[i]];//3
	}
	for(int i = 0;i < maxs;i++){
		cnt[i + 1] += cnt[i];
	}
	for(int i = n - 1;i >= 0;i--){
		res[--cnt[a[ord[i]]]] = ord[i];//4
	}
	for(int i = 0;i < n;i++){
		printf("%d %d\n",a[res[i]],b[res[i]]);//5
	}
	return 0;
}
