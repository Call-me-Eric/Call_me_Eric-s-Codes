#include <cstdio>
#include <queue>
using namespace std;
bool book[1001];
queue<int> que;
int n, m;
int ans;
int main() {
	scanf("%d%d",&m, &n);
	for(int i = 1;i <= n;i++){
		int x;
		scanf("%d",&x);
		if(!book[x]){
			que.push(x);
			book[x] = 1;
			ans++;
		}
		if(que.size() > m) {
			book[que.front()] = 0;
			que.pop();
		}
	}
	printf("%d",ans);
	return 0;
}

