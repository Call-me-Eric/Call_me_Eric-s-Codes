#include<cstdio>
#include <cctype>
using namespace std;
int qread(){
	char ch;int k = 1, t = 0;
	while (!isdigit(ch = getchar())) 
	{
		if (ch == EOF) return -1;
		if (ch == '-') k=-1;
	}
	t = ch-'0';
	while (isdigit(ch=getchar())) t=t*10+ch-'0';
	return k * t;
}
void data(int k){
	if(k > 9)data(k / 10);
	putchar(k % 10 + '0');
}
void qwrite(int k){
	if(k < 0){	k = -k;	putchar('-');}
	data(k);
}
int n, left[50002], right[50002];
void swap(int &a, int &b){int t = a; a = b;b = t;}
void sort(int l, int r){
	int i = l, j = r, mid = left[(l + r) / 2];
	while(i <= j){
		while(left[i] < mid) i++;
		while(left[j] > mid) j--;
		if(i <= j) {
			swap(left[i], left[j]);
			swap(right[i], right[j]);
			i++; j--;
		}
	}
	if(l < j) sort(l, j);
	if(i < r) sort(i, r);
}
int max(int i, int j){return i > j ? i : j;}
int main(){
	n = qread();
	for(int i = 1;i <= n;i++){
		left[i] = qread();right[i] = qread();
	}
	sort(1, n);
	left[0] = left[1];right[0] = right[1];
	for(int i = 1;i < n;i++){
		if(left[i + 1] > right[0]){printf("no");return 0;}
		right[0] = max(right[0], right[i + 1]);
	}
	printf("%d %d",left[0],max(right[0],right[n]));
	return 0;
}
