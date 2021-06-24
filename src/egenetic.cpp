#include "../include/egenetic.h"

#include "egenetic_p.h"

template<typename T>
EGenetic<T>::EGenetic(const EGeneticFunctions<T>& funcs,
                      const EGeneticSettings& settings) {
    d = new EGeneticPrivate<T>(funcs, settings);
}

template<typename T>
void EGenetic<T>::start() {
    d->start();
}

template<typename T>
void EGenetic<T>::stop() {
    d->stop();
}

template<typename T>
ESpecimen<T> EGenetic<T>::getBest() {
    return d->getBest();
}
