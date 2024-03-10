#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
int read(){
	int sum=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){sum=sum*10+c-'0';c=getchar();}
	return f*sum;
}
const int N=1e6+10;
struct Node{
	int to,nxt;
}e[N],r[N];
int head1[N],head2[N],cnt1,cnt2,sum,num[N],n,m;
int nd[N],fd[N],nd1[N],fd1[N];
void add1(int u,int v){
	e[++cnt1].to=v;
	e[cnt1].nxt=head1[u];
	head1[u]=cnt1;
	//e[i].w=1;
}
void add2(int u,int v){
	r[++cnt2].to=v;
	r[cnt2].nxt=head2[u];
	head2[u]=cnt2;
	//r[i].w=1;
}
bool vis[N];
inline bool top1(int k){
	memset(vis,0,sizeof(vis));
	int cnt=0;
	queue<int> q;
	q.push(k);
	for(re int i=1;i<=n;i++){
		nd1[i]=nd[i];
		fd1[i]=fd[i];
	}
	while(!q.empty()){
		int tmp=q.front();q.pop();
		if(!vis[tmp]){
			cnt++;
			vis[tmp]=1;
			if(cnt==n) return 1;
		}
		for(re int i=head1[tmp];i;i=e[i].nxt){
			nd1[e[i].to]--;
			if(nd1[e[i].to]>=0){
				q.push(e[i].to);
			}
		}
	}
	q.push(k);
	while(!q.empty()){
		int tmp=q.front();q.pop();
		if(!vis[tmp]){
			cnt++;
			vis[tmp]=1;
		}
		for(re int i=head2[tmp];i;i=r[i].nxt){
			fd1[r[i].to]--;
			if(fd1[r[i].to]>=0){
				q.push(r[i].to);
			}
		}
	}
	//cout<<cnt;
	if(cnt!=n) return 0;
	return 1;
}
int main(){
	freopen("goood.in","r",stdin);freopen("goood.out","w",stdout);
	n=read(),m=read();
	for(re int i=1;i<=m;i++){
		int u=read(),v=read();
		add1(u,v);nd[v]++;
		add2(v,u);fd[u]++;
	}
	//top1(6);
	for(re int i=1;i<=n;i++){
		if(top1(i)){
			num[++sum]=i;
		}
	}
	printf("%d\n",sum);
	for(re int i=1;i<=sum;i++) printf("%d ",num[i]);
}
/*
6 7
1 2
1 3
2 4
3 4
4 5
5 6
6 5
*/
