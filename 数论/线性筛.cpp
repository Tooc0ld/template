#include <bits/stdc++.h>

const int N = 1e6 + 10;

/*
 * 使用线性筛对积性函数求和
 * 保证每个数只被自己的最小素因子筛到,很容易用来求素数列表,参考break后的注释
 * 
 * 欧拉函数. Phi(x) 等于不超过x且和x互素的整数个数
 * Phi(x) = x * (1 - 1 / p_1) *... * (1 - 1 / p_n) p_i指x的第i个素因子
 * 积性函数, y 与 x 互质时 Phi(y * x) = Phi(y) * Phi(x)
 * 若 x 为素数, 显然Phi(x) = x - 1
 * 若 y 被 x 整除, 则Phi(y * x) = Phi(y) * x (原来与y互质的数，乘上小于等于x的数依旧互质)
 * 
 * 莫比乌斯函数.
 * 若 x = 1, Mu(x) = 1
 * 若 x 存在平方因子, Mu(x) = 0
 * x = p_1 * p_2 *... * p_k, Mu(x) = (-1)^k
 * 
 * 约数个数.
 * x = p_1^e_1 * p_2^e_2 *... *p_k^e_k
 * Factor(x) = (1 + e_1) * (1 + e_2) * ...*(1 + e_k)
 * 令Index(x) = e_1,最小素因数的指数
 * 显然积性函数, y 与 x 互质时 Factor(y * x) = Factor(y) * Factor(x), 令Index(y * x) = 1
 * 若 x 为素数, 显然Factor(x) = 2, Index(x) = 1
 * 若 y 被 x 整除, 且x为最小素因子, 则Factor(y * x) = Factor(y) / (Index(y) + 1) * (Index(y) + 2), 而Index(y * x) = Index(y) + 1
 * 
 * 约数和.
 * SumFactor(x) = \sum_{i=0}^{e_1}p_1^i * \sum_{i=0}^{e_2}p_2^i ...* \sum_{i=0}^{e_k}p_k^i
 * 令Low(x) = p_1 ^ e_1,最小素因数的幂次方
 * 显然积性函数, y 与 x 互质时 SumFactor(y * x) = SumFactor(y) * SumFactor(x), Low(y * x) = x(此刻x为最小素因子);
 * 若 x 为素数, 显然SumFactor(x) = x + 1, Low(x) = x
 * 若 y 被 x 整除, 且x为最小素因子, 根据等比公式, SumFactor(y * x) = SumFactor(y) / (1 - Low(y) * x) * (1 - Low(y) * x * x), 而Low(y * x) = low(y) * x
 */

bool bNoPrime[N];
int nPrime[N];              //素数函数
int nMu[N];                 //莫比乌斯函数
int nPhi[N];                //欧拉函数
int nFactor[N], nIndex[N];  //约数个数 & 最小质因子的指数
int nSumFactor[N], nLow[N]; //约束和 & 最小质因子的幂次方

void InitAll()
{
    int nNum = 0;
    bNoPrime[1] = true;
    nMu[1] = 1;
    nPhi[1] = 1;
    nFactor[1] = nIndex[1] = 1;
    nSumFactor[1] = nLow[1] = 1;

    for (int i = 2; i < N; i++)
    {
        if (!bNoPrime[i]) //i是素数
        {
            nPrime[nNum++] = i;
            nMu[i] = -1;
            nPhi[i] = i - 1;
            nFactor[i] = 2;
            nIndex[i] = 1;
            nSumFactor[i] = i + 1;
            nLow[i] = i;
        }
        for (int j = 0; j < nNum && i * nPrime[j] < N; j++)
        {
            int nScreen = i * nPrime[j];
            bNoPrime[nScreen] = true;
            if (i % nPrime[j] == 0)
            {
                nPhi[nScreen] = nPhi[i] * nPrime[j];
                nMu[nScreen] = 0;
                nFactor[nScreen] = nFactor[i] / (nIndex[i] + 1) * (nIndex[i] + 2);
                nIndex[nScreen] = nIndex[i] + 1;
                nSumFactor[nScreen] = nSumFactor[i] * (nLow[i] * nPrime[j] * nPrime[j] - 1) / (nLow[i] * nPrime[j] - 1); //注意溢出
                nLow[nScreen] = nLow[i] * nPrime[j];
                break; //i * Prime[k](k>j) 必定会被Prime[j]在之后筛掉(准确的说Newi等于i/Prime[j]*Prime[k])
            }
            else
            {
                // nIndex 和 nLow 非积性函数
                nPhi[nScreen] = nPhi[i] * nPhi[nPrime[j]];
                nMu[nScreen] = nMu[i] * nMu[nPrime[j]];
                nFactor[nScreen] = nFactor[i] * nFactor[nPrime[j]];
                nIndex[nScreen] = 1;
                nSumFactor[nScreen] = nSumFactor[i] * nSumFactor[nPrime[j]];
                nLow[nScreen] = nPrime[j];
            }
        }
    }
}

int main()
{
    InitAll();
    return 0;
}