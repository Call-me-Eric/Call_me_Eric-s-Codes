#include <cstdio>
#include <vector>
using namespace std;
int n, m;
int x;
vector<int> r, d, s, t;
void cannot(int i){printf("-1\n%d",i);return;}
int main() {
	scanf("%d%d",&n,&m);
	r.push_back(0); 	d.push_back(0);
	s.push_back(0); 	t.push_back(0);
	for(int i = 1;i <= n;i++){
		scanf("%d",&x);
		r.push_back(x);
	}
	
	for(int i = 1;i <= m;i++){
		scanf("%d",&x);
		d.push_back(x);
		scanf("%d",&x);
		s.push_back(x);
		scanf("%d",&x);
		t.push_back(x);
	}
	for(int i = 1;i <= m;i++){
		for(int j = s[i];j <= t[i];j++){
			if(r[j] >= d[j]) r[j] -= d[j];
			else {
				cannot(i);
				return 0;
			}
		}
	}
	printf("0");
	return 0;
}

