#include "a3_binary_search_tree.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

void printNode(BinarySearchTree::Node* node);
BinarySearchTree::Node* searchTree(BinarySearchTree::DataType val, BinarySearchTree::Node* node);
int maxDepth(BinarySearchTree::Node* node);
BinarySearchTree::Node* findparentMin(BinarySearchTree::Node* node);
BinarySearchTree::Node* findparentMax(BinarySearchTree::Node* node);
void printNode(BinarySearchTree::Node* node);
void convert(BinarySearchTree::Node* node, int a[], int start, int end);


BinarySearchTree::Node::Node(DataType newval){
    val = newval;
    left = NULL;
    right = NULL;
}

int BinarySearchTree::getNodeDepth(Node* n) const{
    Node* node = root_;
    int depth = 0;
    
    while (node != n) {
        if (n -> val > node -> val){
            node = node -> right;
            depth++;
        }
        else {
            node = node -> left;
            depth++;
        }
    }
    return depth;
}

BinarySearchTree::BinarySearchTree(){
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree(){
    
    if (root_ == NULL) {
        return;
    }
    
    Node** queue = new Node*[size_];
    
    int parent = 0;
    queue[parent] = root_;
    int next = 1;
    
    while (parent < size_ -1) {
        if (queue[parent] -> left != NULL) {
            queue[next] = queue[parent] -> left;
            next++;
        }
        if (queue[parent] -> right != NULL) {
            queue[next] = queue[parent] -> right;
            next++;
        }
        parent++;
    }
    delete [] queue;
    size_ = 0;
}

unsigned int BinarySearchTree::size() const{
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const{
    Node* node = root_;
    while (node -> right != NULL) {
        node = node -> right;
    }
    return node -> val;
}

BinarySearchTree::DataType BinarySearchTree::min() const{
    Node* node = root_;
    while (node -> left != NULL) {
        node = node -> left;
    }
    return node -> val;
}

unsigned int BinarySearchTree::depth() const{
    int depth = maxDepth(root_) - 1;
    
    return depth;
}

void BinarySearchTree::print() const{
  
    if (root_ == NULL) {
        cout << "Error: Tree is empty " << endl;
        return;
    }
    
    Node** queue = new Node*[size_];
    
    int parent = 0;
    queue[parent] = root_;
    int next = 1;
    
    while (parent < size_ -1) {
        if (queue[parent] -> left != NULL) {
            queue[next] = queue[parent] -> left;
            next++;
        }
        if (queue[parent] -> right != NULL) {
            queue[next] = queue[parent] -> right;
            next++;
        }
        parent++;
    }
    
    for (int i = 0; i < size_; i++) {
        cout << "[" << queue[i] -> val << "]";
    }

    queue = NULL;
    
    cout << endl << "End of tree " << endl;
    
    int* a = new int[size_];
    
    convert(root_, a, 0, size_ - 1);
    cout << "Printing array" << endl;
    
    for (int i = 0; i < size_; i++) {
        cout << "[" << a[i] << "]";
    }
}

bool BinarySearchTree::exists(DataType val) const{
    if (root_ == NULL) {
        cout << "Error: Tree is empty." << endl;
        return false;
    }
    else if (root_ -> val == val) {
        return true;
    }
    else if(searchTree(val, root_) != NULL){
        return true;
    }
    cout << "Error: value does not exist " << endl;
    return false;
}

bool BinarySearchTree::insert(DataType val){
    if (root_ == NULL) {
        root_ = new Node(val);
        size_++;
        return true;
    }
    
    Node* newNode = root_;
    bool add = false;
    while (!add) {
        if (val > newNode -> val) {
            if (newNode -> right == NULL) {
                newNode -> right = new Node(val);
                add = true;
            }
            else {
                newNode = newNode -> right;
            }
        }
        else {
            if (newNode -> left == NULL) {
                newNode -> left = new Node(val);
                add = true;
            }
            else {
                newNode = newNode -> left;
            }
        }
    }
    size_++;
    return true;
}

bool BinarySearchTree::remove(DataType val){
    
    if (root_ == NULL) {
        cout << "Error: Tree is empty." << endl;
        return false;
    }
    
    if (root_ -> val == val) {
        if (root_ -> right == NULL && root_ -> left == NULL) {
            delete root_;
            root_ = NULL;
            size_--;
            return true;
        }
        else if (root_ -> right != NULL && root_ -> left == NULL) {
            Node* temp = root_;
            root_ = root_ -> right;
            delete temp;
            size_--;
            return true;
        }
        else if (root_ -> right == NULL && root_ -> left != NULL){
            Node* temp = root_;
            root_ = root_ -> left;
            delete temp;
            size_--;
            return true;
        }
        else {
            if (root_ -> right -> left == NULL) {
                Node* temp = root_ -> right;
                root_ -> val = root_ -> right -> val;
                root_ -> right = root_ -> right -> right;
                delete temp;
                size_--;
                return true;
            }
            else {
                Node* minParent = findparentMin(root_ -> right);
                Node* min = minParent -> left;
                root_ -> val = min -> val;
                minParent -> left = min -> right;
                delete min;
                size_--;
                return true;
            }
        }
    }

    Node* node = searchTree(val, root_);
    
    if (node == NULL) {
        cout << "Error: Value doesn't exist" << endl;
        return false;
    }
        
    if (node -> left -> val == val) {
        Node* child = node -> left;
        if (child -> left == NULL && child -> right == NULL) {
            delete child;
            node -> left = NULL;
            size_--;
            return true;
        }
        else if (child -> left == NULL && child -> right != NULL){
            Node* tempnode = child;
            node -> left = child -> right;
            delete tempnode;
            size_--;
            return true;
        }
        else if (child -> left != NULL && child -> right == NULL){
            Node* tempnode = child;
            node -> left = child -> left;
            delete tempnode;
            size_--;
            return true;
        }
        else {
            Node* minParent;
            Node* min;
           if (child -> right -> left != NULL) {
               minParent = findparentMin(child -> right);
               min = minParent -> left;
               
               child -> val = min -> val;
               minParent -> left = min -> right;
           }
           else {
               min = child -> right;
               child -> val = min -> val;
               child -> right = min -> right;
           }
            
            delete min;
            size_--;
            return true;
        }
    }
    else {
        Node* child = node -> right;
        if (child -> left == NULL && child -> right == NULL) {
            delete child;
            node -> right = NULL;
            size_--;
            return true;
        }
        else if (child -> left == NULL && child -> right != NULL){
            Node* tempnode = child;
            node -> right = child -> right;
            delete tempnode;
            size_--;
            return true;
        }
        else if (child -> left != NULL && child -> right == NULL){
            Node* tempnode = child;
            node -> right = child -> left;
            delete tempnode;
            size_--;
            return true;
        }
        else {
            Node* minParent;
            Node* min;
            if (child -> right -> left != NULL) {
                minParent = findparentMin(child -> right);
                min = minParent -> left;
                
                child -> val = min -> val;
                minParent -> left = min -> right;
            }
            else {
                min = child -> right;
                child -> val = min -> val;
                child -> right = min -> right;
            }
            
            delete min;
            size_--;
            return true;
        }
    }
}

BinarySearchTree::Node* searchTree(BinarySearchTree::DataType val, BinarySearchTree::Node* node){
    if (val > node -> val) {
        if (node -> right == NULL) {
            return NULL;
        }
        else if (node -> right -> val == val) {
            return node;
        }
        else return searchTree(val, node -> right);
    }
    else if (val < node -> val){
        if (node -> left == NULL){
            return NULL;
        }
        else if (node -> left -> val == val){
            return node;
        }
        else return searchTree(val, node -> left);
    }
    else return NULL;
}

int maxDepth(BinarySearchTree::Node* node){
    if (node == NULL) {
        return 0;
    }
    else if (maxDepth(node -> left) > maxDepth(node -> right)) {
        return 1 + maxDepth(node -> left);
    }
    else return 1 + maxDepth(node -> right);
}

BinarySearchTree::Node* findparentMin(BinarySearchTree::Node* node){
    while (node -> left -> left != NULL) {
        node = node -> left;
    }
    return node;
}

BinarySearchTree::Node* findparentMax(BinarySearchTree::Node* node){
    while (node -> right -> right != NULL) {
        node = node -> right;
    }
    return node;
}

void printNode(BinarySearchTree::Node* node){
    if (node -> left != NULL) {
        printNode(node -> left);
    }
        cout << "[" << node -> val << "]";
    if (node -> right != NULL) {
        printNode(node -> right);
    }
}

void convert(BinarySearchTree::Node* node, int a[], int start, int end){
    if (end - start >= 0) {
        int mid = (start + end)/2;
        if (node -> right) {
            convert(node -> right, a, mid+1, end);
        }
        a[mid] = node -> val;
        if (node -> left) {
            convert(node -> left, a, start, mid - 1);
            
        }
    }
}

