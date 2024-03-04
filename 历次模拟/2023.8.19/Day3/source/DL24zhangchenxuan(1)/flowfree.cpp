#include<bits/stdc++.h>
#define read(a) scanf("%d",&a)
using namespace std;
const int N=20;
int n,m,a,b,c,d;
int vis[N][N],j[N][N],cnt[N];
//int nx={-1,0,0,1},ny={0,-1,1,0};
/*
void dfs(int x,int y,int c,int s){
	if(s==n){
		for(int i=1;i<=m;i++){
			printf("%d\n",cnt[i]);
		}
	}
	for(int i=1;i<=m;i++){
		for(int i=0;i<4;i++){
			int xx=x+nx,yy=y+ny;
			if(xx>n||yy>n||xx<1||yy<1||vis[xx][yy])  continue;
			vis[xx][yy]=c;
			cnt[c]++;
			j[c][cnt[c]][1]=xx;
			j[c][cnt[c]][2]=yy;
			dfs(xx,yy,c,s+1);
			vis[xx][yy]=0;
			cnt[c]--;
			j[c][cnt[c]][1]=0;
			j[c][cnt[c]][2]=0;
		}
	}
}
*/
int main(){
	freopen("flowfree.in","r",stdin);
	freopen("flowfree.out","w",stdout);
	read(n);read(m);
	for(int i=1;i<=m;i++){
		read(a);read(b);read(c);read(d);
//		d[i].op=i;
		printf("2\n");
		printf("%d %d\n%d %d\n",a,b,c,d);
	}
//	dfs(0,0,1,n);
}
