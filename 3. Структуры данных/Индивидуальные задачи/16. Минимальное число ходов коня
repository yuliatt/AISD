#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream in("in.txt");
ofstream out("out.txt");

int main()
{
    int Ox[8] = {-2, -2, 2, 2, 1, 1, -1, -1};
    int Oy[8] = {1, -1, 1, -1, 2, -2, 2, -2};
    int n, m;
    in >> n >> m;
    int **chess = new int*[n + 4];
    for (int i = 0; i < n + 4; i++)
    {
        chess[i] = new int[m + 4];
    }
    for (int i = 2; i < n + 2; i++)
    {
        for (int j = 2; j < m + 2; j++)
            in >> chess[i][j];

    }

    int x1, y1, x2, y2;
    in >> x1 >> y1 >> x2 >> y2;

    for (int i = 0; i < n + 4; i++)
        chess[i][0] = chess[i][1] = chess[i][m + 2] = chess[i][m + 3] = -1;

    for (int i = 0; i < m + 4; i++)
        chess[0][i] = chess[1][i] = chess[n + 2][i] = chess[n + 3][i] = -1;

    queue<int> qX;
    queue<int> qY;

    if (chess[x1 + 1][y1 + 1] == 0)
    {
        chess[x1 + 1][y1 + 1] = 1;
        qX.push(x1 + 1);
        qY.push(y1 + 1);
    }

    while (!qX.empty())
    {
        int x = qX.front();
        int y = qY.front();
        qX.pop();
        qY.pop();
        for (int i = 0; i < 8; i++)
        {
            if (chess[Ox[i] + x][Oy[i] + y] == 0)
            {
                chess[Ox[i] + x][Oy[i] + y] = chess[x][y] + 1;
                qX.push(Ox[i] + x);
                qY.push(Oy[i] + y);
            }
        }
    }
    if (chess[x2 + 1][y2 + 1] < 1)
        out << "No" << endl;
    else
        out << chess[x2 + 1][y2 + 1] - 1 << endl;

    return 0;
}
