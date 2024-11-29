/*------------------------------------------------------------------------------
                           File Name                                        
                           SegmentTree.cpp                                       
--------------------------------------------------------------------------------
                            Description                                      
      En este archivo se encuentra ejemplos de uso de la clase             
      SegmentTree para la creacion y uso de arbol de segmentos                             
                                                                            
                                                                            
--------------------------------------------------------------------------------
                            Files History

        Name        Date        Description
        ffocilme    11/01/24    Refactoring code for legibility    
        ffocilme    05/09/24    Creation
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
class SegmentTree {
public:
    using vT = vector<T>;
    vT data,st;
    int n;

    SegmentTree(vT &a) {
        n = sz(a);
        data = a;
        st.resize(4 * n);
        build(1, 0, n - 1);
    }

    T query(int l, int r) { return query(1, 0, n - 1, l, r);}
    void update(int pos, T val) {update(1, 0, n - 1, pos, val);}

    int find(T& val) { return find(1, 0, n - 1, val);}
    int lower_bound(T& val) { return lower_bound(1, 0, n - 1, val);}
    int upper_bound(T& val) {return upper_bound(1, 0, n - 1, val);}

    // FIX ME : SUM default
    T operation(T& a, T& b) { return a + b; }
private:
    void build(int v, int l, int r) {
        if (l == r) {st[v] =  data[l]; return; }

        int m = mid(l, r);
        build(lc(v), l, m);
        build(rc(v), m + 1, r);
        
        //Fix me (Optional)
        T a = st[lc(v)];
        T b = st[rc(v)];
        st[v] = operation(a, b);
    }

    T query(int v, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return st[v];

        int m = mid(l, r);
        T a = query(lc(v), l, m, ql, qr);
        T b = query(rc(v), m + 1, r, ql, qr);

        return operation(a, b);
    }

    void update(int v, int l, int r, int pos, T val) {
        if (l == r) { st[v] = val; return; }
        int m = mid(l, r);
        if (pos <= m)  update(lc(v), l, m, pos, val);
        else update(rc(v), m + 1, r, pos, val);

        //Fix me (Optional)
        T a = st[lc(v)];
        T b = st[rc(v)];
        st[v] = operation(a, b);
    }

    int find(int v, int l, int r, T& val) {
        if (l == r) 
            return ((st[v] == val) ? 1 : -1);
        
        int m = mid(l, r);
        int i = find(lc(v), l, m, val);
       
        return ((i == -1) ? find(rc(v), m+1, r, val) : i);
    }

    int lower_bound(int v, int l, int r, T& val) {
        if (l == r) return ((st[v] >= val) ? 1 : -1);
        
        int m = mid(l, r);
        if (st[lc(v)] >= val) 
            return lower_bound(lc(v), l, m, val);
        
        return lower_bound(rc(v), m + 1, r, val);
    }

    int upper_bound(int v, int l, int r, T& val) {
        if (l == r) return ((st[v] > val) ? 1 : -1);
        
        int m = mid(l, r);
        if (st[lc(v)] > val)
            return upper_bound(lc(v), l, m, val);
        
        return upper_bound(rc(v), m + 1, r, val);
    }

    int lc(int v) { return 2 * v; }
    int rc(int v) { return 2 * v + 1; }
    int mid(int l, int r) { return (l + r) / 2; }
};

void example() {
    vi a = { 1, 2, 3, 4, 5 };
    SegmentTree<int> st(a);

    cout << st.query(0, 2) << endl;
    cout << st.query(1, 3) << endl;
    cout << st.query(2, 4) << endl;
    cout << st.query(3, 4) << endl;
    cout << st.query(0, 4) << endl;

    st.update(0, 100);
    cout << st.query(0, 4) << endl;

    int val = 5;
    cout << "Find: " << st.find(val) << endl;

    val = 22;
    cout << "Lower Bound: " << st.lower_bound(val) << endl;

    val = 3;
    cout << "Upper Bound: " << st.upper_bound(val) << endl;
}

int main() {
    FIN;
    example();
    return 0;
}
