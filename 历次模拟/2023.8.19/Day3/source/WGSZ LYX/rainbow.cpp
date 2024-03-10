#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fr first
#define sc second
inline int rd(){
	int f=1,tmp=0;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		tmp=tmp*10+(ch-'0');
		ch=getchar();
	}
	return tmp*f;
}
const int N=2e3+10;
int n,m,a[N][N],v[N][N],t[N*N];
signed main(){
	freopen("rainbow.in","r",stdin);
	freopen("rainbow.out","w",stdout);	
	n=rd();m=rd();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=rd();
		}
	}
	for(int i=1;i<=n;i++){
		int x=i,y=m;
		while(x>0&&y>0){
			if(a[x][y]==a[x+1][y+1])v[x][y]=v[x+1][y+1]+1;
			else v[x][y]=1;
			x--;y--;
		}
	}
	for(int i=1;i<m;i++){
		int x=n,y=i;
		while(x>0&&y>0){
			if(a[x][y]==a[x+1][y+1])v[x][y]=v[x+1][y+1]+1;
			else v[x][y]=1;
			x--;y--;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int res=v[i][j],l;
			t[a[i][j]]=1;
			for(l=2;l+i-1<=n&&l+j-1<=m;l++){
				int x=l+i-1,y=l+j-1;
				if(t[a[x][j]]||t[a[i][y]]||a[x][j]==a[i][y])break;
				res=min({res,v[i][y]+l-1,v[x][j]+l-1});
				t[a[x][j]]=t[a[i][y]]=1;
				if(l>res)break;
			}	
			for(int p=1;p<=l;p++){
				int x=p+i-1,y=p+j-1;
				t[a[x][j]]=t[a[i][y]]=0;
			}
			ans+=l-1;
		}
	}
	cout<<ans<<endl;
	return 0;
}

