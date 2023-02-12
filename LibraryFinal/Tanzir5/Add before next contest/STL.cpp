/// bit manipulation
__builtin_popcount(mask);
/// C++ Fast IO:
ios_base::sync_with_stdio(false);
cin.tie(NULL);
/*
    numeric_limits<long double>::max()
    numeric_limits<long double>::min()
    numeric_limits<long double>::lowest()
    LLONG_MAX
    ULLONG_MAX
    UINT_MAX
    INT_MAX
/*

iterator:
    map<int,int>::iterator myIt;
new operator:
    int **ara;
    ara = new int*[5];
    ara[2] = new int[10];
Vector:
    Resize for Vector:
        V.resize(5);
    Assign for Vector:
        V.assign(5,1);
        V = [1,1,1,1,1];
    Erase for Vector:
        V.erase(V.begin()+2) ( Removes the third element )
        V.erase(V.begin()+2, V.begin()+5) ( Removes from the third to the FIFTH element )
lower_bound and upper_bound: ( Never use with set!)
    lower_bound(V.begin(),V.end(),val);
    lower_bound returns an iterator pointing to the first element in the range [first,last) which has a value not less than ‘val’.
    upper_bound returns an iterator pointing to the first element in the range [first,last) which has a value greater than ‘val’.
    Complexity: On non-random-access iterators, the iterator advances produce themselves an additional linear complexity in N on average.
Map:
    M.erase(s);
        removes the key value pair where key is s
    Map iterator is a key value pair.
Set:
    S.erase(40) ( erases the element 40 from the set )
    S.erase(it) ( erases element pointed by iterator it )
    S.erase(it, S.end()) From it till S.end(), the whole range is erased
    S.insert(v.begin()+2, v.begin()+5) inserts v[2] to v[4] to the set
    S.lower_bound(val) returns iterator to first element that is not less than val in the set
    S.upper_bound(val) returns similar that is greater than val
Multiset:
    Same as set.
    Inserts same element at the end of the range of current same elements
**After erasing an iterator, that iterator becomes invalidated. Don't use it anymore.
Functions:
    advance(it,n)
        equivalent to: it+=n.   Takes O(n*logn)time for non-random access iterators.
                                Takes O(1) time for random access iterators.
    next_permutation(v.begin(),v.end()):
    it permutes the given range and then sees if it is sorted. If it is sorted, then it returns false.That's why you write do{}while(next_permutation..);
    max_element(v.begin(),v.end())
    min_element(v.begin(),v.end())
    max({3,6,354,12,45})
string:
    Raw strings. This ignores escape characters.
    string r =
R"(The next is a tab    That really was a tab! and now let's print double quote "wow"
Wow this is a new line.
)";
    string to_string(double/int/LL);
    int stoi(string a)
    LL stoll(string a)
*/
