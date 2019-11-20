#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void ToW(vector<int>& v, int start, int end, int n_left, int& s_sel, int& s_res, int& d_min, int& s_mid)
{
    if (n_left == 0) return;

    for (int i = start; i <= end; i++)
    {
        s_sel += v[i];
        int dif = (s_sel - s_mid > 0 ? s_sel - s_mid : s_mid - s_sel);
        if (s_sel >= s_mid + d_min) 
        {
            s_sel -= v[i];
            continue;
        }
        if (dif <= d_min)
        {
            d_min = dif;
            s_res = s_sel;
        }
        ToW(v, i + 1, end, n_left - 1, s_sel, s_res, d_min, s_mid);
        s_sel -= v[i];
    }
}

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    const int MAX_INT = 2e9;

    ifstream inputFile("input.txt", ios::in);

    vector<int> v;
    int N, T, w, sum;
    inputFile >> N;
    for (int i = 1; i <= N; i++)
    {
        inputFile >> T;
        sum = 0;
        for (int j = 0; j < T; j++)
        {
            inputFile >> w;
            sum += w;
            v.push_back(w);
        }
        
        int s_sel = 0, dif = MAX_INT, s_res = 0, s_mid = sum / 2; 
        ToW(v, 0, T - 1, T / 2, s_sel, s_res, dif, s_mid);
        
        cout << "Game " << i << " : " << s_res << "   " << sum - s_res << '\n';
        v.clear();
    }
}