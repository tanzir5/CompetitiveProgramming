
#include <ext/rope> //header with rope
using namespace __gnu_cxx;
/// push_back(element), substr(st,len), erase(st,len), insert(st,rope), + for concatenation

rope <char> R;
string str = "12345678";
/// inserting a string character by character into a rope.
for(auto s: str)
    R.push_back(s);
/// substr(st,len) works in log(n) time. It returns a rope starting from st with len elements.
/// sub and R will share memory for some time till sub or R is not modified.
rope<char>sub = R.substr(2,3);

/// you can access and even modify a rope at random positions in O(log(n))
cout << R[2] << endl;
R.mutable_reference_at(2) = 'a';
cout << R[2] << endl;

/// erase(st,len) works in log(n) time too. It erases len amount of elements starting from position st.
R.erase(2, 3);
/// insert(st,rope) works in log(n). It inserts the rope given in the parameter at position st.
R.insert(4, sub);

/// concatenation of ropes. Guessed it. It's also log(n)
R = R + sub + R;
/// iterate over the rope. You can use auto it = R.begin(). But in that case you
/// will only get a const iterator and won't be able to modify the element.
for(auto it= R.mutable_begin(); it!=R.mutable_end(); it++)
    *it = 'q';
