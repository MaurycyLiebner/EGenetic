#include "egenetic_p.h"

#include "eeventloop.h"

template<typename T>
EGeneticPrivate<T>::EGeneticPrivate(const EGeneticFunctions<T>& funcs,
                                    const EGeneticSettings& settings) :
    mFuncs(funcs), mSettings(settings) {
    mEventLoop = new EEventLoop<T>(funcs, settings);
}

template<typename T>
void EGeneticPrivate<T>::start() {
    if(!mFuncs.fGenerator) std::runtime_error("No generator defined");
    if(!mFuncs.fBreeder) std::runtime_error("No mutator defined");
    if(!mFuncs.fSelector) std::runtime_error("No selector defined");
    if(!mFuncs.fReceiver) std::runtime_error("No receiver defined");

    if(mSettings.fNThreads < 0) std::runtime_error("Invalid thread count");
    if(mSettings.fPopSize < 2) std::runtime_error("Invalid population size");
    if(mSettings.fNGen < 0) std::runtime_error("Invalid number of generations");
    if(mSettings.fReceiveInc < 1) std::runtime_error("Invalid receive increment");
    if(mSettings.fReceiveCount < 1) std::runtime_error("Invalid receive count");

    mEventLoop->run();
}

template<typename T>
void EGeneticPrivate<T>::stop() {
    mEventLoop->stop();
}

template<typename T>
ESpecimen<T> EGeneticPrivate<T>::getBest() {
    return mEventLoop->getBest();
}
