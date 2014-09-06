/*
author: jbenet
os x, compile with: gcc -o testo test.c
linux, compile with: gcc -o testo test.c -lrt
*/
#include <iostream>
#include <climits>
#include <pthread.h>

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

void current_utc_time(struct timespec *ts) {

#ifdef __MACH__  // OS X does not have clock_gettime, use clock_get_time
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
#else
    clock_gettime(CLOCK_REALTIME, ts);
#endif
}

timespec diff(timespec start, timespec end) {
    timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

using namespace std;

int main(int argc, char **argv) {
    pthread_mutex_t lock;
    int i = 0;
    const int FIVE_MILLION = 500000000;
    struct timespec start, end;
    current_utc_time(&start);

    while (i < FIVE_MILLION) {
        pthread_mutex_lock(&lock);
        ++i;
        pthread_mutex_unlock(&lock);
    }
    current_utc_time(&end);
    struct timespec eclipse = diff(start, end);
    cout << eclipse.tv_sec << ":" << eclipse.tv_nsec << endl;
    return 0;
}
