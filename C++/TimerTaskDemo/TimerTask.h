//
// Created by Mybogames on 2020/8/27.
//

#ifndef TIMERTASKDEMO_TIMERTASK_H
#define TIMERTASKDEMO_TIMERTASK_H

class TimerTask{
public:
    int run_index = 0;
    void setTask();
};

void runTask(int times, double period);

#endif //TIMERTASKDEMO_TIMERTASK_H
