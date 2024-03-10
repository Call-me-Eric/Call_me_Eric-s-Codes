#include<bits/stdc++.h>
using namespace std;
int vis[10001][10001];
int main(){
	freopen("up.in","r",stdin);
	freopen("up.out","w",stdout);
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		while(1){
			vis[a][b]++;
			if(a>b){
				a-=b;
			}else if(a<b){
				b-=a;
			}else{
				vis[a][0]++;
				vis[0][a]++;
				break;
			}
		}
	}
	for(int i=1;i<=q;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%d\n",vis[a][b]);
	}
	return 0;
}
