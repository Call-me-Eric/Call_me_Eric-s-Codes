#include<cstdio>
#include<bitset>
#include<algorithm>
int n,k,q,a[100010][13],b[100010][13],cur;
bool cmp(int i,int j){return a[cur][i]<a[cur][j];}
std::bitset<4096>f[100030];
int main(){
  freopen("compose.in","r",stdin);
  freopen("compose.out","w",stdout);
	scanf("%d%d%d",&n,&k,&q);
	for(int i=0;i<k;i++)
		for(int j=0;j<n;j++)scanf("%d",a[j]+i),b[j][i]=i;
	for(cur=0;cur<n;cur++)std::sort(b[cur],b[cur]+k,cmp);
	for(int st=0;st<1<<k;st++)
		for(int i=0;i<k;i++)if(st>>i&1)f[i][st]=1;
	int tot=k;
	while(q--){
		int t,x,y;scanf("%d%d%d",&t,&x,&y);x--;y--;
		if(t==1)f[tot++]=f[x]|f[y];
		if(t==2)f[tot++]=f[x]&f[y];
		if(t==3){
			int st=0,i=k;
			while(!f[x][st])st|=1<<b[y][--i];
			printf("%d\n",a[y][b[y][i]]);
		}
	}
  return 0;
}
