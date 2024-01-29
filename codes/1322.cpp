#include <cstdio>
int a[1001], n = 1, l[1001], k, flag;
int main() {
	while(scanf("%d",&a[n]) != EOF)n++;
	n--;	k = 1;	  l[1] = a[1];
	for(int i = 2;i <= n;i++){
		flag = 0;
		for(int j = 1;j <= k;j++){
			if(l[j] >= a[i]){
				if(flag){
					if(l[flag] > l[j]){
						flag = j;
					}
				}
				else flag = j;
			}
		}
		if(!flag){
			k++;
			l[k] = a[i];
		}
		else l[flag] = a[i];
	}
	printf("%d\n",k);
	return 0;
}

