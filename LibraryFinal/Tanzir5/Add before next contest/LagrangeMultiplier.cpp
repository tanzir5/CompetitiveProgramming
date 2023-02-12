/*
    A constraint equation Cons()
    Cons() must be equation, not inequality. If problem gives you inequality like,
    t1 + t2 <= T
    then try to prove that there is no point in keeping (t1+t2) < T and solve it for (t1+t2) = T. Lagrange can only solve for equations, not inequalities.

    A objective function ( minimization or maximization ) Obj()
    It should be the case that either minimization or maximization for the given objective function is very easy and the other is very tough
    and has to be solved by lagrange multiplier.
    lambda * D(Cons()) = D(Obj) ,where D(F(x)) is d/dx(F(x))
    Find out the lower or upper bound of lambda from the above function if needed ( using fact such as no probability can be negative etc),
    otherwise set infinity to lower and upper bounds
    Then do a binary search over lambda to find out which value of lambda forces the variables to be equal to constraint.
    That lambda value is the lagrange multiplier and now you know the individual values for the variables which optimizes the given objective function
    If you have additional constraints, try bitmasking or a greedy choice to pick optimal set of variables so that the weaker variables
    don't violate additional constraint.
*/

