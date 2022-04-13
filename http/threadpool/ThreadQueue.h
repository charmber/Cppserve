#include <queue>
#include <thread>
#include <mutex>
#include <unistd.h>

template<typename T>
class ThreadQueue{
private:
    std::queue<T> safeQueue;    //线程队列
    std::mutex queueLock;   //访问队列锁
public:
    //判断队列是否为空
    bool empty(){
        std::unique_lock<std::mutex> lock(queueLock);   //加锁，防止队列被改变
        return safeQueue.empty();
    }
    //添加队列元素
    void add(T &t){
        std::unique_lock<std::mutex> lock(queueLock);
        safeQueue.emplace(t);
    }
    //取出元素
    bool getQueue(T &t){
        std::unique_lock<std::mutex> lock(queueLock);
        if(safeQueue.empty())
            return false;
        t=std::move(safeQueue.front());
        safeQueue.pop();
        return true;
    }
};
