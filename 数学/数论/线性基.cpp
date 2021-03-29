/*
线性基
集合B是集合S的线性基，当且仅当：
1.S是B的张成的子集
2.B是线性无关的
性质：
1.B是极小的，任何B的真子集都不是线性基
2.S中的任意元素都可以唯一表示为B中若干个元素异或起来的结果
构造方式：
设集合S中最大的数在二进制意义下有L位，用[0...L]的数组a来储存线性基B。
1.ai=0,只有j>i的aj的第i个二进制为可能为1
2.ai!=0,只有ai的第i个二进制位为1，ai的更高的二进制位一定为0，ai的更低的二进制位可能为1
举例：
1.n个数字，子集异或和为0的种类数为2^(n-rank)
2.两个线性基可以直接暴力合并
3.最大的子集使得异或和不为0，该子集大小即基底大小
4.求第k大
*/

struct LinearBasis {
    int Rank;
    LL a[65];
    void init() { CLR(a, 0); Rank = 0; }
    void insert(LL t) {
        for(int j = 60; j >= 0; j--) if(t>>j&1) {
            if(a[j]) { t ^= a[j]; continue; }
            /*
                求第k大/最大
                for(int k = 0; k < j; k++) if(t>>k&1) t ^= a[k];
                for(int k = j+1; k <= 60; k++) if(a[k]>>j&1) a[k] ^= t;
            */
            a[j] = t; Rank++;
            return;
        }
    }
};
