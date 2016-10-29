#include <vector>

using namespace std;

const long long MOD = 1000000007;
const int K = 2;

// computes A * B
vector<vector<long long> > mul(vector<vector<long long> > A, vector<vector<long long> > B)
{
    vector<vector<long long> > C(K+1, vector<ll>(K+1));
    for (int i = 1; i <= K; i++)
      for (int j = 1; j <= K; j++)
        for (int k = 1; k <= K; k++)
            C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

// computes A ^ p
vector<vector<long long> > pow(vector<vector<long long> > A, int p)
{
    if (p == 1)
        return A;
    if (p % 2 == 1)
        return mul(A, pow(A, p-1));
    vector<vector<long long> > X = pow(A, p/2);
    return mul(X, X);
}

// returns the N-th term of Fibonacci sequence
int fib(int N)
{
    // create vector F1
    vector<ll> F1(K+1);
    F1[1] = 1;
    F1[2] = 1;

    // create matrix T
    vector<vector<long long> > T(K+1, vector<ll>(K+1));
    T[1][1] = 0, T[1][2] = 1;
    T[2][1] = 1, T[2][2] = 1;

    // raise T to the (N-1)th power
    if (N == 1)
        return 1;
    T = pow(T, N-1);

    // the answer is the first row of T . F1
    long long res = 0;
    for (int i = 1; i <= K; i++)
        res = (res + T[1][i] * F1[i]) % MOD;
    return res;
}
