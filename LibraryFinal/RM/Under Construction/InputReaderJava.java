
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.math.BigInteger;
import java.util.Scanner;
import java.lang.Exception;
import java.util.StringTokenizer;

public class Main  {

    public static void main(String args[])
    {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        
        
        int n = in.nextInt(), i;
        
        vector a, b, c, d;
        a = new vector(n);
        b = new vector(n);
        c = new vector(n);
        d = new vector(n); 
        
        a.arr = new int[n + 5];
        b.arr = new int[n + 5];
        c.arr = new int[n + 5];
        d.arr = new int[n + 5];
        
        for(i = 0; i < n; i++){
            int v = in.nextInt();
            a.arr[i] = v;
        }
        
         for(i = 0; i < n; i++){
            int v = in.nextInt();
            b.arr[i] = v;
        }
         
          for(i = 0; i < n; i++){
            int v = in.nextInt();
            c.arr[i] = v;
        }
          
           for(i = 0; i < n; i++){
            int v = in.nextInt();
            d.arr[i] = v;
        }

        long a1, b1, c1, a2, b2, c2; 
                
        a1 = 0;                    
        for(i = 0; i < n; i++)
            a1 = a1 +((long) (b.arr[i] - a.arr[i]) * (b.arr[i] - a.arr[i]));        
        a2 = 0;                    
        for(i = 0; i < n; i++)
            a2 = a2 + (long) (d.arr[i] - c.arr[i]) * (d.arr[i] - c.arr[i]);
       
        
        b1 = 0;
        for(i = 0; i < n; i++)
            b1 = b1 - (long) (b.arr[i] - a.arr[i]) * (d.arr[i] - c.arr[i]); 
        b2 = 0;
        for(i = 0; i < n; i++)
            b2 = b2 - (long) (d.arr[i] - c.arr[i]) * (b.arr[i] - a.arr[i]); 
        
        
        c1 = 0;
        for(i = 0; i < n; i++)
            c1 = c1 + (long) (b.arr[i] - a.arr[i]) * (a.arr[i] - c.arr[i]); 
        c2 = 0; 
        for(i = 0; i < n; i++)
            c2 = c2 + (long) (d.arr[i] - c.arr[i]) * (c.arr[i] - a.arr[i]);      
        
//        System.out.println(a1 + " _ " + b1 + " " + c1);
//        System.out.println(b2 + " _ " + a2 + " " + c2);
       
        Fraction A1 = new Fraction(a1, 1); 
        Fraction B1 = new Fraction(b1, 1);
        Fraction C1 = new Fraction(c1, 1); 
        
        Fraction A2 = new Fraction(b2, 1); 
        Fraction B2 = new Fraction(a2, 1); 
        Fraction C2 = new Fraction(c2, 1);
        Fraction MINUSONE = new Fraction(-1, 1); 
        
        Fraction up, dwn, s, t;
        Fraction zero = new Fraction(0, 1); 
        
        if( (A1.multiply(B2)).equals(A2.multiply(B1)) == false)
        {                        
            up = ((A2.multiply(C1).multiply(MINUSONE)).add((A1.multiply(C2))));      
            dwn = (B1.multiply(A2)).sub(B2.multiply(A1));            
            t = up.divide(dwn); 

            up = ((C2.multiply(B1)).add((C1.multiply(B2)).multiply(MINUSONE)));
            dwn = (A1.multiply(B2)).sub(A2.multiply(B1));       
            s = up.divide(dwn);   
        }
        else{
            if(A1.equals(zero) == false)
            {
                t = new Fraction(0, 1);           
                s = C1.divide(A1).multiply(MINUSONE);               
            }
            else if(B1.equals(zero) == false){
                s = new Fraction(0, 1); 
                t = C1.divide(B1).multiply(MINUSONE);
            }
            else{
                s = new Fraction(0, 1);
                t = new Fraction(0, 1);
            }
        }
        
        Fraction result = new Fraction(0, 1);
      
        long aa = 0, ab_a = 0, cd_c = 0, cc = 0, ac = 0, cb_a = 0, ad_c = 0, b_a_m_d_c = 0;
        for(i = 0; i < n; i++){
            aa += (long) a.arr[i] * a.arr[i]; 
            ab_a += (long) a.arr[i] * (b.arr[i] - a.arr[i]); 
            cd_c += (long) c.arr[i] * (d.arr[i] - c.arr[i]);
            cc += (long) c.arr[i] * c.arr[i]; 
            
            ac += (long) a.arr[i] * c.arr[i]; 
            cb_a += (long) c.arr[i] * (b.arr[i] - a.arr[i]); 
            ad_c += (long) a.arr[i] * (d.arr[i] - c.arr[i]); 
            
            b_a_m_d_c += (long) (b.arr[i] - a.arr[i]) * (d.arr[i] - c.arr[i]);
        }
        
        result = new Fraction(aa, 1).add(new Fraction(a1, 1).multiply(s).multiply(s));
        result = result.add(new Fraction(ab_a, 1).multiply(s).multiply(new Fraction(2, 1)));
        result = result.add(new Fraction(cc, 1)); 
        result = result.add(new Fraction(a2, 1).multiply(t).multiply(t));
        result = result.add(new Fraction(cd_c, 1).multiply(t).multiply(new Fraction(2, 1)));
        
        result = result.sub(new Fraction(ac, 1).multiply(new Fraction(2, 1)));         
        result = result.sub(new Fraction(cb_a, 1).multiply(s).multiply(new Fraction(2, 1))); 
        result = result.sub(new Fraction(ad_c, 1).multiply(t).multiply(new Fraction(2, 1)));
        result = result.sub(new Fraction(b_a_m_d_c, 1).multiply(s).multiply(t).multiply(new Fraction(2, 1)));
        
        
        result.reduce();
        System.out.println(result.up + "/" + result.dwn);
               
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
    
    Fraction(long u, int d){
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
    
    boolean equals(Fraction ano){
        return up.multiply(ano.dwn).equals(ano.up.multiply(dwn));
    }

    
    Fraction divide(Fraction ano){
        if(ano.equals(new Fraction(0, 1))){
            while(true){
                ;
            }
        }
        Fraction F = new Fraction( up.multiply(ano.dwn), dwn.multiply(ano.up));
        return F;
    }

    
    void copy(Fraction ano){
        up = ano.up;
        dwn = ano.dwn;
    }
}


class vector{
    int arr[], n;
    vector(int _n){
        //arr = new int[n + 5]; 
        n = _n;
    }
    void take_input(){
        Scanner scan = new Scanner(System.in);         
        int i;
        for(i = 0; i < n; i++) {
            arr[i] = scan.nextInt();
        } 
    }    
}

class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

    }