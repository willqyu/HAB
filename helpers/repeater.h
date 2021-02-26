#ifndef REPEATER_H
#define REPEATER_H

#include "pico/time.h"
#include <list>

class Repeater {
    
    std::list<uint64_t> delay_times;
    std::list<uint64_t>::iterator delay_index;
    absolute_time_t current_time;
    absolute_time_t next_fire;
    bool active;

    public: 
        Repeater(uint64_t delay);
        bool can_fire();
        void play();
        void pause();
        void clear();
        std::list<uint64_t>* queue();
        bool update_delay() {return true;};
        template <typename ... Ts> bool update_delay(uint64_t delay, Ts... ts);

};

template <typename ... Ts>
bool Repeater::update_delay(uint64_t delay, Ts... delays) {
    delay_times.push_back(delay * 1000);
    return update_delay(delays...);
}


#endif