// experiment.h                                                       -*-C++-*-
#ifndef INCLUDED_EXPERIMENT
#define INCLUDED_EXPERIMENT

#include <tupleutil.h>
#include <sample.h>

#include <map>

template <class State>
class Experiment {
  public:
    std::map<typename State::Result, int> resultMap_;

  public:
    void run(size_t count) {
        State s;
        auto getters = tupleutil::tuple_getters(s.actions());
        for (size_t i = 0; i < count; ++i) {
            Sample<State> sample;
            sample.run(getters);
            resultMap_[sample.result_]++;
            std::next_permutation(getters.begin(), getters.end());
        }
    }
};

#endif
