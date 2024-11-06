/*------------------------------------------------------------------------------
                           File Name
                           FenwickTree.cpp
--------------------------------------------------------------------------------
                            Description
      En este archivo se encuentra ejemplos de uso de la clase
      Sparse Table para la creacion y uso de Sparse Table para operaciones
	  rapidas como min,max,gcd


--------------------------------------------------------------------------------
                            Files History

        Name        Date        Description
        ffocilme    11/06/24    Creation
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

template <typename T>
class SparseTable {
	using vT = vector<T>;
	using vvT = vector<vT>;
public:

    vvT st; // Sparse Table
    vi lgt; // LoG Table 
	
	T f(const T &x, const T &y){
		return min(x,y);
	}

    SparseTable(const vT& data) { build(data); }

    T query(int l, int r) {
        int i = lgt[r - l + 1];
		int j = r - (1 << i) + 1;
        return f(st[l][i], st[j][i]);
    }


    void build(const vT& data) {
        int n = sz(data);
		int mxl = log2(n) + 1; // MaX Log
        st.assign(n, vT(mxl));
        lgt.assign(n + 1, 0);

        forn(i,2,n+1) lgt[i] = lgt[i / 2] + 1;
        forn(i,0,n) st[i][0] = data[i];

        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
				int k = i + (1 << (j - 1) );
                st[i][j] = f(st[i][j-1], st[k][j-1]);
            }
        }
    }
};

int main() {
    vi data = {1, 3, -1, 8, 5, 6};
    SparseTable<int> st(data);

    cout << "Min from index 1 to 4: " << st.query(1, 4) << endl;
    return 0;
}

