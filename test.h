#ifndef TEST
#define TEST

#include <vector>
#include <functional>
#include "testCase.h"

template<typename outType, typename inType>
class test {
public:
    test() = default;
    test(const std::function<outType(inType&)>& fun);
    test(const std::function<outType(inType&)>& fun, std::vector<testCase<outType, inType>>& tcs);
    void addTestCase(testCase<outType, inType> tc);
    bool check(void);
    unsigned countTestCases(void) const;
    unsigned countPassedTestCases(void) const;
    double getTime(unsigned i) const;
    double totalTime(void) const;
    double averageTime(void) const;
private:
    std::function<outType(inType&)> fun;
    std::vector<testCase<outType, inType>> tcs;
    std::vector<double> vTime;
};

#endif

template <typename outType, typename inType>
inline test<outType, inType>::test(const std::function<outType(inType&)>& fun)
    :fun(fun) {}
    
template <typename outType, typename inType>
inline test<outType, inType>::test(const std::function<outType(inType&)>& fun, std::vector<testCase<outType, inType>>& tcs)
    : fun(fun), tcs(tcs) {}

template <typename outType, typename inType>
inline void test<outType, inType>::addTestCase(testCase<outType,inType> tc) {
    this->tcs.push_back(tc);
}

template <typename outType, typename inType>
inline bool test<outType, inType>::check(void) {
    bool passed = true;
    for (auto& tc : this->tcs) {
        auto timeTaken = tc.calculateOutput(this->fun);
        vTime.push_back(timeTaken);
        if(!tc.check()) passed = false;
    }

    return passed;
}

template <typename outType, typename inType>
inline unsigned test<outType, inType>::countTestCases(void) const {
    return this->tcs.size();
}

template <typename outType, typename inType>
inline unsigned test<outType, inType>::countPassedTestCases(void) const {
    unsigned count = 0;
    for (auto& tc : this->tcs) {
        if (tc.check()) count++;
    }

    return count;
}

template <typename outType, typename inType>
inline double test<outType, inType>::getTime(unsigned i) const {
    return vTime[i];
}

template <typename outType, typename inType>
inline double test<outType, inType>::totalTime(void) const {
    double total;
    for (auto t : vTime) {
        total += t;
    }

    return total;
}

template <typename outType, typename inType>
inline double test<outType, inType>::averageTime(void) const {
    return totalTime() / countTestCases();
}
