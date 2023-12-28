#include<bits/stdc++.h>
#define ll long long 
#define P 20
using namespace std;
int n,q,x;
ll s1,s2;
int main(){
	freopen("war1.in","w",stdout); 
	srand(time(0)); 
	n=q=10; 
	cout<<n<<' '<<q<<endl;
	for(int i=2; i<=n; i++){
		s1=rand()*rand()+rand(); s1%=i-1;
		cout<<s1+1<<' '<<i<<endl;
	}
	for(int i=1; i<=n; i++){
		s1=rand()*rand()+rand(); s1%=P;
		cout<<s1+1<<' ';
		s1=rand()*rand()+rand(); s1%=P;
		cout<<s1+1<<endl;
	}
	for(int i=1; i<=q; i++){
		x=rand()+rand(); x%=n; cout<<x+1<<' ';
		x=rand()+rand(); x%=n; cout<<x+1<<' ';
		s1=rand()*rand()+rand(); s1%=P; cout<<s1+1<<endl;
	}
} 
