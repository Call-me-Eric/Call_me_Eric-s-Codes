#include<bits/stdc++.h>
#define read(a) scanf("%d",&a)
using namespace std;
const int N=2e3+5;
int n,m,ans;
int p[N][N],sq[N],vis[N][N];
bool check(int k,int x,int y,int nx,int ny){
	if(p[nx][y]==p[x][ny])  return 0;
	for(int i=1;i<k;i++){
		if(p[nx+i][y]!=p[nx+i-1][y-1]&&p[nx+i][y]==p[nx][y]){
			return 0;
		}
		if(p[x][ny+i]!=p[x-1][ny+i-1]&&p[x][ny+i]==p[x][ny]){
			return 0;
		}
	}
	for(int i=0;i<=k;i++){
//		printf("%d %d %d %d\n",nx+i,y,x,ny+i);
		vis[nx+i][y]=1;
		vis[x][ny+i]=1;
	}
	return 1;
}
int main(){
	freopen("rainbow4.in","r",stdin);
	freopen("rainbow.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			read(p[i][j]);
		}
	}
	ans=n*m;
	for(int i=1;i<=min(n,m);i++)  sq[i]=i*i;
	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){
			if(vis[i][j])  continue;
			vis[i][j]=1;
			for(int k=1;i+k<=n&&j+k<=m;k++){
				if(check(k,i+k,j+k,i,j)){
//					printf("%d %d %d\n",i,j,k);
					ans+=sq[k];
				}
				else{
//					printf("QWQ %d %d %d\n",i,j,k);
					break;
				}
			}
		}
	}
	printf("%d",ans);
}

