#include <iostream>
#include <fstream>

long long dpBackward[10000000];

int main() {
    std::ifstream fin;
    std::ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
        int n;
        fin >> n;
        dpBackward[0] = 1;
        dpBackward[1] = 1;
        for(int i = 2; i <= n; i++)
        {
            dpBackward[i] = (dpBackward[i - 1] + dpBackward[i - 2]) % 1000000007;
        }
        fout << dpBackward[n];
    fin.close();
    fout.close();
    return 0;
}
