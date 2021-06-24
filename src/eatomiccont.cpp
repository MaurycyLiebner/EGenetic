#include "eatomiccont.h"

template<typename T, typename C>
size_t EAtomicCont<T, C>::size() {
    std::lock_guard<std::mutex> lk(mMutex);
    return C::size();
}

template<typename T, typename C>
bool EAtomicCont<T, C>::isEmpty() {
    std::lock_guard<std::mutex> lk(mMutex);
    return C::empty();
}

template<typename T, typename C>
void EAtomicCont<T, C>::copy(C& list) {
    std::lock_guard<std::mutex> lk(mMutex);
    list = *this;
}

template<typename T, typename C>
C EAtomicCont<T, C>::get() {
    std::lock_guard<std::mutex> lk(mMutex);
    return *this;
}

template<typename T, typename C>
C EAtomicCont<T, C>::takeAll() {
    std::lock_guard<std::mutex> lk(mMutex);
    C result;
    C::swap(result);
    return result;
}

template<typename T, typename C>
bool EAtomicCont<T, C>::takeFirst(T& t) {
    std::lock_guard<std::mutex> lk(mMutex);
    if(C::empty()) return false;
    t = C::front();
    C::pop_front();
    return true;
}

template<typename T, typename C>
void EAtomicCont<T, C>::append(const T& t) {
    std::lock_guard<std::mutex> lk(mMutex);
    C::push_back(t);
    mCv.notify_one();
}

template<typename T, typename C>
void EAtomicCont<T, C>::append(const C& list) {
    std::lock_guard<std::mutex> lk(mMutex);
    for(const auto& t : list) C::push_back(t);
    mCv.notify_all();
}

template<typename T, typename C>
void EAtomicCont<T, C>::assign(const int id, const T& t) {
    std::lock_guard<std::mutex> lk(mMutex);
    const auto it = C::begin() + id;
    *it = t;
    mCv.notify_all();
}

template<typename T, typename C>
void EAtomicCont<T, C>::remove(const T& t) {
    std::lock_guard<std::mutex> lk(mMutex);
    C::remove(t);
    mCv.notify_all();
}

template<typename T, typename C>
void EAtomicCont<T, C>::clear() {
    std::lock_guard<std::mutex> lk(mMutex);
    C::clear();
    mCv.notify_all();
}

template<typename T, typename C>
bool EAtomicCont<T, C>::waitTakeLast(T& t, const Stopper& stop) {
    std::unique_lock<std::mutex> lk(mMutex);
    while(C::empty()) {
        mCv.wait(lk);
        if(stop()) return false;
    }
    t = C::back();
    C::pop_back();
    mCv.notify_all();
    return true;
}

template<typename T, typename C>
bool EAtomicCont<T, C>::waitTakeAll(C& t, const Stopper& stop) {
    std::unique_lock<std::mutex> lk(mMutex);
    while(C::empty()) {
        mCv.wait(lk);
        if(stop()) return false;
    }
    t = C::takeAll();
    mCv.notify_all();
    return true;
}

template<typename T, typename C>
void EAtomicCont<T, C>::waitTakeLast(T& t) {
    waitTakeLast(t, []() { return false; });
}

template<typename T, typename C>
void EAtomicCont<T, C>::waitTakeAll(C& t) {
    waitTakeAll(t, []() { return false; });
}

template<typename T, typename C>
void EAtomicCont<T, C>::waitEmpty() {
    std::unique_lock<std::mutex> lk(mMutex);
    while(!C::empty()) {
        mCv.wait(lk);
    }
}
