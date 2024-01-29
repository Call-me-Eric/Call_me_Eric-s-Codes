#include <bits/stdc++.h>
using namespace std;
int N, K;
int r[50005];
int res[50005];
int ori_idx[50005];
int main(){
	scanf("%d%d", &N, &K);
	for(int i = 0; i < K; ++i) {
		scanf("%d", r + i);
	}
	int min_num = 1;
	int max_num = N;
	int min_idx = 0;
	for(int i = 0; i < N; ++i) {
		ori_idx[i] = i;
		res[i] = -1;
	}
	for(int i = 0; i < N; ++i) {
		int rand_idx = min_num - 1 + r[i%K] % (max_num - min_num + 1);
		if(ori_idx[rand_idx] == min_idx) {
			res[min_idx] = min_num;
			swap(ori_idx[rand_idx], ori_idx[min_num - 1]);
			++min_num;
			for(;min_idx < N && res[min_idx] >= 0;){++min_idx;}
		} else {
			res[ori_idx[rand_idx]] = max_num;
			swap(ori_idx[rand_idx], ori_idx[min_num - 1]);
			swap(ori_idx[max_num - 1], ori_idx[min_num - 1]);
			--max_num;
		}
	}
	for(int i = 0;i < N; ++i){cout << res[i] << endl;}
	return 0;
}

