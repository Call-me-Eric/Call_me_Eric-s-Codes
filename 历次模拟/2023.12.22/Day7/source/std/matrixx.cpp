/** This is Standard Algorithm */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#ifdef FAST_IO
	#define read_bit(inp) inp = getchar() - '0'
	#define write_bit(oup) putchar(char(oup) + '0')
#else
	#define read_bit(inp) scanf("%1d", &inp)
	#define write_bit(oup) printf("%d", int(oup))
#endif

typedef unsigned long long llu;
const int M = 1011;
int n, m, p, l;
template <int len> 
	struct Int{
		llu data[(M >> 6) * len + 5];
		void OR(int a, bool v){
			data[a >> 6] |= llu(v) << (a & 63);
		}
		bool get(int a)const{
			return (data[a >> 6] >> (a & 63)) & 1;
		}
		void clear(){
			memset(data, 0, sizeof(data));
		}
		llu& operator[](int a){
			return data[a];
		}
		const llu& operator[](int a)const{
			return data[a];
		}
		Int& operator ^=(const Int& a){
			for(int i = 0, ll = l * len; i < ll; i++)
				data[i] ^= a[i];
			return *this;
		}
		void write(const char* end = "", bool expand = false)const{
			for(int i = 0; i < m; i++)
				write_bit(get(i));
			if(expand){
				putchar('+');
				write_bit(get(m));
			}
			printf(end);
		}
	};
Int<1> A1[M], AT[M], b[M], f, L[M], U[M], ap, kp, cur, ans, ap_;
Int<2> prod, pw, k2p[M];

template <int len>
	void shl(Int<len>& a, const Int<len>& b){
		a[len * l] = 0;
		for(int i = len * l - 1; i >= 0; i--){
			llu tmp = b[i];
			a[i + 1] |= (tmp >> 63) & 1;
			a[i] = tmp << 1;
		}
	}
	
template <int len1, int len2>
	void cp(Int<len1>& a, const Int<len2>& b){
		int ll = std::min(len1, len2);
		for(int i = 0, end = l * ll; i < end; i++)
			a[i] = b[i];
		for(int i = l * ll, end = l * len1; i < end; i++)
			a[i] = 0;
	}
	
void mat_multi(Int<1>& b1, const Int<1>* A, const Int<1>& b0){
	b1.clear();
	for(int i = 0; i < m; i++){
		if(b0.get(i))
			b1 ^= A[i];
		//printf("%d ", b0.get(i));
		//b1.write("\n");
	}
}

void poly_multi(){
	prod.clear();
	cp(pw, cur);
	for(int i = 0; i < p; i++){
		if(cur.get(i))
			prod ^= pw;
		shl(pw, pw);
	}
}

void init(){
	int inp;
	scanf("%d ", &m);
	l = (m >> 6) + 1;
	//printf("l = %d\n", l);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < m; j++){
			read_bit(inp);
			A1[i].OR(j, inp);
			AT[j].OR(i, inp);
		}
		scanf(" ");
	}
	for(int i = 0; i < m; i++){
		read_bit(inp);
		b[0].OR(i, inp);
	}
}

void eigen_poly(){
	static int cnt = 0, maxp = 0;
	while(p != m){	//This loop only runs once unless some ap is lucky enough to be an eigen-vector
		cnt += 1;
		ap.clear();
		for(int i = 0; i < m; i++)
			ap.OR(i, rand() & 1);
		ap_ = ap;
		for(int i = 0; i < m; i++){
			U[i].clear();
			L[i].clear();
		}
		for(p = 0;; p++){
			//printf("a_%d = ", p);
			//ap.write("\n");
			kp.clear();
			kp.OR(p, 1);
			bool is_zero = true;
			for(int i = 0; i < m; i++)
				if(ap.get(i)){
					if(U[i].get(i)){
						ap ^= U[i];
						kp ^= L[i];
					}else{
						U[i] = ap;
						L[i] = kp;
						is_zero = false;
						break;
					}
				}
			/*printf("p = %d\n", p);
			ap.write(" = ap\n");
			ap_.write(" = ap_\n");
			kp.write(" = kp\n");*/
			if(is_zero)
				break;
			mat_multi(ap, A1, ap_);
			ap_ = ap;
		}
		if(cnt > 20 && p == maxp)
			break;
		maxp = std::max(maxp, p);
		//fprintf(stderr, "p = %d\n", p);
		//kp.write(" = kp\n", true);
	}
	/*for(; p < m; p++){
		shl(ap_, kp);
		kp = ap_;
	}*/
	//kp.write(" = kp\n", true);
	fprintf(stderr, "%s\ntry = %d\n", cnt > 20 ? "0" : "1", cnt);
}

void initial_value(){
	for(int i = 1; i < p; i++){
		mat_multi(b[i], AT, b[i - 1]);
		//printf("b_%d = ", i);
		//b[i].write("\n");
	}
	cp(k2p[0], kp);
	for(int i = 1; i < p; i++)
		shl(k2p[i], k2p[i - 1]);
}

void pwer(int a){
	cur.clear();
	cur.OR(0, 1);
	for(int i = 30; i >= 0; i--){
		poly_multi();
		for(int j = p - 1; j >= 0; j--)
			if(prod.get(j + p))
				prod ^= k2p[j];
		cp(cur, prod);
		if((a >> i) & 1){
			shl(cur, cur);
			if(cur.get(p))
				cur ^= kp;
		}
	}
	//cur.write(" = cur\n");
	//printf("b_%d = ", a);
	ans.clear();
	for(int i = 0; i < p; i++)
		if(cur.get(i))
			ans ^= b[i];
	ans.write("\n");
}

void solve(){
	scanf("%d", &n);
	for(; n--;){
		int q;
		scanf("%d", &q);
		pwer(q);
	}
}

int main(){
  freopen("matrix.in","r",stdin);
  freopen("matrix.out","w",stdout);
	init();
	eigen_poly();
	initial_value();
	solve();
	
	return 0;
}
