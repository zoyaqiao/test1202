/**
 * @file threadPool-demo.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-08
 * 
 * c++11中的std::future是一个模板类
 * std::future提供了一种用于访问异步操作结果的机制
 * std::future所引用的共享状态不能与其他异步返回的对象共享
 * （与std::shared_future相反）
 * 一个future是一个对象，它可以从某个提供者的对象或函数中检索值
 * 如果在不同的线程中，用它可以正确地同步此访问
 * 
 */
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include <atomic>
#include <iostream>
#include <time.h>

using namespace std;
class ThreadPool {
public:
    ThreadPool(size_t);
    // 返回一个基于F的函数函数对象,其参数被绑定到Args中
    template<class F, class... Args> 
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

    int get_workers_num() {
        return workers.size();
    }

    queue<std::function<void()>> get_tasks() {
        return tasks;
    }

    bool get_stop() {
        return stop;
    }

    ~ThreadPool();

private:

    // need to keep track of threads so we can join them
    std::vector<std::thread> workers;
    // the task queue
    std::queue<std::function<void()>> tasks;

    // synchronization 同步互斥
    std::mutex queue_mutex;  //锁
    std::condition_variable condition; //条件变量
    bool stop;
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
        :stop(false) {
    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back(
            [this] {
                for (;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock,
                            [this]{return this->stop || !this->tasks.empty();});
                        if (this->stop && this->tasks.empty()) {
                            return;
                        }
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            }
        );
    }
}
// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        // don't allow enqueueing after stopping the pool
        if (stop) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        tasks.emplace([task](){
            (*task)();
        });
        condition.notify_one();
        return res;
    }
}
// the destructor join all threads
inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread& worker : workers) {
        worker.join();
    }
}

//线程函数
int st(int i) {
    std::cout << "hello " << i << std::endl;
    std::cout << "world " << i << std::endl;
    return i*i;
}

int main() {
    // 池中创建4个线程
    ThreadPool pool(4);
    
    // std::future 提供访问异步操作结果的机制
    std::vector<std::future<int>> results;

    pool.enqueue(st, 1);
    pool.enqueue(st, 2);

    for (auto && result : results) {
        std::cout << result.get() << " ";
    }
    std::cout << std::endl;
    return 0;
}








#endif