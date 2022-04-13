#include "./controller/test.cpp"


void RouterManage(){
    router.Get("index",test);
    router.Get("login",login);
    router.Get("fin",fin);
}

