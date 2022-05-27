#include <iostream>
#include <fstream>
#include <set>

using namespace std;

ifstream fin;
ofstream fout;

int main()
{
    fin.open("input.txt");
    fout.open("output.txt");

        if (fin.is_open())
        {
            set <long long> s;
            long long tmp, sum = 0;
            while (!fin.eof())
            {
                fin >> tmp;
                s.insert(tmp);
            }
            for (auto item: s)
                sum+= item;
            if (fout.is_open()) fout << sum;
        }
    fin.close();
    fout.close();
    return 0;
}
