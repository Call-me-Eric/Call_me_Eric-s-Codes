#include<bits/stdc++.h>
using namespace std;
const int maxn = 1010;
int n, m;
bool book[maxn * maxn / 10];
signed main(){
	srand(time(0));mt19937 rnd(rand());
	n = rnd() % 1000 + 1,m = rnd() % 20000 + 1;m = m / n;int sd = rnd() % (n * m);
	freopen("tmp.in","w",stdout);
	printf("%d %d\n",n,m);
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			while(book[sd]){
				sd = (sd + rnd()) % (n * m) + 1;
			}
			printf("%d ",sd);book[sd] = 1;
		}
		puts("");
	}
	return 0;
}