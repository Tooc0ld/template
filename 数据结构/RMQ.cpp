I namespace RMQ {
    void init() { for(int i = 2; i < N; i++) Log[i] = Log[i>>1]+1; }
    void RMQ_init(int n, int *A) { //A下标从1开始
        for(int i = 1; i <= n; i++) dp[i][0] = A[i];
        for(int j = 1; (1<<j) <= n; j++)
            for(int i = 1; i+(1<<j)-1 <= n; i++)
                dp[i][j] = min(dp[i][j-1], dp[i+(1<<j-1)][j-1]);
    }
    I int RMQ(int L, int R) { //下标从1开始
        int k = Log[R-L+1];
        return min(dp[L][k], dp[R-(1<<k)+1][k]);
    }
}
