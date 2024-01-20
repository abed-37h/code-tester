#ifndef TEST_CASE
#define TEST_CASE

#include <tuple>
#include <functional>
#include <chrono>

template<typename outType, typename... inType>
class testCase {
public:
    testCase() = default;
    testCase(const outType expectedOutput, const inType... input);
    void setInput(const inType... input);
    void setExpectedOutput(const outType expectedOutput);
    double calculateOutput(const std::function<outType(inType&...)>& fun);
    std::tuple<inType...> getInput(void) const;
    outType getExpectedOutput(void) const;
    outType getOutput(void) const;
    bool check(void) const;
private:
    std::tuple<inType...> input;
    outType output;
    outType expectedOutput;
};

template <typename outType, typename... inType>
inline testCase<outType, inType...>::testCase(const outType expectedOutput, const inType... input)
    :expectedOutput(expectedOutput) {
    this->input = make_tuple(input...);
}

template <typename outType, typename... inType>
inline void testCase<outType, inType...>::setInput(const inType... input) {
    this->input = make_tuple(input...);
}

template <typename outType, typename... inType>
inline void testCase<outType, inType...>::setExpectedOutput(const outType expectedOutput) {
    this->expectedOutput = expectedOutput;
}

template <typename outType, typename... inType>
inline double testCase<outType, inType...>::calculateOutput(const std::function<outType(inType&...)>& fun) {
    auto start = std::chrono::high_resolution_clock::now();

    // expand `this->input` tuple into function args to be passed to `fun`
    this->output = std::apply(fun, this->input);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() * 1e-6;

    return duration;
}

template <typename outType, typename... inType>
inline std::tuple<inType...> testCase<outType, inType...>::getInput(void) const {
    return this->input;
}

template <typename outType, typename... inType>
inline outType testCase<outType, inType...>::getExpectedOutput(void) const {
    return this->expectedOutput;
}

template <typename outType, typename... inType>
inline outType testCase<outType, inType...>::getOutput(void) const {
    return this->output;
}

template <typename outType, typename... inType>
inline bool testCase<outType, inType...>::check(void) const {
    return output == expectedOutput;
}

#endif
