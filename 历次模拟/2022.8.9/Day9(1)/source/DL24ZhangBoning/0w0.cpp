#include<bits/stdc++.h>
using namespace std;

#define FO(name) freopen(name".in","r",stdin);freopen(name".out","w",stdout)
#define lowbit(x) ((x)&(-x))

const long long MOD = 4294967296;

const int maxN = 5e4;

// ( -> 1
// 0 -> 2
// w -> 3
// ) -> 4
inline int chk(char c){
	if(c == '(') return 1;
	if(c == '0') return 2;
	if(c == 'w') return 3;
	if(c == ')') return 4;
	return 0;
}

int A[maxN];

//struct BIT{
//	int bi[maxN];
//	inline void add(int x,int k) {
//		while (x <= n) {  
//			bi[x] = bi[x] + k;
//			x = x + lowbit(x);
//		}
//	}
//	inline int getsum(int x) {
//		int ans = 0;
//		while (x >= 1) {
//			ans = ans + bi[x];
//			x = x - lowbit(x);
//		}
//		return ans;
//	}
//}BIT_lc,BIT_0,BIT_w,BIT_rc;

vector<int> V;

inline bool check(int a,int b,int c,int d,int e){
	return (V[a] == 1 && V[b] == 2 && V[c] == 3 && V[d] == 2 && V[e] == 4);
}
int N,M;
inline void printA(){
	for(int i = 1;i<=N;i++) cout << A[i] << " ";
	cout << endl;
}

int main(){
	FO("0w0");
	ios::sync_with_stdio(false);
	V.resize(15);
	cin >> N >> M;
	char c;
	for(int i = 1;i<=N;i++){
		cin >> c;
		A[i] = chk(c);
	}
	int x,y;
	char z;
	
	for(int i = 1;i<=M;i++){
		cin >> c >> x;
		if(c == 'A'){
			cin >> z;
			A[x] = chk(z);
//			printA();
		}else if(c == 'B'){
			cin >> y >> z;
			for(int i = x;i<=y;i++) A[i] = chk(z);
//			printA();
		}else{
			cin >> y;
			V.clear();
			for(int i = x;i<=y;i++) if(A[i]) V.push_back(A[i]);
			
			int R = V.size();
//			for(int i = 0;i<R;i++) cout << V[i] << " ";
//			cout << endl;
			if(R < 5){
				cout << "0" << endl;
				continue;
			}
			long long count = 0;
			for(int a1 = 1;a1<=R-4;a1++){
				for(int a2 = a1+1;a2<=R-3;a2++){
					for(int a3 = a2+1;a3<=R-2;a3++){
						for(int a4 = a3+1;a4<=R-1;a4++){
							for(int a5 = a4+1;a5<=R;a5++){
								if(check(a1-1,a2-1,a3-1,a4-1,a5-1)){
									count++;
									if(count == MOD) count = 0;
								}
							}
						}
					}
				}
			}
			cout << count << endl;
		}
	}
	return 0;
}
