#include <iostream>
using namespace std;

 int print(int arr[],int  len){
     for (int i = 0; i < len; i++)
         if (arr[i]== -1){
             cout << "  ";
         } else
             cout << arr[i]<< ' ';
}
int main() {
//    string input[24] = {"[","[","]","[","[","]","[","[","[","]","]","]","[","]","]","[","[","[","]","[","]","]","]","]"};
    string input[18] = {"[", "[", "]", "[", "[", "]", "[", "]", "[", "[", "]", "]", "]", "[", "]", "[", "]", "]"};
    int length = sizeof(input) / sizeof(*input);
    cout << "section 1 :' Count nodes, compute nesting depth ' \n";
    cout << "input : ";
    for (int i = 0; i < length; i++)
        cout << input[i];
    int node_count = length/2;
    int node[length] = {0};
    int depth[length]= {0};
    int index[node_count]= {0} ;
    int new_depth[node_count]={0} ;
    int bfs[node_count]={0};
    int parent[node_count];
    int count[node_count];
    int nchild[node_count]= {0};
    int par[node_count];
    int alloc[node_count] = {0};
    int val = -1;
    int max_depth=0;
    for (int i = 0; i < node_count ; i++){
        par[i] = val;
    }
    int i = 0;
    int j = 0;
    //------------------------------------------------------
    // section one:
    while (i < length){
        if (input[i] == "["){
            node[i+1] = node[i]+1;
            depth[i+1] = depth[i]+1;
            index[j] = node[i];
            new_depth[j] = depth[i];
            if (max_depth < new_depth[j]){
                max_depth = new_depth[j];
            }
            j++;
        }
        if (input[i] == "]"){
            node[i+1] = node[i];
            depth[i+1] = depth[i]-1;}
    i++;
    }
    cout << "\n Node : ";
    print(node,length );
    cout << "\nDepth : ";
    print(depth, length);

    //------------------------------------------------------
    //section two
    cout << "\n\nsection 2 : ' Reduce to nodes '";
    cout << "\nIndex : ";
    print(index, node_count);
    cout << "\nDepth : ";
    print(new_depth, node_count);

    //------------------------------------------------------
    //section three
    cout << "\n\nsection 3 : ' Sort by depth '";
    int bfs_counter = 0;
    j = 0;
    while (j <= max_depth){
        for (i = 0; i < node_count; i++) {
            if (new_depth[i] == j) {
                bfs[i] = bfs_counter;
                bfs_counter++;
            }
        }
        j++;
    }
    cout << "\nIndex : ";
    print(index, node_count);
    cout << "\nDepth : ";
    print(new_depth, node_count);
    cout << "\n  bfs : ";
    print(bfs, node_count);

    //------------------------------------------------------
    //section 4
    cout << "\n\nsection 4 : ' Determine parents of first children '";
    for (i = 0; i < node_count; i++) {
        if (new_depth[i+1] == new_depth[i] +1){
            int node_num = bfs[i+1];
            par[node_num] = bfs[i];
        }
    }
    cout << "\nIndex : ";
    print(index, node_count);
    cout << "\n 1par : ";
    print(par, node_count);

    //------------------------------------------------------
    //section 5
    cout << "\n\nsection 5 : ' Propagate parent links '";
    int flag = -1;
    for (i = 0; i < node_count; i++) {
        if (par[i] != -1){
            flag = par[i];
        }
        parent[i] = flag;
    }
    int counter = 0;
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
    cout << "\nIndex : ";
    print(index, node_count);
    cout << "\nParent: ";
    print(parent, node_count);
    cout << "\nCount : ";
    print(count, node_count);

    //------------------------------------------------------
    // section 6
    cout << "\n\nsection 6 : ' Scatter child counts '";
    int nchild_counter = 0;
    for (i = 0; i < node_count; i++) {
        for (j = 0; j < node_count; j++) {
            if (parent[j] == i){
                nchild_counter++;
            }
        }
        nchild[i] = nchild_counter;
        nchild_counter = 0;
    }
    cout << "\nIndex : ";
    print(index, node_count);
    cout << "\nParent: ";
    print(parent, node_count);
    cout << "\nCount : ";
    print(count, node_count);
    cout << "\nnchild: ";
    print(nchild, node_count);

    //------------------------------------------------------
    //section7
    int max_alloc;
    cout << "\n\nsection 7 : ' Allocate '";
    for (i = 0; i < node_count; i++) {
        alloc[i+1] = alloc[i] + nchild[i] + 1;
        max_alloc = alloc[i+1];
    }
    cout << "\nIndex : ";
    print(index, node_count);
    cout << "\nParent: ";
    print(parent, node_count);
    cout << "\nnchild: ";
    print(nchild, node_count);
    cout << "\nalloc : ";
    print(alloc, node_count);

    //------------------------------------------------------
    //section 8
    cout << "\n\nsection 8 : ' Generate the result '";
    int value[max_alloc]= {0};
    int new_index[max_alloc];
    for (int i = 0; i < max_alloc ; i++){
        new_index[i] = i;
    }
    for (i = 0; i < node_count; i++) {
        int num = alloc[i];
        value[num] = nchild[i];
        if (parent[i] != -1){
            num = new_index[i] + parent[i];
            value[num] = alloc[i];
        }
    }

    cout << "\nindex : ";
    print(new_index, max_alloc);
    cout << "\nvalue : ";
    print(value, max_alloc);
    return 0;
}
