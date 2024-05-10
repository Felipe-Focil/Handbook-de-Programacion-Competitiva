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
class DisjointSet {
public:
    using vT = vector<T>;
    using vvT = vector<vT>;

    int n;
    vT parent, rank, size;
    enum Type { BASIC, SIZE, RANK };
    Type type;

    DisjointSet(int n, Type type = BASIC) {
        this->n = n;
        this->type = type;
        parent.resize(n);
        if (type == SIZE) size.resize(n, 1);
        if (type == RANK) rank.resize(n, 0);
        for (int i = 0; i < n; ++i) make(i);
    }

    void make(T v) {
        parent[v] = v;
    }

    T find(T v) {
        if (v == parent[v]) return v;
        return parent[v] = find(parent[v]);
    }

    void unionSet(T a, T b) {
        a = find(a);
        b = find(b);
        if (a != b) parent[b] = a;
    }

    void unionBySize(T a, T b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }

    void unionByRank(T a, T b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        }
    }

    bool sameGroup(T a, T b) {
        return find(a) == find(b);
    }

    int sizeOfGroup(T a) {
        return size[find(a)];
    }

    vvT groups() {
        vvT group(n), ans;
        forn(i, 0, n)
            group[find(i)].pb(i);

        for (auto& g : group)
            if (!g.empty()) ans.pb(g);

        return ans;
    }
};

void exampleBasic() {
    DisjointSet<int> ds(5);

    ds.unionSet(0, 1);
    ds.unionSet(2, 3);

    cout << (ds.sameGroup(0, 1) ? "Yes" : "No") << endl;
    cout << (ds.sameGroup(0, 2) ? "Yes" : "No") << endl;

    auto groups = ds.groups();
    for (auto& g : groups) {
        for (auto& e : g)  cout << e << " ";
        cout << endl;
    }
}

void exampleRank() {
    DisjointSet<int> ds(5, DisjointSet<int>::RANK);

    ds.unionByRank(0, 1);
    ds.unionByRank(2, 3);

    cout << (ds.sameGroup(0, 1) ? "Yes" : "No") << endl;
    cout << (ds.sameGroup(0, 2) ? "Yes" : "No") << endl;

    auto groups = ds.groups();
    for (auto& g : groups) {
        for (auto& e : g)  cout << e << " ";
        cout << endl;
    }
}

void exampleSize() {
    DisjointSet<int> ds(5, DisjointSet<int>::SIZE);
    ds.unionBySize(0, 1);
    ds.unionBySize(2, 3);

    cout << (ds.sameGroup(0, 1) ? "Yes" : "No") << endl;
    cout << (ds.sameGroup(0, 2) ? "Yes" : "No") << endl;

    cout << ds.sizeOfGroup(0) << endl;
    auto groups = ds.groups();
    for (auto& g : groups) {
        for (auto& e : g)  cout << e << " ";
        cout << endl;
    }

}


int main() {
    FIN;

    // exampleBasic();
    // exampleRank();
    // exampleSize();

    return 0;
}
