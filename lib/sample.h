// sample.h                                                           -*-C++-*-
#ifndef INCLUDED_SAMPLE
#define INCLUDED_SAMPLE

#include <batch.h>
#include <tupleutil.h>

template <class Test> class Sample {
    template <typename Tuple, typename Variant, size_t I>
    void add(Tuple const& tuple, std::array<Variant, I> const& array) {
        auto adder = [this](auto&& f) {
            using F = std::remove_cv_t<std::remove_reference_t<decltype(f)>>;
            if constexpr(std::is_callable_v<F(void), void>) {
                batch_.add(f);
            }
            else {
                batch_.add(f, std::ref(result_));
            }
        };
        for (auto&& v : array) {
            std::visit(adder, v(tuple));
        }
        return;
    }

  public:
    Batch batch_;
    Test test_;
    typename Test::Result result_;

    Sample() : batch_(),
               test_(),
               result_()
    {}

    void run() {
        auto const& actions = test_.actions();
        auto const& getters = tupleutil::tuple_getters(actions);
        add(actions, getters);
        batch_.run();
    }

    template <typename V, size_t I>
    void run(std::array<V, I> const& getters) {
        auto const& actions = test_.actions();
        add(actions, getters);
        batch_.run();
    }
};


// ============================================================================
//              INLINE FUNCTION AND FUNCTION TEMPLATE DEFINITIONS
// ============================================================================


#endif
