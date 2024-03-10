#include<bits/stdc++.h>
using namespace std;
//只能跑过500的数据？？折磨菜。
//只能跑过500的数据？？折磨菜。
//只能跑过500的数据？？折磨菜。
//只能跑过500的数据？？折磨菜。
 
const int N=3e5+7;

struct node{
	int l,r,id;
}q[N];

int n,m;
int ans,belongs[N];
int a[N];
int num[N];
int pos[N];
vector<int> vec;
bool flag[N];

bool cmp(node c,node d){
	int cid=belongs[c.l],did=belongs[d.l];
	if(cid!=did) return cid<did;
	return c.r<d.r;
}

void add(int x){
	flag[x]=1;
	for(int qaq:vec){
		if(qaq-a[x]<=0) continue;
		int p=pos[qaq-a[x]];
		if(flag[p]&&p!=x) ans++;
	}
}

void del(int x){
	flag[x]=0;
	for(int qaq:vec){
		if(qaq-a[x]<=0) continue;
		int p=pos[qaq-a[x]];
		if(flag[p]&&p!=x) ans--;
	}
}

void init(int len){
	len=len*2+1;
	int _=sqrt(len)+1;
	for(int i=2;i<=_;i++){
		int qwq=i*i;
		if(qwq>len) return;
		else vec.push_back(qwq);
	}
}

int main(){
	freopen("liyue.in","r",stdin);
	freopen("liyue.out","w",stdout);
	scanf("%d",&n);
	init(n);
	int len=sqrt(n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pos[a[i]]=i;
		belongs[i]=(i-1)/len+1;
	}
	scanf("%d",&m); 
	for(int i=1;i<=m;i++){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
//	printf("Done");
	sort(q+1,q+1+m,cmp);
	int l=1,r=0;	
	for(int i=1;i<=m;i++){
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(l<q[i].l) del(l++);
		while(r>q[i].r) del(r--);
		num[q[i].id]=ans;
	}
	for(int i=1;i<=m;i++) printf("%d\n",num[i]);
	return 0;
}

