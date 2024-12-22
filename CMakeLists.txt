# Copyright 2018-2023 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

# We support CMake 3.5, but prefer 3.20 policies and behavior
cmake_minimum_required(VERSION 3.5...3.20)

project(boost_assert VERSION "${BOOST_SUPERPROJECT_VERSION}" LANGUAGES CXX)


if (BOOST_CXX20_MODULE)
  add_library(boost_assert STATIC)
  boost_set_cxx20_module_settings(boost_assert)
  target_sources(boost_assert PUBLIC FILE_SET CXX_MODULES FILES modules/assert.cxx)
  set(__scope PUBLIC)
else()
  add_library(boost_assert INTERFACE)
  set(__scope INTERFACE)
endif()


add_library(Boost::assert ALIAS boost_assert)
target_include_directories(boost_assert ${__scope} include)
target_link_libraries(boost_assert
  ${__scope}
    Boost::config
)

if(CMAKE_VERSION VERSION_GREATER 3.18 AND CMAKE_GENERATOR MATCHES "Visual Studio")

  file(GLOB_RECURSE boost_assert_IDEFILES CONFIGURE_DEPENDS include/*.hpp)
  source_group(TREE ${PROJECT_SOURCE_DIR}/include FILES ${boost_assert_IDEFILES} PREFIX "Header Files")
  list(APPEND boost_assert_IDEFILES extra/boost_assert.natvis)
  target_sources(boost_assert PRIVATE ${boost_assert_IDEFILES})

endif()

# BUILD_TESTING is the standard CTest variable that enables testing

if(BUILD_TESTING)

  add_subdirectory(test)

endif()
