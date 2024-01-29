#include<iostream>
#include<cstdio>
using namespace std;
int n, m;
int q;
int a[1000040];
int func(){
	int l = 1, r = n, mid = 0;
	while(l < r){
		mid = l + (r - l) / 2;
		if(a[mid] >= q){
			r = mid;
		}
		else{
			l = mid + 1;
		}
	}
	if(a[l] == q)return l;
	else return -1;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
	}
	for(int i = 1;i <= m;i++){
		scanf("%d",&q);
		printf("%d ",func());
	}
	return 0;
} 
