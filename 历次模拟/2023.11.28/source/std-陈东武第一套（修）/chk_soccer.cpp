#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
int n,len[5000050],cnt=0,res[5000050];
string s,t,t1,t2;
int main(int argc, char* argv[]){
    registerTestlibCmd(argc, argv);
	n=inf.readInt();
	s=inf.readToken();
	t1=ouf.readToken();
	t2=ans.readToken();
	if(t1!=t2){
		quitf(_wa,"WA!");
		return 0;
	}
	if(t1[0]=='N'){
    	quitf(_ok, "Correct.");
    	return 0;
	}
	t=ouf.readToken();
	if(t.size()!=n){
		quitf(_wa,"WA!");
		return 0;
	}
	int lst=-1;
	for(int i=0;i<n;i++){
		if(t[i]=='R'){
			if(lst<(i-1)) len[++cnt]=i-lst-1;
			lst=i;
		}
	}
	if(lst<(n-1)) len[++cnt]=n-1-lst;
	int pre=0,suf=0;
	for(int i=1;i<=cnt;i++) suf+=len[i];
	for(int i=0;i<=cnt;i++){
		pre+=len[i];
		suf-=len[i];
		int l=pre,r=n-suf-1;
		if(i) l+=i-1;
		if(i<cnt) r-=cnt-i-1;
		if(l<=r){
			res[l]++;
			res[r+1]--;
		}
	}
	for(int i=1;i<n;i++) res[i]+=res[i-1];
	for(int i=0;i<n;i++){
		if((res[i]&&s[i]=='1')||(!res[i]&&s[i]=='0')){
			quitf(_wa,"WA!");
			return 0;
		}
	}
    quitf(_ok, "Correct.");
}
