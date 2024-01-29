#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc,char** argv)
{
 registerValidation(argc,argv);//初始化校验器
 int T=inf.readInt(1,5e5);inf.readEoln();
 int k=0;
 while(T--){
 	int n=inf.readInt(1,1e5);inf.readEoln();
// 	ensure(n%2==0);
 	k+=n;
 	ensure(k<=5e5);
 	for(int i=1;i<=n;i++) inf.readInt(0,(1<<30)-1),inf.readSpace();
 	inf.readEoln();
 }
 inf.readEof();
}
