#ifndef __TICK_THREAD_H__
#define __TICK_THREAD_H__

#include "xdebug.h"

#include <pthread.h>
#include <sys/epoll.h>
#include <queue>
#include <map>

#include "port.h"
#include "tick_item.h"
#include "status.h"
#include "csapp.h"


class TickItem;
class TickEpoll;
class TickConn;

class TickThread
{
public:
    TickThread();
    ~TickThread();

    void RunProcess();


    int notify_receive_fd() { return notify_receive_fd_; }
    int notify_send_fd() { return notify_send_fd_; }

    pthread_t thread_id_;

    // port::Mutex mutex() { return mutex_; }

private:

    friend class TickServer;

    /*
     * These two fd receive the notify from master thread
     */
    int notify_receive_fd_;
    int notify_send_fd_;

    /*
     * The TickItem queue is the fd queue, receive from master thread
     */
    std::queue<TickItem> conn_queue_;

    /*
     * The epoll handler
     */
    TickEpoll *tickEpoll_;

    std::map<int, TickConn *> conns_;


    port::Mutex mutex_;

    // No copy || assigned operator allowed
    TickThread(const TickThread&);
    void operator=(const TickThread &);
};

#endif
