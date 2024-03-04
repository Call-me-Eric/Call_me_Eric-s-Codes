#include<bits/stdc++.h>
#define int long long
#include<deque>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) +ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 2e6 + 10;
int buc[maxn];
int n;
struct node{
	int val, col;
	node(int v = 0,int c = 0):val(v),col(c){}
}a[maxn];
int c[maxn], tot;
struct cmp{bool operator()(node a,node b){return a.val < b.val;}};

deque<int> que;
bool check(int mid){
//	puts("");
//	printf("mid = %d\n",mid);
	int cnt = 0;
	memset(buc,0,sizeof(buc));
	while(!que.empty())que.pop_front();
	for(int i = 1;i <= tot;i++){
		while(!que.empty() && a[que.back()].val < a[i].val - mid){
			--buc[a[que.back()].col];
//				printf("a[%d]=%d poped by a[%d]=%d - mid=%d\n",que.back(),a[que.back()].val,i,a[i].val,mid);
			if(!buc[a[que.back()].col]){
				cnt--;
			}
			que.pop_back();
		}
		que.push_front(i);
		if(!buc[a[i].col])cnt++;
		buc[a[i].col]++;
//		for(int i = 1;i <= n;i++){
//			printf("buc[%d] = %d\n",i,buc[i]);
//		}
//		printf("i = %d, cnt = %d, col = %d, val = %d\n",i,cnt,a[i].col,a[i].val);
		if(cnt >= n)return 1;
	}
	return 0;
}
signed main(){
	freopen("eliminate.in","r",stdin);
	freopen("eliminate.out","w",stdout);
	n = read();
	for(int i = 1;i <= n;i++){
		c[i] = read();
		for(int j = 1;j <= c[i];j++){
			a[++tot] = node(read(),i);
		}
	}
	sort(a + 1,a + 1 + tot,cmp());
//	for(int i = 1;i <= tot;i++){
//		printf("a[%d] : val=%d,col=%d\n",i,a[i].val,a[i].col);
//	}
	int l = 0, r = a[tot].val - a[1].val, mid, ans = 0;
	while(l < r){
		int mid = l + r >> 1;
		if(check(mid)){r = mid; ans = mid;}
		else{l = mid + 1;}
	}
	printf("%lld\n",ans);
	return 0;
}

