#include "MessageQueue.hpp"

MessageQueue::MessageQueue()
    : queue()
{
}

void MessageQueue::Enqueue(const Message& message)
{
    if (queue.size() < queue.max_size())
        queue.push_back(message);
}

Message MessageQueue::Dequeue()
{
    if (IsEmpty()) 
        return Message(0, 0, uint8_t{0});

    Message message = queue.front();
    queue.erase(queue.begin());
    return message;
}

bool MessageQueue::IsEmpty() const
{
    return queue.empty();
}
