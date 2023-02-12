
/*
    COMPLEXITY: min(eqn, var) * eqn * var
    The MOD must be a prime.
    MUST CALL CLEAR BEFORE CALLING RESIZE on A
*/

int gauss(vector < vector < int > > A, vector < int > &ret){

    if(!A.size()) return 1;
    int eqn = A.size();
    int var = A.back().size() - 1, i, j;
    int free_var = 0;
    vector<int> where;
    where.resize(var, -1);
    LL c;


    for(int clm = 0, row = 0; clm < var && row < eqn; clm++){
        if(!A[row][clm])
            for(i = row + 1; i < eqn; i++)
                if(A[i][clm]) {
                    for(j = 0; j <= var; j++)
                        swap(A[i][j], A[row][j]);
                    break;
                }

        if(!A[row][clm]) {continue;}
        where[clm] = row;

        for(i = 0; i < row; i++) assert(!A[row][i]);
        for(c = mod_inv(A[row][clm]), i = 0; i <= var; i++) A[row][i] = mul( A[row][i] , c );

        for(i = 0; i < eqn; i++)
            if(i == row) continue;
            else
                for(c = A[i][clm], j = 0; j <= var; j++) {
                        A[i][j] = sub(A[i][j] , mul(A[row][j] , c));
                    }
        row++;
    }

    ret.assign(var, 0);
    for(i = 0; i < var; i++)
       if(where[i] != -1) ret[i] = A[where[i]][var];
       else free_var++;

    for(i = 0; i < eqn; i++){
        int sum = 0;
        for(j = 0; j < var; j++)
            sum = add(sum ,  mul(A[i][j] , ret[j]));
        if(sum != A[i][var]) return 0;
    }

    if(free_var) return INF;
    return 1;
}
