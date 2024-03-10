#include <bits/stdc++.h>
using namespace std;

int t;
int n,m;
char c[55];
int a[55][55];

int main(){
	
	freopen("battery.in","r",stdin);
	freopen("battery.out","w",stdout);
	
	scanf("%d",&t);
	
	for(int z=1;z<=t;z++){
		
		scanf("%d%d",&n,&m);
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%s",c+1);
			}
			for(int j=1;j<=m;j++){
				if(c[j]=='-'){
					a[i][j]=1;
				}
				if(c[j]=='|'){
					a[i][j]=2;
				}
				if(c[j]=='.'){
					a[i][j]=0;
				}
				if(c[j]=='#'){
					a[i][j]=3;
				}
			}
		}
	}
	
	return 0;
}
