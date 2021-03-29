/*
1.Lucas定理
lucas(n, m, p) = C(n % p, m % p) * lucas(n / p, m / p, p) (p为质数)
即:
n = a[x] * p ^ (x) + a[x - 1] * p ^ (x - 1) + ... + a[0] * p ^ 0
m = b[x] * p ^ (x) + b[x - 1] * p ^ (x - 1) + ... + b[0] * p ^ 0
C(n, m) ≡ C(a[x], b[x]) * ... *C(a[0], b[0])(mod p)
如: C(n, m) mod 2 == 1 当且仅当 n & m == m
*/

LL Lucas(int n, int m, LL p)
{
    LL ret = 1;
    while (m)
    {
        ret = ret * C(n % p, m % p, p) % p;
        n /= p, m /= p;
        if (!ret)
            break;
    }
    return ret;
}