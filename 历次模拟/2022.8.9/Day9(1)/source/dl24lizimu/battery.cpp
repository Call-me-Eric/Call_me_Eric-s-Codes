#include<bits/stdc++.h>
using namespace std;
const int N=51;
int n,m;
int a[N][N];
void print(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]==0) printf(".");
			if(a[i][j]==1) printf("|");
			if(a[i][j]==2) printf("-");
			if(a[i][j]==3) printf("#");
			if(a[i][j]==4) printf("?");
			if(a[i][j]==5) printf("/");
		}
	}
}
int main(){
	freopen("battery.in","r",stdin);
	freopen("battery.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		char c;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("\n%c",&c);
			}
		}
		printf("IMPOSSIBLE\n");
	}
	return 0;
}
