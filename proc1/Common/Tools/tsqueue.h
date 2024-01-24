#pragma once

#include <functional>
#include <mutex>
#include <list>


template <typename element_type,
          typename container_type = std::list<element_type>>
class tsqueue
{
public:
    using element_t = element_type;
    using queue_t = container_type;

public:
    void push(element_t elem) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.emplace_back(std::move(elem));
    }

    queue_t popall() {
        queue_t queue;
        std::unique_lock<std::mutex> lock(m_mutex);
        queue = std::move(m_queue);
        return queue;
    }

private:
    std::mutex      m_mutex;
    queue_t         m_queue;
};

using callable_t = std::function<void()>;
using callable_tsqueue = tsqueue<callable_t>;