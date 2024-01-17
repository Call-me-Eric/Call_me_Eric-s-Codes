#include<iostream>
#include<cstdio>
#include<sstream>
#include<string>
using namespace std;
const int MAXN=1e6+100;
int s[MAXN],p[51]={2,3,5,7,11,19,41,61,89,409,449,499,881,991,6469,6949,9001,9049,9649,9949,60649,666649,946669};
bool inSub(int x,int y) {
	stringstream SIO;
	SIO<<x<<' '<<y<<endl;
	string s,t;
	SIO>>s>>t;
	int len=0;
	for(int i=0;i<t.size();i++) {
		if(t[i]==s[len]) ++len;
		if(len==s.size()) return 1;
	}
	return 0;
}
void Query(int n) {
	for(int i=1;i<=n;i++) {
		bool flag=0;
		for(int j=0;j<23;j++) {
			if(inSub(p[j],i)) {flag=1; break;}
		}
		s[i]=s[i-1]+!flag;
	}
}
int main() {
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	int T,l,r; cin>>T; Query(1e5);
	while(T--) cin>>l>>r,cout<<s[r]-s[l-1]<<endl;
	return 0;
}