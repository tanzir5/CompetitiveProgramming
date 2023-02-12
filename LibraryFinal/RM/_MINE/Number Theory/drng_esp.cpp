
//derangement_esp
int derangement(int i, int j)
{
    if(i == 0) return 1;
    if(i == 1) return j-1;
    if(i == 2) return (j-1 + (j-2)*(j-2))%MOD;

    if(dr[i][j] != -1) return dr[i][j];
    return  dr[i][j] = (((LL)(j-i)*derangement(i-1,j-1))%MOD + ((LL)(i-1)*derangement(i-2,j-2))%MOD + ((LL)(i-1) * derangement(i-1,j-1))%MOD)%MOD;
}
