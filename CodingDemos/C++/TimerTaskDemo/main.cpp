#include <iostream>
#include "ctime"
#include "unistd.h"
#include "TimerTask.h"
#define TASK_TIMES 20    //执行次数
#define TASK_PERIOD 2   //执行周期，单位秒

using namespace std;

void TimerTask::setTask(){
    cout << "任务开始" << endl;
    int second = TASK_PERIOD*1000000;
    while (run_index!=TASK_TIMES){
        time_t now = time(0);
        char* date = ctime(&now);
        cout << "system now date is:" << date;
        usleep(second);
        run_index+=1;
    }
}

int main() {
    TimerTask task;
    task.setTask();
    return 0;
}
