#include <stdio.h>
#include <cinttypes>
#include "repeater.h"
#include "pico/time.h"

Repeater::Repeater(uint64_t delay) {
    active = true;
    delay_times = {delay*1000};
    delay_index = delay_times.begin();
    current_time = get_absolute_time();
    next_fire = get_absolute_time();
}

bool Repeater::can_fire() {
    if (!active) {
        return false;
    }
    current_time = get_absolute_time();
    int64_t diff = absolute_time_diff_us(current_time, next_fire);
    if (diff < 0) {
        if (delay_index == --delay_times.end()) {
            delay_index = delay_times.begin();
        } else {
            delay_index++;
        }
        uint64_t delay = *delay_index;
        printf("delay: %" PRIu64 "\n", delay);
        next_fire = delayed_by_us(current_time, delay);
        return true;
    } else {
        return false;
    }
}

void Repeater::play() {
    active = true;
}

void Repeater::pause() {
    active = false;
}

void Repeater::clear() {
    delay_times.clear();
}

std::list<uint64_t>* Repeater::queue() {
    return &delay_times;
}

