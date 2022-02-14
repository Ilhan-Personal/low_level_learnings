#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
pthread_mutex_t lock;
int counter;
void* increment(void * argc){
    int i;
    for(i=0;i<1000;i++){
        //Entering critical section of code
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
}
int main(){
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,increment,NULL);
    pthread_create(&thread2,NULL,increment,NULL);
    getchar();
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    printf("%d",counter);
    return 0;

}