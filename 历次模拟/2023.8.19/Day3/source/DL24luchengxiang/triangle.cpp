#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define inl inline
const int N=1e2+5;
inl int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,k,a[N][N];
priority_queue<int>q[N][N],ans;
signed main(){
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
	n=read();k=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			a[i][j]=read();
		}
	}
	q[1][1].push(-a[1][1]);
	for(int i=1;i<=n-1;i++){
		for(int j=1;j<=i;j++){
			while(!q[i][j].empty()){
				q[i+1][j].push(q[i][j].top()-a[i+1][j]);
				q[i+1][j+1].push(q[i][j].top()-a[i+1][j+1]);
				if(q[i+1][j].size()>k)q[i+1][j].pop();
				q[i][j].pop();
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			while(!q[n][i].empty()){
				ans.push(q[n][i].top());
				if(ans.size()>k)ans.pop();
				q[n][i].pop();
			}
		}
	}
	printf("%d\n",-ans.top());
	return 0;
}

