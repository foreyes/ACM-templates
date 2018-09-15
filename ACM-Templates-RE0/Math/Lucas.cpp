long long fac[400],inv[400];
const int MOD = 1e9+7;
long long pow_mod(long long x, long long n, long long mod){
    long long res=1;
    while(n>0){
        if(n&1)res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
void init(){
    fac[0] = 1;
    for(int i = 1;i <= 300;++i){
        fac[i] = fac[i-1]*i%MOD;
    }
    for(int i = 0;i <= 300;++i){
        inv[i] = pow_mod(fac[i],MOD-2,MOD);
    }
}
long long C(long long n,long long m){
    long long ans = fac[n];
    ans = ans * inv[m] % MOD;
    ans = ans * inv[n-m] % MOD;
    return ans;
}
