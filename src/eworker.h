#ifndef EWORKER_H
#define EWORKER_H

#include "egenetic_p.h"
#include "econditionvalue.h"
#include "eatomiccont.h"

#include "qeworker.h"

enum class EWorkerTask {
    quit, run
};

template <typename T>
class EWorker : public QEWorker {
public:
    EWorker(const EGeneticFunctions<T>& funcs,
            const EGeneticSettings& settings);

    void doWork();

    void setParents(const ESpecimen<T>& p1,
                    const ESpecimen<T>& p2);
    ESpecimen<T> getResult();
private:
    const EGeneticFunctions<T> mFuncs;
    const EGeneticSettings mSettings;

    void wait();

    ESpecimen<T> mS;
    ESpecimen<T> mP1;
    ESpecimen<T> mP2;
};

#include "eworker.cpp"

#endif // EWORKER_H
