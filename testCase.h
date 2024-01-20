#ifndef TEST_CASE
#define TEST_CASE

#include <functional>

template<typename outType, typename inType>
class testCase {
public:
    testCase() = default;
    testCase(const outType expectedOutput, const inType input);
    void setInput(const inType input);
    void setExpectedOutput(const outType expectedOutput);
    void calculateOutput(std::function<outType(inType&)> fun);
    inType getInput(void) const;
    outType getExpectedOutput(void) const;
    outType getOutput(void) const;
    bool check(void) const;
private:
    inType input;
    outType output;
    outType expectedOutput;
};

#endif

template <typename outType, typename inType>
inline testCase<outType, inType>::testCase(const outType expectedOutput, const inType input)
    :expectedOutput(expectedOutput), input(input) {}

template <typename outType, typename inType>
inline void testCase<outType, inType>::setInput(const inType input) {
    this->input = input;
}

template <typename outType, typename inType>
inline void testCase<outType, inType>::setExpectedOutput(const outType expectedOutput) {
    this->expectedOutput = expectedOutput;
}

template <typename outType, typename inType>
inline void testCase<outType, inType>::calculateOutput(std::function<outType(inType&)> fun) {
    this->output = fun(this->input);
}

template <typename outType, typename inType>
inline inType testCase<outType, inType>::getInput(void) const {
    return this->input;
}

template <typename outType, typename inType>
inline outType testCase<outType, inType>::getExpectedOutput(void) const {
    return this->expectedOutput;
}

template <typename outType, typename inType>
inline outType testCase<outType, inType>::getOutput(void) const {
    return this->output;
}

template <typename outType, typename inType>
inline bool testCase<outType, inType>::check(void) const
{
    return output == expectedOutput;
}
