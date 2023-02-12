
/*
    Gauss for BigInteger + Fraction
*/

import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    public static void main(String args[])
    {

        int i, t, cs, lim;
        String s;
        Scanner sf = new Scanner(System.in);

        t = sf.nextInt();
        for(cs = 1; cs <= t; cs++){
            lim = sf.nextInt();
            s = sf.next();

            KMP k = new KMP(s);
            k.failure_function();

            Matrix M = new Matrix(s.length() + 1, s.length() + 1);

            for(i = 0; i < s.length(); i++){

                M.mat[i][i] = new Fraction(-1, 1);
                M.mat[i][s.length() + 1] = new Fraction(-1, 1);

                for(int x = 1; x <= lim; x++){
                    if(s.charAt(i) == (char) ('A' + x - 1)){
                        M.mat[i][i+1] = M.mat[i][i + 1].add(new Fraction(1, lim));
                    }
                    else{
                        boolean matched = false;
                        int npos = i;
                        while(npos != 0){
                            npos = k.F[npos];

                            if(s.charAt(npos) == (char) ('A' + x - 1)){
                                M.mat[i][npos + 1] = M.mat[i][npos + 1].add(new Fraction(1, lim));
                                matched = true;
                                break;
                            }
                        }

                        if(matched == false){
                             M.mat[i][0] = M.mat[i][0].add(new Fraction(1, lim));
                        }
                    }
                }
            }

            M.mat[s.length()][s.length()] = new Fraction(1, 1);
            M.mat[s.length()][s.length() + 1] = new Fraction(0, 1);

            M.elim();
            System.out.println("Case " + cs + ":");
            System.out.println(M.ret[0].up);
            if(cs != t) System.out.println("");
        }
    }
}

class KMP{
    String str;
    int F[];

    KMP(String s){
        str = s;
        F = new int[str.length() + 5];
    }

    void failure_function(){
        int len = str.length(), idx, i;

        F[0] = F[1] = 0;
        for(idx = 2; idx <= len; idx++)
        {
            i = F[idx  - 1];
            while(true)
            {
                if(str.charAt(i) == str.charAt(idx - 1)) {
                    F[idx] = i + 1;
                    break;
                }
                else if(i != 0) i = F[i];
                else{
                    F[idx] = 0;
                    break;
                }
            }
        }
    }
}

class Fraction{
    BigInteger up, dwn;

    void reduce()
    {
        BigInteger g = up.gcd(dwn);
        up = up.divide(g);
        dwn = dwn.divide(g);

        if(up.signum() == -1 && dwn.signum() == -1){
            up = up.negate();
            dwn = dwn.negate();
        }
    }

    Fraction(){
        up = BigInteger.valueOf(0);
        dwn = BigInteger.valueOf(1);
        reduce();
    }

    Fraction(int u, int d){
        up = BigInteger.valueOf(u);
        dwn = BigInteger.valueOf(d);
        reduce();
    }

    Fraction(BigInteger u, BigInteger v){
        up = u;
        dwn = v;
        reduce();
    }

    Fraction add(Fraction ano){
        Fraction F = new Fraction( up.multiply(ano.dwn).add(ano.up.multiply(dwn))  , dwn.multiply(ano.dwn) );
        return F;
    }

    Fraction sub(Fraction ano){
        Fraction F = this;
        F = F.add(new Fraction(ano.up.negate(), ano.dwn));
        return F;
    }

    Fraction multiply(Fraction ano){
        Fraction F = new Fraction( up.multiply(ano.up), dwn.multiply(ano.dwn));
        return F;
    }

    Fraction divide(Fraction ano){
        Fraction F = new Fraction( up.multiply(ano.dwn), dwn.multiply(ano.up));
        return F;
    }

    boolean equals(Fraction ano){
        return up.multiply(ano.dwn).equals(ano.up.multiply(dwn));
    }

    void copy(Fraction ano){
        up = ano.up;
        dwn = ano.dwn;
    }
}

class Matrix{
    int neq, nvar;
    Fraction mat[][];
    Fraction ret[];


    Matrix(int r, int c){
        neq = r;
        nvar = c;
        mat = new Fraction[r][c + 1];
        ret = new Fraction[c];

        for(int i = 0; i < r; i++)
            for(int j = 0; j <= c; j++)
                mat[i][j] = new Fraction(0, 1);

        for(int i = 0; i < nvar; i++)
            ret[i] = new Fraction(0, 1);
    }

    int elim(){
        int free_var = 0;
        int eqn = neq;
        int var = nvar;
        int where[] = new int[nvar];
        for(int i = 0; i < nvar; i++) where[i] = -1;
        Fraction zero = new Fraction(0, 1);
        Fraction c = new Fraction(0, 1);

        int row = 0;
        for(int clm = 0; clm < var && row < eqn; clm++)
        {
            if(mat[row][clm].equals(zero)){
                for(int i = row + 1; i < eqn; i++)
                {
                    if(mat[row][clm].equals(zero) == false){
                        for(int j = 0; j <= var; j++){
                            Fraction tmp = new Fraction();
                            tmp.copy(mat[i][j]);
                            mat[i][j].copy(mat[row][j]);
                            mat[row][j].copy(tmp);
                        }
                    }
                }
            }

            if(mat[row][clm].equals(zero)) continue;
            where[clm] = row;

            c.copy(mat[row][clm]);
            for(int  i = 0; i <= var; i++){
                mat[row][i] = mat[row][i].divide(c);
            }

            for(int i = 0; i < eqn; i++)
                if(i == row) continue;
                else{
                    c.copy(mat[i][clm]);
                    for(int j = 0; j <= var; j++){
                        Fraction tmp = new Fraction(0, 1);
                        tmp.copy(mat[row][j]);
                        tmp = tmp.multiply(c);
                        mat[i][j] = mat[i][j].sub(tmp);
                    }
                }
            row++;
        }

        for(int i = 0; i < var; i++) ret[i] = new Fraction(0, 1);
        for(int i = 0; i < var; i++){
            if(where[i] != -1) ret[i].copy(mat[where[i]][var]);
            else free_var++;
        }

        for(int i = 0; i < eqn; i++){
            Fraction sum = new Fraction(0, 1);
            for(int j = 0; j < var; j++){
                Fraction tmp = new Fraction(0, 1);
                tmp.copy(mat[i][j]);
                tmp = tmp.multiply(ret[j]);
                sum = sum.add(tmp);
            }
           if(sum.equals(mat[i][var]) == false) return 0;
        }

        if(free_var != 0) return 1000000000;
        return 1;
    }
}
