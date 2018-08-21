//  MIT License
//
//  Copyright (c) 2018 Francisco de Lanuza
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#include <string>
#include <chrono>

using namespace std;

/**
  *  \brief Formats a 'system_clock::time_point' according to a format string (must be supported by 'strftime')
  *  @param   date_time [in] The system_clock::time_point
  *  @param   format    [in] The format of the date time to be returned as a string
  *  @return  string    Formatted date-time string
  */
inline string formatDateTime(chrono::system_clock::time_point date_time, string format) {
  time_t time_now = chrono::system_clock::to_time_t(date_time);
  char time_str[200];
  strftime( time_str, sizeof time_str, format.data(), localtime( &time_now ) );
  return string(time_str);
}
