#ifndef ECONDITIONVALUE_H
#define ECONDITIONVALUE_H

#include <mutex>
#include <condition_variable>
#include <functional>

template <typename T>
class EConditionValue {
public:    
    EConditionValue(const T& t);

    T operator++(int);
    T operator--(int);

    T value();
    void setValue(const T& value);

    void wait(const std::function<bool(T)>& func);
private:
    T mValue;
    std::mutex mMutex;
    std::condition_variable mCv;
};

#include "econditionvalue.cpp"

#endif // ECONDITIONVALUE_H
