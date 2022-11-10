#ifndef LAB1_TEST_CPP
#define LAB1_TEST_CPP

#include "MyTest.h"
#include "Queue.h"

namespace {
    bool queueTestCheckSize_ofThreeElements() {
        Queue<uint16_t> q;

        q.add(1);
        q.add(4);
        uint16_t b = 3;
        q.add(b);

        return ASSUME_EQ<uint16_t>("queueTestCheckSize_ofThreeElements", q.size(), 3);
    }

    bool queueTestOverPoll() {
        Queue<uint16_t> q;

        q.add(1);
        q.add(4);
        q.poll();
        q.poll();
        q.poll();
        q.poll();
        q.poll();
        q.poll();

        return ASSUME_EQ<uint16_t>("queueTestOverPoll", q.size(), 0);
    }

    bool queueTestFront() {
        Queue<uint16_t> q;

        q.add(5);
        q.add(4);
        q.poll();
        q.add(99);
        q.add(4);
        q.add(8);
        q.poll();
        q.add(63);

        return ASSUME_EQ<uint16_t>("queueTestFront", q.front(), 99);
    }

    bool emptyQueueCheckIsEmpty() {
        Queue<uint16_t> q;
        return ASSUME_EQ<uint16_t>("emptyQueueCheckIsEmpty", q.isEmpty(), true);
    }

    bool notEmptyQueueCheckIsEmpty() {
        Queue<uint16_t> q;
        q.add(6);
        return ASSUME_EQ<uint16_t>("notEmptyQueueCheckIsEmpty", q.isEmpty(), false);
    }
}

namespace Test {
    void doTest() {
        const bool tests[] {
                queueTestCheckSize_ofThreeElements(),
                queueTestOverPoll(),
                queueTestFront(),
                emptyQueueCheckIsEmpty(),
                notEmptyQueueCheckIsEmpty()
        };
    }
}

#endif //LAB1_TEST_CPP
