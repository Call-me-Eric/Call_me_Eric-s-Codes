#include<bits/stdc++.h>
using namespace std;
const int N=1000;
int a[N][N];
int n,m;
int main(){
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	int cnt=0;
	for(int sz=0;sz<=min(n,m);sz++){
		for(int i=1;i+sz<=n;i++){
			for(int j=1;j+sz<=m;j++){
				int flag=1;
				for(int i1=i;i1<=i+sz;i1++){
					if(!flag) break;
					for(int i2=i;i2<=i+sz;i2++){
						if(!flag) break;
						for(int j1=j;j1<=j+sz;j1++){
							if(!flag) break;
							for(int j2=j;j2<=j+sz;j2++){
								if(!flag) break;
								if(i1-i2==j1-j2&&a[i1][j1]!=a[i2][j2]) flag=0;
								if(i1-i2!=j1-j2&&a[i1][j1]==a[i2][j2]) flag=0;
							}
						}
					}
				}
				if(flag) cnt++;
			}
		}
	}
	printf("%d",cnt);
	return 0;
}
