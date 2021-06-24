#include "econditionvalue.h"

template<typename T>
EConditionValue<T>::EConditionValue(const T& t) {
    mValue = t;
}

template<typename T>
T EConditionValue<T>::operator++(int) {
    std::lock_guard<std::mutex> lk(mMutex);
    mValue++;
    mCv.notify_all();
    return mValue;
}

template<typename T>
T EConditionValue<T>::operator--(int) {
    std::lock_guard<std::mutex> lk(mMutex);
    mValue--;
    mCv.notify_all();
    return mValue;
}

template <typename T>
T EConditionValue<T>::value() {
    std::lock_guard<std::mutex> lk(mMutex);
    return mValue;
}

template <typename T>
void EConditionValue<T>::setValue(const T& value) {
    std::lock_guard<std::mutex> lk(mMutex);
    mValue = value;
    mCv.notify_all();
}

template <typename T>
void EConditionValue<T>::wait(const std::function<bool(T)>& func) {
    std::unique_lock<std::mutex> lk(mMutex);
    while(!func(mValue)) {
        mCv.wait(lk);
    }
}
