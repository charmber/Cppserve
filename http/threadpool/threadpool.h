#include "ThreadQueue.h"
#include <future>

class ThreadPool{
private:
    class ThreadWork{
    private:
        ThreadPool *in_pool;
    public:
        ThreadWork(ThreadPool *pool):in_pool(pool){
        }
        ThreadWork operator()(){
            std::function<void()> func;
            bool que;   //是否正在取出元素
            while (!in_pool->shut_thread){
                {
                    std::unique_lock<std::mutex> lock(in_pool->mutually_thread);

                    //如果任务为空就阻塞
                    if(in_pool->task_queue.empty()){
                        //等待唤醒
                        in_pool->notice_thread.wait(lock);
                    }
                    que=in_pool->task_queue.getQueue(func);
                    if(que){
                        func();
                    }
                }
            }
        }
    };
    bool shut_thread;   //判断线程池是否关闭
    std::vector<std::thread> thread_list;       //线程工作列表
    std::mutex mutually_thread;    //互斥锁
    std::condition_variable notice_thread;  //通知唤醒线程
    ThreadQueue<std::function<void()>> task_queue;      //任务队列
public:
    ThreadPool(const int n_thread=4){
        thread_list=std::vector<std::thread>(n_thread);
        shut_thread= false;
    }

    //删除默认拷贝构造函数
    ThreadPool(const ThreadPool&)=delete;
    ThreadPool(const ThreadPool&&)=delete;
    ThreadPool &operator=(const ThreadPool&)=delete;
    ThreadPool &operator=(const ThreadPool&&)=delete;

    //初始化线程池
    void init(){
        for(int i=0;i<thread_list.size();i++){
            //分配线程
            thread_list.at(i)=std::thread(ThreadWork(this));
        }
    }
    //结束关闭线程池
    ~ThreadPool(){
        shut_thread= true;

        //唤醒所有线程池
        notice_thread.notify_all();
        for(int i=0;i<thread_list.size();i++){
            //判断线程是否在等待
            if(thread_list.at(i).joinable()){
                thread_list.at(i).join();
            }
        }
    }
    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...); // 连接函数和参数定义，特殊函数类型，避免左右值错误

        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        std::function<void()> warpper_func = [task_ptr]()
        {
            (*task_ptr)();
        };

        // 队列通用安全封包函数，并压入安全队列
        task_queue.add(warpper_func);

        // 唤醒一个等待中的线程
        notice_thread.notify_one();

        // 返回先前注册的任务指针
        return task_ptr->get_future();
    }
};




