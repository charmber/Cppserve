#include <iostream>


void test(Header hea){
    ChJson te;
    te["测试"]="成功";
    te["测试2"]="哈哈哈";
    std::string st= Json(te);

    hea.SendRequestHeader(200,st);
}

void login(Header hea){
    ChJson te;
    te["测试"]="成功";
    std::string st= Json(te);
    hea.SendRequestHeader(200,st);
}
void fin(Header hea){
    ChJson te;
    te["查找"]="成功";
    std::string st= Json(te);
    hea.SendRequestHeader(200,st);
}