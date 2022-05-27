#include <iostream>

using namespace std;

unsigned long long func(unsigned long long den, unsigned long long exp, unsigned long long M) {
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * den) % M;
        den = (den * den) % M;
        exp >>= 1;
    }
    return result;
}

int main() {
    const auto M=1000000007;
    long long N(0), K(0);
    unsigned long long num(1), den(1);
    cin >> N >> K;

    for (int i = N; i > N - K; i--)
        num = (num * i) % M;

    for (int i = 1; i <= K; i++)
        den = (den * i) % M;

    unsigned long long exp = M-2;
    unsigned long long rez = (num * func(den, exp, M)) % M;
    cout << rez;
    return 0;
}
