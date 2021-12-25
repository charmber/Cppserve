#include "../Cmdoule.h"
//const std::string Hearder="HTTP/1.1 200 ok\r\ncontent-type: application/json;charset=utf-8\r\nconnection: close\r\n\r\n";
//const std::string buf="{\n\"user\":\"1234567890\",\n\"name\":\"梦\",\n\"title\":\"哈哈哈哈哈了\",\n\"news_type\":\"科技\"\n}";//HTTP响应
//字符串转换char*


class Header
{
public:
    std::string init1();
    char* StrChangeChar(std::string str,int len);//字符串转char类型
    std::string SendRequestHeader(int code,std::string Type);//封装响应头部

private:
    const std::string Header="HTTP/1.1 200 ok\r\n";
    const std::string ContentTypeJson="content-type: application/json;charset=utf-8\r\n";
    const std::string connection="connection: close\r\n\r\n";
    char *Http;
};
char * Header::StrChangeChar(std::string str, int len) {
    char p[len];
    str.copy(p,str.length(),0);
    return p;
}

std::string Header::init1() {
    return Header+ContentTypeJson+connection;
}

std::string Header::SendRequestHeader(int code,std::string Type){
    if(Type=="json"){
        return "HTTP/1.1 "+std::to_string(code)+" "+"ok\r\n"+ContentTypeJson+connection;
    }

}




