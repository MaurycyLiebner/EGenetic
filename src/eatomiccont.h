#ifndef EATOMICLIST_H
#define EATOMICLIST_H

#include <atomic>
#include <vector>
#include <list>
#include <mutex>
#include <condition_variable>
#include <functional>

template <typename T, typename C>
class EAtomicCont : private C {
    using Cit = typename C::iterator;
public:
    size_t size();
    bool isEmpty();

    void copy(C& list);
    C get();

    void append(const T& t);
    void append(const C& list);

    void assign(const int id, const T& t);

    void remove(const T& t);
    void clear();

    C takeAll();
    bool takeFirst(T& t);

    using Stopper = std::function<bool()>;
    bool waitTakeLast(T& t, const Stopper& stop);
    bool waitTakeAll(C& t, const Stopper& stop);

    void waitTakeLast(T& t);
    void waitTakeAll(C& t);

    void waitEmpty();
private:
    std::mutex mMutex;
    std::condition_variable mCv;
};

template <typename T>
class EAtomicList : public EAtomicCont<T, std::list<T>> {
};

template <typename T>
class EAtomicVector : public EAtomicCont<T, std::vector<T>> {
};

#include "eatomiccont.cpp"

#endif // EATOMICLIST_H
