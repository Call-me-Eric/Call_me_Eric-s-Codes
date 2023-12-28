#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
string s,ans,tmp;
bool book[30];
int sumask,sum;
int main(){
    ans = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
    cin >> s;
    int st = 0;
    for(int i = 0,len = s.length();i < len;i++){
        if(s[i] != '?'){
            if(book[s[i] - 'A']){
                while(s[st] != s[i]){
                    if(s[st] != '?'){
                        sum--;
                        book[s[st] - 'A'] = 0;
                    }
                    else{
                        sumask--;
                    }
                    st++;
                }
                st++;
            }
            else{
                book[s[i] - 'A'] = 1;
                sum++;
            }
        }
        else{
            sumask++;
        }
        if(sum + sumask == 26){
            tmp.erase();
            char k = 'A';
            for(int j = st;j <= i;j++){
                if(s[j] != '?'){
                    tmp += s[j];
                }
                else{
                    for(;book[k - 'A'];k++);
                    tmp += k;
                    k++;
                }
            }
            ans = min(ans,tmp);
            break;
        }
    }
    if(ans != "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ") cout << ans << endl;
    else cout << "-1" << endl;
    return 0;
}