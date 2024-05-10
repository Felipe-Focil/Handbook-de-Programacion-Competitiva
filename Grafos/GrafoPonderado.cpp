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

template<typename T, typename W>
class Graph {

public:
    int n;
    using vT = vector<T>;
    using vvT = vector<vT>;
    using vW = vector<W>;
    using vvW = vector<vW>;
    using pTW = pair<T, W>;
    using vpTW = vector<pTW>;
    using vvpTW = vector<vpTW >;

    vvpTW adj;

    Graph(int n) {
        this->n = n;
        adj.resize(n);
    }

    void add(T u, T v, W w, bool directed = false) {
        adj[u].pb({ v,w });
        if (directed) adj[v].pb({ u,w });
    }

    vW dijkstra(T s) {
        vW d(n, INF);
        vT p(n, -1);
        d[s] = 0;

        priority_queue<pTW, vpTW, greater<pTW>> pq;
        pq.push({ 0, s });

        while (!pq.empty()) {
            T u = pq.top().se;
            W du = pq.top().fi;
            pq.pop();

            if (du != d[u]) continue;
            for (auto& child : adj[u]) {
                T v = child.fi;
                W w = child.se;
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    p[v] = u;
                    pq.push({ d[v], v });
                }
            }
        }
        return d;
    }

    vW bellmanFord(T s) {
        vW d(n, INF);
        d[s] = 0;
        for (;;) {
            bool any = false;
            forn(u, 0, n) {
                for (auto& child : adj[u]) {
                    T v = child.fi;
                    W w = child.se;

                    if (d[u] < INF) {
                        if (d[v] > d[u] + w) {
                            d[v] = d[u] + w;
                            any = true;
                        }
                    }
                }
            }
            if (!any)break;
        }
        return d;
    }

    vT bellmanFordPath(T s) {
        vW d(n, INF);
        vT p(n, -1);
        d[s] = 0;
        for (;;) {
            bool any = false;
            forn(u, 0, n) {
                for (auto& child : adj[u]) {
                    T v = child.fi;
                    W w = child.se;

                    if (d[u] < INF && d[v] > d[u] + w) {
                        d[v] = d[u] + w;
                        p[v] = u;
                        any = true;
                    }
                }
            }
            if (!any) break;
        }
        vT path;
        for (T v = 0; v < n; ++v) {
            if (p[v] != -1) {
                T current = v;
                stack<T> temp;
                temp.push(v);
                while (current != s) {
                    current = p[current];
                    temp.push(current);
                }
                while (!temp.empty()) {
                    path.pb(temp.top());
                    temp.pop();
                }
            }
        }
        return path;
    }

    void bellmanFordNegativeCycles(T s) {
        vW d(n, INF);
        d[s] = 0;
        vT p(n, -1);
        W x;
        forn(i, 0, n) {
            x = -1;
            forn(u, 0, n) {
                for (auto& child : adj[u]) {
                    T v = child.fi;
                    W w = child.se;
                    if (d[u] < INF && d[v] > d[u] + w) {
                        d[v] = max(-INF, d[u] + w);
                        p[v] = u;
                        x = v;
                    }
                }
            }
        }

        if (x == -1)
            cout << "No negative cycle from " << s;
        else {
            T y = x;
            forn(i, 0, n) y = p[y];

            vT path;
            for (T cur = y;; cur = p[cur]) {
                path.pb(cur);
                if (cur == y && sz(path) > 1) break;
            }
            reverse(all(path));
            cout << "Negative cycle: ";
            for (T u : path) cout << u << " ";
        }
    }

    vT bfs01(T s) {
        vW d(n, INF);
        d[s] = 0;
        deque<T> q;
        q.push_front(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (auto child : adj[v]) {
                int u = child.fi;
                int w = child.se;
                if (d[v] + w < d[u]) {
                    d[u] = d[v] + w;
                    if (w == 1) q.pb(u);
                    else q.push_front(u);
                }
            }
        }
        return d;
    }

    vvW floydWarshall() {
        vvW d(n, vector<W>(n, INF));

        for (int u = 0; u < n; ++u) {
            for (auto& child : adj[u]) {
                T v = child.fi;
                W w = child.se;
                d[u][v] = w;
            }
            d[u][u] = 0;
        }
        forn(k, 0, n) {
            forn(i, 0, n) {
                forn(j, 0, n) {
                    if (d[i][k] < INF && d[k][j] < INF)
                        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
        return d;
    }


    vvpTW kruskal() {
        W cost = 0;
        vvpTW result(n);
        vT parent(n), rank(n);
        for (T i = 0; i < n; ++i) make_set(i, parent, rank);
        vector<pair<W, pair<T, T>>> edges;
        for (T u = 0; u < n; ++u) {
            for (auto& child : adj[u]) {
                T v = child.first;
                W w = child.second;
                edges.push_back({ w, {u, v} });
            }
        }

        sort(edges.begin(), edges.end());

        for (auto& edge : edges) {
            T u = edge.second.first;
            T v = edge.second.second;
            W w = edge.first;
            if (find_set(u, parent) != find_set(v, parent)) {
                cost += w;
                result[u].push_back({ v, w });
                union_sets(u, v, parent, rank);
            }
        }
        return result;
    }

    void make_set(T v, vT& parent, vT& rank) {
        parent[v] = v;
        rank[v] = 0;
    }

    T find_set(T v, vT& parent) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v], parent);
    }

    void union_sets(T a, T b, vT& parent, vT& rank) {
        a = find_set(a, parent);
        b = find_set(b, parent);
        if (a != b) {
            if (rank[a] < rank[b])
                swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                rank[a]++;
        }
    }
private:
    const W INF = numeric_limits<W>::max();
};


void exampleDijkstra() {
    Graph<int, float> g(5);
    g.add(0, 1, 2);
    g.add(0, 2, 5);
    g.add(1, 2, 1);
    g.add(1, 3, 6);
    g.add(2, 3, 3);
    g.add(2, 4, 8);

    vector<float> d = g.dijkstra(0);
    for (auto x : d) cout << x << " ";
}

void exampleBellmanFord() {
    Graph<int, int> g(6);
    g.add(1, 2, 7);
    g.add(1, 3, 3);
    g.add(3, 2, 4);
    g.add(2, 4, -2);
    g.add(3, 5, -5);
    g.add(5, 2, 1);
    g.add(4, 3, 6);
    g.add(5, 4, 4);

    vector<int> d = g.bellmanFord(1);
    for (auto x : d) cout << x << " ";
}

void exampleBellmanFordPath() {
    Graph<int, int> g(6);
    g.add(1, 2, 7);
    g.add(1, 3, 3);
    g.add(3, 2, 4);
    g.add(2, 4, -2);
    g.add(3, 5, -5);
    g.add(5, 2, 1);
    g.add(4, 3, 6);
    g.add(5, 4, 4);

    vector<int> d = g.bellmanFordPath(1);
    for (auto x : d) cout << x << " ";
}

void exampleBellmanFordNegativeCycles() {
    Graph<int, int> g(4);
    g.add(1, 0, 4);
    g.add(1, 2, -6);
    g.add(2, 3, 5);
    g.add(3, 1, -2);

    g.bellmanFordNegativeCycles(1);
}

void exampleBfs01() {
    Graph<int, int> g(6);
    g.add(1, 2, 1);
    g.add(1, 3, 1);
    g.add(3, 2, 1);
    g.add(2, 4, 0);
    g.add(3, 5, 1);
    g.add(5, 2, 0);
    g.add(4, 3, 1);
    g.add(5, 4, 1);

    vector<int> d = g.bfs01(1);
    for (auto x : d) cout << x << " ";
}

void exampleFloydWarshall() {
    int n = 4;
    Graph<int, int>g(n);

    g.add(0, 1, 3);
    g.add(1, 0, 2);
    g.add(0, 3, 5);
    g.add(3, 2, 2);
    g.add(2, 1, 1);
    g.add(1, 3, 8);

    vvi d = g.floydWarshall();

    forn(i, 0, n) {
        forn(j, 0, n) cout << d[i][j] << " ";
        cout << endl;
    }
}

void exampleKruskal() {
    Graph<int, int>g(5);
    g.add(0, 1, 2, true);
    g.add(0, 2, 5, true);
    g.add(1, 2, 5, true);
    g.add(1, 3, 3, true);
    g.add(2, 4, 4, true);
    g.add(3, 4, 4, true);
    g.add(1, 4, 2, true);
    g.add(0, 4, 6, true);

    vector<vector<pair<int, int>>> mst = g.kruskal();
    for (int i = 0; i < mst.size(); ++i) {
        cout << i << ": ";
        for (auto x : mst[i])
            cout << x.first << "," << x.second << " ";

        cout << endl;
    }
}


int main() {
    FIN;
    // exampleDijkstra();
    // exampleBellmanFord();
    // exampleBellmanFordPath();
    // exampleBellmanFordNegativeCycles();
    // exampleBfs01();
    // exampleFloydWarshall();
    exampleKruskal();

    return 0;
}
