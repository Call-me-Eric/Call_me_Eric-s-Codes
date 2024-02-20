#include<bits/stdc++.h>
template <typename _Tp>void read(_Tp &x){
	char ch(getchar());bool f(false);while(!isdigit(ch))f|=ch==45,ch=getchar();
	x=ch&15,ch=getchar();while(isdigit(ch))x=x*10+(ch&15),ch=getchar();
	if(f)x=-x;
}
template <typename _Tp,typename... Args>void read(_Tp &t,Args &...args){read(t);read(args...);}
template <typename _Tp>inline void chmax(_Tp &a,const _Tp &b){a=a<b?b:a;}
const int N=1000005,NC=(1<<21)+5;typedef long long ll;
int a[N],b[N];ll pre[N];
int st[N],top,f[NC],M,n;
void build(int n){for(M=1;M<=n+2;M<<=1);}
void upd(int s,int t,int C){
	for(s+=M-1,t+=M+1;s^t^1;s>>=1,t>>=1){
		if(~s&1)chmax(f[s^1],C);
		if(t&1)chmax(f[t^1],C);
	}
}
void out(){for(int i=1;i<=M+n;++i)chmax(f[i],f[i>>1]);}
int main(){
	freopen("room.in", "r", stdin);
	freopen("room.out", "w", stdout);
	read(n);for(int i=1;i<=n;++i)read(a[i]),pre[i]=pre[i-1]+a[i];
	for(int i=1;i<=n+1;++i)read(b[i]);
	build(n);
	for(int i=1;i<=n+1;++i){
		while(top>=2&&b[i]>=b[st[top]]&&b[st[top]]<=b[st[top-1]]){
			ll cur=pre[st[top]-1]-pre[st[top-1]-1];
			if(b[st[top]]-cur>=0)upd(st[top-1],st[top]-1,b[st[top]]-cur);
			cur=pre[i-1]-pre[st[top]-1];
			if(b[st[top]]-cur>=0)upd(st[top],i-1,b[st[top]]-cur);
			--top;
		}
		st[++top]=i;
	}
	out();
	for(int i=1;i<top;++i){
		int mn=std::min(b[st[i]],b[st[i+1]]);ll cur=pre[st[i+1]-1]-pre[st[i]-1];
		for(int j=st[i];j<st[i+1];++j)printf("%lld%c",std::max((ll)f[j+M],mn-cur)," \n"[j==n]);
	}
	return 0;
}
