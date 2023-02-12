
namespace NT{

    int ocr(LL n, int p){
        int ret = 0;
        while(n){
            ret += n/p;
            n /= p;
        }
        return ret;
    }

    LL ip(LL a, LL p, int MOD){
        if(!p) return 1 % MOD;
        if(p & 1) return (a * ip(a, p - 1, MOD)) % MOD;
        LL ret = ip(a, p/2, MOD);
        return (ret * ret) % MOD;
    }

    LL F(LL n, int p, int MOD){ //This loops inside this function can be optimized with O(MOD * MOD) memory
        if(!n) return 1 % MOD;

        LL c = 1, ret;
        for(int i = 1; i <= min(n, (LL) MOD); i++){
            if(i % p == 0) continue;
            c = (c * i) % MOD;
        }

        LL complete = n / MOD;
        ret = ip(c, complete, MOD);

        for(LL i = complete * MOD + 1; i <= n; i++ ){
            if(i % p == 0) continue;
            ret = (ret * (i % MOD)) % MOD;
        }

        return (ret * F(n/p, p, MOD)) % MOD;
    }


    LL modular_inverse(int a, int p, int n){
        return ip(a, n - n / p - 1, n);
    }

    vector<int> p;
    vector<int> e;
    vector<int> num;
    vector<int> rm;

    void init(int MOD)
    {
        int i, s = sqrt(MOD);
        for(i = 2; i <= s; i++)
        {
            if(MOD % i == 0){
                p.push_back(i);
                e.push_back(0);
                num.push_back(1);
                while(MOD % i == 0){
                    e.back()++;
                    num.back() *= i;
                    MOD /= i;
                }

                s = sqrt(MOD);
            }
        }
        if(MOD != 1){
            p.push_back(MOD);
            e.push_back(1);
            num.push_back(MOD);
        }
    }

    LL crt(){
        LL M = 1, ret = 0, c, b;
        for(int i = 0; i < (int) num.size(); i++)
            M = M * num[i];

        for(int i = 0; i < (int) num.size(); i++){
            b = modular_inverse(M / num[i], p[i], num[i]);
            c = (b * rm[i]) % M;
            c = (c * M/num[i]) % M;
            ret = (ret + c) % M;
        }
        return ret;
    }


    int nCr(LL n, LL r, int MOD) // O( (pi ^ ei) * log n ) -> for maximum pi ^ ei
    {
        if(n == r ||r == 0) return 1 % MOD;

        init(MOD);
        for(int i = 0; i < (int) p.size() ; i++)
        {
            int x = ocr(n, p[i]) - (ocr(r, p[i]) + ocr(n - r, p[i]));


            if(x >= e[i]) rm.push_back(0);
            else{
                rm.push_back(1);
                while(x--) rm.back() *= p[i];

                rm.back() = (rm.back() * F(n, p[i], num[i])) % num[i];
                rm.back() = (rm.back() * modular_inverse(F(r, p[i], num[i]), p[i], num[i])) % num[i];
                rm.back() = (rm.back() * modular_inverse(F(n - r, p[i], num[i]), p[i], num[i])) % num[i];
            }
        }

        return crt();
    }

    void clear(){
        p.clear();
        e.clear();
        num.clear();
        rm.clear();
    }
}
