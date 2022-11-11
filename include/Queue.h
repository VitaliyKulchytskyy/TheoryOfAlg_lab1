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

    void add(const T& value) {
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

    [[nodiscard]]
    T front() const {
        if(!isEmpty())
            return head->value;
    }

    bool isEmpty() const {
        return m_iSize == 0;
    }

    void poll() {
        if(m_iSize != 0) {
            Node *pollNode = head;
            head = pollNode->next;
            delete pollNode;
            m_iSize--;
        }
    }

    std::size_t size() const {
        return m_iSize;
    }
};

#endif //LAB1_QUEUE_H
