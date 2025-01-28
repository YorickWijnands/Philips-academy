#ifndef I_MESSAGE_QUEUE_HPP
#define I_MESSAGE_QUEUE_HPP

#include "Message.hpp"
#include <cstddef>

class IMessageQueue
{
public:
    virtual ~IMessageQueue() = default;

    virtual void Enqueue(const Message& message) = 0;
    virtual Message Dequeue() = 0;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;
};

#endif // I_MESSAGE_QUEUE_HPP
