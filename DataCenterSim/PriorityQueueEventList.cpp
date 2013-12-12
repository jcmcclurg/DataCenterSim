//
//  PriorityQueueEventList.cpp
//  DataCenterSim
//
//  Created by Josiah McClurg on 12/10/13.
//  Copyright (c) 2013 Josiah McClurg. All rights reserved.
//

#include <stdio.h>
#include "PriorityQueueEventList.h"
#include "IEvent.h"
#include <limits>

void PriorityQueueEventList::enqueue(IEvent& e){
    printf("Enqueueing %f\n", e.time);
    list.push_back(&e);
}

IEvent& PriorityQueueEventList::getMin(){
    int i;
    double d = std::numeric_limits<double>::max();
    int di = -1;
    for(i = 0; i < this->list.size(); i++){
        if(this->list[i]->time < d){
            di = i;
            d = this->list[i]->time;
        }
    }
    printf("Minimum is %d, %f\n",di ,this->list[di]->time);
    return *(this->list[di]);
}

void PriorityQueueEventList::dequeue(){
    int i;
    double d = std::numeric_limits<double>::max();
    int di = -1;
    for(i = 0; i < this->list.size(); i++){
        if(this->list[i]->time < d){
            di = i;
            d = this->list[i]->time;
        }
    }
    printf("Dequeueing %d, %f\n",di,this->list[di]->time);
    this->list.erase(this->list.begin() + di);
}

void PriorityQueueEventList::remove(IEvent& e){
    int i;
    std::vector<int> rem;
    for(i = 0; i < this->list.size(); i++){
        if(this->list[i]->time == e.time){
            rem.push_back(i);
        }
    }
    
    for(i = 0; i < rem.size(); i++){
        list.erase(list.begin() + rem[i] - i);
    }
}
