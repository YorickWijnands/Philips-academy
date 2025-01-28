#ifndef MESSAGE_QUEUE_IMPLEMENTATION_HPP
#define MESSAGE_QUEUE_IMPLEMENTATION_HPP

#include "IMessageQueue.hpp"
#include "infra/util/BoundedVector.hpp"

class MessageQueue : public IMessageQueue
{
public:
    MessageQueue();

    void Enqueue(const Message& message) override;
    Message Dequeue() override;
    bool IsEmpty() const override;
    size_t Size() const override { return queue.size(); }

private:
    infra::BoundedVector<Message>::WithMaxSize<2000> queue;
};

#endif // MESSAGE_QUEUE_IMPLEMENTATION_HPP
