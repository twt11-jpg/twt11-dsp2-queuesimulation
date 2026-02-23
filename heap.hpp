/***************************************************************
  Student Name: Wanda Tran
  File Name: heap.hpp
  Assignment number 2

  Declares class Heap and implements heap-based priority queue.
***************************************************************/

#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include "Event.h"
#include <algorithm>

class Heap {
    private:
        std::vector<Event> heap;

        void heapUp(int index) {           //compare new element w/ parent
            while (index > 0) {
                int parent = (index - 1) / 2;
                if(heap[index].time >= heap[parent].time) break;
                std::swap(heap[index], heap[parent]);           //swap if child's time is earlier than parent
                index = parent;
            }
        }

        void heapDown(int index) {     //have the smallest time be the root
            int left, right, smallest;

            while (true) {
                left = 2 * index + 1;
                right = 2 * index + 2;
                smallest = index;

                if(left < heap.size() && heap[left].time < heap[smallest].time) {
                    smallest = left;
                }

                if(right < heap.size() && heap[right].time < heap[smallest].time) {
                    smallest = right;
                }

                if(smallest == index) break;

                std::swap(heap[index], heap[smallest]);
                index = smallest;
            }
        }
    
    public:
         void insert(const Event&eventType) {      // add new event (end of vec)
            heap.push_back(eventType);
            heapUp(heap.size() - 1);       //move to correct
         }

         Event extractMin() {
            if(heap.empty()) {
                return Event(-1, Arrival);
            }
                
            Event minEvent = heap[0];
            heap[0] = heap.back();      //move last ele to root
            heap.pop_back();
            if(!heap.empty()) heapDown(0);      //restore
            return minEvent;        //return earliest event/time
        }

        int size() {
            return heap.size();
        }
};

#endif  // HEAP_HPP