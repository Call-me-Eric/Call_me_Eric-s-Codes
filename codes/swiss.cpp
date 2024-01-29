#include <bits/stdc++.h>
using namespace std;
#define maxn 200001
struct Node{
	int sorce;
	int i;
};
Node a[maxn];
Node A[100001];
Node B[100001];
int w[maxn];
bool cmp(Node a, Node b){
	if(a.sorce == b.sorce)
		return a.i < b.i;
	return a.sorce > b.sorce;
}
int n, r, q;
void MergeSort(){
	int i = 1, j = 1, k = 1;
	while(i <= n && j <= n){
		if(A[i].sorce > B[j].sorce || (A[i].sorce == B[j].sorce && A[i].i < B[j].i)){
			a[k].sorce = A[i].sorce;
			a[k++].i = A[i++].i;
		}
		else{
			a[k].sorce = B[j].sorce;
			a[k++].i = B[j++].i;
		}
	}
	while(i <= n){
		a[k].sorce = A[i].sorce;
		a[k++].i = A[i++].i;
	}
	while(j <= n){
		 a[k].sorce = B[j].sorce;
		a[k++].i = B[j++].i;
	}
}
int main(){
	scanf("%d%d%d",&n,&r,&q);
	for(int i = 1;i <= 2 * n;i++){
		scanf("%d",&a[i].sorce);
		a[i].i = i;
	}
	for(int i = 1;i <= 2 * n;i++)scanf("%d",w[i]);
	sort(a + 1,a + 1 + 2 * n,cmp);
	for(int k = 1;k <= r;k++){
		int tt = 1;
		for(int i = 1;i < 2 * n;i += 2){
			if(w[a[i].i] > w[a[i + 1].i])
			{
				A[tt].sorce = a[i].sorce + 1;
				A[tt].i = a[i].i;
				B[tt].sorce  =  a[i + 1].sorce;
				B[tt].i = a[i + 1].i;
				tt++;
			}
			else {
				A[tt].sorce = a[i + 1].sorce + 1;
				A[tt].i = a[i + 1].i;
				B[tt].sorce  =  a[i].sorce;
				B[tt].i = a[i].i;
				tt++;
			}
		}
		MergeSort();
	}
	printf("%d",a[q].i);
	return 0;
}

