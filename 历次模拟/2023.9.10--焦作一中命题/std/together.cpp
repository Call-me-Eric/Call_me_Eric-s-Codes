#include<bits/stdc++.h>
using namespace std;
typedef unsigned int UI;
const int N = 3e5+7;
int n,m,a[N],b[N];
int lp[N],rp[N],stk[N],top=0;
int lson[N],rson[N];
void dfs(int x,int l,int r)
{
	if(l>r)return;
	lp[x]=l;rp[x]=r;
	if(l==r)return;
	dfs(lson[x],l,x-1);
	dfs(rson[x],x+1,r);
}
UI ans[N];
struct BIT
{
	UI c[N];
	void upd(int x,UI v)
	{
		for(int i=x;i<=n;i+=i&-i)
		c[i]+=v;
	}
	UI ask(int x)
	{
		UI res=0;
		for(int i=x;i;i-=i&-i)
		res+=c[i];
		return res;
	}
	UI qry(int l,int r)
	{
		return ask(r)-ask(l-1);
	}
}C[28];
struct IO{
    static const int S=1<<21;
    char buf[S],*p1,*p2;int st[105],Top;
    ~IO(){clear();}
    inline void clear(){fwrite(buf,1,Top,stdout);Top=0;}
    inline void pc(const char c){Top==S&&(clear(),0);buf[Top++]=c;}
    inline char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;}
    inline IO&operator >> (char&x){while(x=gc(),x==' '||x=='\n'||x=='\r');return *this;}
    template<typename T>inline IO&operator >> (T&x){
        x=0;bool f=0;char ch=gc();
       while(!isdigit(ch)){if(ch=='-') f^=1;ch=gc();}
        while(isdigit(ch)) x=(x<<3)+(x<<1)+ch-'0',ch=gc();
        f?x=-x:0;return *this;
    }
    inline IO&operator << (const char c){pc(c);return *this;}
    template<typename T>inline IO&operator << (T x){
        if(x<0) pc('-'),x=-x;
        do{st[++st[0]]=x%10,x/=10;}while(x);
        while(st[0]) pc('0'+st[st[0]--]);return *this;
    }
}fin,fout;
void put(char c)
{
	fout.pc(c);
}
const UI base = 114514;
const UI hbase = 57257;
struct Query
{
	int c,l,r,u;
};
vector<Query> Gr[N],Gl[N];	
UI s[4][N],rv[N],lv[N];
vector<Query> G[N];
int main()
{
	freopen("together.in","r",stdin);
	freopen("together.out","w",stdout);
	fin>>n>>m;
	for(int i=1;i<=n;i++)fin>>a[i];
	for(int i=1;i<=n;i++)fin>>b[i];
	for(int i=1;i<=n;i++)
	{
		s[1][i]=s[1][i-1]+b[i];
		s[0][i]=s[0][i-1]+(UI)b[i]*i;
		s[2][i]=s[2][i-1]+(UI)b[i]*i*(i-1);
		s[3][i]=s[3][i-1]+(UI)b[i]*(i-1);
	}
	for(int i=1;i<=n;i++)
	{
		while(top&&a[stk[top]]<a[i])lson[i]=stk[top--];
		if(top)rson[stk[top]]=i;
		stk[++top]=i;
	}
	dfs(stk[1],1,n);
	for(int i=1;i<=n;i++)
	{
		rv[i]=(UI)(i+rp[i])*(rp[i]-i+1);
		lv[i]=(UI)(lp[i]+i)*(i-lp[i]+1);
	}
	for(int i=1;i<=m;i++)
	{
		int tp,l,r;
		fin>>tp>>l>>r;
		if(tp==1)
		{
			Gr[r].push_back((Query){1,r,r,i});
			Gr[l-1].push_back((Query){-1,r,r,i});
			Gl[r].push_back((Query){1,l,l,i});
			Gl[l-1].push_back((Query){-1,l,l,i});
			ans[i]=s[1][r]-s[1][l-1];
			ans[i]*=base;
		}
		else 
		{
			ans[i]=(s[0][r]-s[0][l-1])*r
				  -(s[1][r]-s[1][l-1])*(l-1)*r
				  -(s[2][r]-s[2][l-1])
				  +(s[3][r]-s[3][l-1])*(l-1);
			ans[i]*=base;
			G[l-1].push_back((Query){-1,l,r,i});
			G[r].push_back((Query){1,l,r,i});
		}
	}
	for(int i=1;i<=n;i++)
	{
		C[0].upd(rp[i],(UI)b[i]*rp[i]);
		C[1].upd(rp[i],b[i]);
		C[2].upd(lp[i],(UI)b[i]*lp[i]);
		C[3].upd(lp[i],b[i]);
		
		C[4].upd(rp[i],(UI)b[i]*i*rv[i]);
		C[5].upd(rp[i],(UI)b[i]*i*rp[i]);
		C[6].upd(rp[i],(UI)b[i]*i*rp[i]*rp[i]);
		C[7].upd(rp[i],(UI)b[i]*rv[i]);
		C[8].upd(rp[i],(UI)b[i]*rp[i]);
		C[9].upd(rp[i],(UI)b[i]*rp[i]*rp[i]);
		
		C[10].upd(rp[i],(UI)b[i]*i*i);
		C[11].upd(rp[i],(UI)b[i]*i);
		C[12].upd(rp[i],(UI)b[i]*i*(i-1));
		C[13].upd(rp[i],(UI)b[i]*i*i*(i-1));
		C[14].upd(rp[i],(UI)b[i]);
		C[15].upd(rp[i],(UI)b[i]*(i-1));
		
		C[16].upd(lp[i],(UI)b[i]*lv[i]);
		C[17].upd(lp[i],(UI)b[i]*lp[i]*lp[i]);
		C[18].upd(lp[i],(UI)b[i]*lp[i]);
		C[19].upd(lp[i],(UI)b[i]*(i-1)*lv[i]);
		C[20].upd(lp[i],(UI)b[i]*(i-1)*lp[i]*lp[i]);
		C[21].upd(lp[i],(UI)b[i]*(i-1)*lp[i]);
		
		C[22].upd(lp[i],(UI)b[i]*i*i);
		C[23].upd(lp[i],(UI)b[i]*i);
		C[24].upd(lp[i],(UI)b[i]);
		C[25].upd(lp[i],(UI)b[i]*(i-1)*i*i);
		C[26].upd(lp[i],(UI)b[i]*(i-1)*i);
		C[27].upd(lp[i],(UI)b[i]*(i-1));
		for(auto U:Gr[i])
		{
			int c=U.c,r=U.r,u=U.u;
			ans[u]+=(UI)base*c*(C[0].qry(1,r)+(UI)r*C[1].qry(r+1,n));
		}
		for(auto U:Gl[i])
		{
			int c=U.c,l=U.l,u=U.u;
			ans[u]-=(UI)base*c*(C[2].qry(l,n)+(UI)l*C[3].qry(1,l-1));
		}
		for(auto U:G[i])
		{
			int c=U.c,l=U.l,r=U.r,u=U.u;
			ans[u]+=(UI)c*C[4].qry(1,r)*hbase;
			ans[u]+=(UI)c*C[5].qry(1,r)*base*r;
			ans[u]-=(UI)c*C[6].qry(1,r)*base;
			ans[u]-=(UI)c*C[7].qry(1,r)*(l-1)*hbase;
			ans[u]-=(UI)c*C[8].qry(1,r)*(l-1)*base*r;
			ans[u]+=(UI)c*C[9].qry(1,r)*(l-1)*base;
			
			ans[u]+=(UI)c*C[10].qry(r+1,n)*hbase*r;
			ans[u]+=(UI)c*C[11].qry(r+1,n)*hbase*(r-l+1)*r;
			ans[u]-=(UI)c*C[12].qry(r+1,n)*hbase*(r-l+1);
			ans[u]-=(UI)c*C[13].qry(r+1,n)*hbase;
			ans[u]-=(UI)c*C[14].qry(r+1,n)*hbase*r*r*(l-1);
			ans[u]+=(UI)c*C[15].qry(r+1,n)*hbase*(l-1)*r;
			
			ans[u]-=(UI)c*C[16].qry(l,n)*hbase*r;
			ans[u]-=(UI)c*C[17].qry(l,n)*base*r;
			ans[u]+=(UI)c*C[18].qry(l,n)*base*r*l;
			ans[u]+=(UI)c*C[19].qry(l,n)*hbase;
			ans[u]+=(UI)c*C[20].qry(l,n)*base;
			ans[u]-=(UI)c*C[21].qry(l,n)*base*l;
			
			ans[u]-=(UI)c*C[22].qry(1,l-1)*hbase*r;
			ans[u]-=(UI)c*C[23].qry(1,l-1)*hbase*r;
			ans[u]+=(UI)c*C[24].qry(1,l-1)*hbase*r*l*(l-1);
			ans[u]+=(UI)c*C[25].qry(1,l-1)*hbase;
			ans[u]+=(UI)c*C[26].qry(1,l-1)*hbase;
			ans[u]-=(UI)c*C[27].qry(1,l-1)*hbase*l*(l-1);
		}
	}	
	for(int i=1;i<=m;i++)fout<<ans[i],put('\n');
	return 0;
}


