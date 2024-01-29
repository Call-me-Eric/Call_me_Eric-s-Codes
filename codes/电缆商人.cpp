#include <cstdio>
#include <algorithm>
using namespace std;
int n, m;
double s;
int f[100005];
double sum;
struct asdf{
	int x, y;
	double s;
}	a[100005];
struct cmp{
	bool operator()(asdf a,asdf b){
		return a.s < b.s;
	}
};

int getf(int x){
	if(x == f[x])return x;
	else {
		x = getf(f[x]);
		return x;
	}
}
bool _merge(int x, int y){
	int x1 = getf(x);
	int y1 = getf(y);
	if(x1 != y1){
		f[x1] = y1;
		return true;
	}
	return false;
}
int main() {
	int cnt = 0;
	scanf("%lf",&s);
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++)f[i] = i;
	for(int i = 1;i <= m;i++){
		scanf("%d%d%lf",&a[i].x,&a[i].y,&a[i].s);
	}
	sort(a + 1,a + 1 + m, cmp());
	//KruskalºËÐÄ´úÂë
	for(int i = 1;i <= m;i++){
		if(_merge(a[i].x,a[i].y)){
			sum += a[i].s;
			cnt++;
		}
		if(cnt == n - 1)break;
	} 
	///////end///////
	if(s < sum || m < n - 1)printf("Impossible");
	else printf("Need %.2lf miles of cable",sum);
	return 0;
}

