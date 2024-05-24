#pragma once

#include <chrono>

template <typename T>
class Timer
{

private:

    std::chrono::nanoseconds _time_stamp;
    std::chrono::nanoseconds _wait_duration; 

    static inline std::chrono::nanoseconds current_time() { return std::chrono::high_resolution_clock::now().time_since_epoch(); }
    static inline std::chrono::nanoseconds to_nanoseconds(T time) { return std::chrono::duration_cast<std::chrono::nanoseconds>(time); }

public:

    void set_timer(int64_t time_to_wait)
    {
        this->_time_stamp = current_time();
        this->_wait_duration = to_nanoseconds(T(time_to_wait));
    }

    bool time_elapsed()
    {
        std::chrono::nanoseconds _current_time, _difference;

        _current_time = current_time();
        _difference = _current_time - this->_time_stamp;

        return (_difference > this->_wait_duration);
    }

    Timer() : 
        _time_stamp(current_time()),
        _wait_duration(to_nanoseconds(T(0)))
    {
        static_assert(std::chrono::__is_duration<T>::value, "Timer type must be std::chrono ");
    }
    Timer(int64_t time_to_wait) : 
        _time_stamp(current_time()),
        _wait_duration(to_nanoseconds(T(time_to_wait)))
    {
        static_assert(std::chrono::__is_duration<T>::value, "Timer type must be std::chrono ");
    }
};



