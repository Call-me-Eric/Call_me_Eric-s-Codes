#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int n, k, l, r; 
int a[200001],b[200001];
vector<int> ans;vector<int>::iterator it;
int i, j;
int main(){
	scanf("%d",&n);
	for(i = 1;i <= n;i++){
		scanf("%d%d",&a[i],&b[i]);
	}
	scanf("%d",&k);
	for(i = 1;i <= k;i++){
		scanf("%d%d",&l,&r);
		ans.clear();
		ans.push_back(l);
		
		for(j = l + 1;j <= r;j++){
			for(it = ans.begin();it != ans.end();it++){
				if(a[j] >= a[*it] && b[j] >= b[*it]){
					*it = j;
				}
				else if(!(a[j] <= a[*it]) && !(b[j] <= b[*it])) ans.push_back(j);
			}
		}
		int t = 1;
		for(it = ans.begin();it != ans.end();it++){
			t *= (a[*it] ^ b[*it]);
		}
		printf("%d\n",t);
	}
	return 0;
}

