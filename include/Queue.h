#ifndef LAB1_QUEUE_H
#define LAB1_QUEUE_H

template<class T>
class Queue final {
private:
    struct Node {
        T value = T();
        Node* next = nullptr;
    };
private:
    Node *curr = nullptr;
    Node *head = nullptr;
    size_t m_iSize = 0;
public:
    Queue() = default;

    [[nodiscard]]
    T front() const;
    void add(const T& value);
    bool isEmpty() const;
    void poll();
    std::size_t size() const;
};

template<class T>
T Queue<T>::front() const {
    if(!isEmpty())
        return head->value;
}

template<class T>
void Queue<T>::add(const T& value) {
    Node *addNode = new Node;
    addNode->value = value;
    addNode->next = nullptr;

    if(head == nullptr)
        head = addNode;
    else
        curr->next = addNode;

    curr = addNode;
    m_iSize++;
}

template<class T>
bool Queue<T>::isEmpty() const {
    return m_iSize == 0;
}

template<class T>
void Queue<T>::poll() {
    if(m_iSize != 0) {
        Node *pollNode = head;
        head = pollNode->next;
        delete pollNode;
        m_iSize--;
    }
}

template<class T>
std::size_t Queue<T>::size() const {
    return m_iSize;
}

#endif //LAB1_QUEUE_H
