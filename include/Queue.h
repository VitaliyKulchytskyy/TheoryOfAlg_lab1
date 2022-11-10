#ifndef LAB1_QUEUE_H
#define LAB1_QUEUE_H

template<class T>
class Queue final {
private:
    std::vector<T> queue;
public:
    Queue() = default;

    void add(T& value) {
        queue.push_back(value);
    }

    void add(T&& value) {
        queue.push_back(value);
    }

    void poll() {
        if(size() > 0)
            queue.erase(queue.begin());
    }

    [[nodiscard]]
    T front() const {
        if(!isEmpty())
            return queue[0];
    }

    bool isEmpty() const {
        return queue.empty();
    }

    std::size_t size() const {
        return queue.size();
    }
};

#endif //LAB1_QUEUE_H
