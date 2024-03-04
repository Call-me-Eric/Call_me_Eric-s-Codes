#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n;
int a[maxn];
int pos[maxn];
bool book[maxn];
signed main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		pos[a[i]] = i;
	}
	for(int i = n;i > 0;i--){
		int u = pos[i];
		book[u] = 0;
		int v = u;
		while(v - a[u] > 0)v -= a[u];
		for(;v <= n;v += a[u]){
			if(!(a[u] < a[v]))continue;
			if(book[v] == 0){
				book[u] = 1;
				break;
			}
		}
	}
	for(int i = 1;i <= n;i++){
		putchar(book[i] ? 'A' : 'B');
	}
	return 0;
}

