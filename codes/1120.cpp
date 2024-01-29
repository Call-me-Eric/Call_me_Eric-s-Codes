#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
int next[1001], a[101];
int sum;
int m, q;
bool book[1001], ok;
void dfs(int k,int last, int res){
	int i;
	if(res == 0){
		if(k == m){
			ok = true;
			return;
		}
		for(i = 1;i <= n;i++)
			if(book[i] == false)break;
		book[i] = true;
		dfs(k + 1, i, q - a[i]);
		book[i] = false;
	}
	int l = last + 1, r = n, mid = 0;
	while(l < r){
		mid = (l + r) >> 1;
		if(a[mid] <= res)r = mid;
		else l = mid + 1;
	}
	for(i = l;i <= n;i++){
		if(book[i] == false){
			book[i] = true;
			dfs(k, i, res - a[i]);
			book[i] = false;
			if(ok) return;
			if(res == a[i] || res == q)
				return;
			i = next[i];
			if(i == n)return;
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		if(a[i] > 50){
			n--;
			i--;
		}
	}
	int sum = 0, max = -9999;
	for(int i = 1;i <= n;i++){
		sum += a[i];
		if(a[i] > max)max = a[i];
	}
	sort(a + 1, a + 1 + n);
	next[n] = n;
	for(int i = n - 1;i > 0;i--){
		if(a[i] == a[i + 1])
			next[i] = next[i + 1];
		else next[i] = i;
	}
	for(int i = a[1];i <= sum / 2;i++){
		if(sum % i != 0)continue;
		q = i;
		m = sum / i;
		ok = false;
		book[1] = true;
		dfs(1, 1, i - a[1]);
		book[1] = false;
		if(ok){printf("%d",i);	return 0;	}
	}
	printf("%d",sum);
	return 0;
} 
