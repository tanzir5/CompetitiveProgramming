///RANGE_MINIMUM_QUEREY[STATIC DATA]
///Preprocessing O(n log n)
///Query O(1)
///Shanto vai's book has a nice explanation

#define MAXLG   17
#define MAXN    30000

struct data{
    int val, idx;
    data(){;}
    data(int v, int i){
        val = v;
        idx = i;
    }
}rmq[MAXLG+5][MAXN+10];
data min(data a, data b) { return (a.val <= b.val)?a:b;}


void preprocess(int in[], int n) // -> 1 based indexing [must be]
{
    int stp, i;
    for(stp = 0; (1<<stp) <= n; stp++)
        for(i = 1; i <= n; i++)
        {
            if(!stp) rmq[stp][i] = data(in[i], i);
            else if(i + (1<<stp) -1 > n) break;
            else rmq[stp][i] = min(rmq[stp-1][i], rmq[stp-1][i+(1<<(stp-1))]);
        }
}

data query(int l, int r)
{
    int mxs = sizeof(int) * 8 - 1 - __builtin_clz(r+1-l);
    return min(rmq[mxs][l], rmq[mxs][r-(1<<mxs)+1]);
}
