#include "eeventloop.h"

#include <QThread>
#include <algorithm>
#include <numeric>

template <typename T>
EEventLoop<T>::EEventLoop() {
    if(mSettings.fNThreads == 0) {
        mNWorkers = QThread::idealThreadCount();
    } else {
        mNWorkers = mSettings.fNThreads;
    }
    mTotPopSize = mNWorkers*mSettings.fPopSize;

    mPopIds = std::vector<int>(mTotPopSize);
    std::iota(mPopIds.begin(), mPopIds.end(), 0);
    std::random_shuffle(mPopIds.begin(), mPopIds.end());
}

template<typename T>
void EEventLoop<T>::run(const EGeneticFunctions<T>& funcs,
                        const EGeneticSettings& settings) {
    mFuncs = funcs;
    mSettings = settings;
    for(int i = 0; i < mTotPopSize; i++) {
        auto sp = mFuncs.fGenerator();
        const int s = mFuncs.fSelector(sp);
        mPop.push_back({s, sp});
    }
    for(int i = 0; i < mNWorkers; i++) {
        const auto w = new EWorker<T>(mFuncs, mSettings);
        const auto t = new QThread();
        mWorkers.push_back(w);
        mThreads.append(t);
        w->moveToThread(t);
        t->start();
        mFreeWorkers << w;
        QObject* qo = new QObject();
        QObject::connect(w, &QEWorker::workDone,
                         qo, [this](QEWorker* w) { workerFinished(w); },
                         Qt::QueuedConnection);
    }
    useWorkers();
}

template<typename T>
void EEventLoop<T>::stop() {
    mStop = true;
}

template<typename T>
ESpecimen<T> EEventLoop<T>::getBest() const {
    return mPop.front();
}

template<typename T>
int EEventLoop<T>::requestPopIdId() {
    mPopIdId++;
    if(mPopIdId >= (int)mPopIds.size()) {
        std::random_shuffle(mPopIds.begin(), mPopIds.end());
        mPopIdId = 0;
    }
    return mPopIds[mPopIdId];
}

template<typename T>
void EEventLoop<T>::workerFinished(QEWorker* w) {
    EWorker<T>* wt = static_cast<EWorker<T>*>(w);
    const auto sorter = [](const ESpecimen<T>& a, const ESpecimen<T>& b) {
        return a.first < b.first;
    };
    const auto s = wt->getResult();
    auto it = upper_bound(mPop.begin(), mPop.end(), s, sorter);
    mPop.insert(it, s);

    mPop.resize(mTotPopSize);
    mFreeWorkers << wt;

    if(mReceive++ % mSettings.fReceiveInc == 0) {
        std::vector<T> data;
        data.reserve(mSettings.fReceiveCount);
        for(int i = 0; i < mSettings.fReceiveCount; i++) {
            data.push_back(mPop[i].second);
        }
        mFuncs.fReceiver(data);
    }

    if(mStop) {
        if(mFreeWorkers.count() == mNWorkers) {
            if(mFuncs.fStopped) mFuncs.fStopped();
        }
        return;
    }
    useWorkers();
}

template<typename T>
void EEventLoop<T>::useWorkers() {
    for(const auto w : mFreeWorkers) {
        w->setParents(mPop[requestPopIdId()], mPop[requestPopIdId()]);
        emit w->requestWork();
    }
    mFreeWorkers.clear();
}
