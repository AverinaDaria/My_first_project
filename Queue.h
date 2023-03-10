#include <cstdlib>
using namespace std;

class Queue {
private:
    static const size_t DEFAULT_CAPACITY = 10;

    int *array;
    size_t head, tail;
    size_t length, capacity;

    void ensureCapacity();
public:
    void put(int element);
    int pop();
    int wait_and_pop();

    size_t size();

    explicit Queue(size_t capacity);
    explicit Queue();

    ~Queue();
};
