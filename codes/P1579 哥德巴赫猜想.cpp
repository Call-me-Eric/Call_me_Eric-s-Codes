#include<iostream>
#include<cmath>
using namespace std;
bool prime(int n)//判断是否是质数的函数
{
    int i;
    if(n==2)	return true;
    if(n%2==0)	return false;
    for(i=3;i<=sqrt(n);i+=2)
        if(n%i==0)
            return false;
    return	true; 
}
int main()
{
    int number;
    int a,b;
    int flag=0;
 
    cin>>number;//输入奇数
 
    for(a=2;;a++)//寻找第一个数a
    {
        for(b=a;b<=number-a-b;b++)//寻找第二个数b
        {
            if( prime(a) && prime(b) && prime(number-a-b) )//判断三个数是否都是质数
            {
                flag=1;
                cout<<a<<" "<<b<<" "<<number-a-b<<endl;//若都是质数，输出
                break;//终止内循环
            }
        }
        if(flag==1)	break;//终止外循环
    }
    return 0;
}

