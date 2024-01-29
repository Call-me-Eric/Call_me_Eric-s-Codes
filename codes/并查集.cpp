#include<cstdio>
#include<iostream>
using namespace std;
int f[101];
int getf(int v){
	printf("v=%d\n", v);
	if(f[v] == v){
		return v;
	}
	else{
		f[v] = getf(f[v]);
		return f[v];
	}
}
void merge(int x,int y){
	int t1 = getf(x);
	int t2 = getf(y);
	if(t2 != t1){
		f[t2] = t1;
	}
}
int main(){
	int x[20], y[20], n, i,m;
	for(i = 0;i <= 50;i++){
		f[i] = i;
	}
	scanf("%d%d",&n,&m);
	for(i = 1;i <= m;i++){
		scanf("%d%d",&x[i],&y[i]);
	}
	for(i = 1;i <= m;i++){
		merge(x[i],y[i]);printf("i=%d:\n",i);
		for(int j = 1;j <= n;j++){
			printf("f[%d]=%d\n",j,f[j]);
		}
	}
	int sum = 0;
	for(i = 1;i <= n;i++){
		if(f[i] == i){
			sum++;
		}
	}
	printf("%d",sum);
	return 0;
}

