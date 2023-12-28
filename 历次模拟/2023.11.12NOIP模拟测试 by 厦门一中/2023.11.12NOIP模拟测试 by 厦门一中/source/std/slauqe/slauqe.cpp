#include <bits/stdc++.h>
using namespace std;

/* d0j1a_1701 FastIO Lite ver. 5.0 */
#define dIO_USE_BUFFER // 取消注释以开启 fread（交卷时请取消注释）
struct IO{
#ifdef dIO_USE_BUFFER
	const static int BUFSIZE=1<<20;
	char ibuf[BUFSIZE], obuf[BUFSIZE], *p1, *p2, *pp;
	inline int getchar(){return(p1 == p2&&(p2=(p1=ibuf)+fread(ibuf,1,BUFSIZE,stdin),p1==p2)?EOF:*p1++);}
	inline int putchar(char x){return((pp-obuf==BUFSIZE&&(fwrite(obuf,1,BUFSIZE,stdout),pp=obuf)),*pp=x,pp++),x;}
	IO(){p1=p2=ibuf,pp=obuf;}
	~IO(){fwrite(obuf,1,pp-obuf,stdout),pp=obuf,fflush(stdout);}
#else
	int (*getchar)()=&::getchar,(*putchar)(int)=&::putchar;
	inline IO &flush(){return fflush(stdout),*this;}
#endif
	template<typename Tp,typename enable_if<is_integral<Tp>::value>::type * =nullptr>
	inline void read(Tp &s){
		int f=1,ch=getchar();s=0;
		while(!isdigit(ch))f=(ch=='-'?-1:1),ch=getchar();
		while(ch == '0')ch = getchar();
		while(isdigit(ch))s=s*10+(ch^48),ch=getchar();
		s*=f;
	}
	template<typename Tp,typename enable_if<is_integral<Tp>::value>::type * =nullptr>
	inline void write(Tp x){
		if(x<0)putchar('-'),x=-x;
		static char sta[41];
		int top=0;
		do sta[top++]=x%10^48,x/=10;while(x);
		while(top)putchar(sta[--top]);
	}
	template<typename Tp>
	inline void writeln(const Tp &x){write(x);putchar('\n');}
	template<typename Tp>
	inline void writeSp(const Tp &x){write(x);putchar(' ');}
}io;

#define int long long

const int maxn = 3e5 + 10;

int T, n;
int a[maxn], b[maxn], c[maxn];
int s, t, k, m;
vector<int> p[4];
int cnt[4];

void f(int x, int z) { while (z--) c[p[x].back()] = 1, p[x].pop_back(); }
void print() { for (int i = 1; i <= n; i++) io.writeSp(c[i]); io.putchar('\n'); }

signed main() {
	freopen("slauqe.in","r",stdin);
	freopen("slauqe.out","w",stdout);
	io.read(T);
	while (T--) {
		io.read(n);
		p[0].clear(), p[1].clear(), p[2].clear(), p[3].clear(), s = t = 0;
		for (int i = 1; i <= n; i++) c[i] = 0;
		for (int i = 1; i <= n; i++) io.read(a[i]), s += a[i];
		for (int i = 1; i <= n; i++) io.read(b[i]), t += b[i];
		if ((s & 1) | (t & 1)) {
			io.writeln(-1);
			continue;
		}
		if (s < t) {
			for (int i = 1; i <= n; i++) swap(a[i], b[i]);
			swap(s, t);
		}
		for (int i = 1; i <= n; i++) p[(a[i] - 1 << 1) + b[i] - 1].push_back(i);
		k = s - t >> 1;
		while (k--) f(2, 1);
		m = n - (s - t >> 1), k = t - (s >> 1);	
		cnt[1] = p[0].size(), cnt[2] = p[3].size(), cnt[3] = min(p[1].size(), p[2].size());
		if (m == 0 || k == 0) {
			print();
			continue;
		}
		if (!cnt[1] && cnt[2] && cnt[3]) {
			if (k % 3 == 1) {
				if (cnt[2] == 1) {
					io.writeln(-1);
					continue;
				}
				k -= 4, f(3, 2), cnt[2] -= 2;
			} else if (k % 3 == 2) k -= 2, f(3, 1), cnt[2]--;
			while (cnt[2] >= 3 && k >= 6) k -= 6, f(3, 3), cnt[2] -= 3;
			while (cnt[3] && k >= 3) f(1, 1), f(2, 1), k -= 3, cnt[3]--;
			print();
			continue;
		}
		if (!cnt[2] && cnt[1] && cnt[3]) {
			if (k % 3 == 2) {
				if (cnt[1] == 1) {
					io.writeln(-1);
					continue;
				}
				k -= 2, f(0, 2), cnt[1] -= 2;
			} else if (k % 3 == 1) k--, f(0, 1), cnt[1]--;
			while (cnt[1] >= 3 && k >= 3) k -= 3, f(0, 3), cnt[1] -= 3;
			while (cnt[3] && k >= 3) f(1, 1), f(2, 1), k -= 3, cnt[3]--;
			print();
			continue;
		}
		int z = 0;
		while (cnt[3]) {
			if (z >= 0) p[1].pop_back(), p[2].pop_back(), z -= 3;
			else f(1, 1), f(2, 1), z += 3;
			cnt[3]--;
		}
		while (cnt[2]) {
			if (z >= 0) p[3].pop_back(), z -= 2;
			else f(3, 1), z += 2;
			cnt[2]--;
		}
		while (cnt[1]) {
			if (z >= 0) p[0].pop_back(), z--;
			else f(0, 1), z++;
			cnt[1]--;
		}
		if (z) io.writeln(-1);
		else print();
	}
	return 0;
}
