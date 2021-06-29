# EGenetic

Qt based genetic algoritms library.

## Example
See [include/egenetic.h](include/egenetic.h).

```C++

EGeneticFunctions<double> funcs;

funcs.fGenerator = []() {
    return 0.01* rand() % 100;
};

funcs.fBreeder = [](const double& s1, const double& s2) {
    return 0.5*(s1 + s2);
};

funcs.fSelector = [](const double& s) {
    return 10000 * (s - 1./3.);
};

funcs.fReceiver = [](const std::vector<double>& ss) {
    // here handle the result
};

funcs.fStopped = [](const std::vector<double>& ss) {
    // here delete the EGenetic<double> instance
};

EGeneticSettings sett;
// set how often to receive results (the lower the value the more often)
sett.fReceiveInc = 100;

const auto g = new EGenetic<double>();
g->start();
// call g->stop() when you want to stop the calculations

```
