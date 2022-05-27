#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("input.txt");
    fout.open("output.txt");
    int n = 0;
    char tmp;
    char* arr = new char[10000];
    while (fin >> tmp)
    {
        arr[n] = tmp;
        n++;
    }

    int** m = new int*[n + 1];
    for (int i = 0; i < n + 1; i++)
        m[i] = new int[n + 1];

    for (int i = 0; i < n + 1; i++)
    {
        m[i][0] = 0;
        m[0][i] = 0;
    }
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = i; j < n + 1; j++)
        {
            if (arr[i - 1] == arr[n - j])
                m[i][j] = m[i - 1][j - 1] + 1;
            else
                m[i][j] = max(m[i][j - 1], m[i - 1][j]);
        }
        for (int k = i + 1; k < n + 1; k++)
        {
            if (arr[k - 1] == arr[n - i])
                m[k][i] = m[k - 1][i - 1] + 1;
            else
                m[k][i] = max(m[k][i - 1], m[k - 1][i]);
        }
    }
    string str;
    int t = 0, j = n;
    for (int i = n; t < (m[n][n] + 1) * 0.5 && j > 0 && not i <= 0;)
    {
        if (m[i][j] != m[i][j - 1] && m[i][j] != m[i - 1][j])
        {
            str = str + arr[i - 1];
            t++;
            if (j > 1 == true)
            {
                j--;
                while (m[i][j] == m[i - 1][j] && i > 1) i = i - 1;
                while (m[i][j] == m[i][j - 1] && j > 1) j = j - 1;
            }
            else break;
        }
        else
        {
            if (i > 1  == true)
            {
                while (m[i][j] == m[i - 1][j] && i > 1) i = i - 1;
                while (m[i][j] == m[i][j - 1] && j > 1) j = j - 1;
            }
            else j--;
        }
    }

    for (int i = t; i < m[n][n]; i++)
        str += str.at(m[n][n] - i - 1);

    fout << m[n][n] << endl << str;
    fin.close();
    fout.close();
    return 0;
}
