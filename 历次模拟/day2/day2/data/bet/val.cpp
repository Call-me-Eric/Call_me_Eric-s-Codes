#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc,char** argv)
{
 registerValidation(argc,argv);//初始化校验器
 int n=inf.readInt(1,500000);
 inf.readEoln();
 for(int i=1;i<=n;i++) inf.readInt(1,n),inf.readSpace();
 inf.readEoln();
 inf.readEof();
}
