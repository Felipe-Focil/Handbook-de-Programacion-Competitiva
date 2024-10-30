/*------------------------------------------------------------------------------
                           File Name                                        
                           Grafos.cpp                                       
--------------------------------------------------------------------------------
                            Description                                      
      En este archivo se encuentra ejemplos de uso de la clase             
<<<<<<< HEAD
      Graph para la creacion y uso de grafos
      Felipe nos dijo que los nombres se anotan de abajo para 
      arriba, que todo minusculas                              
=======
      Graph para la creacion y uso de grafos                                
>>>>>>> 83d133c69b8cfbd2a700acef12ff628bd0f09e72
                                                                            
                                                                            
--------------------------------------------------------------------------------
                            Files History

        Name        Date        Description
<<<<<<< HEAD
        illergos    10/26/24    Ortographic correction
=======
>>>>>>> 83d133c69b8cfbd2a700acef12ff628bd0f09e72
        ffocilme    10/26/24    Add comments and header information    
        ffocilme    05/10/24    Add topological sort
        ffocilme    05/09/24    Creation
--------------------------------------------------------------------------------
*/
#include <bits/stdc++.h>
<<<<<<< HEAD
#define FIN ios::ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
=======
#define FIN ios::ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
>>>>>>> 83d133c69b8cfbd2a700acef12ff628bd0f09e72
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
using vb = vector<bool>;
using pi = pair<int, int>;

template<typename T> // Plantilla Generica de Grafo
class Graph { 
public:
    int n; // Tamaño del Grafo
    using vT = vector<T>; // Vector Generico
    using vvT = vector<vT>; // Matriz Generica
    vvT adj; // Vertices
    Graph(int n) { // Cantidad de Vertices
        this->n = n;
        adj.resize(n);
    }

    Graph(int n, vvi& mat) { // Matriz de Adyacencia
        this->n = n;
        adj = mat;
    }

    void add(int u, int v, bool undirected = false) {
        adj[u].push_back(v);
        if (undirected)
            adj[v].push_back(u);
    }

    // Busqueda en Profundidad
    void dfs(int u, vb& visited) {
        cout << u << " ";
        for (auto v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                dfs(v, visited);
            }
        }
    }
    
    void dfsComponent(int i, vT& c, vb& u) {
        u[i] = 1;
        c.push_back(i);
        for (T v : adj[i]) {
            if (!u[v])
                dfsComponent(v, c, u);
        }
    }

    // Componentes Conexas
    vvT findComponents() {
        vb visited(n, false);
        vvT components;
        forn(i, 0, n) {
            if (!visited[i]) {
                vT component;
                dfsComponent(i, component, visited);
                components.push_back(component);
            }
        }
        return components;
    }

    // Puentes
    void findBridges() {
        int timer = 0;
        vb visited(n, false);
        vector<T> tin(n, -1), low(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfsBridges(i, -1, timer, visited, tin, low);
        }
    }

    void dfsBridges(int u, int p, int& timer, vb& vis, vT& tin, vT& low) {
        vis[u] = true;
        tin[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (vis[v]) {
                low[u] = min(low[u], tin[v]);
            }
            else {
                dfsBridges(v, u, timer, vis, tin, low);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u])
                    IS_BRIDGE(u, v);
            }
        }
    }

    void IS_BRIDGE(int u, int v) {
        cout << u << " " << v << endl;
    }

    // Puntos de Articulacion
    void findArticulationsPoints() {
        int timer = 0;
        vb visited(n, false);
        vT tin(n, -1), low(n, -1);
        forn(i, 0, n) {
            if (!visited[i])
                dfsArticulations(i, -1, timer, visited, tin, low);
        }
    }

    void dfsArticulations(int u, int p, int& timer, vb& vis, vT& tin, vT& low) {
        vis[u] = true;
        tin[u] = low[u] = timer++;
        int c = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (vis[v]) low[u] = min(low[u], tin[v]);
            else {
                dfsArticulations(v, u, timer, vis, tin, low);
                low[u] = min(low[u], low[v]);
                if (low[v] >= tin[u] && p != -1) IS_CUTPOINT(u);
                ++c;
            }
        }
        if (p == -1 && c > 1) IS_CUTPOINT(u);
    }

    void IS_CUTPOINT(int u) {
        cout << u << endl;
    }

    //Deteccion de Ciclos
    vi findCycle() {
        vi color(n, 0);
        vi parent(n, -1);
        vi cycle;
        int start = -1;

        forn(v, 0, n) {
            if (color[v] == 0 && dfsCycle(v, color, parent, start)) break;
        }

        if (start != -1) {
            cycle.push_back(start);
            for (int i = parent[start]; i != start; i = parent[i])
                cycle.push_back(i);
            cycle.push_back(start);
            reverse(all(cycle));
        }

        return cycle;
    }

    bool dfsCycle(int v, vi& c, vi& p, int& s) {
        c[v] = 1;
        for (int u : adj[v]) {
            if (c[u] == 0) {
                p[u] = v;
                if (dfsCycle(u, c, p, s)) return true;
            }
            else if (c[u] == 1 && p[v] != u) {
                s = u;
                return true;
            }
        }
        c[v] = 2;
        return false;
    }

    // Camino Euleriano
    vi eulerianPath() {
        // Assuming adj is adjacency matrix
        vi deg(n);
        vi path;
        forn(i, 0, n) {
            for (int j : adj[i])
                deg[i]++;
        }

        int start = 0;
        while (start < n && !deg[start])
            start++;

        if (start == n) return path;

        int v1 = -1, v2 = -1;
        bool bad = false;

        forn(i, 0, n) {
            if (deg[i] & 1) {
                if (v1 == -1) v1 = i;
                else if (v2 == -1) v2 = i;
                else bad = true;
            }
        }

        if (v1 != -1)
            ++adj[v1][v2], ++adj[v2][v1];

        stack<int>st;

        st.push(start);
        while (!st.empty()) {
            int v = st.top();
            int i;
            for (i = 0; i < n; ++i)
                if (adj[v][i]) break;

            if (i == n) {
                path.pb(v);
                st.pop();
            }
            else {
                --adj[v][i];
                --adj[i][v];
                st.push(i);
            }
        }

        if (v1 != -1) {
            for (size_t i = 0; i + 1 < sz(path); ++i) {
                if ((path[i] == v1 && path[i + 1] == v2) ||
                    (path[i] == v2 && path[i + 1] == v1)) {
                    vi path2;
                    for (size_t j = i + 1; j < sz(path); ++j)
                        path2.pb(path[j]);
                    for (size_t j = 1; j <= i; ++j)
                        path2.pb(path[j]);
                    path = path2;
                    break;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adj[i][j])
                    bad = true;
            }
        }

        if (bad) {
            vi dummy;
            return dummy;
        }

        return path;
    }

    // Revisar si un grafo es Bipartito
    bool isBipartite() {
        vi side(n, -1);
        bool ans = true;
        queue<int> q;
        forn(i, 0, n) {
            if (side[i] == -1) {
                q.push(i);
                side[i] = 0;
                while (!q.empty()) {
                    int v = q.front();
                    q.pop();
                    for (int u : adj[v]) {
                        if (side[u] == -1) {
                            side[u] = side[v] ^ 1;
                            q.push(u);
                        }
                        else {
                            ans &= side[u] != side[v];
                            if (!ans) return ans;
                        }
                    }
                }
            }
        }
        return ans;
    }
    // Ordenamiento Topologico
    vT topologicalSort() {
        vi degree(n, 0);
        vT topoSort;
        queue<int> q;
        forn(u, 0, n) {
            for (T v : adj[u]) degree[v]++;
        }

        forn(u, 0, n) {
            if (degree[u] == 0) q.push(u);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoSort.pb(u);
            for (int v : adj[u]) {
                degree[v]--;
                if (degree[v] == 0) q.push(v);
            }
        }

        if (topoSort.size() != n)
            topoSort.clear();

        return topoSort;
    }
};

// Ejemplos de uso:  Puedes reemplazarlo por un main
// Esta dividido en multiples funciones para no generar conflictos de nombres

void exmapleComponents() {
    //Construccion del Grafo
    Graph<int> g(7);
    g.add(0, 1);
    g.add(1, 2);
    g.add(2, 4);
    g.add(3, 5);
    
    //Devuelve una lista de adyacencia con los nodos que forman parte de
    //la misma componente
    vvi components = g.findComponents();
    
    for (const auto& component : components) {
        for (int node : component)
            cout << node << " ";
        cout << endl;
    }
}



void exampleBridges() {
    Graph<int> g(6);
    g.add(0, 1);
    g.add(1, 2);
    g.add(2, 0);
    g.add(1, 3);
    g.add(1, 4);
    g.add(3, 4);
    g.add(3, 5);
    // Encuentra las aristas que son necesarias para conectar todo el grafo
    // El procesamiento de estos puentes se encuentra en 

void exampleArticulationsPoints() {
    Graph<int> g(7);
    g.add(0, 1);
    g.add(0, 2);
    g.add(1, 2);
    g.add(2, 3);
    g.add(3, 4);
    g.add(3, 5);
    g.add(4, 5);
    g.add(4, 6);

    g.findArticulationsPoints();
    // Encuentra los vertices que son necesarios para conectar todo el grafo
    // El procesamiento de estos puntos de articulacion
    // se encuentra en IS_CUT_POINT
}

void exampleCycle() {
    Graph<int> g(4);
    g.add(1, 0);
    g.add(0, 2);
    g.add(2, 1);
    g.add(0, 3);
    
    //Devuelve una lista con los vertices que forman un ciclo
    vector<int> cycle = g.findCycle();
    if (!cycle.empty()) {
        cout << "Ciclo encontrado: ";
        for (int node : cycle)
            cout << node << " ";
        cout << endl;
    }
    else
        cout << "No se encontró ningún ciclo." << endl;
}

void exampleEulerianPath() {
    //Matriz de adyacencia de ejemplo
    vvi mat = { {0,1,1,0},{1,0,1,1},{1,1,0,1},{0,1,1,0} };
    Graph<int>g(4, mat);
    
    //Devuelve una lista con el orden que se tienen que visitar todos
    //los vertices del grafo sin repetir
    vector<int> eulerianPath = g.eulerianPath();
    
    if (!eulerianPath.empty()) {
        cout << "Camino euleriano encontrado: ";
        for (int node : eulerianPath)
            cout << node << " ";
        cout << endl;
    }
    else
        cout << "No se encontró ningún camino euleriano." << endl;
}

void exampleCheckBipartite() {
    Graph<int>g(4);
    g.add(0, 1, true);
    g.add(1, 2, true);
    g.add(2, 3, true);
    g.add(3, 0, true);
    // g.add(1, 3, true); // Add to make it not bipartite

    // Devuelve un booleano si el grafo se puede dividir en exactamente
    // dos conjutnos disconjuntos
    cout << ((g.isBipartite()) ? "YES" : "NO") << endl;

}


int main() {
    FIN;
    // Remove comment to test

    // exmapleComponents();
    // exampleBridges();
    // exampleArticulationsPoints();
    // exampleCycle();
    // exampleEulerianPath();
    // exampleCheckBipartite();

    return 0;

}
