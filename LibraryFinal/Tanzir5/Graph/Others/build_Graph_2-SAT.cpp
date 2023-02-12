/*
    For building graphs in 2-SAT

    1.      1 x y means that either x or y should be present in the meeting.
    2.      2 x y means that if x is present, then no condition on y, but if x is absent y should be absent
    3.      3 x y means that either x or y must be absent.
    4.      4 x y means that either x or y must be present but not both.

    void buildGraph(int m)
    {
        int i, j, u, v;
        FRE(i,1,m)
        {
            sf(j);
            sff(u,v);
            if(j == 1)
            {
                E[n+u].pb(v);
                E[n+v].pb(u);
                REV[v].pb(n+u);
                REV[u].pb(n+v);
            }
            else if ( j == 2)
            {
                E[n+u].pb(n+v);
                E[v].pb(u);
                REV[n+v].pb(n+u);
                REV[u].pb(v);
            }
            else if( j == 3)
            {
                E[u].pb(n+v);
                E[v].pb(n+u);
                REV[n+v].pb(u);
                REV[n+u].pb(v);
            }
            else
            {
                E[u].pb(n+v);
                E[v].pb(n+u);
                E[n+u].pb(v);
                E[n+v].pb(u);
                REV[n+v].pb(u);
                REV[n+u].pb(v);
                REV[v].pb(n+u);
                REV[u].pb(n+v);
            }
        }
    }

*/
