#define MAXN ?
/**
*** centerAt : len of longest palindrome center at i
*** centerAfter : len of longest palindrome center after i
*** centerAt is valid for i = 0 to len-1
*** centerAfter is valid for i = 0 to len-2
*** memset these two arrays to zero if you dont want to remember so many things
**/
int centerAt[MAXN],centerAfter[MAXN];
vector <int> manacher(char *str)
{
    int i = 0, j = 0, k = 0, len = strlen(str), n = len << 1;
    vector <int> pal(n);
    for ( ; i < n; j = max( 0, j - k ), i += k)
    {
        while (j <= i && (i + j + 1) < n && str[(i - j) >> 1] == str[(i + j + 1) >> 1]) j++;
        for (k = 1, pal[i] = j; k <= i && k <= pal[i] && (pal[i] - k) != pal[i - k]; k++)
        {
            pal[i + k] = min(pal[i - k], pal[i] - k);
        }
    }
    pal.pop_back();
    return pal;
}
void buildManacher(char *str)
{
    vector < int >  v = manacher(str);
    for(int i=0; i<v.size(); i++)
    {
        if(i&1)
            centerAfter[i/2]=v[i];
        else
            centerAt[i/2]=v[i];
    }
    v.clear();
}
bool isPal(int L, int R)
{
    int zog = L +R,mid = zog/2;
    if(zog&1) return (centerAfter[mid]>=(R-L+1));
    else return centerAt[mid]>=(R-L+1);
}

