#include "../httpheader.h"
#include "../threadpool/threadpool.h"


class Router{
public:
    //添加请求地址
    void AddUrl(std::string url,std::function<void(Header)> p);
    void Post(std::string url,std::function<void(Header)> p);
    void Get(std::string url,std::function<void(Header)> p);
    void CallRequest(Header&);
    void StartThreadPool(ThreadPool* p){
        pool=p;
        use_thread= true;
    }

private:
    std::unordered_map<std::string,std::function<void(Header)>> router;
    std::unordered_map<std::string,std::function<void(Header)>> PostRouter;
    std::unordered_map<std::string,std::function<void(Header)>> GetRouter;

    ThreadPool* pool;
    bool use_thread= false;
};

//添加GET请求
void Router::Get(std::string url, std::function<void(Header)> p) {
    GetRouter[url]=p;
}

//添加POST请求
void Router::Post(std::string url, std::function<void(Header)> p) {
    PostRouter[url]=p;
}


//添加请求
void Router::AddUrl(std::string url, std::function<void(Header)> p) {
    router[url]=p;
}

//key为url路径，value为调用函数
void Router::CallRequest(Header& header) {
    if(use_thread) {
        if (header.HttpRequestWay=="GET"||header.HttpRequestWay=="get") {
            if(GetRouter.count(header.HttpRequestUrl) == 1){
                pool->submit(GetRouter[header.HttpRequestUrl],header);
            }else{
                std::cout<<"router error"<<std::endl;
                close(header.serverID);
            }
        }else if(header.HttpRequestWay=="POST"||header.HttpRequestWay=="post"){
            if(PostRouter.count(header.HttpRequestUrl) == 1){
                pool->submit(PostRouter[header.HttpRequestUrl],header);
            }else{
                std::cout<<"router error"<<std::endl;
                close(header.serverID);
            }
        }
    } else{
        if (header.HttpRequestWay=="GET"||header.HttpRequestWay=="get") {
            if(GetRouter.count(header.HttpRequestUrl) == 1){
                pool->submit(GetRouter[header.HttpRequestUrl],header);
            }else{
                std::cout<<"router error"<<std::endl;
                close(header.serverID);
            }
        }else if(header.HttpRequestWay=="POST"||header.HttpRequestWay=="post"){
            if(PostRouter.count(header.HttpRequestUrl) == 1){
                pool->submit(PostRouter[header.HttpRequestUrl],header);
            }else{
                std::cout<<"router error"<<std::endl;
                close(header.serverID);
            }
        }
    }
}


