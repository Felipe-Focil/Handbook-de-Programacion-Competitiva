/*------------------------------------------------------------------------------
                           File Name
                           FenwickTree.cpp
--------------------------------------------------------------------------------
                            Description
      En este archivo se encuentra ejemplos de uso de la clase
      FenwickTree para la creacion y uso de Fenwick Tree / Binary Index Tree


--------------------------------------------------------------------------------
                            Files History

        Name        Date        Description
        ffocilme    11/01/24    Creation
--------------------------------------------------------------------------------
*/


#include <bits/stdc++.h>

#define FIN ios::ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
#define forn(i,a,b) for(int i = int(a); i < int(b);i++)
#define pb push_back
#define all(v) v.begin(),v.end()
#define sz(a) int(a.size())
#define coutBool(a) cout << ((a) ? "YES" : "NO")<<endl
#define mp make_pair
#define fi first
#define se second
#define debug(x) cout<<#x<<" : "<<x<<endl

using namespace std;

using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vs = vector<string>;
using pi = pair<int, int>;
using u64 = uint64_t;

template<typename T>
class FenwickTree {
public:
    using vT = vector<T>;

    vT bit;
    int n;
    FenwickTree(int s) {
        n = s;
        bit.assign(s, 0);
    }

    FenwickTree(vector<int> const& a) : FenwickTree(a.size()) {
        forn(i, 0, n) {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) { return sum(r) - sum(l - 1); }

    void add(int i, int k) {
        for (; i < n; i = i | (i + 1))
            bit[i] += k;
    }
};

template<typename T>
class FenwickTreeMin {
public:
    using vT = vector<T>;
    vT bit;
    int n;
    const int INF = 1e9;
    FenwickTreeMin(int s) {
        n = s;
        bit.assign(n, INF);
    }
    FenwickTreeMin(vT a) : FenwickTreeMin(sz(a)) {
        forn(i, 0, n) update(i, a[i]);
    }

    int getmin(int r) {
        int ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    void update(int i, int k) {
        for (; i < n; i = i | (i + 1))
            bit[i] = min(bit[i], k);
    }
};


template<typename T>
class FenwickTree2D {
    using vT = vector<T>;
    using vvT = vector<vT>;
    vvT bit;
    int n, m;
public:
    FenwickTree2D(int x, int y) : n(x), m(y) {
        bit.assign(n, vT(m, 0));
    }
    FenwickTree2D(const vvT& mt) : FenwickTree2D(sz(mt), sz(mt[0])) {
        forn(i,0,n)
            forn(j,0,m) add(i, j, mt[i][j]);
    }

    int sum(int x, int y) {
        int ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    int sum(int x, int y, int x2, int y2) {
        return sum(x2, y2) - sum(x-1, y2) - sum(x2, y-1) + sum(x-1, y-1);
    }

    void add(int x, int y, int d) {
        for (int i = x; i < n; i = i | (i + 1))
            for (int j = y; j < m; j = j | (j + 1))
                bit[i][j] += d;
    }
};

int main(){
    FenwickTree<int> ft(5);
    FenwickTree2D<int> ft2d(4,4);
    
    ft.add(0,5);
    ft.add(1,3);
    ft.add(2,3);

    cout<<ft.sum(0,2)<<endl;

    ft2d.add(1,1,5);
    ft2d.add(2,3,5);
    
    cout<<ft2d.sum(0,2)<<endl;
}
