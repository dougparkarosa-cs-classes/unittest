#include <unity.h>

#include <Arduino.h>

#include <BitManipulation.h>

using namespace bit_manipulation;
namespace {
template <typename T> void testAllOn(T bits) {
  for (unsigned int bit = 0; bit < sizeof(bits) * 8; ++bit) {
    TEST_ASSERT(test(bits, bit));
  }
}

template <typename T> void testAllOff(T bits) {
  for (unsigned int bit = 0; bit < sizeof(bits) * 8; ++bit) {
    TEST_ASSERT(!test(bits, bit));
  }
}
} // namespace

void test_bit_on() {

  unsigned int bits = 0;

  TEST_ASSERT(bits == 0);
  on(bits, 0);
  TEST_ASSERT(bits != 0);
  TEST_ASSERT(bits == 1 << 0);

  bits = 0;
  for (unsigned int bit = 0; bit < sizeof(bits) * 8; ++bit) {
    on(bits, bit);
    TEST_ASSERT(bits > 0);
    TEST_ASSERT(test(bits, bit));
  }

  testAllOn(bits);
}

void test_bit_off() {

  int bits = 0;
  for (unsigned int bit = 0; bit < sizeof(bits) * 8; ++bit) {
    on(bits, bit);
  }

  for (unsigned int bit = 0; bit < sizeof(bits) * 8; ++bit) {
    off(bits, bit);
    TEST_ASSERT(!test(bits, bit));
  }

  testAllOff(bits);
}

void test_bit_toggle() {
  int bits = 0;
  for (unsigned int bit = 0; bit < sizeof(bits) * 8; ++bit) {
    toggle(bits, bit);
    TEST_ASSERT(test(bits, bit));
  }
  testAllOn(bits);

  for (unsigned int bit = 0; bit < sizeof(bits) * 8; ++bit) {
    toggle(bits, bit);
    TEST_ASSERT(!test(bits, bit));
  }
  testAllOff(bits);
}

void testSetSpeed() {
  const long kNumIter = 10000L;

  auto s1 = micros();
  for (int i = 0; i < kNumIter; ++i) {
    on(PORTB, PORTB5);
  }
  auto f1 = micros();
  auto s2 = micros();
  for (int i = 0; i < kNumIter; ++i) {
    PORTB |= (1 << PORTB5);
  }
  auto f2 = micros();
  TEST_ASSERT((f1 - s1) > 0);
  TEST_ASSERT((f2 - s2) > 0);
  TEST_ASSERT_INT_WITHIN(0, f1 - s1, f2 - s2);
}

void setup() {
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  UNITY_BEGIN();
  RUN_TEST(test_bit_on);
  RUN_TEST(test_bit_off);
  RUN_TEST(test_bit_toggle);
  RUN_TEST(testSetSpeed);
  UNITY_END();

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Blink LED when tests are done
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}