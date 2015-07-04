#ifndef A3_TESTS_HPP
#define A3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include "a3_priority_queue.hpp"
#include "a3_binary_search_tree.hpp"

// Libraries needed for BinarySearchTreeTest
#include <sstream>
#include <queue>
#include <iostream>
#include <cstdlib>

class PriorityQueueTest
{
public:
    bool test1()
    {
        PriorityQueue q(16);
        ASSERT_TRUE( q.empty() );
        ASSERT_TRUE( !q.full() );
        ASSERT_TRUE( q.size() == 0 );
        return true;
    }
    
    bool test2()
    {
        PriorityQueue q(2);
        ASSERT_TRUE( q.enqueue(10) );
        ASSERT_TRUE( !q.empty() );
        ASSERT_TRUE( !q.full() );
        ASSERT_TRUE( q.size() == 1 );
        ASSERT_TRUE( q.max() == 10 );
        
        ASSERT_TRUE( q.dequeue() );
        ASSERT_TRUE( q.empty() );
        ASSERT_TRUE( !q.full() );
        ASSERT_TRUE( q.size() == 0 );
        return true;
    }
    
    bool test3()
    {
        PriorityQueue q(3);
        ASSERT_TRUE( q.enqueue(5) );
        ASSERT_TRUE( q.max() == 5 );
        ASSERT_TRUE( q.enqueue(3) );
        ASSERT_TRUE( q.max() == 5 );
        ASSERT_TRUE( q.enqueue(4) );
        ASSERT_TRUE( q.max() == 5 );
        ASSERT_TRUE( q.full() );
        
        ASSERT_TRUE( !q.enqueue(7) );
        ASSERT_TRUE( q.max() == 5 );
        ASSERT_TRUE( q.full() );
        return true;
    }
    
    bool test4()
    {
        PriorityQueue q(16);
        ASSERT_TRUE( q.enqueue(7));
        q.print();
        ASSERT_TRUE(q.max() == 7);
        ASSERT_TRUE(q.enqueue(8));
        ASSERT_TRUE(q.enqueue(9));
        ASSERT_TRUE(q.enqueue(4));
        ASSERT_TRUE(q.enqueue(5));
        ASSERT_TRUE(q.enqueue(20));
        ASSERT_TRUE(q.max() == 20);
        ASSERT_TRUE(!q.full());
        ASSERT_TRUE(q.enqueue(3));
        ASSERT_TRUE(q.enqueue(2));
        ASSERT_TRUE(q.enqueue(1));
        ASSERT_TRUE(q.enqueue(6));
        ASSERT_TRUE(q.enqueue(12));
        ASSERT_TRUE(q.enqueue(11));
        ASSERT_TRUE(q.enqueue(14));
        ASSERT_TRUE(q.enqueue(13));
        ASSERT_TRUE(q.enqueue(28));
        ASSERT_TRUE(q.enqueue(10));
        ASSERT_TRUE(q.max() == 28);
        ASSERT_TRUE(q.full());
        ASSERT_TRUE(q.size() == 16);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 20);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 14);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 13);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 12);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 11);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 10);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 9);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 8);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 7);
        ASSERT_TRUE(q.size() == 7);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 6);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 5);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 4);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 3);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 2);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.max() == 1);
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.empty());
        ASSERT_TRUE(!q.dequeue());
        return true;    }
};

class BinarySearchTreeTest
{
private:
    // Traverse the tree in level-order so we can check if it was constructed
    // properly. Output is as follows:
    //   "val1 val2 ... valN"
    // where vali is the value of node i, using level-order traversal.
    std::string level_order(BinarySearchTree::Node* root)
    {
        // If no nodes, return an empty string.
        if (root == NULL) {
            return "";
        }
        
        std::stringstream ss;
        std::queue<BinarySearchTree::Node*> node_queue;
        node_queue.push(root);
        while (!node_queue.empty()) {
            BinarySearchTree::Node* cur_node = node_queue.front();
            node_queue.pop();
            ss << cur_node->val << " ";
            if (cur_node->left != NULL) {
                node_queue.push(cur_node->left);
            }
            if (cur_node->right != NULL) {
                node_queue.push(cur_node->right);
            }
        }
        
        std::string level_order_str = ss.str();
        // There is a trailing space at the end of the string; return everything
        // before this.
        return level_order_str.substr(0, level_order_str.size() - 1);
    }
    
public:
    bool test1()
    {
        // We expect an empty tree at construction.
        std::string expected_tree_level_order = "";
        
        BinarySearchTree bst;
                ASSERT_TRUE(bst.root_ == NULL);
        ASSERT_TRUE(bst.size_ == 0 && bst.size() == 0);
        
        std::string tree_level_order = level_order(bst.root_);
        // Compare the tree's representation to the expected tree.
        ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
        return true;
    }
    
    bool test2()
    {
        // We expect a single root node with value "5" after everything.
        std::string expected_tree_level_order = "5";
        
        BinarySearchTree bst;
        ASSERT_TRUE(bst.insert(5));
        ASSERT_TRUE(!bst.remove(4));
        ASSERT_TRUE(bst.exists(5));
        ASSERT_TRUE(bst.max() == bst.min() && bst.max() == 5);
        ASSERT_TRUE(bst.size() == 1);
        bst.print();
        
        std::string tree_level_order = level_order(bst.root_);
        // Compare the tree's representation to the expected tree.
        ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
        return true;
    }
    
    bool test3()
    {
        // We expect a 2-node tree at the end of this function -- root node 10 and
        // a child node with value 6.
        std::string expected_tree_level_order = "10 6";
        
        BinarySearchTree bst;
        ASSERT_TRUE(bst.insert(10));
        ASSERT_TRUE(bst.insert(8));
        ASSERT_TRUE(bst.size() == 2);
        ASSERT_TRUE(bst.insert(6));
        ASSERT_TRUE(bst.size() == 3);
        
        ASSERT_TRUE(bst.remove(8));
        ASSERT_TRUE(bst.size() == 2);
        
        std::string tree_level_order = level_order(bst.root_);
        // Compare the tree's representation to the expected tree.
        ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
        return true;
    }
    
    bool test4()
    {
        std::string expected_tree_level_order = "7 1 9 8";

        BinarySearchTree bst;
        
        ASSERT_TRUE(bst.insert(10));
        ASSERT_TRUE(bst.insert(6));
        
        ASSERT_TRUE(bst.insert(20));
        bst.print();
        ASSERT_TRUE(bst.depth() == 1);
        
        ASSERT_TRUE(bst.insert(30));
        bst.print();
        
        ASSERT_TRUE(bst.depth() == 2);
        
        ASSERT_TRUE(bst.insert(25));
        bst.print();
        
        ASSERT_TRUE(bst.depth() == 3);
        
        ASSERT_TRUE(bst.insert(5));
        bst.print();
        ASSERT_TRUE(bst.depth() == 3);
        
        ASSERT_TRUE(bst.insert(1));
        bst.print();
        ASSERT_TRUE(bst.depth() == 3);
        
        ASSERT_TRUE(bst.insert(7));
        bst.print();
        ASSERT_TRUE(bst.depth() == 3);
        
        ASSERT_TRUE(bst.insert(9));
        bst.print();
        ASSERT_TRUE(bst.depth() == 3);
        
        ASSERT_TRUE(bst.insert(8));
        bst.print();
        ASSERT_TRUE(bst.depth() == 4);
        
        ASSERT_TRUE(bst.size() == 10);
        
        ASSERT_TRUE(bst.remove(5));
        bst.print();
        
        ASSERT_TRUE(bst.remove(20))
        bst.print();
        ASSERT_TRUE(bst.remove(30));
        bst.print();
        ASSERT_TRUE(bst.remove(25));
        bst.print();
        
        ASSERT_TRUE(bst.remove(6));
        bst.print();
        
        ASSERT_TRUE(bst.min() == 1);

        ASSERT_TRUE(bst.remove(10));
        bst.print();
        ASSERT_TRUE(bst.max() == 9);
        
        ASSERT_TRUE(bst.size() == 4);
        std::string tree_level_order = level_order(bst.root_);
        
        // Compare the tree's representation to the expected tree.
        ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
        return true;
    }
};
#endif

