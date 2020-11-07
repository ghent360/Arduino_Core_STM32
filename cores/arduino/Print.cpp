/*
  Copyright (c) 2014 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "Core.h"

#include "Print.h"

#if defined (VIRTIO_LOG)
  #include "virtio_log.h"
#endif

// Public Methods //////////////////////////////////////////////////////////////

/* default implementation: may be overridden */
size_t Print::write(const uint8_t *buffer, size_t size) NOEXCEPT
{
  size_t n = 0;
  while (size--) {
    if (write(*buffer++)) {
      n++;
    } else {
      break;
    }
  }
  return n;
}

#ifndef DISABLE_ARDUINO_STRING
size_t Print::print(const __FlashStringHelper *ifsh) NOEXCEPT
{
  return print(reinterpret_cast<const char *>(ifsh));
}

size_t Print::print(const String &s) NOEXCEPT
{
  return write(s.c_str(), s.length());
}
#endif

size_t Print::print(const char str[]) NOEXCEPT
{
  return write(str);
}

size_t Print::print(char c) NOEXCEPT
{
  return write(c);
}

size_t Print::print(unsigned char b, int base) NOEXCEPT
{
  return print((unsigned long) b, base);
}

size_t Print::print(int n, int base) NOEXCEPT
{
  return print((long) n, base);
}

size_t Print::print(unsigned int n, int base) NOEXCEPT
{
  return print((unsigned long) n, base);
}

size_t Print::print(long n, int base) NOEXCEPT
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

size_t Print::print(unsigned long n, int base) NOEXCEPT
{
  if (base == 0) {
    return write(n);
  } else {
    return printNumber(n, base);
  }
}

size_t Print::print(long long n, int base) NOEXCEPT
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printULLNumber(n, 10) + t;
    }
    return printULLNumber(n, 10);
  } else {
    return printULLNumber(n, base);
  }
}

size_t Print::print(unsigned long long n, int base) NOEXCEPT
{
  if (base == 0) {
    return write(n);
  } else {
    return printULLNumber(n, base);
  }
}

size_t Print::print(double n, int digits) NOEXCEPT
{
  return printFloat(n, digits);
}

#ifndef DISABLE_ARDUINO_STRING
size_t Print::println(const __FlashStringHelper *ifsh) NOEXCEPT
{
  size_t n = print(ifsh);
  n += println();
  return n;
}

size_t Print::println(const String &s) NOEXCEPT
{
  size_t n = print(s);
  n += println();
  return n;
}
#endif

size_t Print::print(const Printable &x) NOEXCEPT
{
  return x.printTo(*this);
}

size_t Print::println(void) NOEXCEPT
{
  return write("\r\n");
}

size_t Print::println(const char c[]) NOEXCEPT
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(char c) NOEXCEPT
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t Print::println(unsigned char b, int base) NOEXCEPT
{
  size_t n = print(b, base);
  n += println();
  return n;
}

size_t Print::println(int num, int base) NOEXCEPT
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned int num, int base) NOEXCEPT
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(long num, int base) NOEXCEPT
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned long num, int base) NOEXCEPT
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(long long num, int base) NOEXCEPT
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(unsigned long long num, int base) NOEXCEPT
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t Print::println(double num, int digits) NOEXCEPT
{
  size_t n = print(num, digits);
  n += println();
  return n;
}

size_t Print::println(const Printable &x) NOEXCEPT
{
  size_t n = print(x);
  n += println();
  return n;
}

extern "C" {
  __attribute__((weak))
  int _write(int file, char *ptr, int len)
  {
    switch (file) {
      case STDOUT_FILENO:
      case STDERR_FILENO:
        /* Used for core_debug() */
#if defined (VIRTIO_LOG)
        virtio_log((uint8_t *)ptr, (uint32_t)len);
#elif defined(HAL_UART_MODULE_ENABLED) && !defined(HAL_UART_MODULE_ONLY)
        uart_debug_write((uint8_t *)ptr, (uint32_t)len);
#endif
        break;
      case STDIN_FILENO:
        break;
      default:
        ((class Print *)file)->write((uint8_t *)ptr, len);
        break;
    }
    return len;
  }
}

#ifndef NO_PRINTF
int Print::printf(const char *format, ...) NOEXCEPT
{
  va_list ap;
  va_start(ap, format);
  return vdprintf((int)this, format, ap);
}

int Print::printf(const __FlashStringHelper *format, ...) NOEXCEPT
{
  va_list ap;
  va_start(ap, format);
  return vdprintf((int)this, (const char *)format, ap);
}
#endif

// Private Methods /////////////////////////////////////////////////////////////

size_t Print::printNumber(unsigned long n, uint8_t base) NOEXCEPT
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) {
    base = 10;
  }

  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (n);

  return write(str);
}

/*
void Print::printULLNumber(uint64_t n, uint8_t base)
{
  unsigned char buf[16 * sizeof(long)];
  unsigned int i = 0;

  if (n == 0) {
    print((char)'0');
    return;
  }

  while (n > 0) {
    buf[i++] = n % base;
    n /= base;
  }

  for (; i > 0; i--) {
    print((char)(buf[i - 1] < 10 ? '0' + buf[i - 1] : 'A' + buf[i - 1] - 10));
  }
}
*/
// REFERENCE IMPLEMENTATION FOR ULL
// size_t Print::printULLNumber(unsigned long long n, uint8_t base)
// {
// // if limited to base 10 and 16 the bufsize can be smaller
// char buf[65];
// char *str = &buf[64];

// *str = '\0';

// // prevent crash if called with base == 1
// if (base < 2) base = 10;

// do {
// unsigned long long t = n / base;
// char c = n - t * base;  // faster than c = n%base;
// n = t;
// *--str = c < 10 ? c + '0' : c + 'A' - 10;
// } while(n);

// return write(str);
// }

// FAST IMPLEMENTATION FOR ULL
size_t Print::printULLNumber(unsigned long long n64, uint8_t base) NOEXCEPT
{
  // if limited to base 10 and 16 the bufsize can be 20
  char buf[64];
  uint8_t i = 0;
  uint8_t innerLoops = 0;

  // prevent crash if called with base == 1
  if (base < 2) {
    base = 10;
  }

  // process chunks that fit in "16 bit math".
  uint16_t top = 0xFFFF / base;
  uint16_t th16 = 1;
  while (th16 < top) {
    th16 *= base;
    innerLoops++;
  }

  while (n64 > th16) {
    // 64 bit math part
    uint64_t q = n64 / th16;
    uint16_t r = n64 - q * th16;
    n64 = q;

    // 16 bit math loop to do remainder. (note buffer is filled reverse)
    for (uint8_t j = 0; j < innerLoops; j++) {
      uint16_t qq = r / base;
      buf[i++] = r - qq * base;
      r = qq;
    }
  }

  uint16_t n16 = n64;
  while (n16 > 0) {
    uint16_t qq = n16 / base;
    buf[i++] = n16 - qq * base;
    n16 = qq;
  }

  size_t bytes = i;
  for (; i > 0; i--) {
    write((char)(buf[i - 1] < 10 ?
                 '0' + buf[i - 1] :
                 'A' + buf[i - 1] - 10));
  }
  return bytes;
}

size_t Print::printFloat(double number, uint8_t digits) NOEXCEPT
{
  size_t n = 0;

  if (isnan(number)) {
    return print("nan");
  }
  if (isinf(number)) {
    return print("inf");
  }
  if (number > 4294967040.0) {
    return print("ovf");  // constant determined empirically
  }
  if (number < -4294967040.0) {
    return print("ovf");  // constant determined empirically
  }

  // Handle negative numbers
  if (number < 0.0) {
     n += print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i) {
    rounding /= 10.0;
  }

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print('.');
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)remainder;
    n += print(toPrint);
    remainder -= toPrint;
  }

  return n;
}
