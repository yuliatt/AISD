#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

long long multiplyOrder(vector<vector<long long>> &mDimensions, long long &n) {

    auto v = vector<vector<long long>> (n, vector<long long>(n));
    for (long long i = 0; i < n; i++) {
        for(long long j = 0; j < n; j++) {
            v[i][j] = 0;
        }
    }

    for(long long i = 0; i < n; i++) {

        for(long long j = 0; j < n; j++) {
            if(i + j < n) {
                if(i != 0) v[j][j + i] = INT_MAX;
                for(long long k = j; k < i + j; k++) {
                    v[j][j + i] = min(v[j][j + i],
                                      v[j][k] + v[k + 1][j + i] + mDimensions[j][0] * mDimensions[k][1] * mDimensions[j + i][1]);

                }
            }
        }
    }
    return v[0][n - 1];
}

int main() {
    ifstream fin;
    ofstream fout;

    fin.open("input.txt");
    fout.open("output.txt");

    if (fin.is_open()) {

        long long n(0);
        fin >> n;
        auto mDimensions = vector<vector<long long>> (n, vector<long long>(2));

        while (!fin.eof()) {
            for(auto i = 0; i < n; i++) {
                fin>>mDimensions[i][0];
                fin>>mDimensions[i][1];
            }
        }

        if (fout.is_open()) fout << multiplyOrder(mDimensions, n);
    }
    fin.close();
    fout.close();
    return 0;
}
