/*------------------------------------------------------------------------------
                           File Name
                           FenwickTree.cpp
--------------------------------------------------------------------------------
                            Description
      En este archivo se encuentra ejemplos de uso de la clase
      Knapsack para la creacion y uso del problema de la mochila de 
      progamacion dinamica


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
class Knapsack{
	using vT = vector<T>;
	using vvT = vector<vT>;
public:
    T mxW;
    vT ws,v,used;
    vvT dp;
    
	Knapsack(T mxW, const vT& ws, const vT& v)
        : mxW(mxW), ws(ws), v(v) {}

    T build() {
        int n = sz(ws);
        dp = vvT(n + 1, vT(mxW + 1, 0));

        forn (i,1,n+1) {
            for (T w = 0; w <= mxW; w++) {
                if (ws[i - 1] <= w)
                    dp[i][w] = max(
					dp[i-1][w], v[i-1] + 
					dp[i-1][w - ws[i-1]]
					);
                else dp[i][w] = dp[i - 1][w];
            }
        }
        rebuild();
        return dp[n][mxW];
    }

    void rebuild() {
        used.clear();
        T w = mxW;
        for (int i = sz(ws); i > 0; i--) {
            if (dp[i][w] != dp[i - 1][w]) {
                used.pb(i - 1);
                w -= ws[i - 1];
            }
        }
        reverse(all(used));
    }
};

int main(){
	int maxWeight = 50;
    vi weights = {10, 20, 30};
    vi values = {60, 100, 120};

    Knapsack<int> dp(maxWeight, weights, values);
    int maxValue = dp.build();

	cout<<maxValue<<endl;
	//Selected values for getting max value
	vi used = dp.used;
    for (int item : used)
        cout << item << " ";
    
}
