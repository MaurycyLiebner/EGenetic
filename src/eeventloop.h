#ifndef EEVENTLOOP_H
#define EEVENTLOOP_H

#include <QObject>
#include <QList>
#include <atomic>
#include "econditionvalue.h"
#include "eworker.h"
#include "../include/egenetic.h"

enum class ELoopState {
    stopped, running
};

template <typename T>
class EEventLoop {
public:
    EEventLoop();

    void run(const EGeneticFunctions<T>& funcs,
             const EGeneticSettings& settings);
    void stop();

    ESpecimen<T> getBest() const;
private:
    int requestPopIdId();
    void workerFinished(QEWorker* w);
    void useWorkers();

    EGeneticFunctions<T> mFuncs;
    EGeneticSettings mSettings;

    bool mStop = false;

    QList<EWorker<T>*> mFreeWorkers;
    QList<QThread*> mThreads;
    QList<EWorker<T>*> mWorkers;

    int mPopIdId = 0;
    int mReceive = 0;
    int mNWorkers;
    int mTotPopSize;
    std::vector<int> mPopIds;

    std::vector<ESpecimen<T>> mPop;
};

#include "eeventloop.cpp"

#endif // EEVENTLOOP_H
