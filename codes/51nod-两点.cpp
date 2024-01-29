#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n, m;
int fa[100001];
char a[101][101];
int getf(int x){
	if(fa[x] == x)return x;
	else return fa[x] = getf(fa[x]);
}
int main(){
	while(scanf("%d%d",&n,&m) != EOF){
		for(int i = 1;i <= n * m + 1;i++){
			fa[i] = i;
		}
		for(int i = 0;i < n;i++)memset(a[i],0,sizeof(a[i]));
		for(int i = 0;i < n;i++){
			scanf("%s",a[i]);
		}
		bool flag = false;
		for(int i = 0;i < n;i++){
			for(int j = 0;j < m;j++){
				if(i > 0 && a[i][j] == a[i - 1][j]){
					int f1 = getf(i * m + j), f2 = getf(i * m + j - m);
					if(f1 == f2)flag = 1;
					else fa[f1] = f2;
				}
				if(j > 0 && a[i][j] == a[i][j - 1]){
					int f1 = getf(i * m + j), f2 = getf(i * m + j - 1);
					if(f1 == f2)flag = 1;
					else fa[f1] = f2;
				}
			}
		}
		if(flag)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

