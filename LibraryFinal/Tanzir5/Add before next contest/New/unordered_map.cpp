struct HASH{
  size_t operator()(const pair<int,int>&x)const{
    return (size_t) x.first * 2411U + (size_t) x.second;
  }
};
unordered_map< pair<int,int>, int, HASH> M;
/// alternatively
#include<bits/stdtr1c++.h>
tr1::unordered_map<int,int>M;
/// Speed up with more memory
M.reserve(1024);
M.max_load_factor(0.25);


/// Better hash tables with 60-70% of time taken by unordered_map
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
????????????????????/// add custom hash function for gp
gp_hash_table<int, int>M; /// preferable, reading/writing is 10% slower than cc, but 3-4 times
                              /// faster in terms of insertion, clearing, deletion
/// or alternatively,
cc_hash_table<int, int>M;
