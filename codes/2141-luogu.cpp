#include <algorithm>
#include <cstdio>
#include <cstdlib>
#define inf 99999999
using namespace std;

int n, a[101], ans, book[20001];

int findn(int left, int right, int m){
	int mid = (left + right) / 2;
	if(a[mid] == m) return 1;
	else 
		if(a[mid] < m){
			return findn(mid + 1, right, m);
		}
		else {
			return findn(left, mid - 1, m); 
		}
	return 0;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
	}
	sort(a + 1, a + 1 + n);
	for(int i = 1;i <= n;i++){
		for(int j = i;j <= n;j++){
			if(i != j)
				for(int k = 1;k <= n;k++)
					if(a[i] + a[j] == a[k] && !book[a[i] + a[j]])
						ans++,book[a[i] + a[j]] = 1;
		}
	}
	printf("%d",ans);
	return 0;
}

