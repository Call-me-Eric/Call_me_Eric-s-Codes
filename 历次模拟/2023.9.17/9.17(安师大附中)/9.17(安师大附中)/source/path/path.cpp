#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <algorithm>
#define mod 998244353
using namespace std;
int tot,V;
int S,ans;
struct WORK{
	int tot,xa[505],ya[505],xb[505],yb[505];
	int n,m,pos_x[1005],pos_y[1005];
	map<int,int> id_x,id_y;
	int dis[505][505];
	int id[505];
	int f[505],h[505];
	void bubble_sort1(){
		for (int i=1;i<=tot;i++)
			for (int j=1;j<tot;j++)
				if (ya[j]>ya[j+1]){
					swap(xa[j],xa[j+1]);
					swap(ya[j],ya[j+1]);
					swap(xb[j],xb[j+1]);
					swap(yb[j],yb[j+1]);
				}
		return;
	}
	void bubble_sort2(){
		for (int i=1;i<=tot;i++)
			for (int j=1;j<tot;j++)
				if (yb[id[j]]>yb[id[j+1]])swap(id[j],id[j+1]);
		return;
	}
	void work(){
		id_x[V]=1,pos_x[++n]=V;
		id_y[V]=1,pos_y[++m]=V;
		for (int i=1;i<=tot;i++){
			if (id_x[xa[i]]==0){
				id_x[xa[i]]=1;
				pos_x[++n]=xa[i];
			}
			if (id_y[ya[i]]==0){
				id_y[ya[i]]=1;
				pos_y[++m]=ya[i];
			}
			if (id_x[xb[i]-1]==0){
				id_x[xb[i]-1]=1;
				pos_x[++n]=xb[i]-1;
			}
			if (id_y[yb[i]-1]==0){
				id_y[yb[i]-1]=1;
				pos_y[++m]=yb[i]-1;
			}
		}
		sort(pos_x+1,pos_x+1+n);
		for (int i=1;i<=n;i++)id_x[pos_x[i]]=i;
		sort(pos_y+1,pos_y+1+m);
		for (int i=1;i<=m;i++)id_y[pos_y[i]]=i;
		for (int i=1;i<=tot;i++){
			xa[i]=id_x[xa[i]];
			ya[i]=id_y[ya[i]];
			xb[i]=id_x[xb[i]-1]+1;
			yb[i]=id_y[yb[i]-1]+1;
		}
		bubble_sort1();
		for (int i=1;i<=tot;i++)
			for (int j=i+1;j<=tot;j++)
				if (xb[i]<=xa[j]&&yb[i]<=ya[j])dis[i][j]=1;
		for (int k=1;k<=tot;k++)
			for (int i=1;i<k;i++)
				for (int j=k+1;j<=tot;j++)
					if (dis[i][k]>0&&dis[k][j]>0)dis[i][j]=max(dis[i][j],dis[i][k]+dis[k][j]);
		for (int i=1;i<=tot;i++)id[i]=i;
		bubble_sort2();
		for (int i=n;i>=1;i--){
			memset(f,0,sizeof(f));
			int p=tot;
			for (int j=m;j>=1;j--){
				while(p>=1&&ya[p]>=j){
					if (xa[p]>=i){
						f[p]=1;
						for (int k=p+1;k<=tot;k++)
							if (xa[k]>=i&&dis[p][k]>0)f[k]=max(f[k],dis[p][k]+1);
					}
					p--;
				}
				for (int k=1;k<=tot;k++)h[k]=V+1;
				int s=0;
				for (int k=1;k<=tot;k++){
					int t=id[k];
					if (f[t]>0){
						int _f=f[t],_x=xb[t],_y=yb[t];
						if (pos_x[_x]<h[_f]){
							s=(s+1ll*(h[_f]-(pos_x[_x-1]+1))*(V-(pos_y[_y-1]+1)+1))%mod;
							h[_f]=pos_x[_x-1]+1;
						}
					}
				}
				ans=(ans+1ll*(pos_x[i]-pos_x[i-1])*(pos_y[j]-pos_y[j-1])%mod*s)%mod;
			}
		}
		return;
	}
}work1,work2;
int main(){
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	cin>>tot>>V;
	S=(1ll*V*(V+1)/2%mod*(-V-1)%mod+mod)%mod;
	S=(S+1ll*V*(V+1)%mod*(2*V+1)%mod*((mod+1)/3)%mod)%mod;
	S=1ll*S*V%mod*V%mod*2%mod;
	for (int i=1;i<=tot;i++){
		int xa,ya,xb,yb;
		cin>>xa>>ya>>xb>>yb;
		if (ya<yb){
			int t=++work1.tot;
			work1.xa[t]=xa,work1.ya[t]=ya,work1.xb[t]=xb,work1.yb[t]=yb;
		}
		else{
			int t=++work2.tot;
			work2.xa[t]=xa,work2.ya[t]=V-ya+1,work2.xb[t]=xb,work2.yb[t]=V-yb+1;
		}
	}
	work1.work();
	work2.work();
	cout<<(S-ans+mod)%mod<<endl;
	return 0;
}