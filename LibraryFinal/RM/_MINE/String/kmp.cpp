
//KMP
char ptrn[MAX+10], text[MAX+10];
int F[MAX+10];

void failure_function(char *pat)
{
    int len = strlen(pat), idx, i;

    F[0] = F[1] = 0; // F[i] = length of the longest PROPER suffix ending at pat[i-1] which is also a PROPER prefix
    for(idx = 2; idx <= len; idx++)
    {
        i = F[idx-1];
        while(1)
        {
            if(pat[i] == pat[idx-1]){ F[idx] = i+1; break;}
            else if(i) i = F[i];
            else {F[idx] = 0; break;}
        }
    }
}

int kmp(char *txt, char *pat) // both 0 indexed
{
    failure_function(pat);
    int txt_len = strlen(txt), pat_len = strlen(pat), pid, ti, ret = 0;
    if(pat_len > txt_len) return 0;

    for(ti = pid = 0; ti < txt_len; ti++)
    {
        while(1)
        {
            if(txt[ti] == pat[pid])
            {
                pid++;
                if(pid == pat_len) ret++, pid = F[pid]; // Match Found at position ti
                break;
            }
            else if(pid) pid = F[pid];
            else break;
        }
    }
    return ret;
}
