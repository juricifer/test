#include <stdio.h>
#include <pthread.h>

int main()
{
    pthread_t tid = 0xffffff15;
    printf("main thread is running...\n");
    if (0 == pthread_join(tid, NULL))
        printf("pthread_join success\n");
    printf("exit\n");
    return 0;
}

