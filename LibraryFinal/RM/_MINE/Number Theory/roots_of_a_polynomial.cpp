
// Computes the real roots of a n-degree polynomial
#define eps             1e-9
#define DEPTH_LIMIT     100     // Terminates the process in case of existence of imaginary roots

long double random(long double low, long double high, int itr = 10){
    /*
        returns a double value between the range low and high
        decrease the parameter itr if you just got TLE
    */
    uniform_real_distribution<long double> unif(low, high);
    default_random_engine re;

    int x = rand() % itr;
    while(x--) unif(re);
    return unif(re);
}

void normalize(vector<long double> &polynomial){
    /*
        removes the leading zeros
    */
    while(polynomial.size() && fabs(polynomial.back()) < eps) polynomial.pop_back();
}


long double eval(vector<long double> polynomial, long double x){
    long double ret = 0, p = 1;
    for(auto c : polynomial)
    {
        ret += c * p;
        p = p * x;
    }
    return ret;
}

vector<long double> divide(vector<long double> polynomial, long double z){
    /*
        divides the polynomial by (x - z)
        (x-z) must divide the polynomial
    */
    vector<long double> ret;
    int i;
    for(i = (int) polynomial.size() - 1; i > 0; i--){
        if(i == (int) polynomial.size() - 1) ret.push_back(polynomial[i]);
        else ret.push_back(polynomial[i] + ret.back() * z);
    }

    reverse(ret.begin(), ret.end());
    normalize(ret);
    return ret;
}

vector<long double> differentiate(vector<long double> polynomial){
    vector<long double> ret;
    int i;
    for(i = 1; i < (int) polynomial.size(); i++)
        ret.push_back(polynomial[i] * i);

    return ret;
}


vector<long double> nothing; // Just an empty vector
vector<long double> newton_raphson(vector<long double> polynomial, vector<long double> derivative, long double low, long double high, int depth, int itr = 50){
    /*
        decrease the parameter itr if you just got TLE
        increase the parameter itr if you just got WA
    */

    if(depth > DEPTH_LIMIT) return nothing;

    normalize(polynomial);
    normalize(derivative);

    if(polynomial.size() <= 1) return nothing;

    long double x0 = random(low, high);

    while(itr--){
        long double up = eval(polynomial, x0);
        long double dwn = eval(derivative, x0);

        if(fabs(dwn) < eps) {return newton_raphson(polynomial, derivative, low, high, depth + 1);}
        x0 = x0 - up/dwn;
    }


    if(abs(eval(polynomial, x0)) < eps){
        polynomial = divide(polynomial, x0);
        derivative = differentiate(polynomial);

        vector<long double> ret = newton_raphson(polynomial, derivative, low, high, depth + 1);
        ret.push_back(x0);
        return ret;
    }
    return newton_raphson(polynomial, derivative, low, high, depth + 1);
}

vector<long double> solve(vector<long double> polynomial, long double low, long double high){
    /*
        this is the function to be called from main
        polynomial -> f(x) = p[0] + p[1] * x + p[2] * x^2 + ...... p[n-1] * x^(n - 1)
        [low, high] -> the range where the roots can exist.
    */
    if(polynomial.size() <= 1) return nothing;

    vector<long double> ret, tmp;
    vector<long double> derivative = differentiate(polynomial);
    tmp = solve(derivative, low, high);

    for(auto x : tmp){
        if(fabs(eval(polynomial, x)) < eps){
            ret.push_back(x);
            polynomial = divide(polynomial, x);
        }
    }

    tmp = newton_raphson(polynomial, differentiate(polynomial), low, high, 0);
    for(auto x : tmp)
        ret.push_back(x);

    return ret;
}
