#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int r[50001];
int n, k;
int ans[50001]; 
int index[50001];
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 0;i < k;i++){
		scanf("%d",&r[i]);
	}
	int min_index = 0;
	int min_num = 1;
	int max_num = n;
	int rand_index = 0;
	for(int i = 0;i < n;i++){
		index[i] = i;
		ans[i] = -1;
	}
	for(int i = 0;i < n;i++){
		rand_index = min_num - 1 + r[i % k] % (max_num - min_num + 1);
		if(index[rand_index] == min_index){
			ans[min_index] = min_num;
			swap(index[rand_index],index[min_num - 1]);
			min_num++;
			while(min_index < n && ans[min_index]>= 0)min_index++;
		}
		else{
			ans[index[rand_index]] = max_num;
			swap(index[rand_index],index[min_num - 1]);
			swap(index[max_num - 1],index[min_num - 1]);
			max_num--;
		}
	}
	for(int i = 0;i < n;i++)printf("%d\n",ans[i]);
	return 0;
}

