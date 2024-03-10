#include<bits/stdc++.h>
using namespace std;
int head[1000004],n,a[1000004],cnt;
long long tt,bb;
bool b[1000002]={};
struct love{
	int to,next,w;
}zyc[2000010];
void addd(int u,int v,int w){
	cnt++;
	zyc[cnt].to=v;
	zyc[cnt].next=head[u];
	zyc[cnt].w=a[u]-w;
	head[u]=cnt;
	cnt++;
    zyc[cnt].to=u;
	zyc[cnt].next=head[v];
	zyc[cnt].w=a[v]-w;
	head[v]=cnt;
}
void aaaaa(int x){
	for(int j=head[x];j;j=zyc[j].next){
		bb+=zyc[j].w;
		if(bb>0&&(!b[zyc[j].to])){
            b[zyc[j].to]=1;
			tt++;
			aaaaa(zyc[j].to);
		}
		bb-=zyc[j].w;
	}
}
int main(){
	freopen("transport.in","r",stdin);
	freopen("transport.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int u,v,w;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		addd(u,v,w);
	}
	for(int i=1;i<=n;i++){
		bb=1;
		memset(b,0,sizeof(b));
		b[i]=1;
		aaaaa(i);
	}
	cout<<tt;
	return 0;
}
