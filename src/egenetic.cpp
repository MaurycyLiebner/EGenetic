#include "../include/egenetic.h"

#include "egenetic_p.h"

template<typename T>
EGenetic<T>::EGenetic() {
    d = new EGeneticPrivate<T>();
}

template<typename T>
EGenetic<T>::~EGenetic() {
    delete d;
}

template<typename T>
void EGenetic<T>::start(const EGeneticFunctions<T>& funcs,
                        const EGeneticSettings& settings) {
    d->start(funcs, settings);
}

template<typename T>
void EGenetic<T>::stop() {
    d->stop();
}

template<typename T>
ESpecimen<T> EGenetic<T>::getBest() {
    return d->getBest();
}
