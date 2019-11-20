#include <iostream>
using namespace std;
typedef long long ll;
ll quo[100], rem[100];

int check(int idx)
{
    for (int i = 0; i < idx; i++)
        if (rem[idx] == rem[i])
            return i;
    return -1;
}

int main()
{
    ll num, den;
    int idx = 0, start;
    cout << "Input Numerator Number: ";
    cin >> num;
    cout << "Input Denominator Number: ";
    cin >> den;

    num *= 10;
    if (num < den || den * 10 < num )
    {
        cout << "The Range of \"Numerator / Denominator\" is not from 0.1 to 1" << endl;
    }
    else if (num == den * 10)
    {
        cout << "The Result:: Finite Number: 1";
    }
    else
    {
        quo[0] = 0;
        rem[0] = num;
        while((start = check(idx)) == -1 && rem[idx] != 0)
        {
            ++idx;
            quo[idx] = rem[idx - 1] / den;
            rem[idx] = (rem[idx - 1] % den) * 10;
        }

        cout << "The Result:: " << (start == -1 ? "Finite" : "Infinite") << " Number: 0.";
        if (start == -1)
        {
            for (int i = 1; i <= idx; i++) cout << quo[i];
        }
        else
        {
            for (int i = 1; i <= idx; i++)
            {
                if(i == start + 1) cout << '[';
                cout << quo[i];
                if(i == idx) cout << ']';
            }
        }
        cout << endl;
    }

    return 0;
}