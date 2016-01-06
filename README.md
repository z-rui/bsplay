# bsplay

This is a binary splay tree implementation.

`sp_splay` splays a node to the root of the tree, while keeping the binary search tree properties. Thus, frequently-accessed nodes are moved closer to the root, and the amortized access time is guaranteed to be O(logN).

`sp_erase` erases a node from the tree. It performs a splay operation after erasing, as it is required to maintain the O(logN) time bound.

This implementation does not provide any other general binary search tree algorithms, such as the _search_ or _findMin_. You can implement them on your own.
