//
// Created by amit on 06/06/18.
//

#ifndef HW2_DATA_STRUCURE_AVL_TREE_H
#define HW2_DATA_STRUCURE_AVL_TREE_H
//


#include <iostream>
#include <clocale>
#include <cmath>

template<typename D,typename K>
class Node {
    template<typename Data,typename Key> friend class Avl_tree;
private:
    D data;
    K key;
    Node<D,K> * left;
    Node<D,K> * right;
    int hight;
    int childs;
    int sum;
public:
    //Copy constructor:
    Node(D data,K key) {
        this->data = data;
        this->key=key;
        left = NULL;
        right = NULL;
        hight = 0;
        childs=1;
        sum=key;
    }
    //Constructor:
    Node() :
            data(NULL),key(NULL), left(NULL), right(NULL), hight(0),childs(1),sum(0){
    }
    //Copy constructor:
    Node(const Node<D,K>& nd) {
        data = nd.data;
        key=nd.key;
        left = nd.left;
        right = nd.right;
        hight = nd.hight;
        childs=nd.childs;
        sum=nd.sum;

    }
    //Assignment operator:
    Node & operator=(const Node & nd) {
        this->key=nd.key;
        this->data=nd.data;
        right = nd.right;
        hight = nd.hight;
        childs=nd.childs;
        sum=nd.sum;
        return *this;

    }
    D get_data(){ return data; }
    K get_key(){ return key; }
    int get_childs(){ return childs; }
    int get_sum(){ return sum; }

    //Destructor:
    ~Node() {
        //delete (data);
    }
};
/*----------------------------------------------------------------------------*/
//Generic Avl_tree Class:
template<typename Data,typename Key>
class Avl_tree {

private:

    Node<Data, Key> *root;

    //Is Contain

    //recursive inesrt
    Node<Data,Key>* Insertion(Node<Data,Key>* cur_root, Data data,Key key,Key sum);

    //hightCalcltion
    int hightCalc(Node<Data,Key>* node);

    //balance
    Node<Data,Key>* balance(Node<Data,Key>*cur_root);

    //factor
    int factor(Node<Data,Key>* node);

    //leftrotate
    Node<Data,Key>* leftRotate(Node<Data,Key> *node);

    //rightrotate
    Node<Data,Key>* rightRotate(Node<Data,Key> *node);

    Node<Data,Key>* Deletion(Node<Data,Key>* cur_root,Key key);

    //minLeftChild
    Node<Data,Key>* FindMinChild(Node<Data,Key>* root);

    //destroyTree
    void destroyTree(Node<Data,Key>* node);

    //helper function
    int getBalance(Node<Data,Key>* node);
    int checkHeight(Node<Data,Key> *node);
    int check_child(Node<Data,Key> *node);
    Key check_sum(Node<Data,Key> *node);
    int max(int a,int b);

        public:
    bool Is_Contain(Node<Data,Key>* root,Key key);

    //Constructor:
    Avl_tree() : root(NULL) {
    };

    //Destructor:
    ~Avl_tree() {destroyTree(root), root = NULL; }

    //inesrt
    Node<Data, Key>* InsertOasis(Data data ,Key key);
    Node<Data, Key>* Insert(Data data ,Key key);

    //inorder
    void inorder(Node<Data,Key>* node);

    //getroot
    Node<Data,Key>* getRoot(){ return root;}

    //Select
    Key selcet(int index,Node<Data,Key> *node,int sum);

    //rank
    Key rank(Key key,Node<Data,Key> *node,Key sum);

    //delete
    Node<Data,Key>* Delete(Key key);

};

/**
 * helper function for calc
 */
template<typename Data,typename Key>
int Avl_tree<Data, Key>::check_child(Node<Data,Key> *node){
    if(node ==  NULL) return 0;
    return node->get_childs();
}
template<typename Data,typename Key>
Key Avl_tree<Data, Key>::check_sum(Node<Data,Key> *node){
    if(node ==  NULL) return NULL;
    return node->get_sum();
}


/*----------------------------------------------------------------------------*/
/**
 * Inserts a new node with data to the tree.
 * parameters:
 * @param data - Is the data to insert to the tree.
 * @return
 * The updated tree root.
 * @reurn if is contain return NULL
 */
template<typename Data,typename Key>
Node<Data, Key>* Avl_tree<Data, Key>::InsertOasis(Data data ,Key key) {
    if (!root) {
        root = new Node<Data,Key>(data,key);
        return root;
    }
    if ((Is_Contain(root, key))) {
        return NULL;
    }
    return root = Insertion(root, data,key,key);

}
/*----------------------------------------------------------------------------*/
/**
 * Inserts a new node with data to the tree.
 * parameters:
 * @param data - Is the data to insert to the tree.
 * @return
 * The updated tree root.
 * @reurn if is contain return NULL
 */
template<typename Data,typename Key>
Node<Data, Key>* Avl_tree<Data, Key>::Insert(Data data ,Key key) {
    if (!root) {
        root = new Node<Data,Key>(data,key);
        return root;
    }
    return root = Insertion(root, data,key,key);

}
/*----------------------------------------------------------------------------*/
/**
 * Checks whether a node with the given data exists in the tree.
 * parameters:
 * @param root - Is the root of the tree.
 * @param data - Is the searched data.
 * @return
 * true- if exists in the tree.
 * false - otherwise.
 */
template<typename Data,typename Key>
bool Avl_tree<Data,Key>::Is_Contain(Node<Data,Key>* root,Key key) {
    if (!root)
        return false;
    if (key == root->key) {
        return true;
    } else if (key < root->key) {
        return Is_Contain(root->left, key);
    } else if (key > root->key) {
        return Is_Contain(root->right, key);
    } else {
        return false;
    }
}

/*----------------------------------------------------------------------------*/
/**
 * Inserts a new node with the the given data to the tree, a recursive function.
 * parameters:
 * @param cur_root - Is the current root of the tree.
 * @param data - Is the requested data.
 * @return
 * The updated tree node.
 */
template<typename Data,typename Key>
Node<Data,Key>* Avl_tree<Data,Key>::Insertion(Node<Data,Key>* cur_root, Data data,Key key,Key sum) {
    if (!cur_root) {
        cur_root = new Node<Data,Key>(data,key);
        return cur_root;
    }

    if (cur_root->key > key && (cur_root->left == NULL)) {
        cur_root->childs+=1;
        cur_root->sum+=key;
        cur_root->left = new Node<Data,Key>(data,key);
        cur_root->hight = hightCalc(cur_root);
        return cur_root;
    }
    if (key > cur_root->key  && (cur_root->right == NULL)) {
        cur_root->childs+=1;
        cur_root->sum+=key;
        cur_root->right = new Node<Data,Key>(data,key);
        cur_root->hight = hightCalc(cur_root);
        return cur_root;

    }

    if (key < cur_root->key) {
        cur_root->childs+=1;
        cur_root->sum+=key;
        cur_root->left = Insertion(cur_root->left, data,key,sum);
    } else if (key > cur_root->key) {
        cur_root->childs+=1;
        cur_root->sum+=key;
        cur_root->right = Insertion(cur_root->right,data,key,sum);
    } else {
        if (data>cur_root->data){
            cur_root->childs+=1;
            cur_root->sum+=key;
            cur_root->right = Insertion(cur_root->right,data,key,sum);
        } else if (data<cur_root->data){
            cur_root->childs+=1;
            cur_root->sum+=key;
            cur_root->left = Insertion(cur_root->left, data,key,sum);
        } else {
            return cur_root;
        }
    }

    cur_root->hight = hightCalc(cur_root);
    return balance(cur_root);
}
/*----------------------------------------------------------------------------*/
/**
 * Returns the height of a tree.
 * parameters:
 * @param node - Is the root of the tree.
 * @return
 * The height of the tree.
 */
template<typename Data,typename Key>
int Avl_tree<Data,Key>::hightCalc(Node<Data,Key>* node) {
    if (!node)
        return 0;
    if (!(node->right) && !(node->left)) {
        return 0;
    } else if (!node->right) {
        return node->left->hight + 1;
    } else if (!node->left) {
        return node->right->hight + 1;
    } else {
        int lhight = node->left->hight;
        int rhight = node->right->hight;
        int num = lhight >= rhight ? lhight : rhight;
        return num + 1;

    }
}
/*----------------------------------------------------------------------------*/
/**
 * Balances the AVL tree after an action.
 * parameters:
 * @param cur_root - Is the root of the tree.
 * @return
 * The updated tree root.
 */
template<typename Data,typename Key>
Node<Data,Key>* Avl_tree<Data,Key>::balance(Node<Data,Key>*cur_root) {
    int balance = factor(cur_root);
    int blance_right = factor(cur_root->right);
    int blance_left = factor(cur_root->left);

    if (balance < -1 && blance_right <= 0)
        return leftRotate(cur_root);

    if (balance > 1 && blance_left >= 0)
        return rightRotate(cur_root);

    if (balance > 1 && blance_left == -1) {
        cur_root->left = leftRotate(cur_root->left);
        return rightRotate(cur_root);
    }

    if (balance < -1 && blance_right == 1) {
        cur_root->right = rightRotate(cur_root->right);
        return leftRotate(cur_root);
    }
    return cur_root;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * Returns the avl node factor.
 * parameters:
 * @param node - Is the node which the factor is calculated to.
 * @return
 * The factor of the node.
 */
template<typename Data,typename Key>
int Avl_tree<Data,Key>::factor(Node<Data,Key>* node) {
    if (!node)
        return 0;
    if (!(node->right) && !(node->left)) {
        return 0;
    } else if (!node->right) {
        return node->left->hight + 1;
    } else if (!node->left) {
        return (0 - node->right->hight) - 1;
    } else {
        int lhight = node->left->hight;
        int rhight = node->right->hight;
        return lhight - rhight;
    }
}

/*----------------------------------------------------------------------------*/
/**
 * Rotate right the AVL tree.
 * parameters:
 * @param node - Is the current node from where to rotate.
 * @return
 * The updated tree node.
 */
template<typename Data,typename Key>
Node<Data,Key>* Avl_tree<Data,Key>::rightRotate(Node<Data,Key> *node) {
    Node<Data,Key>* temp = node->left;
    Node<Data,Key>* temp1_tree = temp->right;

    temp->right = node;
    node->left = temp1_tree;
    if(node->right) {
        temp->childs += node->right->childs + 1;
        temp->sum+=node->right->sum+node->key;
        if(temp1_tree) {
            node->childs = node->right->childs + temp1_tree->childs+1;
            node->sum = node->right->sum + node->key + temp1_tree->sum;
        }
        else{
            node->childs = node->right->childs+1;
            node->sum = node->right->sum + node->key;
        }
    }

    else{
        temp->sum+=node->key;
        temp->childs+=1;
        node->sum=node->key;
        node->childs=1;
    }
    node->hight = hightCalc(node);
    temp->hight = hightCalc(temp);

    return temp;
}
/*----------------------------------------------------------------------------*/
/**
 * Rotate left the AVL tree.
 * parameters:
 * @param node - Is the current node from where to rotate.
 * @return
 * The updated tree node.
 */
template<typename Data,typename Key>
Node<Data,Key> *Avl_tree<Data,Key>::leftRotate(Node<Data,Key> *node) {
    Node<Data,Key> *temp = node->right;
    Node<Data,Key> *big_tree = temp->left;

    temp->left = node;
    node->right = big_tree;
    if(node->left) {
        temp->childs += node->left->childs + 1;
        temp->sum+=node->left->sum+node->key;
        if(big_tree) {
            node->childs = node->left->childs + big_tree->childs+1;
            node->sum = node->left->sum + node->key + big_tree->sum;
        }
        else{
            node->childs = node->left->childs+1;
            node->sum = node->left->sum + node->key;
        }

    }
    else{
        temp->sum+=node->key;
        temp->childs+=1;
        node->sum=node->key;
        node->childs=1;
    }
    node->hight = hightCalc(node);
    temp->hight = hightCalc(temp);

    return temp;
}
/*----------------------------------------------------------------------------*/
/**
 * Do an Inorder search in the avl tree.
 * parameters:
 * @param node - Is the current node from where to search.
 */
template<typename Data,typename Key>
void Avl_tree<Data,Key>::inorder(Node<Data,Key>* node) {
    if (node == NULL)
        return;
    inorder(node->left);
    std::cout << "The Node:"<<std::endl;
    std::cout << "The Data --"<<node->get_data()<<std::endl;
    std::cout << "The Key --"<<node->get_key()<<std::endl;
    std::cout << "The childs --"<<node->get_childs()<<std::endl;
    std::cout << " the sum of all bigger----"<<node->get_sum()<<std::endl;
    std::cout << "--------------------"<<std::endl;

    inorder(node->right);
}


/*----------------------------------------------------------------------------*/
/**
 * Deletes a node in the tree which contains the data.
 * parameters:
 * @param data - Is the data to delete from the tree.
 * @return
 * The updated tree root.
 */
template<typename Data,typename Key>
Node<Data,Key>* Avl_tree<Data,Key>::Delete(Key key) {
    if (!this->root)
        return NULL;
    if ((!root->left) && (!root->right) && key == root->key) {
        delete (root);
        root = NULL;
        return root;
    }

    return root = Deletion(root, key);
}
/*----------------------------------------------------------------------------*/
/**
 * Finds the child to replace the deleted node from the tree.
 * parameters:
 * @param root - Is the root of the tree.
 * @return
 * The updated tree root.
 */
template<typename Data,typename Key>
Node<Data,Key>* Avl_tree<Data,Key>::FindMinChild(Node<Data,Key>* root) {
    if (root->left == NULL)
        return root;
    return FindMinChild(root->left);
}
/*----------------------------------------------------------------------------*/

template<typename Data,typename Key>
int Avl_tree<Data,Key>::getBalance(Node<Data,Key>* node)
{
    if (node == NULL)
        return 0;
    return checkHeight(node->left) - checkHeight(node->right);
}
/*----------------------------------------------------------------------------*/
template<typename Data,typename Key>
int Avl_tree<Data,Key>::checkHeight(Node<Data,Key>* node)
{
    if (node == NULL)
        return 0;
    return node->hight;
}
/*----------------------------------------------------------------------------*/
template<typename Data,typename Key>
int Avl_tree<Data,Key>::max(int a,int b) {
	return (a > b) ? a : b;
}

/*----------------------------------------------------------------------------*/
/**
 * Deletes a node in the tree starts in current_root, a recursive function.
 * parameters:
 * @param current_root - Is the root of the tree.
 * @param data - Is the data to delete from the tree.
 * @return
 * The updated tree root.
 */
template<typename Data,typename Key>
Node<Data,Key>* Avl_tree<Data,Key>::Deletion(Node<Data,Key>* current_root, Key key) {

    if (current_root == NULL)
        return current_root;


    if ( key < current_root->key )
        current_root->left = Deletion(current_root->left, key);

    else if( key > current_root->key )
        current_root->right = Deletion(current_root->right, key);


    else
    {
        if( (current_root->left == NULL) || (current_root->right == NULL) )
        {
            Node<Data,Key>*temp = current_root->left ? current_root->left :
                                  current_root->right;

            if (temp == NULL)
            {
                temp = current_root;
                current_root = NULL;
            }
            else
                *current_root = *temp;
            delete(temp);
        }
        else
        {

            Node<Data,Key>* temp = FindMinChild(current_root->right);
            current_root->key = temp->key;
            current_root->right = Deletion(current_root->right, temp->key);
        }
    }

    if (current_root == NULL)
        return current_root;

    current_root->hight = 1 + max(checkHeight(current_root->left),
                                  checkHeight(current_root->right));

    int balance = getBalance(current_root);


    if (balance > 1 && getBalance(current_root->left) >= 0)
        return rightRotate(current_root);

    if (balance > 1 && getBalance(current_root->left) < 0)
    {
        current_root->left =  leftRotate(current_root->left);
        return rightRotate(current_root);
    }

    if (balance < -1 && getBalance(current_root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(current_root->right) > 0)
    {
        current_root->right = rightRotate(current_root->right);
        return leftRotate(current_root);
    }

    return current_root;
}
/*----------------------------------------------------------------------------*/
/**
 * Destroys a Tree, this is the actual function.
 * parameters:
 * @param node - Is the root of the tree.
 */
template<typename Data,typename Key>
void Avl_tree<Data,Key>::destroyTree(Node<Data,Key>* node)
{
    if (node != NULL) {
        if (node->left) {
            destroyTree(node->left);
        }
        if (node->right) {
            destroyTree(node->right);
        }
        delete node;
    }
}
template<typename Data,typename Key>


/*----------------------------------------------------------------------------*/

/**
 * Select - give from the tree the data that is in  the index of sorted array .
 * parameters:
 * @param node - Index.
 * @return faulire NULL
 */
Key Avl_tree<Data,Key>:: selcet(int index,Node<Data,Key>* node,int sum) {
    if (!node) return NULL;
    if(index <=0||index>node->childs) return NULL;
    int calc = check_child(node->left);
    if (calc == index-1 ) {
        return sum+check_sum(node->right)+node->key;
    }
    else if (calc  < index-1) {
        index = index-calc - 1;
        return    selcet(index, node->right,sum);
    }
    else {
        //index = index - 1;
        sum+=check_sum(node->right)+node->key;
        return    selcet(index, node->left,sum);
    }
}
/*----------------------------------------------------------------------------*/

/**
 * Rank - give from the tree the data that is in  the index of sorted array .
 * parameters:
 * @param node - Index.
 * @return faulire NULL
 */
template<typename Data,typename Key>
Key Avl_tree<Data,Key>::rank(Key key,Node<Data,Key>* node,Key sum){
    if(!node) return NULL;
    if( key > node->key){
        return rank(key,node->right,sum);
    }
    else if ( key < node->key){
        sum+=check_sum(node->right)+node->key;
        return rank(key,node->left,sum);
    }
    else{
        return sum+check_sum(node->right)+node->key;
    }
}








#endif //HW2_DATA_STRUCURE_AVL_TREE_H