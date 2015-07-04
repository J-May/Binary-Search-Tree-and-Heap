#include <iostream>
#include <string>
using namespace std;

#include "a3_tests.hpp"

string get_status_str(bool status)
{
    return status ? "Pass" : "Fail";
}

int main()
{
    PriorityQueueTest pqueue_test;
    BinarySearchTreeTest btree_test;

    bool pqueue_test1_passed = pqueue_test.test1();
    bool pqueue_test2_passed = pqueue_test.test2();
    bool pqueue_test3_passed = pqueue_test.test3();
    bool pqueue_test4_passed = pqueue_test.test4();

    bool btree_test1_passed = btree_test.test1();
    bool btree_test2_passed = btree_test.test2();
    bool btree_test3_passed = btree_test.test3();
    bool btree_test4_passed = btree_test.test4();

    cout << "---Priority Queue Tests---" << endl;
    cout << "Test1: " << get_status_str(pqueue_test1_passed) << endl;
    cout << "Test2: " << get_status_str(pqueue_test2_passed) << endl;
    cout << "Test3: " << get_status_str(pqueue_test3_passed) << endl;
    cout << "Test4: " << get_status_str(pqueue_test4_passed) << endl;
    cout << endl;
    
    cout << "---Binary Search Tree Tests---" << endl;
    cout << "Test1: " << get_status_str(btree_test1_passed) << endl;
    cout << "Test2: " << get_status_str(btree_test2_passed) << endl;
    cout << "Test3: " << get_status_str(btree_test3_passed) << endl;
    cout << "Test4: " << get_status_str(btree_test4_passed) << endl;

    return 0;
}
