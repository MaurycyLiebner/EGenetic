#include "eworker.h"

#include <algorithm>
#include <iostream>
#include <cassert>

template<typename T>
EWorker<T>::EWorker(const EGeneticFunctions<T>& funcs,
                    const EGeneticSettings& settings) :
    mFuncs(funcs), mSettings(settings) {
    connect(this, &QEWorker::requestWork,
            this, &EWorker<T>::doWork);
}

template<typename T>
void EWorker<T>::doWork() {
    auto i2 = mFuncs.fBreeder(mP1.second, mP2.second);
    mS = {mFuncs.fSelector(i2), i2};
    emit workDone(this);
}

template<typename T>
void EWorker<T>::setParents(const ESpecimen<T>& p1, const ESpecimen<T>& p2) {
    mP1 = p1;
    mP2 = p2;
}

template<typename T>
ESpecimen<T> EWorker<T>::getResult() {
    return mS;
}
