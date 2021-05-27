#pragma once
#include "evpp/tcp_client.h"
#include "evpp/ssl_tcp_client.h"
#include "evpp/event_loop.h"
#include "evpp/duration.h"
#include "evpp/event_watcher.h"
#include "evpp/event_loop_thread.h"
#include "evpp/event_loop_thread_pool.h"

using  namespace  std;
evpp::EventLoopThread* g_threadloop = nullptr;
evpp::EventLoopThreadPool* g_threadpool = nullptr;

std::unique_ptr<evpp::TimerEventWatcher> timer_;
void  OnConnectTimeout(void* data) {
    evpp::EventLoop* loop = (evpp::EventLoop*)data;
    int  a = 10;
    /*evpp::Duration timeout_(3.0);
    std::unique_ptr<evpp::TimerEventWatcher> timer_;
    timer_.reset(new evpp::TimerEventWatcher(g_threadloop->loop(), std::bind(&OnConnectTimeout), timeout_));
    timer_->Init();
    timer_->AsyncWait();
    g_threadloop->loop()->Run();*/

    evpp::Duration timeout_(5.0);

    timer_.reset(new evpp::TimerEventWatcher(loop, std::bind(&OnConnectTimeout, loop), timeout_));
    timer_->Init();
    timer_->AsyncWait();
}

void  testmain() {
    std::cout << "Hello World!\n";
    WSADATA wsaData;
    // Initialize Winsock 2.2
    int nError = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (nError) {
        std::cout << "WSAStartup() failed with error: %d" << nError;
    }

    //std::shared_ptr<evpp::EventLoop> pLoop(new evpp::EventLoop);
    //pLoop->Run();
    //evpp::EventLoop* loop = pLoop.get();

    g_threadloop = new evpp::EventLoopThread();
    g_threadloop->Start(true);

    evpp::EventLoop* loop = g_threadloop->loop();
    evpp::Duration timeout_(4.0);
    std::unique_ptr<evpp::TimerEventWatcher> timer_;
    timer_.reset(new evpp::TimerEventWatcher(loop, std::bind(&OnConnectTimeout, loop), timeout_));
    timer_->Init();
    timer_->AsyncWait();

    //loop->Run();
    //g_threadloop->Start();

    int  a = 10;
    printf("hello world\n");
    Sleep(30 * 1000);
    getchar();
    return 1;
}