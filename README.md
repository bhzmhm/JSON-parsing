# JSON-parsing
## The Problem
We’ll choose a juicy fragment of general JSON: parsing Dyck languages. In this post, we’ll concentrate entirely on extracting the tree structure from the input.
The output will be an array representation suitable for both random access and batch processing. Each node in the tree will be stored as a contiguous block in the output array. The first word in the block is the number of children, and the successive words will be the indices of the children (with the root at index 0). This representation is similar to Cap’n Proto, Flat buffers, and FIDL. For reasons that will become clear later, we’ll generate this result in BFS order.
## Steps
1. Count nodes, compute nesting depth

The first pass counts the number of nodes and the nesting depth of each node. To count nodes, map [ to 1 and ] to 0, and compute (exclusive) prefix sum. Nesting depth is the same, but map ] to -1.

2. Reduce to nodes

We only care about nodes, not symbols.
I have done part one and two in a single while.
  ```
  while (i < length){
        if (input[i] == "["){
            node[i+1] = node[i]+1;
            depth[i+1] = depth[i]+1;
            index[j] = node[i];
            new_depth[j] = depth[i];
            j++;
        }
        if (input[i] == "]"){
            node[i+1] = node[i];
            depth[i+1] = depth[i]-1;}
    i++;
    }
```

Time Complexity = O(n).

3. Sort by depth

Find the bfs order of our nodes based on the depth of each node.

  ```
 while (j <= max_depth){
        for (i = 0; i < length/2; i++) {
            if (new_depth[i] == j) {
                bfs[i] = bfs_counter;
                bfs_counter++;
            }
        }
        j++;
    }
```

Time Complexity = O(node_count * max_depth) = O(nd).

4. Determine parents of first children
5. Propagate parent links
6. Scatter child counts
7. Allocate
8. Generate the result
