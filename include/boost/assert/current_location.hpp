#ifndef BOOST_ASSERT_CURRENT_LOCATION_HPP_INCLUDED
#define BOOST_ASSERT_CURRENT_LOCATION_HPP_INCLUDED


#include <boost/config.hpp>

#if defined(BOOST_DISABLE_CURRENT_LOCATION)

# define BOOST_CURRENT_LOCATION ::boost::source_location()

#elif defined(BOOST_MSVC) && BOOST_MSVC >= 1935

# define BOOST_CURRENT_LOCATION ::boost::source_location(__builtin_FILE(), __builtin_LINE(), __builtin_FUNCSIG(), __builtin_COLUMN())

#elif defined(BOOST_MSVC) && BOOST_MSVC >= 1926

// std::source_location::current() is available in -std:c++20, but fails with consteval errors before 19.31, and doesn't produce
// the correct result under 19.31, so prefer the built-ins
# define BOOST_CURRENT_LOCATION ::boost::source_location(__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION(), __builtin_COLUMN())

#elif defined(BOOST_MSVC)

// __LINE__ is not a constant expression under /ZI (edit and continue) for 1925 and before

# define BOOST_CURRENT_LOCATION_IMPL_1(x) BOOST_CURRENT_LOCATION_IMPL_2(x)
# define BOOST_CURRENT_LOCATION_IMPL_2(x) (x##0 / 10)

# define BOOST_CURRENT_LOCATION ::boost::source_location(__FILE__, BOOST_CURRENT_LOCATION_IMPL_1(__LINE__), "")

#elif defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L && !defined(__NVCC__)

// Under nvcc, __builtin_source_location is not constexpr
// https://github.com/boostorg/assert/issues/32

# define BOOST_CURRENT_LOCATION ::boost::source_location(::std::source_location::current())

#elif defined(BOOST_CLANG) && BOOST_CLANG_VERSION >= 90000

# define BOOST_CURRENT_LOCATION ::boost::source_location(__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION(), __builtin_COLUMN())

#elif defined(BOOST_GCC) && BOOST_GCC >= 80000

// The built-ins are available in 4.8+, but are not constant expressions until 7
// In addition, reproducible builds require -ffile-prefix-map, which is GCC 8
// https://github.com/boostorg/assert/issues/38

# define BOOST_CURRENT_LOCATION ::boost::source_location(__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION())

#elif defined(BOOST_GCC) && BOOST_GCC >= 50000

// __PRETTY_FUNCTION__ is allowed outside functions under GCC, but 4.x suffers from codegen bugs
# define BOOST_CURRENT_LOCATION ::boost::source_location(__FILE__, __LINE__, __PRETTY_FUNCTION__)

#else

// __func__ macros aren't allowed outside functions, but BOOST_CURRENT_LOCATION is
# define BOOST_CURRENT_LOCATION ::boost::source_location(__FILE__, __LINE__, "")

#endif

#endif