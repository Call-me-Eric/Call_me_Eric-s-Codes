#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = (x << 1) + (x << 3) + (ch ^ 48);ch = getchar();}
	return x * f;
}
const int maxn = 1e3 + 10;
int b[maxn], n;
struct node{
	int num, id, nid;
	node(int num = 0,int id = 0,int nid = 0):num(num),id(id),nid(nid){}
}a[maxn];
struct cmp1{bool operator () (node a,node b){return a.num != b.num ? a.num < b.num : a.id < b.id;}};
struct cmp2{bool operator () (node a,node b){return a.id < b.id;}};
vector<pair<int,int> > ans;
signed main(){
	n = read();
	for(int i = 1;i <= n;i++){a[i] = node(read(),i);}
	sort(a + 1,a + 1 + n,cmp1());
	for(int i = 1;i <= n;i++)a[i].nid = i;
	sort(a + 1,a + 1 + n,cmp2());
	for(int i = 1;i <= n;i++)b[a[i].nid] = i;
//	for(int i = 1;i <= n;i++)printf("%d ",b[i]);puts("");
	for(int i = 1;i <= n;i++){
		for(int j = 1;j < n;j++){
			if(b[j] > b[j + 1]){
				swap(b[j],b[j + 1]);
				ans.push_back(make_pair(b[j],b[j + 1]));
			}
		}
	}
	
	printf("%d\n",ans.size());
	for(auto i : ans)printf("%d %d\n",i.first,i.second);
	return 0;
}
