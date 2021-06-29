#ifndef EGENETICPRIVATE_H
#define EGENETICPRIVATE_H

#include <utility>

template <typename T>
class EEventLoop;

template <typename T>
using EParents = std::pair<ESpecimen<T>, ESpecimen<T>>;

#include "../include/egenetic.h"

template <typename T>
class EGeneticPrivate {
public:
    EGeneticPrivate();

    void start(const EGeneticFunctions<T>& funcs,
               const EGeneticSettings& settings);
    void stop();

    //! @brief returns the current best solution
    ESpecimen<T> getBest();
private:    
    EEventLoop<T>* mEventLoop;
};

#include "egenetic_p.cpp"

#endif // EGENETICPRIVATE_H
