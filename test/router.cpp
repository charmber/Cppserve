#include "./controller/test.cpp"


void RouterManage(Router* r){
    r->AddUrl("index",test);
    r->AddUrl("login",login);
    r->AddUrl("fin",fin);
}

