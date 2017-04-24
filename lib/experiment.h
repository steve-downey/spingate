// experiment.h                                                       -*-C++-*-
#ifndef INCLUDED_EXPERIMENT
#define INCLUDED_EXPERIMENT

#include <tupleutil.h>
#include <sample.h>

#include <map>

template <class Test>
class Experiment {
  public:
    std::map<typename Test::Result, int> resultMap_;

  public:
    void run(size_t count) {
        Test s;
        auto getters = tupleutil::tuple_getters(s.actions());
        for (size_t i = 0; i < count; ++i) {
            Sample<Test> sample;
            sample.run(getters);
            resultMap_[sample.result_]++;
            std::next_permutation(getters.begin(), getters.end());
        }
    }
};

#endif
