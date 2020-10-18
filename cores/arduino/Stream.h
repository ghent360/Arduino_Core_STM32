/*
  Stream.h - base class for character-based streams.
  Copyright (c) 2010 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  parsing functions based on TextFinder library by Michael Margolis
*/
#ifndef Stream_h
#define Stream_h

#include <inttypes.h>
#include "Print.h"

// compatability macros for testing
/*
#define   getInt()            parseInt()
#define   getInt(skipChar)    parseInt(skipchar)
#define   getFloat()          parseFloat()
#define   getFloat(skipChar)  parseFloat(skipChar)
#define   getString( pre_string, post_string, buffer, length)
readBytesBetween( pre_string, terminator, buffer, length)
*/

#define NO_IGNORE_CHAR  '\x01' // a char not found in a valid ASCII numeric field

class Stream : public Print {
  protected:
    unsigned long _timeout;      // number of milliseconds to wait for the next char before aborting timed read
    unsigned long _startMillis;  // used for timeout measurement
    int timedRead() noexcept;    // private method to read stream with timeout
    int timedPeek() noexcept;    // private method to peek stream with timeout
    int peekNextDigit(LookaheadMode lookahead, bool detectDecimal) noexcept; // returns the next numeric digit in the stream or -1 if timeout

  public:
    virtual int available() noexcept = 0;
    virtual int read() noexcept = 0;
    virtual int peek() noexcept = 0;

    Stream() noexcept
    {
      _timeout = 1000;
    }

    // parsing methods

    void setTimeout(unsigned long timeout) noexcept;  // sets maximum milliseconds to wait for stream data, default is 1 second
    unsigned long getTimeout(void) noexcept
    {
      return _timeout;
    }

    bool find(const char *target) noexcept;   // reads data from the stream until the target string is found
    bool find(const uint8_t *target) noexcept
    {
      return find((const char *)target);
    }
    // returns true if target string is found, false if timed out (see setTimeout)

    bool find(const char *target, size_t length) noexcept;   // reads data from the stream until the target string of given length is found
    bool find(const uint8_t *target, size_t length) noexcept
    {
      return find((const char *)target, length);
    }
    // returns true if target string is found, false if timed out

    bool find(char target) noexcept
    {
      return find(&target, 1);
    }

    bool findUntil(const char *target, const char *terminator) noexcept;   // as find but search ends if the terminator string is found
    bool findUntil(const uint8_t *target, const char *terminator) noexcept
    {
      return findUntil((const char *)target, terminator);
    }

    bool findUntil(const char *target, size_t targetLen, const char *terminate, size_t termLen) noexcept;   // as above but search ends if the terminate string is found
    bool findUntil(const uint8_t *target, size_t targetLen, const char *terminate, size_t termLen) noexcept
    {
      return findUntil((const char *)target, targetLen, terminate, termLen);
    }

    long parseInt(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR) noexcept;
    // returns the first valid (long) integer value from the current position.
    // lookahead determines how parseInt looks ahead in the stream.
    // See LookaheadMode enumeration at the top of the file.
    // Lookahead is terminated by the first character that is not a valid part of an integer.
    // Once parsing commences, 'ignore' will be skipped in the stream.

    float parseFloat(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR) noexcept;
    // float version of parseInt

    virtual size_t readBytes(char *buffer, size_t length) noexcept;  // read chars from stream into buffer
    size_t readBytes(uint8_t *buffer, size_t length) noexcept
    {
      return readBytes((char *)buffer, length);
    }
    // terminates if length characters have been read or timeout (see setTimeout)
    // returns the number of characters placed in the buffer (0 means no valid data found)

    virtual size_t readBytesUntil(char terminator, char *buffer, size_t length) noexcept;  // as readBytes with terminator character
    size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length) noexcept
    {
      return readBytesUntil(terminator, (char *)buffer, length);
    }
    // terminates if length characters have been read, timeout, or if the terminator character  detected
    // returns the number of characters placed in the buffer (0 means no valid data found)

    // Arduino String functions to be added here
    String readString() noexcept;
    String readStringUntil(char terminator) noexcept;

  protected:
    long parseInt(char ignore) noexcept
    {
      return parseInt(SKIP_ALL, ignore);
    }
    float parseFloat(char ignore) noexcept
    {
      return parseFloat(SKIP_ALL, ignore);
    }
    // These overload exists for compatibility with any class that has derived
    // Stream and used parseFloat/Int with a custom ignore character. To keep
    // the public API simple, these overload remains protected.

    struct MultiTarget {
      const char *str;  // string you're searching for
      size_t len;       // length of string you're searching for
      size_t index;     // index used by the search routine.
    };

    // This allows you to search for an arbitrary number of strings.
    // Returns index of the target that is found first or -1 if timeout occurs.
    int findMulti(struct MultiTarget *targets, int tCount) noexcept;
};

#endif
