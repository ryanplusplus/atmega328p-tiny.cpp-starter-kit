/*!
 * @file
 * @brief
 */

#ifndef Interrupts_hpp
#define Interrupts_hpp

#include <avr/interrupt.h>
#include <avr/io.h>
#include <cstdint>

class Interrupts {
 public:
  static auto enable() -> void
  {
    sei();
  }

  static auto disable() -> void
  {
    cli();
  }

  static auto wait_for_interrupt() -> void
  {
    SMCR = _BV(SE);
    __asm__ __volatile__("sleep");
  }

  static auto save() -> uint8_t
  {
    uint8_t state = SREG;
    disable();
    return state;
  }

  static auto restore(uint8_t state) -> void
  {
    SREG = state;
  }

  template <typename t>
  static auto critical_section(t body) -> void
  {
    uint8_t state = Interrupts::save();
    body();
    Interrupts::restore(state);
  }
};

#endif
