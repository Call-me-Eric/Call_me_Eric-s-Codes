#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

#include<iostream>
#include <vector>

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>

using namespace std;
const int MAX = 3000 + 10;
using namespace std;

class bigint{
friend ostream& operator<<(ostream &, const bigint &);
friend istream& operator>>(istream &, bigint&);

friend bigint operator+(const bigint&, const bigint&);
friend bigint operator-(const bigint&, const bigint&);
friend bigint operator*(const bigint&, const bigint&);
friend bigint operator/(const bigint&, const bigint&);
friend bigint operator%(const bigint&, const bigint&);
friend bigint operator>>(const bigint&, int);

friend bool operator<(const bigint&, const bigint&);
friend bool operator>(const bigint &, const bigint &);
friend bool operator<=(const bigint&, const bigint&);
friend bool operator>=(const bigint &, const bigint &);
friend bool operator==(const bigint &, const bigint &);
friend bool operator!=(const bigint &, const bigint &);
friend bool operator!=(const bigint &, const int &);

public:
    bigint() {
        memset(nums, 0, sizeof(nums));
        len = 1;
    }
    bigint(int num) {
        memset(nums, 0, sizeof(nums));
        *this = num;
    }
    bigint(const char *num) {
        memset(nums, 0, sizeof(nums));
        *this = num;
    }

    bigint& operator=(const char* right) {
        len = strlen(right);
        for (int i = 0; i < len; ++i) {
            nums[i] = right[len - i - 1] - '0';
        }
        return *this;
    }
    bigint& operator=(int right) {
        char c_right[MAX];
        sprintf(c_right, "%d", right);
        *this = c_right;

        return *this;
    }
    bigint operator>>=(int n) {
        if (n >= this->len) {
            *this = 0;
        } else {
            int i = 0;
            for (; n < this->len; ++i, ++n) {
                this->nums[i] = this->nums[n];
            }
            this->len = i;
        }
        return *this;
    }

    bigint operator+=(const bigint &a) {
        return (*this = *this + a);
    }
    bigint operator-=(const bigint &a) {
        return (*this = *this - a);
    }
    bigint operator*=(const bigint &a) {
        return (*this = *this * a);
    }

    int& operator[](size_t index) {
        return this->nums[index];
    }
    const int& operator[](size_t index) const {
        return this->nums[index];
    }

    int length() const {
        return len;
    }
    string str() const {
        string str;
        for (int i = len - 1; i >= 0; --i) {
            if (nums[MAX] == 1) {
                str.push_back('-');
            }
            str.push_back(nums[i] + '0');
        }
        return str;
    }
    void clearnZero() {
        while(len > 1 && !nums[len -1])
            --len;
    }

    static bigint pow_bigint(bigint a, int n) {
        bigint res = 1;
        while (n--) {
            res *= a;
        }
        return res;
    }
private:
    int len;
    int nums[MAX + 1];
};

ostream& operator<<(ostream &out, const bigint &num) {
    out << num.str();
    return out;
}
istream& operator>>(istream &in, bigint &num) {
    string ss;
    in >> ss;
    num = ss.c_str();
    return in;
}

bigint operator + (const bigint &a, const bigint &b) {
    bigint res;
    int len = a.len > b.len ? a.len : b.len;
    int c = 0;
    int i;
    for (i = 0; i < len; ++i) {
        int sum = 0;
        if (i < a.len) sum += a.nums[i];
        if (i < b.len) sum += b.nums[i];
        sum += c;
        res.nums[i] = sum % 10;
        c = sum / 10;
    }
    if (c) {res.nums[i++] = c;}
    res.len = i;
    return res;
}
bigint operator - (const bigint &a, const bigint &b) {
    bigint res = 0;
    if (a >= b) {
        for (int i = 0, c = 0; i < a.len; ++i) {
            int s = (i < b.len) ? (a[i] - b[i] - c) : (a[i] - c);
            if (s < 0) {
                s += 10;
                c = 1;
            } else {
                c = 0;
            }
            res[i] = s;
        }
        int len;
        for (len = a.len; len > 1; --len) {
            if (res[len - 1] != 0)
                break;
        }
        res.len = len;
    }

    return res;
}
bigint operator * (const bigint &a, const bigint &b) {
    bigint res;
    res.len = a.len + b.len;
    for (int i = 0; i < a.len; ++i) {
        for (int j = 0; j < b.len; ++j) {
            res[i + j] += a.nums[i] * b.nums[j];
        }
    }
    for (int i = 0; i < res.len - 1; ++i) {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    res.clearnZero();
    return res;
}
bigint operator / (const bigint &a, const bigint &b) {
    bigint a1 = a;
    bigint sum = 0;
    int c = 0;
    assert(b != 0);
    while (a1 >= b) {
        bigint n_10 = bigint::pow_bigint(10, a1.len - b.len - c);
        int i = 9;
        bigint inter = 0;
        for (; i > 0; --i) {
            inter = b * i * n_10;
            if (a1 >= inter) {
                break;
            }
        }
        sum += i * n_10;
        if (i != 0) {
            a1 -= inter;
            c = 0;
        } else {
            c += 1;
        }
    }

    return sum;
}
bigint operator % (const bigint &a, const bigint &b) {
    bigint res = 0;
    res = a - b * (a / b);
    return res;
}

bool operator < (const bigint &a, const bigint &b){
    if (a.len != b.len)
        return a.len < b.len;
    for (int i = a.len - 1; i >= 0; --i) {
        if (a.nums[i] != b.nums[i])
            return a.nums[i] < b.nums[i];
    }
    return false;
}
bool operator>(const bigint &a, const bigint &b){return (b < a);}
bool operator==(const bigint &a, const bigint &b){return !(a < b) && !(a > b);}
bool operator!=(const bigint &a, const bigint &b){return (a > b) || (a < b);}
bool operator!=(const bigint &a, const int &b){bigint c = b;return a != c;}
bool operator!=(const int &b, const bigint &a){bigint c = b;return a != c;}
bool operator<=(const bigint &a, const bigint &b){return !(a > b);}
bool operator>=(const bigint &a, const bigint &b){return !(a < b);}
int main(){
	return 0;
}

