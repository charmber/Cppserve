#include "../str/json.h"
#include "../http/httpserve.h"
#include "router.cpp"


int main()
{
    ThreadPool pool(8);
    pool.init();
    router.StartTthreadPool(&pool);
    RouterManage();
    chamber c(8080);
    c.run();
    return 0;
}