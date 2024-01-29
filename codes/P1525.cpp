#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[300000], b[300000];//a[i]是i的父亲(朋友),b[i]是i的敌人 
int n, m;
struct struct_{
	int a, b, c;
}f[300000];
int getf(int i){
	if(a[i] == i)return i;
	else {
		a[i] = getf(a[i]);
		return a[i];
	}
}
struct cmp{
	bool operator()(struct_ a, struct_ b){
		return a.c > b.c;
	}
};
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		a[i] = i;
	}
	for(int i = 1;i <= m;i++){
		scanf("%d%d%d",&f[i].a,&f[i].b,&f[i].c);
	}
	sort(f + 1,f + 1 + m, cmp());
	for(int i = 1;i <= m + 1;i++){
		if(getf(f[i].a) == getf(f[i].b)){
			printf("%d",f[i].c);
			break;
		}
		if(!b[f[i].a]) b[f[i].a] = f[i].b;
		else a[getf(b[f[i].a])] = getf(f[i].b);
		
		if(!b[f[i].b]) b[f[i].b] = f[i].a;
		else a[getf(b[f[i].b])] = getf(f[i].a);
	}
	return 0;
}

