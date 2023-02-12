
/*
    COMPLEXITY: min(eqn, var) * eqn * var
    MUST CALL CLEAR BEFORE CALLING RESIZE on A
*/

int gauss(vector < vector < double > > A, vector < double > &ret){
    /*
        0-based indexing
        n = number of variables
        m = number of equations

        a_11 a_12 a_13 ..... a_1n | e_1
        a_21 a_22 a_23 ..... a_2n | e_2
        ...
        ...
        ...
        a_m1 a_m2 a_m3 ..... a_mn | e_m

    */

    if(!A.size()) return 1;
    int eqn = A.size();
    int var = A.back().size() - 1, i, j;
    int free_var = 0;
    vector<int> where;
    where.assign(var, -1);
    double c;


    for(int clm = 0, row = 0; clm < var && row < eqn; clm++){

        /*
            Iterating over the variables
                - if (the i-th column is full of 0) then the i-th variable is free
                - else do operations to make sure that A[row][clm] = 1 and A[row'][clm] = 0 when row' != row
        */

        if(abs(A[row][clm]) < eps)
            for(i = row + 1; i < eqn; i++)
                if(abs(A[i][clm]) > eps) {
                    for(j = 0; j <= var; j++)
                        swap(A[i][j], A[row][j]);
                    break;
                }

        if(abs(A[row][clm]) < eps) {continue;}
        where[clm] = row;

        for(i = 0; i < row; i++) assert(abs(A[row][i]) < eps);
        for(c = A[row][clm], i = 0; i <= var; i++) A[row][i] /= c;

        for(i = 0; i < eqn; i++)
            if(i == row) continue;
            else for(c = A[i][clm], j = 0; j <= var; j++) A[i][j] = A[i][j] - A[row][j] * c;

        row++;
    }

    ret.assign(var, 0.0); // We MUST let the free variables to take the value 0.
    for(i = 0; i < var; i++)
        if(where[i] != -1) ret[i] = A[where[i]][var];
        else free_var++;


    for(i = 0; i < eqn; i++){
        double sum = 0;
        for(j = 0; j < var; j++)
            sum += A[i][j] * ret[j];

        if(fabs(sum - A[i][var]) > eps) return 0;
    }

    if(free_var) return INF;
    return 1;
}
