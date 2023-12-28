#include "testlib_lemon.h"
#include <vector>
#include <set>
using namespace std;

bool check(int n, vector<int> a, vector<vector<int>> e)
{
    int p = a.back() + 1;
    vector<int> deg(p);
    set<int> S;
    for (int i = 0; i < n; i++)
        S.insert(a[i]);
    set<int> S2 = S;
    for (int i = 0; i < p; i++)
    {
        if (e[i][i])
            quitf(_wa, "e[i][i] = 1");
        for (int j = 0; j < p; j++)
            if (e[i][j])
                deg[i]++;
    }
    for (int i = 0; i < p; i++)
        for (int j = 0; j < p; j++)
            if (e[i][j] != e[j][i])
                quitf(_wa, "e[i][j] != e[j][i]");
    for (int i = 0; i < p; i++)
    {
        if (!S.count(deg[i]))
        {
            // cerr << "!" << endl;
            return false;
        }
        S2.erase(deg[i]);
    }
    return S2.size() == 0;
}

int main(int argc, char **argv)
{
    registerLemonChecker(argc, argv);
    int n = inf.readInt();
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        a[i] = inf.readInt();
    vector<vector<int>> e(a.back() + 1, vector<int>(a.back() + 1));
    for (int i = 0; i < a.back() + 1; i++)
    {
        string s = ouf.readLine();
        while (s.back() != '1' && s.back() != '0')
            s.pop_back();
        ensure((int)s.size() == a.back() + 1);
        for (int j = 0; j < a.back() + 1; j++)
        {
            ensure(s[j] == '1' || s[j] == '0');
            if (s[j] == '1')
                e[i][j] = 1;
        }
    }
    if (check(n, a, e))
        quitf(_ok, "sto wind_whisper khin shr_ orz");
    else
        quitf(_wa, "your answer is incorrect");
    return 0;
}