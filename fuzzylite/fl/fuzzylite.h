/*
 Author: Juan Rada-Vilela, Ph.D.
 Copyright (C) 2010-2014 FuzzyLite Limited
 All rights reserved

 This file is part of fuzzylite.

 fuzzylite is free software: you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free
 Software Foundation, either version 3 of the License, or (at your option)
 any later version.

 fuzzylite is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with fuzzylite.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FL_FUZZYLITE_H
#define FL_FUZZYLITE_H

#include <cmath>
#include <iostream>
#include <sstream>
#include <limits>
#include <memory>

#ifndef FL_VERSION
#define FL_VERSION "?"
#endif

#ifndef FL_DATE
#define FL_DATE "?"
#endif

#ifndef FL_BUILD_PATH
#define FL_BUILD_PATH ""
#endif


namespace fl {
#ifdef FL_USE_FLOAT
    typedef float scalar;
#else
    typedef double scalar;
#endif

    //C++98 defines
#if __cplusplus < 201100L
    const long null = 0L;
#define FL_unique_ptr std::auto_ptr 
#define FL_MOVE(x) x
#define FL_OVERRIDE 
#define FL_FINAL
#define FL_DEFAULT
#define FL_NOEXCEPT throw()
#define FL_DISABLE_COPY(Class) \
    Class(const Class &);\
    Class &operator=(const Class &);

#else //C++11 defines
#define FL_CPP11
    const std::nullptr_t null = nullptr;
#define FL_unique_ptr std::unique_ptr
#define FL_MOVE(x) std::move(x)
#define FL_OVERRIDE override
#define FL_FINAL final
#define FL_DEFAULT default
#define FL_NOEXCEPT noexcept
#define FL_DISABLE_COPY(Class) \
    Class(const Class &) = delete;\
    Class &operator=(const Class &) = delete;

#endif

#ifdef FL_CPP11
#define FL_DEFAULT_COPY(Class) \
    Class(const Class&) = default; \
    Class& operator=(const Class&) = default;
#define FL_DEFAULT_MOVE(Class) \
    Class(Class&&) = default; \
    Class& operator=(Class&&) = default;
#define FL_DEFAULT_COPY_AND_MOVE(Class) \
    Class(const Class&) = default; \
    Class& operator=(const Class&) = default;\
    Class(Class&&) = default; \
    Class& operator=(Class&&) = default;
#else
#define FL_DEFAULT_COPY(Class)
#define FL_DEFAULT_MOVE(Class) 
#define FL_DEFAULT_COPY_AND_MOVE(Class)
#endif

    const scalar nan = std::numeric_limits<scalar>::quiet_NaN();
    const scalar inf = std::numeric_limits<scalar>::infinity();
}

#define FL__FILE__ std::string(__FILE__).substr(std::string(FL_BUILD_PATH).size())

#define FL_LOG_PREFIX FL__FILE__ << " [" << __LINE__ << "]:"

#define FL_AT FL__FILE__, __LINE__, __FUNCTION__


#define FL_LOG(message) {if (fl::fuzzylite::logging()){std::cout << FL_LOG_PREFIX << message << std::endl;}}
#define FL_LOGP(message) {if (fl::fuzzylite::logging()){std::cout << message << std::endl;}}

#define FL_DEBUG_BEGIN if (fl::fuzzylite::debug()){
#define FL_DEBUG_END }

#define FL_DBG(message) FL_DEBUG_BEGIN\
        std::cout << FL__FILE__ << "::" << __FUNCTION__ << "[" << __LINE__ << "]:" \
                << message << std::endl;\
        FL_DEBUG_END

//"class FL_EXPORT Name" is required to build DLLs in Windows.
#ifdef FL_WINDOWS
#include <ciso646> //alternative operator spellings:
//#define and &&
//#define or ||
//#define not !
//#define bitand &
//#define bitor |

//TODO: Address warning 4251 by exporting members 
//http://www.unknownroad.com/rtfm/VisualStudio/warningC4251.html
#pragma warning (disable:4251)
#define FL_EXPORT __declspec(dllexport)
#else
#define FL_EXPORT
#endif

namespace fl {

    class FL_EXPORT fuzzylite {
    protected:
        static int _decimals;
        static scalar _macheps;
        static bool _debug;
        static bool _logging;

    public:
        static std::string name();
        static std::string fullname();
        static std::string version();
        static std::string longVersion();
        static std::string license();
        static std::string author();
        static std::string company();
        static std::string website();

        static std::string date();
        static std::string platform();

        static std::string floatingPoint();

        static bool debug();
        static void setDebug(bool debug);

        static int decimals();
        static void setDecimals(int decimals);

        static scalar macheps();
        static void setMachEps(scalar macheps);

        static bool logging();
        static void setLogging(bool logging);

    };
}


#endif  /* FL_FUZZYLITE_H */

