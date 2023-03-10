#include "Queue.h"
using namespace std;

void Queue::ensureCapacity() {
  if (size() == capacity) {
    int *newArray = (int*) malloc((capacity << 1) * sizeof(int));
    for (int i = 0; i < capacity; i++) {
      newArray[i] = array[head++ % capacity];
    }
    head = 0;
    tail = capacity;
    free(array);
    capacity <<= 1;
    array = newArray;
  }
}

Queue::Queue(size_t capacity) {
  this->capacity = capacity;
  array = (int*) malloc(this->capacity * sizeof(int));
}

Queue::Queue() {
  this->capacity = DEFAULT_CAPACITY;
  array = (int*) malloc(capacity * sizeof(int));
}

Queue::~Queue() {
  free(array);
}

void Queue::put(int element) {
  ensureCapacity();
  array[tail++ % capacity] = element;
  ++length;
}

int Queue::pop() {
  --length;
  int result = array[head % capacity];
  head = (head + 1) % capacity;
  return result;
}

size_t Queue::size() {
  return length;
}

int Queue::wait_and_pop() {
  while (size() == 0) {
  }
  return pop();
}