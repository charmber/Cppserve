#include "../httpheader.h"


class Router:public Header{
public:
    void AddUrl(std::string url,std::function<void(Router)> p);
    void CallRequest(Router rou);

private:
    std::unordered_map<std::string,std::function<void(Router)>> router;
};


//添加请求
void Router::AddUrl(std::string url, std::function<void(Router)> p) {
    router[url]=p;
}


//key为url路径，value为调用函数
void Router::CallRequest(Router rou) {
    if(router.find(HttpRequestUrl)!=router.end()){
        router[HttpRequestUrl](rou);
    } else{
        std::cout<<"router error"<<std::endl;
    }
}
