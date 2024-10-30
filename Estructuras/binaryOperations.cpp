/*------------------------------------------------------------------------------
                           File Name
                           binaryOperations.cpp
--------------------------------------------------------------------------------
                            Description
      En este archivo se encuetran funciones de utilidades para realizar
	  operaciones binarias a mano mediante el uso de bitset


--------------------------------------------------------------------------------
                            Files History

        Name        Date        Description
        ffocilme    10/29/24    Add binary overcharge for bitsets
        ffocilme    10/26/24    Creation
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


#define MXSZ    64
#define bits    bitset<MXSZ>

//Suma
bits operator+(const bits &x, const bits &y)
{
    bits r;
    bool a, b, c = 0;
    forn(i,0,MXSZ)
    {   
        a = x[i] , b = y[i];
        r[i] = a ^ b ^ c;
        c  = (a & b) | (a & c) | (b & c);
    }
    return r;
}

//Requerido para division
bool operator<(const bits &x, const bits &y){
    for(int i = MXSZ - 1; i >= 0; i--)
       if(x[i] != y[i]) return (x[i] < y[i]);
    return 0;
}
// RESTA
bits operator-(const bits &x, const bits &y) {
    bits r;
    bool a, b, c = 0;
    for (int i = 0; i < MXSZ; i++) {
        a = x[i];
        b = y[i];
        r[i] = a ^ b ^ c;            
        c = (!a & b) | (!a & c) | (b & c);
    }
    /*TO DO ADD SIGNED OPERATION SUPPORT*/
    return r;
}

// MUTIPLICACION
bits operator*(const bits &x, const bits &y) {
    bits r,c;
    for (int i = 0; i < MXSZ; i++) {
        if (y[i]) {
            c = x << i;
            r = r + c;  
        }
    }
    return r;
}

//Requerido para division
bool operator>=(const bits &x, const bits &y){
    for(int i = MXSZ - 1; i >= 0; i--)
       if(x[i] != y[i]) return (x[i] > y[i]);
    return 1;
}

// DIVISION
bits operator/(const bits &x, const bits &y) {
    bits r;
    bits c = x;
    for (int i = MXSZ - 1; i >= 0; i--) {
        if (c >> i >= y) {
            r[i] = 1;
            c = c - (y << i);
        }
    }
    return r;
}


// MODULO
bits operator%(const bits &x, const bits &y) {
    bits r = x;
    for (int i = MXSZ - 1; i >= 0; i--)
        if (r >> i >= y)  r = r - (y << i);
    return r;
}

// POTENCIA
bits pow(const bits &x, const bits &y) {
    bits r = 1;
    bits b = x;
    for (int i = 0; i < MXSZ; i++) {
        if (y[i]) r = r * b;
        b = b * b;
    }
    return r;
}

int main() {

    bits a = 8;
    bits b = 3;

    cout<< a + b << endl;
    cout<< a - b << endl;
    cout<< a * b << endl;
    cout<< a / b << endl;
    cout<< a % b << endl;

    return 0;
}
