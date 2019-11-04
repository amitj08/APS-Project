// CPP code to implement Freivald’s Algorithm
#include <bits/stdc++.h>
#define ll long long
#define numiter 20
#define numexpr 10
using namespace std;
vector<vector<ll>> multiply(vector<vector<ll>> &A, vector<vector<ll>> &B, int n)
{
    vector<vector<ll>> C;
    for (int i = 0; i < n; i++)
    {
        vector<ll> t;
        for (int j = 0; j < n; j++)
        {
            ll x = 0;
            for (int k = 0; k < n; k++)
            {
                x += A[i][k] * B[k][j];
            }
            t.push_back(x);
        }
        C.push_back(t);
    }
    return C;
}

bool freivald(vector<vector<ll>> &a, vector<vector<ll>> &b, vector<vector<ll>> &c, int n)
{
    vector<bool> r;
    for (int i = 0; i < n; i++)
    {
        bool x = random() % 2;
        r.push_back(x);
        //cout << r[i];
    }
    //cout << endl;
    // Now comput B*r for evaluating
    // expression A * (B*r) - (C*r)
    //br = b*r;
    vector<int> br(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            br[i] = br[i] + b[i][j] * r[j];
        }
    }
    //cr = c*r;
    vector<int> cr(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cr[i] = cr[i] + c[i][j] * r[j];
        }
    }

    //abr = a*(b*r)
    int axbr[n] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            axbr[i] = axbr[i] + a[i][j] * br[j];
        }
    }
    //checking (a*(b*r) - (c*r)) == 0 for all values or not
    for (int i = 0; i < n; i++)
    {
        if (axbr[i] - cr[i] != 0)
        {
            return false;
        }
    }

    return true;
}

bool check(vector<vector<ll>> &a, vector<vector<ll>> &b, vector<vector<ll>> &c, int n, int k)
{
    for (int i = 0; i < k; i++)
        if (freivald(a, b, c, n) == false)
        {
            return false;
        }
    return true;
}

int main()
{

    cout << "Enter the dimension " << endl;
    int n;
    cin >> n;
    ll Randomtime = 0;
    ll Deterministictime = 0;
    vector<bool> Random;
    vector<bool> Deterministic;
    for (int i = 1; i < numexpr; i++)
    {
        vector<vector<ll>> a;
        vector<vector<ll>> b;
        vector<vector<ll>> c;
        for (int i = 0; i < n; i++)
        {
            vector<ll> t;
            for (int j = 0; j < n; j++)
            {
                ll ele;
                ele = rand() % (1000);
                t.push_back(ele);
            }
            a.push_back(t);
        }
        //cout << "Enter matrix 2 :  " << endl;
        for (int i = 0; i < n; i++)
        {
            vector<ll> t;
            for (int j = 0; j < n; j++)
            {
                ll ele;
                ele = rand() % (1000);
                t.push_back(ele);
            }
            b.push_back(t);
        }

        //for manual checking
        //--------------------------------------------------

        //cout << "Enter the result matrix: " << endl;
        /*
    for (int i = 0; i < n; i++)
    {
        vector<ll> t;
        for (int j = 0; j < n; j++)
        {
            ll ele;
            cin >> ele;
            t.push_back(ele);
        }
        c.push_back(t);
    }
    */

        c = multiply(a, b, n);
        srand(time(0));
        int index1 = rand() % n;
        int index2 = rand() % n;
        c[index1][index2] = rand() % 10;
        //cout << "index1 : " << index1 << " index2 : " << index2 << endl;

        //making any arbitrary index different c is now wrong
        //---------------------------------------------------

        //cout << "by frievald : ";
        auto start = std::chrono::high_resolution_clock::now();
        Random.push_back(check(a, b, c, n, numiter));
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        Randomtime += microseconds;
        //cout << "time taken by frievald : " << microseconds << endl;

        auto start1 = std::chrono::high_resolution_clock::now();
        vector<vector<ll>> C = multiply(a, b, n);
        //C is right matrix multiplcation matrix
        //as c is wrong multiplication it should output wrong in both cases
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (c[i][j] != C[i][j])
                {
                    flag = false;
                    break;
                }
            }
        }
        auto elapsed1 = std::chrono::high_resolution_clock::now() - start1;
        long long microseconds1 = std::chrono::duration_cast<std::chrono::microseconds>(elapsed1).count();
        Deterministictime += microseconds1;
        Deterministic.push_back(flag);
        //cout << "time taken by deterministic is " << microseconds1 << endl;
    }
    int count = 0;
    for (int i = 0; i < Random.size(); i++)
    {
        if (Deterministic[i] != Random[i])
        {
            count++;
        }
    }
    cout << "Frievald failed : " << count << " times" << endl;
    cout << "Time taken by Frievalds Algo (Randomized Algo) : " << Randomtime << " microseconds" << endl;
    cout << "Time taken by Deterministic Algo : " << Deterministictime << " microseconds" << endl;
    return 0;
}
