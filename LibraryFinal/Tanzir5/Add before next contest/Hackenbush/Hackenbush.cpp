Green Hackenbush And Colon Principle:
    Game Rules:
    1. Players move in alternating turns, and both players always move optimally.
    2. During each move, a player removes an edge from the tree, disconnecting one of its leaves or
       branches. The leaf or branch that was disconnected from the rooted tree is removed from the game.
    3. The first player to be unable to make a move loses the game.

    Solution:
    1. A single stalk is like a chain.
    2. Size of a stalk is the number of edges in it.
    3. A single stalk can be considered as a nim pile.
    4. All kind of trees can be transformed to a single stalk using colon principle.
    5. Colon Principle:
        If node u has 3 children a, b, c. then
            stalkSize(u) = (stalkSize(a) + 1) ^ (stalkSize(b) + 1) ^ (stalkSize(c) + 1)
    6. Look at the nim pile size of the stalk obtained from the tree and decide who wins the game.

Fusion Principle:
    The Fusion Principle states that you can fuse all the nodes in any cycle of a Green Hackenbush and get a tree structure.
    Shahin library figure and notes.
    If number of edges in the cycle is even, then the cycle can be replaced by a single node. If
    number of edges in the cycle is odd, then the cycle can be replaced by a single special node with
    an additional edge. In both cases all the other edges of the nodes that just got fused,
    get attached to the new node.

Blue Red Stalk:
    1. Blue player moves first
    2. Blue player only cuts blue edges, Red player only cuts red edges. Substalk or subtree which has no attachment to the
       ground/root gets eliminated just like green hackenbush.
    3. First player who cannot move loses.
Solution:
    Blue is positive, Red is negative.
    Until the color changes for the first time, each edge is worth +V or −V (depending on whether it is blue or red,
    respectively). Once color change occurs, each subsequent edge (regardless of being blue or red), is worth half of the
    previous value, with a +/− corresponding to the color.

For example: BBBRB = +V +V +V -V/2 +V/4. Now sum them to get value of each stalk.

For multiple stalk, instead of using XOR, we add them normally. If positive then Blue wins and if negative Red wins.

Blue Red Hackenbush Tree:
    Same as blue red stalk, but with a tree.
    We can convert a tree to a stalk.
    Figure from pdf
