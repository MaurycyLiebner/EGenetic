#ifndef EGENETIC_H
#define EGENETIC_H

#include <functional>
#include <vector>

#include "egenetic_global.h"

template <typename T>
class EGeneticPrivate;

enum class EGeneticState {
    stopped, running, paused
};

template <typename T>
using EGenerator = std::function<T()>;

template <typename T>
using EBreeder = std::function<T(const T&, const T&)>;

template <typename T>
using ESelector = std::function<long(T&)>;

template <typename T>
using EReceiver = std::function<void(const std::vector<T>&)>;

template <typename T>
using EStopped = std::function<void()>;

//! @brief The set of functions to be used during calculations.
template <typename T>
struct EGeneticFunctions {
    //! @brief Generator that will create the initial population.
    //! Called from a different thread.
    EGenerator<T> fGenerator;
    //! @brief Breeder that will produce a new specimen from it's parents.
    //! Called from a different thread.
    EBreeder<T> fBreeder;
    //! @brief Selector that will calculate the adaptation
    //! of a specimen (the higher the return value the less adapted).
    //! Called from a different thread.
    ESelector<T> fSelector;
    //! @brief Receiver that will be called when new results are available.
    EReceiver<T> fReceiver;
    //! @brief Stop handler that will be called
    //! when the calculations have stopped.
    EStopped<T> fStopped;
};

//! @brief The settings used during calculations.
struct EGeneticSettings {
    //! @brief Number of threads to be used (0 means use all threads).
    int fNThreads = 0;
    //! @brief Number of specimen in population per thread
    //! (must be greater than 1)
    int fPopSize = 10;
    //! @brief Number of generations
    //! (0 means run until a specimen with 0
    //! returned from the selector is reached)
    int fNGen = 0;
    //! @brief Receive increment defines how often
    //! the results should be fed to the receiver
    //! (must be greater than 0)
    int fReceiveInc = 1;
    //! @brief Receive count defines how many specimen
    //! should be fed to the receiver
    //! (must be greater than 0)
    int fReceiveCount = 1;
};


template <typename T>
using ESpecimen = std::pair<long, T>;

//! @brief
//! @tparam T the type of data
template <typename T>
class EGenetic {
public:
    EGenetic(const EGeneticFunctions<T>& funcs,
             const EGeneticSettings& settings);

    //! @brief Starts calculations. Throws an exception if already running.
    //! @param funcs The set of functions to be used during calculations.
    //! @param settings The settings used during calculations.
    void start();
    void stop();

    ESpecimen<T> getBest();
private:
    EGeneticPrivate<T> *d;
};

#include "../src/egenetic.cpp"

#endif // EGENETIC_H
