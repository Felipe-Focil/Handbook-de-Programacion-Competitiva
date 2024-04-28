#include <bits/stdc++.h>


using namespace std;

using u64 = uint64_t;

const u64 MOD = 1e9 + 7;

#define ADD(a, b) (((a % MOD) + (b % MOD)) % MOD)
#define SUBTRACT(a, b) (((a) - (b) + MOD) % MOD)
#define MULTIPLY(a, b) (((a) % MOD) * ((b) % MOD)) % MOD
#define DIVIDE(a, b) (MULTIPLY(a,binpow(b,MOD-2)))

u64 binpow(u64 a, u64 b) {
    u64 r = 1; a %= MOD;
    while (b > 0) {
        if (b & 1)  r = MULTIPLY(r, a);
        a = MULTIPLY(a, a);
        b >>= 1;
    }
    return r;
}

u64 modInverse(u64 a) {
    return binpow(a, MOD - 2);
}


int main() {
    u64 a = 1000000000, b = 987654321;


    cout << "Suma: " << ADD(a, b) << endl;

    cout << "Resta: " << SUBTRACT(a, b) << endl;

    cout << "Multiplicacion: " << MULTIPLY(a, b) << endl;

    cout << "Division: " << DIVIDE(a, b) << endl;

    cout << "Inversa Modular" << modInverse(a);

    return 0;
}