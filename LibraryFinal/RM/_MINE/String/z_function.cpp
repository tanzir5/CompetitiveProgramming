
// Z-function
#define MAX 100000
char str[MAX+10];
int z[MAX+10];

void z_function() // z[i] = length of the longest substring starting from i that is also a prefix of str
{
    int n = strlen(str);
    z[0] = n;
    for (int i=1, l=0, r=0; i<n; ++i)
    {
        z[i] = 0;
        if (i <= r)
            z[i] = min (r-i+1, z[i-l]);
        while (i+z[i] < n && str[z[i]] == str[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
}

