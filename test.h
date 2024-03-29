#ifndef TEST
#define TEST

#include <vector>
#include <functional>
#include "testCase.h"

template<typename outType, typename... inType>
class test {
public:
    test() = default;
    test(const std::function<outType(inType&...)>& fun);
    test(const std::function<outType(inType&...)>& fun, std::vector<testCase<outType, inType...>>& tcs);
    void addTestCase(testCase<outType, inType...>& tc);
    bool check(void);
    unsigned countTestCases(void) const;
    unsigned countPassedTestCases(void) const;
    double totalTime(void) const;
    double averageTime(void) const;
    const testCase<outType, inType...>& operator[](unsigned i) const;
private:
    std::function<outType(inType&...)> fun;
    std::vector<testCase<outType, inType...>> tcs;
};

template <typename outType, typename... inType>
inline test<outType, inType...>::test(const std::function<outType(inType&...)>& fun)
    :fun(fun) {}
    
template <typename outType, typename... inType>
inline test<outType, inType...>::test(const std::function<outType(inType&...)>& fun, std::vector<testCase<outType, inType...>>& tcs)
    : fun(fun), tcs(tcs) {}

template <typename outType, typename... inType>
inline void test<outType, inType...>::addTestCase(testCase<outType,inType...>& tc) {
    this->tcs.push_back(tc);
}

template <typename outType, typename... inType>
inline bool test<outType, inType...>::check(void) {
    bool passed = true;
    for (auto& tc : this->tcs) {
        tc.calculateOutput(this->fun);
        if(!tc.check()) passed = false;
    }

    return passed;
}

template <typename outType, typename... inType>
inline unsigned test<outType, inType...>::countTestCases(void) const {
    return this->tcs.size();
}

template <typename outType, typename... inType>
inline unsigned test<outType, inType...>::countPassedTestCases(void) const {
    unsigned count = 0;
    for (auto& tc : this->tcs) {
        if (tc.check()) count++;
    }

    return count;
}

template <typename outType, typename... inType>
inline double test<outType, inType...>::totalTime(void) const {
    double total = 0;
    for (auto tc : this->tcs) {
        total += tc.getTime();
    }

    return total;
}

template <typename outType, typename... inType>
inline double test<outType, inType...>::averageTime(void) const {
    return totalTime() / countTestCases();
}

template <typename outType, typename... inType>
inline const testCase<outType, inType...>& test<outType, inType...>::operator[](unsigned i) const {
    return tcs[i];
}

#endif
