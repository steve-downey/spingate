// sample.h                                                           -*-C++-*-
#ifndef INCLUDED_SAMPLE
#define INCLUDED_SAMPLE

#include <batch.h>
#include <tupleutil.h>

template <class State> class Sample {
    template <typename F> void add(F f) {
        if constexpr(std::is_callable_v<F(void), void>) {
            batch_.add(f);
        }
        else {
            batch_.add(f, std::ref(result_));
        }
    }

    template <typename T, typename V, size_t I>
    void add(T const& tuple, std::array<V, I> const& array) {
        // auto adder = [this](auto i, auto el) {
        //     this->add(i, el);
        //   return 0;
        // };
        auto adder = [this](auto&& f) {
            using F = std::remove_cv_t<std::remove_reference_t<decltype(f)>>;
            if constexpr(std::is_callable_v<F(void), void>) {
                    batch_.add(f);
                }
            else {
                batch_.add(f, std::ref(result_));
            }
        };
        for (V const& v : array) {
            std::visit(adder, v(tuple));
        }
        return;
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
        auto const& getters = tupleutil::tuple_getters(actions);
        add(actions, getters);
        batch_.run();
    }

    template <typename V, size_t I>
    void run(std::array<V, I> const& getters) {
        auto const& actions = state_.actions();
        add(actions, getters);
        batch_.run();
    }
};


// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================


#endif
