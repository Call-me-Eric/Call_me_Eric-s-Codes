#include <bits/stdc++.h>

int main(){
	freopen("ur.in","r",stdin);
	freopen("ur.out","w",stdout);
	int n,k; scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++) putchar('0'+(n==k));
	return 0;
}