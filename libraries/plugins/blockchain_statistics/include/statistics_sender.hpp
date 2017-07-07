#pragma once

// Libcds initialize and terminate
#include <cds/init.h>
// Libcds implementation of FCQueue
#include <cds/container/fcqueue.h>
#include <cds/threading/model.h>
#include <thread>
#include <atomic>

#include <steemit/chain/steem_object_types.hpp>

#include <fc/api.hpp>
#include <fc/uint128.hpp>
using namespace steemit::chain;

class stat_client {

private:
    std::atomic_bool QUEUE_ENABLED;
    // The thread which contains data sending loop
    std::thread sender_thread;
    // Lock-free FCQueue (not intrusive)
    cds::container::FCQueue<std::string, std::queue<std::string>, cds::container::fcqueue::traits> stat_q;
    // Vector of ip addersses where data will be send
    std::vector<std::string> recipient_ip_vec;
    // Port for asio broadcasting 
    int port;
    // Timeout in seconds
    int sender_sleeping_time;

    void init(int port, int timeout);

public:
    // adds address to _recipient_ip_vec.
    void add_address(const std::string & address);
    stat_client();
    ~stat_client();
    // terminates sending loop
    void stop();
    // pushes a string to the stat_q
    void push(const std::string & item);
    // initializing and runs data sending loop in a new thread
    void start(int br_port, int timeout);
};
