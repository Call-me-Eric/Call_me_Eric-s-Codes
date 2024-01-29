#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
struct note{
	int s;
	int w;
	int d;
	int c;
}a[20010];
struct cmp{
	bool operator ()(note a,note b){
		if(a.w == b.w)return a.s < b.s;
		else return a.w > b.w;
	}
};

int n, k;
int e[11];
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1;i <= 10;i++)
		scanf("%d",&e[i]);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i].w);
		a[i].s = i;
	}
	sort(a + 1, a + 1 + n, cmp());
	for(int i = 1;i <= n;i++){
		a[i].d = i;
		a[i].c = (a[i].d - 1) % 10 + 1;
		a[i].w += e[a[i].c];
	}
	sort(a + 1, a + 1 + n,cmp());
	for(int i = 1;i <= k;i++){
		printf("%d ",a[i].s);
	}
	puts("");
	return 0;
}

