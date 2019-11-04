#include <bits/stdc++.h>
#define ll long long
#define NUMITER 10
#define m 9999992
using namespace std;
bool prime[m];

ll gcd(ll a, ll b)
{
    if (b == 0)
    {
        return a;
    }
    return gcd(b, a % b);
}

ll fast_pow(ll base, ll exp, ll mod)
{
    if (exp == 0)
    {
        return 1;
    }
    ll x = fast_pow(base, exp / 2, mod);
    ll ans = (x * x) % mod;
    if (exp % 2 == 0)
    {
        return ans;
    }
    else
    {
        return (base * ans) % mod;
    }
}

//Deterministic
ll check_prime_det(ll n)
{
    //memset(prime,1,sizeof prime);
    for (long long i = 2; i <= n; i++)
        prime[i] = 1;
    prime[0] = 0;
    prime[1] = 0;
    for (long long i = 2; i * i < n; i++)
        if (prime[i] == 1)
            for (long long j = i * i; j <= n; j++)
                prime[i * j] = 0;
    return prime[n];
}

//Randomized
bool check_prime_rand(ll p)
{
    srand(time(0));
    if (p <= 1)
    {
        return false;
    }
    if (p == 2 || p == 3)
    {
        return true;
    }
    for (int i = 1; i <= NUMITER; i++)
    {
        ll a = 2 + rand() % (p - 4);
        //cout << a << endl;
        /*
        if (gcd(p, a) != 1)
        {
            cout << "gcd failed" << endl;
            return false;
        }
        */
        //cout << "fast_pow " << fast_pow(a, p - 1, p) << endl;
        if (fast_pow(a, p - 1, p) != 1)
        {
            //cout << "fast_pow failed" << endl;
            return false;
        }
    }
    return true;
}

int main()
{

    ll p;
    cout << "Enter number to test : " << endl;
    cin >> p;
    cout<<"Deterministic"<<endl; 
    if (check_prime_det(p) == 1)
        cout << "Prime" << endl;
    else
        cout << "Not Prime" << endl;

    cout<<"Randomized"<<endl; 
    if (check_prime_rand(p) == 1)
        cout << "Prime" << endl;
    else
        cout << "Not Prime" << endl;

    return 0;
}
