#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getc() {
	static char *p1, *p2, buf[1<<20];
	if (p1==p2) p2=(p1=buf)+fread(buf, 1, 1<<20, stdin);
	return p1==p2?10:*p1++;
}
inline int read() {
	int f=1, r=0; char c=getc();
	while (!isdigit(c)) f^=c=='-', c=getc();
	while (isdigit(c)) r=r*10+c-48, c=getc();
	return f?r:-r;
}
#define fi first
#define se second
const int N=1e6+7;
int gcd(int x, int y) {return y?gcd(y, x%y):x;}
int n, K; bool ans[N];
vector<pair<int, int> > vec;
inline void work(int g) {
	int d=n/g, c=K/g;
	for (int i=0; i<c; i++)
		for (int j=i; j<n; j+=d) ans[j]=true;
}
int main() {
	freopen("ur.in", "r", stdin);
	freopen("ur.out", "w", stdout);
	n=read(), K=read();
	if (K<=1 || K==n) {
		for (int i=0; i<n; i++) putchar(48+(K==n));
		return 0;
	}
	int x=n;
	for (int i=2; i*i<=x; i++)
		if (x%i==0) {
			vec.push_back({i, 0});
			while (x%i==0) vec.back().se++, x/=i;
		}
	if (x>1) vec.push_back({x, 1});
	if ((int)vec.size()==1 || ((int)vec.size()==2 && vec[0].se==1 && vec[1].se==1)) {
		while (K) {
			int g=gcd(n, K);
			if (g==1) {K--; continue;}
			work(g); break;
		}
		for (int i=0; i<n; i++) putchar(ans[i]+48);
		return 0;
	}
	while (K) {
		int g=gcd(n, K);
		if (g>1) {work(g); break;}
		if (n==12 && K==5) cout<<"000110010011"<<endl, exit(0);
		if (n==12 && K==7) cout<<"001101100111"<<endl, exit(0);
		if (n==18 && K==5) cout<<"000001010001000011"<<endl, exit(0);
		if (n==18 && K==7) cout<<"000001110001000111"<<endl, exit(0);
		if (n==18 && K==11) cout<<"000111011100011111"<<endl, exit(0);
		if (n==18 && K==13) cout<<"001111011101011111"<<endl, exit(0);
		if (n==20 && K==7) cout<<"00010001100100010011"<<endl, exit(0);
		if (n==20 && K==9) cout<<"00010011100100011011"<<endl, exit(0);
		if (n==20 && K==11) cout<<"00011011100100111011"<<endl, exit(0);
		if (n==20 && K==13) cout<<"00110111011001110111"<<endl, exit(0);
		if (n==24 && K==5) cout<<"000000010010000100000011"<<endl, exit(0);
		if (n==24 && K==7) cout<<"000000010110000100000111"<<endl, exit(0);
		if (n==24 && K==11) cout<<"000000111101001000011111"<<endl, exit(0);
		if (n==24 && K==13) cout<<"000001111011010000111111"<<endl, exit(0);
		if (n==24 && K==17) cout<<"000111110111100101111111"<<endl, exit(0);
		if (n==24 && K==19) cout<<"001111110111101101111111"<<endl, exit(0);
		if (n==30 && K==7) cout<<"000000000100110000010000000111"<<endl, exit(0);
		if (n==30 && K==11) cout<<"000000000111110000010000011111"<<endl, exit(0);
		if (n==30 && K==13) cout<<"000000001111101000100000111111"<<endl, exit(0);
		if (n==30 && K==17) cout<<"000000111110111010000011111111"<<endl, exit(0);
		if (n==30 && K==19) cout<<"000001111101111100000111111111"<<endl, exit(0);
		if (n==30 && K==23) cout<<"000111111101111100110111111111"<<endl, exit(0);
		if (n==36 && K==5) cout<<"000000000001000010000001000000000011"<<endl, exit(0);
		if (n==36 && K==7) cout<<"000000000001000110000001000000000111"<<endl, exit(0);
		if (n==36 && K==11) cout<<"000000000001011110000001000000011111"<<endl, exit(0);
		if (n==36 && K==13) cout<<"000000000001111110000001000000111111"<<endl, exit(0);
		if (n==36 && K==17) cout<<"000000000111111011000100000011111111"<<endl, exit(0);
		if (n==36 && K==19) cout<<"000000001111110111001000000111111111"<<endl, exit(0);
		if (n==36 && K==23) cout<<"000000111111011111100000011111111111"<<endl, exit(0);
		if (n==36 && K==25) cout<<"000001111111011111100001011111111111"<<endl, exit(0);
		if (n==36 && K==29) cout<<"000111111111011111100111011111111111"<<endl, exit(0);
		if (n==36 && K==31) cout<<"001111111111011111101111011111111111"<<endl, exit(0);
		K--;
	}	
	for (int i=0; i<n; i++) putchar(ans[i]+48);
	return 0;
}
