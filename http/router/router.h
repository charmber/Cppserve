#include "../../Cmdoule.h"
#include "../httpheader.h"


class Router:public Header{
public:
    //添加请求地址
    void AddUrl(std::string url,std::function<void()> p);
    void CallRequest(std::string);

private:
    std::unordered_map<std::string,std::function<void()>> router;
};


//添加请求
void Router::AddUrl(std::string url, std::function<void()> p) {
    router[url]=p;
}


//key为url路径，value为调用函数
void Router::CallRequest(std::string url) {
    std::cout<<"te:"<<url<<std::endl;
    //router["url"]();
    if(router.count(url)==1){
        router[url]();
    } else{
        std::cout<<"router error"<<std::endl;
    }
}
