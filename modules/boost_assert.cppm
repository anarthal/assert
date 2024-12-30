module;

#include <boost/config.hpp>
#include <boost/cstdint.hpp>

export module boost.assert;

import std;

extern "C++" {
#include <boost/assert/source_location.hpp>
}
