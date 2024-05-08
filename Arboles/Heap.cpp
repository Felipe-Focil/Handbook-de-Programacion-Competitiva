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
class Heap {
public:
    vector<T> data;
    void push(T v) {
        data.pb(v);
        heapify_up(sz(data) - 1);
    }
    T top() { return data[0]; }
    bool empty() { return data.empty(); }

    void pop() {
        swap(data[0], data[sz(data) - 1]);
        data.pop_back();
        heapify_down(0);
    }

private:
    void heapify_up(int i) {
        if (i == 0) return;

        int p = parent(i);
        if (!isSorted(data[p], data[i])) {
            swap(data[p], data[i]);
            heapify_up(p);
        }
    }

    void heapify_down(int i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int j = i;
        if (l < sz(data) && isSorted(data[l], data[j])) j = l;
        if (r < sz(data) && isSorted(data[r], data[j])) j = r;

        if (j != i) {
            swap(data[i], data[j]);
            heapify_down(j);
        }
    }
    int parent(int i) { return (i - 1) / 2; }
    bool isSorted(T& a, T& b) {
        //FIX ME
        return a > b;
    }
};

void _main() {
    int n;
    cin >> n;
    Heap<int> pq;
    forn(i, 0, n) {
        int x;
        cin >> x;
        pq.push(x);
    }

    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}

int main() {
    FIN;

    int t = 1;

    // cin >> t;

    while (t--) {
        _main();
    }

    return 0;
}
