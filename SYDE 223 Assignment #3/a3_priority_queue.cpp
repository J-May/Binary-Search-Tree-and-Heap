#include "a3_priority_queue.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

PriorityQueue::PriorityQueue(unsigned int capacity){
    capacity_ = capacity;
    heap_ = new DataType[capacity + 1];
    size_ = 0;
}

PriorityQueue::~PriorityQueue(){
    delete [] heap_;
    heap_ = NULL;
}
    
unsigned int PriorityQueue::size() const{
    return size_;
}

bool PriorityQueue::empty() const{
    return size_ == 0;
}

bool PriorityQueue::full() const{
    return size_ == capacity_;
}

void PriorityQueue::print() const{
    if (!empty()) {
        cout << "(";
        for (int i = 1; i <= size_; i++) {
            cout << "[" << heap_[i] << "]";
            if (i < size_) {
                cout << "->";
            }
        }
        cout << ")";
    }
}

PriorityQueue::DataType PriorityQueue::max() const{
    return heap_[1];
}

bool PriorityQueue::enqueue(DataType val){
    if (full()) {
        cout << "Error: Heap is full" << endl;
        return false;
    }
    else{
        size_++;
        heap_[size_] = val;
        
        DataType tempnode;
        int index = size_;
        
        while(heap_[index/2] < heap_[index] && index > 1) {
            tempnode = heap_[index];
            heap_[index] = heap_[index/2];
            heap_[index/2] = tempnode;
            index = index/2;
        }
        return true;
    }
}

bool PriorityQueue::dequeue(){
    if (empty()) {
        cout << "Error: Heap is empty" << endl;
        return false;
    }
    else{
        heap_[1] = heap_[size_];
        heap_[size_] = 0;
        size_--;
        
        DataType tempnode;
        int index = 1;
        bool less = true;
        
        while (index*2 <= size_ && less == true) {
            if (heap_[index] < heap_[2*index] && heap_[2*index] > heap_[2*index + 1]) {
                    tempnode = heap_[index];
                    heap_[index] = heap_[2*index];
                    heap_[2*index] = tempnode;
                    index = 2*index;
            }
            else if (heap_[index] < heap_[2*index + 1]){
                    tempnode = heap_[index];
                    heap_[index] = heap_[2*index + 1];
                    heap_[2*index + 1] = tempnode;
                    index = 2*index + 1;
                }
            else less = false;
            }
        
        return true;
    }
}

