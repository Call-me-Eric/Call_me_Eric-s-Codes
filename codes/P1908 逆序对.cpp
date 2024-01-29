#include <iostream>
#include <cstdio>
#include <algorithm>
#define for1(i, a, b) for(int i = a; i <= b; i++)
using namespace std;
const int N = 5e5+5;  //此处开1e5，运行RE， 
int a[N],b[N];
long long ans = 0;     //此处定义int，运行WA 
void msort(int l, int r){
	if(l == r)	return ;
	int mid = l+(r - l) / 2;
	msort(l, mid);	msort(mid+1, r);
	int i = l, j = mid +1, k = l;
	while(i <= mid && j <= r){
		if(a[i] <= a[j]){
			b[k++] = a[i++]; 
		}
		else{
			b[k++] = a[j++];
			ans += mid - i + 1;
		}
	}
	while(i <= mid)	{
		b[k++] = a[i++];
	}
	while(j <= r) {
		b[k++] = a[j++];
	}
	for1(i,l,r)	a[i] = b[i];
}
int main(){
	int n;
	cin >>n;
	for1(i, 1, n)
		cin>>a[i];
	msort(1, n);
//	for1(i, 1, n)
//		cout <<a[i]<<" ";
//	for1(i, 1, n)
//		cout <<b[i]<<" ";
	cout << ans;	
	return 0;
}

