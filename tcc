tccvcv sdf s sd f



sd sdf sdsad



a





 * Returns the number of nodes in a Tree.
 * parameters:
 * @param node - Is the root of the tree.
 * @param x - Is the parameter for the result.
 * @return
 * The number of nodes in parameter x.

void Heap::numberNodes(MinNode* node, int* x) {
    if (node != NULL) {
        *x = (*x) + 1;
        numberNodes(node->left, x);
        numberNodes(node->right, x);
    }
}



 * Checks if a number is a power of two.
 * parameters:
 * @param number - Is the number.
 * @return
 * true - if the result is positive.
 * false - otherwise.

bool CheckPowerOfTwo(int number) {
    if (floor(log2(number))==ceil(log2(number))){
        return true;
    } else {
        return false;
    }
}

 * Calculates the number of nodes needed in the closest full tree function.
 * parameters:
 * @param number - Is the number of needed nodes.
 * @return
 * the number of nodes that will be in the closest full tree.

int CalculateNodesNumber(int number_of_nodes) {
    int delta_nodes = 1;
    int full_number_of_nodes = 0;
    bool is_found = false;
    while (!is_found) {
        if (CheckPowerOfTwo(number_of_nodes + delta_nodes + 1)) {
            full_number_of_nodes = number_of_nodes + delta_nodes;
            is_found = true;
        }
        delta_nodes++;
    }
    return full_number_of_nodes;
}



MinNode* Heap::ActuallTreeBuild(int height, MinNode* father_node) {
    if (height == 0) {
        MinNode* new_root = new MinNode;
        new_root->hight = 0;
        new_root->left = NULL;
        new_root->right = NULL;
        new_root->father = father_node;
        return new_root;
    }
    MinNode* new_root = new MinNode;
    new_root->hight = height;
    new_root->father = father_node;
    new_root->left = ActuallTreeBuild(height - 1, new_root);
    new_root->right = ActuallTreeBuild(height - 1, new_root);
    return new_root;

}

MinNode* Heap::BuildFullTree(int nodes_number) {
    if (nodes_number == 1) {
        MinNode* new_node = new MinNode;
        new_node->hight = 0;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->father = NULL;
        return new_node;
    }
    int actuall_nodes_number = 0;

    if (CheckPowerOfTwo(nodes_number + 1)) {
        actuall_nodes_number = nodes_number;
    } else {
        actuall_nodes_number = CalculateNodesNumber(nodes_number);
    }
    int tree_height = log2(actuall_nodes_number + 1) - 1;
    return ActuallTreeBuild(tree_height, NULL);
}
//Delete several nodes in order to get the required nodes number:
void Heap::ReBuildFullTree(MinNode* root, int nodes_to_delete) {
    if (nodes_to_delete <= 0) {
        return;
    }
    if (root == NULL) {
        return;
    }
    int num_del = nodes_to_delete;
    int* num_to_del = &num_del;
    ActuallReBuildFullTree(root, num_to_del);
}
//Actuall Delete several nodes in order to get the required nodes number:
void Heap::ActuallReBuildFullTree(MinNode* root, int* nodes_to_delete) {
    //  static int inner_nodes_to_delete=nodes_to_delete;
    if (root == NULL) {
        return;
    }
    if ((root->hight == 0) && (*nodes_to_delete > 0)) {
        //andrey:;
        delete (root);
        if ((root->father) && (root->father->right == root)) {
            root->father->right = NULL;
            if (!root->father->left) {
                root->father->hight -= 1;
            }
        } else if ((root->father) && (root->father->left == root)) {
            root->father->left = NULL;
            if (!root->father->right) {
                root->father->hight -= 1;
            }
        }
        *nodes_to_delete -= 1;
    }
    ActuallReBuildFullTree(root->right, nodes_to_delete);
    ActuallReBuildFullTree(root->left, nodes_to_delete);
}




MinNode* Heap::BuildExactTree(int final_nodes_number) {
    if (final_nodes_number == 0) {
        return NULL;
    }
    MinNode* new_tree;

     new_tree= BuildFullTree(final_nodes_number);

    int num_of_nodes = 0;
    numberNodes(new_tree, &num_of_nodes);

    ReBuildFullTree(new_tree,num_of_nodes - final_nodes_number);

    return new_tree;
}



void Heap::Postorder(MinNode* node,int* arr) {
    if (node == NULL)
        return;

    // first recur on left subtree
    Postorder(node->left);

    // then recur on right subtree
    Postorder(node->right);

    // now deal with the node
    std::cout << node->id << ",";

}

void Heap::inesrtToTree(int* arr,MinNode* node,int i){
    if(i<=size){
       node->id;
    }
}
