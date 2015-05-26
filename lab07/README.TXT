Part b.

Advantages of self-balancing trees (set):
Highly efficient when finding adjacent elements, since elements are stored in a set order (insert and lookup times are lower when n is lower)

Disadvantages of self-balancing trees:
Worse average-case performance than hash tables
Query times seem to increase as n increases

Advantages of hash tables (unordered set):
Significantly faster in insertion and lookup than self-balancing trees
Consistently linear lookup times as n increases

Disadvantages of hash tables:
Because of the random nature of hash tables, there is no advantage looking up adjacent elements, unlike self-balancing trees, which do


For further comparison, I would like to test insertion and lookup for a single element, to test the worst-case performance of self-balancing trees and hash tables.
