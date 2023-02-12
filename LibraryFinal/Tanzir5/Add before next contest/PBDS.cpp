#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
orderedSet;

orderedSet X;
X.find_by_order(a); /// returns iterator to the a'th ( 0 based ) largest value of the set
X.order_of_key(a); /// returns number of elements with value less than a.


