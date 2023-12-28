#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc,char** argv)
{
 registerValidation(argc,argv);//初始化校验器
 int n=inf.readInt(1,1e5),m=(inf.readSpace(),inf.readInt(1,1e6));
 long long k=(inf.readSpace(),inf.readLong()),sum=0;
 ensure(k>=0);
 inf.readEoln();
 for(int i=1;i<=n;i++) sum+=inf.readInt(1,m),inf.readSpace();
 ensure(k<=sum);
// ensure(sum<=1000000); 
 inf.readEoln();
 inf.readEof();
}
