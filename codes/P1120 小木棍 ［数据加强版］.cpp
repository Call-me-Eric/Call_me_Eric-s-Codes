#include <bits/stdc++.h>
using namespace std;
int n, m, a[65], next[65], len, sum = 0, cnt = 0;
bool used[65], ok;
bool cmp(int x , int y){
	return x > y ;
}
void dfs(int k, int last, int rest){
	//k为正在拼的木棍的编号，last为正在拼的木棍的前一节编号
	//rest为该木棍还未拼的长度 
	int i ;
	if(rest == 0){
		if(k == m){   //优化6，找打答案就推出 
			ok = 1;
			return;
		}
		for(i = 1; i <= cnt; i++)
			if(!used[i])
				break;
		used[i] = 1;
		dfs(k + 1 , i , len - a[i]);
		used[i] = 0;
		if(ok) return ;
	}
	//优化4：二分找第一个木棍长度不大于未拼长度rest的位置 
	int l = last + 1 , r = cnt, mid;
	while(l < r){
		mid = (l + r) >> 1;
		if(a[mid] <= rest) r = mid;
		else	l = mid + 1;
	}
	for (i = l; i <= cnt; i++){
		if(!used[i]){ //优化5，判断是否被用过 
			used[i] = 1;
			dfs(k, i , rest - a[i]);
			used[i] = 0;
			if(ok) return ;	//优化6 
			if(rest ==a[i] || rest == len) return ;//优化7 
			i = next[i];
			if(i == cnt) return ;
		}
	} 
} 
int main(){
	scanf("%d", &n);
	for (int i = 1;i <= n; i++){
		int t;
		scanf("%d", &t);
		if(t > 50) continue;
		a[++cnt] = t;
		sum += t;
	}
	sort(a+1, a+n+1, cmp);	//优化1：从大到小排序 
	next[cnt] = cnt;
	for (int i = cnt - 1; i > 0; i--){//优化3：预处理next数组 
		if(a[i] == a[i + 1])
			next[i] = next[i+1];
		else
			next[i] = i; 
	}
	for(len = a[1]; len <= sum /2; len++){
		if(sum % len == 0){
			m = sum / len;
			ok = 0;
			used[1] = 1;
			dfs(1, 1, len -a[1]);
			used[1] = 0;
			if(ok){			//优化6，找到最小的就不搜了 
				printf("%d\n", len);
				return 0;
			}
		}		
	}
	printf("%d\n", sum);	//最长的一根； 
	return 0;
}
