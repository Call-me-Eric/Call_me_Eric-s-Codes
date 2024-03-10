#include<bits/stdc++.h>
using namespace std;
int T, n;
int x, y;
signed main(){
	scanf("%d",&T);
	while(T--){
		x = y = 0;
		scanf("%d",&n);
		scanf("%d",&x);
		for(int i =1 ;i < n;i++){
			scanf("%d",&y);
			x ^= y;
		}
		puts(x ? "Yes" : "No");
	}
	return 0;
}

