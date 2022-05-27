#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;

struct Order
{
    double a;
    double b;
    double d;
};

void insert(vector <Order>&);
void maxHeap(vector <Order>&, double&);

int main()
{
    double result = 0;
    ofstream fout("lazy.out");
    vector <Order> orders;
    insert(orders);
    maxHeap(orders, result);
    fout << fixed << setprecision(2) << result;
    return 0;
}


void maxHeap(vector <Order> &orders, double &result)
{
    double paidDays = 0, daysAll = 0;
    multiset<pair<double, double>> workingDays;
    for (int i = 0; i < orders.size(); i++)
    {
        if (orders[i].b > (paidDays = (orders[i].d - daysAll)))
        {
            if (!workingDays.empty() && (workingDays.rbegin()->first > orders[i].a))
            {
                double delim;
                delim = orders[i].b - paidDays;
                while (!workingDays.empty())
                {
                    if (orders[i].a < (workingDays.rbegin()->first)
                        && (workingDays.rbegin()->second >= delim))
                    {
                        daysAll = daysAll - delim;
                        result = result + (delim / (workingDays.rbegin()->first));

                        double f1 = workingDays.rbegin()->first;
                        double f2 = workingDays.rbegin()->second - delim;
                        workingDays.erase(--workingDays.end());

                        if (f2 > 0)
                        {
                            workingDays.insert(make_pair(f1, f2));
                        }
                        daysAll = daysAll + orders[i].b;
                        delim = 0;
                    }
                    else if (orders[i].a < (workingDays.rbegin()->first))
                    {
                        double t2 = workingDays.rbegin()->second;
                        result = result + (t2 / (workingDays.rbegin()->first));
                        daysAll = daysAll - t2;
                        delim = delim - t2;
                        workingDays.erase(--workingDays.end());
                    }
                    else break;
                    if (delim == 0) break;
                }

                if (delim > 0)
                {
                    result = result + (delim / orders[i].a);
                    paidDays = orders[i].b - delim;
                    daysAll = daysAll + paidDays;
                    orders[i].b = paidDays;
                    orders.shrink_to_fit();
                }
                orders.shrink_to_fit();
            }
            else
            {
                if (paidDays != 0)
                {
                    result = result + ((orders[i].b - paidDays) / orders[i].a);
                    daysAll = daysAll + paidDays;
                    orders[i].b = paidDays;
                    orders.shrink_to_fit();
                }
                else
                {
                    result = result + ((orders[i].b - 0) / orders[i].a);
                    orders[i].b = 0;
                    orders.shrink_to_fit();
                }
                orders.shrink_to_fit();
            }
            orders.shrink_to_fit();
        }
        else
        {
            daysAll = daysAll + orders[i].b;
            orders.shrink_to_fit();
        }
        if (orders[i].b > 0)
        {
            workingDays.insert(make_pair(orders[i].a, orders[i].b));
            orders.shrink_to_fit();
        }
        orders.shrink_to_fit();
    }
}

void insert(vector <Order> &orders)
{
    ifstream fin("lazy.in");
    int n, a, b, d;
    fin >> n;
    orders.resize(n);
    for (int i = 0; i < n; i++)
    {
        fin >> a >> b >> d;
        orders[i].a = a;
        orders[i].b = b;
        orders[i].d = d;
    }

    sort(orders.begin(), orders.end(),
         [](const Order& lhs, const Order& rhs)
         {
             if (lhs.d != rhs.d)
                 return lhs.d < rhs.d;
             else
                 return lhs.a > rhs.a;
         });
}
