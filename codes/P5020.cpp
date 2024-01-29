#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
int T, n;
int a[101];
int book[25052];
int main(){
	scanf("%d",&T);
	while(T--){
		int ans = 0;
		memset(a, 0, sizeof(a));
		memset(book, 0, sizeof(book));
		scanf("%d",&n);
		for(int i = 1;i <= n;i++){
			scanf("%d",&a[i]);
			book[a[i]] = 2;
		}
		sort(a + 1, a + 1 + n);
		for(int i = 1;i <= a[n];i++){
			if(book[i] > 0){
				for(int j = 1;j <= n;j++){
					if(i + a[j] <= a[n])
						book[i + a[j]] = 1;
					else break;
				}
			}
		}
		for(int i = 1;i <= a[n];i++){
			if(book[i] == 2)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}

