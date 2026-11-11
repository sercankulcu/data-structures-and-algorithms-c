# Data Structures and Algorithms in C

C code for the undergraduate **Data Structures and Algorithms with C (C ile Veri Yapıları ve Algoritmalar)** course at Giresun University. Each `BolumNN` folder holds chapter NN of the course and contains the code shown on that chapter's slides as small runnable programs. Function, type, variable and macro names follow the slides, and every program runs the worked example from the lecture notes, so its output can be compared directly with the slides and the notes. The expected output is at the end of each file.

Course page, slides, lecture notes and the course book: <https://sercankulcu.github.io/teaching/data-structures-and-algorithms-with-c/>

## Chapters

| Folder | Chapter | Programs |
|---|---|---|
| `Bolum01` | Introduction and Algorithm Analysis | Fraction ADT with an opaque type split into `kesir.h`/`kesir.c`/`main.c`, selection sort with the `SWAP` macro, `SWAP` macro vs. pointer `swap()`, space complexity (`abc`, `sum`, `rsum`), step counting with a global `count`, odd magic square, sort timing with `clock()`, sentinel linear search and repeated-run timing, recursive factorial, Fibonacci and binomial coefficients |
| `Bolum02` | Arrays and Structures | Array declaration, `sizeof` and pointer arithmetic, `malloc`'d arrays, a growing dynamic array with `realloc` doubling, 2D dynamic array of row pointers, row-major address and offset formulas, lower-triangular and band matrix storage, `&&` short-circuit, structures, nested and self-referential structures, tagged union, array of structures, C strings and a hand-written `strlen`, matrix multiplication |
| `Bolum03` | Recursion, Binary Search and Backtracking | Recursive, iterative and tail-recursive factorial, iterative and recursive binary search with the `COMPARE` macro, Towers of Hanoi, permutations by swapping, subset generation by backtracking, brute-force SAT over a formula tree, n-queens |
| `Bolum04` | Linked Lists | Traversal; insertion at the head, at the tail, after a node and in order; deleting the next node and by value; search; recursive and iterative freeing; in-place reversal; concatenation; middle node and Floyd cycle detection; circular list; header node; doubly linked circular list; avail list of free nodes |
| `Bolum05` | Polynomials and Sparse Matrices | Polynomials as a coefficient array, as a shared term array (`padd` with `COMPARE`/`attach`) and as a linked list (multiplication); sparse matrices as triples: `transpose`, `fast_transpose`, multiplication `smult`, CSR matrix-vector product |
| `Bolum06` | Stacks | Stack on a global array, struct-based stack with `bool` push/pop and string reversal, opaque stack type in `yigit.h`/`yigit.c`, linked stack, several stacks sharing one array |
| `Bolum07` | Queues | Linear array queue, circular queue (exit version and safe `bool` version), counter-based circular queue, linked queue, circular-array deque, round-robin scheduling, queue from two stacks |
| `Bolum08` | Stack and Queue Applications | Maze backtracking with an explicit stack, postfix evaluation, infix-to-postfix with `isp`/`icp`, prefix evaluation, balanced brackets |
| `Bolum09` | List ADT and Generalized Lists | List ADT with an opaque type, array list with shifting, linked insertion with a pointer to pointer, multivariate polynomial as a generalized list, generalized-list routines (copy, equality, printing, depth, reversal), reference counting with header nodes |
| `Bolum10` | Trees | Binary tree in an array, linked nodes, recursive preorder/inorder/postorder, left-child right-sibling general tree, expression-tree evaluation, stack-based traversals, leaf printing, level-order traversal with a circular queue, tree copy, equality and mirroring |
| `Bolum11` | Search Trees | BST insertion (iterative and recursive), iterative and recursive search, depth (recursive and level-order), the `MAX` macro double-evaluation trap, deletion through a pointer to pointer, AVL rotations and insertion, exam problems (node weight, call counting, `SWAP` between recursive calls) |
| `Bolum12` | Threaded Binary Trees | Threaded binary tree with a header node: inorder successor and predecessor, stackless traversals, insertion to the right and left, Morris inorder traversal |
| `Bolum13` | Priority Queues and Heaps | Array-based max heap (sift-up insert, sift-down delete), min heap, increasing and decreasing a priority, bottom-up heap construction, heap in a dynamically allocated struct |
| `Bolum14` | Hash Tables | Direct addressing, division and multiplication hashing, polynomial string hash and djb2, open addressing with linear probing and tombstones, separate chaining, resizing with rehashing |
| `Bolum15` | Graphs | Degree from the adjacency matrix, adjacency lists, the transpose, the sequential array representation, the adjacency multilist, weighted graphs, recursive DFS, BFS with a linked queue, connected components, cycle detection |
| `Bolum16` | Sets and Union-Find | Parent-array union-find and the bad union sequence, weighted union, collapsing find, the Ackermann function, counting components |
| `Bolum17` | Minimum Spanning Trees | Kruskal with `qsort` and weighted union-find, O(n²) Prim, Prim with adjacency lists and a binary min-heap |
| `Bolum18` | Shortest Paths and Activity Networks | Dijkstra with path printing, Bellman-Ford with negative-cycle detection, Floyd-Warshall, topological sort with counter headers, AoE network earliest/latest times, slack and critical activities |
| `Bolum19` | Basic Sorting Algorithms | Common `SWAP` macros and test program, selection sort, insertion sort and the sentinel version, bubble sort and the early-exit version, counting sort, Shell sort, bucket sort |
| `Bolum20` | Advanced Sorting Algorithms | Quicksort, non-recursive quicksort with an explicit stack, median-of-three with a cutoff, `qsort` with `int` and struct comparators, merge sort, linked-list merge sort, heap sort, radix sort on a linked list |

## Running the examples

Every program is standard C11 and uses only the C standard library. A file `BolumNN/name.c` is one program; a folder `BolumNN/name/` (an interface split into `.h` and `.c` files) is one program made of all the `.c` files in it. No program reads the keyboard or leaves files behind.

```bash
cd Bolum06
gcc -std=c11 -Wall -Wextra -pedantic yigit_struct.c -o yigit_struct
./yigit_struct

cd yigit_opak
gcc -std=c11 -Wall -Wextra -pedantic *.c -o yigit
./yigit
```

The timing programs in `Bolum01` and the address printout in `Bolum02/yazdir.c` print different values on every run, and `Bolum19/siralama_deneme.c` prints the numbers of the C library's `rand()` (the expected output shown is glibc's); the comments say so.

`ci/build.sh` compiles and runs every program. GitHub Actions runs it on every push with `gcc` (warnings are errors) and with `clang` under AddressSanitizer and UndefinedBehaviorSanitizer, so a memory leak, an out-of-bounds access or undefined behaviour fails the build.

Comments and identifiers are in Turkish, as on the slides. Where a slide's code uses something it does not show (a type, a helper function, a `main`), the file adds the smallest piece needed, usually from the lecture notes, and marks it with `/* sunumda yok */`.

## Contact

For questions or suggestions, contact [Sercan Külcü](https://github.com/sercankulcu) or open an issue on GitHub.
