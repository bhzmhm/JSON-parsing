# JSON-parsing
## The Problem
We’ll choose a juicy fragment of general JSON: parsing Dyck languages. In this post, we’ll concentrate entirely on extracting the tree structure from the input.
The output will be an array representation suitable for both random access and batch processing. Each node in the tree will be stored as a contiguous block in the output array. The first word in the block is the number of children, and the successive words will be the indices of the children (with the root at index 0). This representation is similar to Cap’n Proto, Flat buffers, and FIDL. For reasons that will become clear later, we’ll generate this result in BFS order.
## Steps
**1. Count nodes, compute nesting depth**

The first pass counts the number of nodes and the nesting depth of each node. To count nodes, map [ to 1 and ] to 0, and compute (exclusive) prefix sum. Nesting depth is the same, but map ] to -1.

**2. Reduce to nodes**

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

Time Complexity = *``` O(n)```*.


**3. Sort by depth**

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

Time Complexity = O(node_count * max_depth) = *``` O(nd)```*.

**4. Determine parents of first children**

Now we do a scatter operation, with the goal of associating first children with their parent nodes. 

Array par shows the first child of each node and if the node has no child we represent it by -1.

  ```
 for (i = 0; i < node_count; i++) {
        if (new_depth[i+1] == new_depth[i] +1){
            int node_num = bfs[i+1];
            par[node_num] = bfs[i];
        }
    }
```
Time Complexity = *``` O(n)```*.

**5. Propagate parent links**

Count the number of childern.

  ```
for (i = 0; i < node_count ; i++) {
        if (parent[i]== parent[i+1] && parent[i] != -1){
            counter++;
            count[i] = counter;
        }
        if (parent[i]!= parent[i+1] && parent[i] != -1){
            counter++;
            count[i] = counter;
            counter =0;
        }
        if (parent[i] == -1)
            count[i] = -1;
    }
```
Time Complexity = *``` O(n)```*.

**6. Scatter child counts**

The count of the childrent of each node.

**7. Allocate**

The number of cells of each node is 1 + the number of children.

 ```
for (i = 0; i < node_count; i++) {
        alloc[i+1] = alloc[i] + nchild[i] + 1;
        max_alloc = alloc[i+1];
    }
```

Time Complexity = *``` O(n)```*.


**8. Generate the result**

For each node i, store nchild[i] into alloc[i], which establishes the size fields. Also store alloc[i] into alloc[parent[i] + count[i]], which establishes the references to the children.

 ```
for (i = 0; i < node_count; i++) {
        int num = alloc[i];
        value[num] = nchild[i];
        if (parent[i] != -1){
            num = new_index[i] + parent[i];
            value[num] = alloc[i];
        }
    }

```
Time Complexity = *``` O(n)```*.

## The Program's Time Complexity

 ```
 O(n + nd + n + n + n + n + n ) = O(nd)
```
