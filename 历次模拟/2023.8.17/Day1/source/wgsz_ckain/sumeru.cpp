#include<bits/stdc++.h>
#define pii pair<int, int>
#define fr first
#define sc second
#define dle double
using namespace std;
inline int rd(void){
	int s=0, f=1; char c=getchar();
	while(c<'0' || c>'9') {if(c=='-') f=0; c=getchar();}
	while(c>='0' && c<='9') {s=s*10+c-'0'; c=getchar();}
	return f? s:-s;
}

dle eps=1e-12;

inline int comp(dle a, dle b){
	if(abs(a-b)<=eps) return 0;
	return a<b? -1:1;
}

struct Node{
	dle x, y;
	inline Node(dle _x=0, dle _y=0){x=_x, y=_y;}
	inline Node operator +(const Node &o)const{return Node(x+o.x, y+o.y);}
	inline Node operator -(const Node &o)const{return Node(x-o.x, y-o.y);}
	inline dle operator *(const Node &o)const{return x*o.y-y*o.x;}
	inline bool operator ==(const Node &o)const{return comp(x, o.x)==0 && comp(y, o.y)==0;}
	inline bool operator <(const Node &o)const{return comp(x, o.x)==0? comp(x, o.x)==-1:comp(y, o.y)==-1;}
};

inline Node getin(){
	dle x=rd(), y=rd(), z=rd();
	if(comp(x, 0)==0){//x==0
		if(comp(y, 0)==0) return comp(z, 0)==0? Node(-1, -1):Node(0, 0);
		else return Node(0, 1);
	}
	dle w=1.0/(1.0+y/x+z/x);
	return Node(w, w*y/x);
}

signed main(){
	freopen("sumeru.in", "r", stdin);
	freopen("sumeru.out", "w", stdout);
	int T=rd();
	
	Node a[4], b;
	const Node zero(-1, -1), epsd[2]={Node(1e-7, 1e-8), Node(1e-10, 1e-9)};
	
	while(T--){
		a[1]=getin(), a[2]=getin(), a[3]=getin(), b=getin();
		
		//特判 
		if(b==zero){
			puts("YES");
			continue;
		}
		if(a[1]==zero && a[2]==zero && a[3]==zero){
			puts("NO");
			continue;
		}
		//
		
		//处理零向量 
		sort(a+1, a+1+3);
		if(a[2]==zero) a[2]=a[3]+epsd[0];
		if(a[1]==zero) a[1]=a[2]+epsd[1];
		//
		
		bool flag=0;
		for(int i=1; i<=3; i++) if(b==a[i]){
			flag=1;
			break;
		}
		if(!flag){
			flag=1;
			if(((a[2]-a[1])*(b-a[1])) * ((b-a[1])*(a[3]-a[1])) < 0) flag=0;
			if(((a[1]-a[2])*(b-a[2])) * ((b-a[2])*(a[3]-a[2])) < 0) flag=0;
			if(((a[1]-a[3])*(b-a[3])) * ((b-a[3])*(a[2]-a[3])) < 0) flag=0;
		}
		puts(flag? "YES":"NO");
	}
	return 0;
}
