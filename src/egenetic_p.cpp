#include "egenetic_p.h"

#include "eeventloop.h"

template<typename T>
EGeneticPrivate<T>::EGeneticPrivate() {
    mEventLoop = new EEventLoop<T>();
}

template<typename T>
void EGeneticPrivate<T>::start(const EGeneticFunctions<T>& funcs,
                               const EGeneticSettings& settings) {
    if(!funcs.fGenerator) std::runtime_error("No generator defined");
    if(!funcs.fBreeder) std::runtime_error("No mutator defined");
    if(!funcs.fSelector) std::runtime_error("No selector defined");
    if(!funcs.fReceiver) std::runtime_error("No receiver defined");

    if(settings.fNThreads < 0) std::runtime_error("Invalid thread count");
    if(settings.fPopSize < 2) std::runtime_error("Invalid population size");
    if(settings.fNGen < 0) std::runtime_error("Invalid number of generations");
    if(settings.fReceiveInc < 1) std::runtime_error("Invalid receive increment");
    if(settings.fReceiveCount < 1) std::runtime_error("Invalid receive count");

    mEventLoop->run(funcs, settings);
}

template<typename T>
void EGeneticPrivate<T>::stop() {
    mEventLoop->stop();
}

template<typename T>
ESpecimen<T> EGeneticPrivate<T>::getBest() {
    return mEventLoop->getBest();
}
