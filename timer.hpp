#pragma once

#include <chrono>

template <typename T>
class Timer
{

private:

    std::chrono::nanoseconds _time_stamp;
    std::chrono::nanoseconds _wait_duration; 

public:

    void set_timer(int64_t time_to_wait)
    {
        this->_time_stamp = std::chrono::high_resolution_clock::now().time_since_epoch();
        this->_wait_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(T(time_to_wait));
    }

    bool time_elapsed()
    {
        std::chrono::nanoseconds _current_time, _difference;

        _current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
        _difference = _current_time - this->_time_stamp;

        return (_difference >= this->_wait_duration);
    }

    Timer() : 
        _time_stamp(std::chrono::high_resolution_clock::now().time_since_epoch()),
        _wait_duration(std::chrono::duration_cast<std::chrono::nanoseconds>(T(0)))
    {
        static_assert(std::chrono::__is_duration<T>::value, "Timer type must be std::chrono ");
    }
    Timer(int64_t time_to_wait) : 
        _time_stamp(std::chrono::high_resolution_clock::now().time_since_epoch()),
        _wait_duration(std::chrono::duration_cast<std::chrono::nanoseconds>(T(time_to_wait)))
    {
        static_assert(std::chrono::__is_duration<T>::value, "Timer type must be std::chrono ");
    }
};



