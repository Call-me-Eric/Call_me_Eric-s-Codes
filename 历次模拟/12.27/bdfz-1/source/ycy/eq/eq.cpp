#include <bits/stdc++.h>

#ifndef _STKLIB_MODINT_HPP
# define _STKLIB_MODINT_HPP

namespace StK {

template <typename Type, Type P, typename MulType = Type>
class ModInt {
   public:
    typedef Type DataType;
    
    static constexpr Type MOD = P;

   protected:
    Type x;

   public:
    template <typename ProType>
    class Protected {
       protected:
        ModInt &data;
       public:
        Protected(ModInt &data) : data(data) {}
        ModInt &replace(ProType a) { return data.replace(a); }
    };
    
    constexpr ModInt() : x(0) {}
    constexpr ModInt(Type c) : x(c) {}
    explicit constexpr operator Type() const { return x; }
    explicit constexpr operator bool() const { return x != 0; }
    constexpr bool operator!() const { return x == 0; }
    constexpr Type &data() { return x; }
    constexpr const Type data() const { return x; }
    template <typename ProType>
    constexpr ModInt &replace(ProType a) { return x = (a %= P) < 0 ? a + P : a, *this; }
    template <typename ProType = Type>
    Protected<ProType> protect() const { return *this; }
    friend constexpr ModInt operator+(ModInt a, const ModInt b) { return (a.x += b.x) >= P ? a.x - P : a.x; }
    friend constexpr ModInt operator-(ModInt a, const ModInt b) { return (a.x -= b.x) < 0 ? a.x + P : a.x; }
    friend constexpr ModInt operator*(ModInt a, const ModInt b) { return MulType(a.x) * b.x % P; }
    constexpr ModInt &operator+=(const ModInt b) { return (x += b.x) >= P ? x -= P, *this : *this; }
    constexpr ModInt &operator-=(const ModInt b) { return (x -= b.x) < 0 ? x += P, *this : *this; }
    constexpr ModInt &operator*=(const ModInt b) { return x = MulType(x) * b.x % P, *this; }
    template <typename ExpType> constexpr ModInt pow(ExpType exp) const { 
        ModInt base(*this), ans(exp & 1 ? base : ModInt(1));
        while (exp >>= 1) if (base *= base, exp & 1) ans *= base; return ans;
    }
    template <typename ExpType> constexpr ModInt &pows(ExpType exp) { return *this = pow(exp); }
    constexpr ModInt inv() const { return pow(P - 2); }
    constexpr ModInt operator~() const { return inv(); }
    constexpr ModInt &invs() { return pows(P - 2); }
    friend constexpr ModInt operator/(ModInt a, const ModInt b) { return a * ~b; }
    constexpr ModInt &operator/=(const ModInt b) { return operator*=(~b); }
    constexpr ModInt &operator++() { return operator+=(1); }
    constexpr ModInt &operator--() { return operator-=(1); }
    constexpr ModInt operator++(int) { ModInt Tmp = *this; return operator++(), Tmp; }
    constexpr ModInt operator--(int) { ModInt Tmp = *this; return operator--(), Tmp; }
    constexpr ModInt operator+() const { return *this; }
    constexpr ModInt operator-() const { return ModInt(0) - *this; }
    constexpr bool operator==(const ModInt a) const { return x == Type(a); }
    constexpr bool operator!=(const ModInt a) const { return x != Type(a); }
    friend constexpr bool operator<(const ModInt a, const ModInt b) { return a.x < b.x; }
    friend constexpr bool operator>(const ModInt a, const ModInt b) { return a.x > b.x; }
    friend constexpr bool operator<=(const ModInt a, const ModInt b) { return a.x <= b.x; }
    friend constexpr bool operator>=(const ModInt a, const ModInt b) { return a.x >= b.x; }
# if __cpp_impl_three_way_comparison >= 201907L
    friend constexpr Type operator<=>(const ModInt a, const ModInt b) { return a.x - b.x; }
# endif

# ifdef _GLIBCXX_ISTREAM

    template <typename _CharT, class _Traits>
    friend std::basic_istream<_CharT, _Traits>&
    operator>>(std::basic_istream<_CharT, _Traits> &in_stream, ModInt &a) {
        return in_stream >> a.x;
    }

    template <typename ProType, typename _CharT, class _Traits>
    friend std::basic_istream<_CharT, _Traits>&
    operator>>(std::basic_istream<_CharT, _Traits> &in_stream, Protected<ProType> a) {
        ProType temp_protect;
        in_stream >> temp_protect;
        a.replace(temp_protect);
        return in_stream;
    }

# endif

# ifdef _GLIBCXX_OSTREAM

    template <typename _CharT, class _Traits>
    friend std::basic_ostream<_CharT, _Traits>&
    operator<<(std::basic_ostream<_CharT, _Traits> &out_stream, const ModInt a) {
        return out_stream << a.x;
    }

# endif

};

}  // namespace StK

#endif

using MInt = StK::ModInt<int, 998244353, int64_t>;

int main() {
    freopen("eq.in", "r", stdin);
    freopen("eq.out", "w", stdout);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    const int m = 1 << std::__lg(q + 1) + 2;
    std::vector<std::vector<std::vector<MInt>>> seg_eq(m);
    {
        std::vector<int> last_time(n);
        std::vector<std::vector<MInt>> now_eq(n, std::vector<MInt>(n + 1));
        for (auto &v : now_eq) {
            for (auto &x : v) {
                std::cin >> x;
            }
        }

        auto _FS_addeq = [&](auto self, int u, int l, int r, int L, int R, const std::vector<MInt> &eq) -> void {
            if (l >= L && r <= R) {
                seg_eq[u].push_back(eq);
                return;
            }
            int mid = l + r >> 1;
            if (L <= mid) {
                self(self, u << 1, l, mid, L, R, eq);
            }
            if (R > mid) {
                self(self, u << 1 | 1, mid + 1, r, L, R, eq);
            }
        };
        auto addeq = [&](int L, int R, const std::vector<MInt> &eq) {
            _FS_addeq(_FS_addeq, 1, 0, q, L, R, eq);
        };

        for (int i = 1; i <= q; ++i) {
            int z;
            std::cin >> z;
            --z;
            addeq(last_time[z], i - 1, now_eq[z]);
            last_time[z] = i;
            for (auto &x : now_eq[z]) std::cin >> x;
        }

        for (int i = 0; i < n; ++i) {
            addeq(last_time[i], q, now_eq[i]);
        }
    }

    std::vector<std::pair<int, std::vector<MInt>>> sta;
    sta.reserve(n);
    auto _FS_solve = [&](auto self, int u, int l, int r) -> void {
        size_t recent_size = sta.size();

        bool fail = false;
        for (auto &f : seg_eq[u]) {
            for (const auto [fir, g] : sta) {
                MInt sub = -f[fir];
                for (int i = 0; i <= n; ++i) f[i] += sub * g[i];
            }
            int p = std::find_if(f.begin(), f.end(), [&](auto x) { return bool(x); }) - f.begin();
            if (p == n) {
                fail = true;
                break;
            } else if (p < n) {
                MInt x = ~f[p];
                for (auto &y : f) y *= x;
                sta.emplace_back(p, f);
            }
        }
        
        if (fail) {
            for (int i = l; i <= r; ++i) std::cout << "No" << '\n';
        } else if (l == r) {
            if (sta.size() < n) {
                std::cout << "Many" << '\n';
            } else {
                std::vector<MInt> val(n), ans(n);
                for (int i = 0; i < n; ++i) val[i] = sta[i].second[n];
                for (int i = n - 1; i >= 0; --i) {
                    const int iu = sta[i].first;
                    for (int j = i - 1; j >= 0; --j) {
                        val[j] -= val[i] * sta[j].second[iu];
                    }
                    ans[iu] = val[i];
                }
                for (int i = 0; i < n; ++i) std::cout << ans[i] << " \n"[i + 1 == n];
            }
        } else {
            int mid = l + r >> 1;
            self(self, u << 1, l, mid);
            self(self, u << 1 | 1, mid + 1, r);
        }
        
        sta.resize(recent_size);
    };
    _FS_solve(_FS_solve, 1, 0, q);

    return 0;
}
