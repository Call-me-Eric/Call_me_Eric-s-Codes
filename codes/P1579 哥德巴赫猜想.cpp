#include<iostream>
#include<cmath>
using namespace std;
bool prime(int n)//�ж��Ƿ��������ĺ���
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
 
    cin>>number;//��������
 
    for(a=2;;a++)//Ѱ�ҵ�һ����a
    {
        for(b=a;b<=number-a-b;b++)//Ѱ�ҵڶ�����b
        {
            if( prime(a) && prime(b) && prime(number-a-b) )//�ж��������Ƿ�������
            {
                flag=1;
                cout<<a<<" "<<b<<" "<<number-a-b<<endl;//���������������
                break;//��ֹ��ѭ��
            }
        }
        if(flag==1)	break;//��ֹ��ѭ��
    }
    return 0;
}

