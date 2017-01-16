// sample.h                                                           -*-C++-*-
#ifndef INCLUDED_SAMPLE
#define INCLUDED_SAMPLE

#include <batch.h>
#include <tupleutil.h>

template <class State> class Sample {
    template <typename F> void add(size_t, F f) {
        if constexpr(std::is_callable_v<F(void), void>) {
            batch_.add(f);
        }
        else {
            batch_.add(f, std::ref(result_));
        }
    }

    template <typename... Args>
    void add(std::tuple<Args...> const& tuple) {
        auto adder = [this](auto i, auto el) {
            this->add(i, el);
          return 0;
        };
        return tupleutil::tuple_for_each(tuple, adder);
    }

  public:
    Batch batch_;
    State state_;
    typename State::Result result_;

    Sample() : batch_(),
               state_(),
               result_()
    {}

    void run() {
        auto const& actions = state_.actions();
        add(actions);
        batch_.run();
    }
};


// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================


#endif
