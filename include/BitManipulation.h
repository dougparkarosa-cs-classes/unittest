#ifndef BITMANIPULATION_H
#define BITMANIPULATION_H
/// \brief Functions to manipulate bits.
namespace bit_manipulation {

/// Turn a specific bit on (set to 1)
/// \tparam T Integral type holding bits to manipulate
/// \param value location of bits to manipulate
/// \param bit bit counting from right to turn on
template <typename T> void on(T &value, unsigned int bit) {
  value |= (1 << bit);
}

/// Turn a specific bit off (set to 0)
/// \tparam T Integral type holding bits to manipulate
/// \param value location of bits to manipulate
/// \param bit bit counting from right to turn on
template <typename T> void off(T &value, unsigned int bit) {
  value &= ~(1 << bit);
}

/// Toggle a specific bit (set to 0 if 1 or 1 if 0)
/// \tparam T Integral type holding bits to manipulate
/// \param value location of bits to manipulate
/// \param bit bit counting from right to turn on
template <typename T> void toggle(T &value, unsigned int bit) {
  value ^= (1 << bit);
}

/// Test if a particular bit is set (!=0)
/// \tparam T Integral type holding bits to manipulate
/// \param value location of bits to test
/// \param bit bit counting from right to test
/// \return true if bit is set false otherwise
template <typename T> bool test(const T &value, unsigned int bit) {
  return (value & (1 << bit)) != 0;
}
} // namespace bit_manipulation
#endif // BITMANIPULATION_H