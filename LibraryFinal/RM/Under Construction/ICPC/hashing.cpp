const pii MOD 	= pii(1000000007, 1000000009);
const pii BASE 	= pii(999983, 999983); 
const pii ZERO 	= pii(0, 0);


pii operator + (const pii &u, const pii &v){
	return pii( ( ((u.xx + v.xx) % MOD.xx) + MOD.xx ) % MOD.xx, ( ((u.yy + v.yy) % MOD.yy) + MOD.yy ) % MOD.yy );
}


pii operator - (const pii &u, const pii &v){
	return pii( ( ((u.xx - v.xx) % MOD.xx) + MOD.xx ) % MOD.xx, ( ((u.yy - v.yy) % MOD.yy) + MOD.yy ) % MOD.yy );
}

pii operator * (const pii &u, const pii &v){
	return pii( ((LL)u.xx * v.xx) % MOD.xx, ((LL)u.yy * v.yy) % MOD.yy );
}

int ip(int a, int p, int m){
	if(!p) return 1; 
	if(p & 1) return ( (LL) a * ip(a, p - 1, m) ) % m; 
	LL ret = ip(a, p/2, m);
	return (ret * ret) % m; 
}

pii modInv(pii u){
	return pii( ip(u.xx, MOD.xx-2, MOD.xx), ip(u.yy, MOD.yy - 2, MOD.yy) );
}

pii operator / (const pii &u, const pii &v){
	return u * modInv(v);
}
