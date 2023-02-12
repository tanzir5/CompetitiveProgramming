

#define xx		first
#define yy		second
typedef long long int LL;
typedef pair<int,int> pii;

#define CW 		-1
#define ACW	 	 1

int direction(pii st, pii ed, pii q){
	LL xp = (LL) (ed.xx - st.xx) * (q.yy - ed.yy) - (LL) (ed.yy - st.yy) * (q.xx - ed.xx);
	if(!xp) return 0;
	if(xp > 0) return ACW;
	return CW;
}

/*
    Minimized border points, works in degenerate case
    To maximize border points
        - change != to == and swap(CW,ACW)
        - Be careful about p[0], p[back] line
*/
int convex_hull(vector <pii> p, vector<pii> &h)
{
	vector<pii> up, dwn; // constructs upper hull in clockwise order, lower hull in anti-clockwise order
	h.clear();
	sort(p.begin(), p.end());
	up.push_back(p[0]);
	dwn.push_back(p[0]);

	for(int i = 1; i < (int) p.size(); i++){
		if(direction(p[0], p.back(), p[i]) != CW){
			while(up.size() >= 2 && direction(up[up.size() - 2], up.back(), p[i]) != CW) up.pop_back();
			up.push_back(p[i]);
		}

		if(direction(p[0], p.back(), p[i]) != ACW){
			while(dwn.size() >= 2 && direction(dwn[dwn.size() - 2], dwn.back(), p[i]) != ACW) dwn.pop_back();
			dwn.push_back(p[i]);
		}
	}

	h = dwn;
	for(int i = (int) up.size() - 2; i >= 1; i--) h.push_back(up[i]);
	return h.size();
}

