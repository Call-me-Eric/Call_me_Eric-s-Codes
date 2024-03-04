#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int n,m;
char c[55000];
int a[55000];
ull ans=0,mod=4294967296,rec1=0,rec2=0,rec3=0;
struct node{
	int l,r,f[5];
}t[550000];

void build(int p,int x,int y){
	t[p].l=x;
	t[p].r=y;
	
	if(x==y){
		
		for(int i=0;i<=4;i++){
			if(a[x]==i){
				t[p].f[i]=1;
				continue;
			}
			t[p].f[i]=0;
		}
		return;
	}
	
	int mid=(x+y)/2;
	build(p*2,x,mid);
	build(p*2+1,mid+1,y);
	
	for(int i=0;i<=4;i++){
		t[p].f[i]=t[p*2].f[i]+t[p*2+1].f[i];
	}
	return;
}
void rebuild(int p,int z){
	if(t[p].l==t[p].r){
		for(int i=0;i<=4;i++){
			if(z==i){
				if(t[p].f[i]!=1){
					int re=p;
					for(; ;){
						re=re/2;
						if(re==0){
							break;
						}
						t[re].f[i]+=1;
					}
				}
				t[p].f[i]=1;
				continue;
			}
			if(t[p].f[i]!=0){
				int re=p;
				for(; ;){
					re=re/2;
					if(re==0){
						break;
					}
					t[re].f[i]-=1;
				}
			}
			t[p].f[i]=0;
		}
		return;
	}
	
	rebuild(p*2,z);
	rebuild(p*2+1,z);
	return;
}
void change(int p,int x,int y,int z){
	
	if(t[p].r<x||t[p].l>y){
		return;
	}
	if(t[p].l>=x&&t[p].r<=y){
		rebuild(p,z);
		return;
	}
	
	change(p*2,x,y,z);
	change(p*2+1,x,y,z);
	return;
}

ull find1(int p,int x,int y){
	if(t[p].r<x||t[p].l>y){
		return 0;
	}
	if(t[p].l>=x&&t[p].r<=y){
		return t[p].f[2];
	}

	return find1(p*2,x,y)+find1(p*2+1,x,y);
}

ull find2(int p,int x,int y){
	if(t[p].r<x||t[p].l>y){
		return 0;
	}
	if(t[p].l>=x&&t[p].r<=y){
		return t[p].f[2];
	}

	return find2(p*2,x,y)+find2(p*2+1,x,y);
}

void searchll1(int p,int x,int y){
	if(t[p].l==t[p].r){
		rec2=find2(1,x,t[p].l)%mod;
		rec3=(rec1*rec2)%mod;
		ans=(ans+rec3)%mod;
		return;
	}
	if(t[p*2].f[4]!=0){
		searchll1(p*2,x,y);
	}
	if(t[p*2+1].f[4]!=0){
		searchll1(p*2+1,x,y);
	}
	return;
}

void searchll(int p,int x,int y){
	if(t[p].r<x||t[p].l>y){
		return;
	}
	if(t[p].l>=x&&t[p].r<=y){
		searchll1(p,x,y);
		return;
	}

	searchll(p*2,x,y);
	searchll(p*2+1,x,y);
	
}

void searchw1(int p,int x,int y){
	if(t[p].l==t[p].r){
		rec1=find1(1,x,t[p].l)%mod;
		searchll(1,t[p].l,y);
		return;
	}
	if(t[p*2].f[3]!=0){
		searchw1(p*2,x,y);
	}
	if(t[p*2+1].f[3]!=0){
		searchw1(p*2+1,x,y);
	}
	return;
}

void searchw(int p,int x,int y){
	if(t[p].r<x||t[p].l>y){
		return;
	}
	if(t[p].l>=x&&t[p].r<=y){
		searchw1(p,x,y);
		return;
	}

	searchw(p*2,x,y);
	searchw(p*2+1,x,y);
	
}

void searchl1(int p,int y){
	if(t[p].l==t[p].r){
		searchw(1,t[p].l,y);
		return;
	}
	if(t[p*2].f[1]!=0){
		searchl1(p*2,y);
	}
	if(t[p*2+1].f[1]!=0){
		searchl1(p*2+1,y);
	}
	return;
}


void searchl(int p,int x,int y){
	
	if(t[p].r<x||t[p].l>y){
		return;
	}
	if(t[p].l>=x&&t[p].r<=y){
		searchl1(p,y);
		return;
	}
	
	searchl(p*2,x,y);
	searchl(p*2+1,x,y);
	
}


int main(){
	
	freopen("0w0.in","r",stdin);
	freopen("0w0.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	scanf("%s",c+1);
	
	for(int i=1;i<=n;i++){
		if(c[i]=='('){
			a[i]=1;
			continue;
		}
		if(c[i]=='0'){
			a[i]=2;
			continue;
		}
		if(c[i]=='w'){
			a[i]=3;
			continue;
		}
		if(c[i]==')'){
			a[i]=4;
			continue;
		}
		a[i]=0;
	}
	
	build(1,1,n);
	
	for(int i=1;i<=m;i++){
		char j;
		int x;
		scanf("\n%c",&j);
		if(j=='A'){
			char y;
			scanf("%d %c",&x,&y);
			if(y=='('){
				change(1,x,x,1);
				continue;
			}
			if(y=='0'){
				change(1,x,x,2);
				continue;
			}
			if(y=='w'){
				change(1,x,x,3);
				continue;
			}
			if(y==')'){
				change(1,x,x,4);
				continue;
			}
			change(1,x,y,0);
		}
		if(j=='B'){
			int y;
			char z;
			scanf("%d%d %c",&x,&y,&z);
			if(z=='('){
				change(1,x,y,1);
				continue;
			}
			if(z=='0'){
				change(1,x,y,2);
				continue;
			}
			if(z=='w'){
				change(1,x,y,3);
				continue;
			}
			if(z==')'){
				change(1,x,y,4);
				continue;
			}
			change(1,x,y,0);
		}
		
		if(j=='C'){
			int y;
			scanf("%d%d",&x,&y);
			searchl(1,x,y);
			printf("%llu\n",ans);
			ans=0;
		}
	}
	
	
	
	return 0;
}


/*

(0w0w0)

*/
