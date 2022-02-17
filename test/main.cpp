#include "../str/json.h"
#include "../http/httpserve.h"
#include "router.cpp"


int main()
{
    ThreadPool pool;
    pool.init();
    Router r(&pool);
    RouterManage(&r);
    chamber c(8889,&r);
    c.run();
    return 0;
}