		#include <pthread.h>
		#include <unistd.h>
		#include <stdio.h>
		#include <stdlib.h>
		int flag=1;
		void* func(void* p)
		{
			for(;flag;)
				fputc(*(char*)p, stderr);
			return p;
		}
		int main()
		{
			pthread_t tid;
			char c='x';
			pthread_create(&tid,NULL,func,&c);
			int i;
			for(i=0;i<5;i++){
				fputc('.', stderr);
				usleep(1000000);
			}
			flag = 0;
			void* p;
			pthread_join(tid,&p);
			printf("p=%p, &c=%p\n", p, &c);
			//sleep(1);
		}

