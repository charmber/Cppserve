#include "../httpheader.h"
#include "../threadpool/threadpool.h"


class Router{
public:
    //添加请求地址
    void AddUrl(std::string url,std::function<void(Header)> p);
    void CallRequest(Header&);
    Router(){};
    Router(ThreadPool* p){
        pool=p;
        use_thread= true;
    }

private:
    std::unordered_map<std::string,std::function<void(Header)>> router;
    ThreadPool* pool;
    bool use_thread= false;
};


//添加请求
void Router::AddUrl(std::string url, std::function<void(Header)> p) {
    router[url]=p;
}

//key为url路径，value为调用函数
void Router::CallRequest(Header& header) {
    if(use_thread) {
        if (router.count(header.HttpRequestUrl) == 1) {
            pool->submit(router[header.HttpRequestUrl],header);
            std::cout<<"test"<<std::endl;
        }else{
            std::cout<<"router error"<<std::endl;
        }
    } else{
        if (router.count(header.HttpRequestUrl) == 1) {
            router[header.HttpRequestUrl](header);
        }else{
            std::cout<<"router error"<<std::endl;
        }
    }
}


