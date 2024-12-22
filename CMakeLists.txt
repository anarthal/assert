# Copyright 2018-2023 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

# We support CMake 3.5, but prefer 3.20 policies and behavior
cmake_minimum_required(VERSION 3.5...3.20)

project(boost_assert VERSION "${BOOST_SUPERPROJECT_VERSION}" LANGUAGES CXX)


if (BOOST_CXX20_MODULE)
  add_library(boost_assert)
  target_sources(boost_assert PUBLIC FILE_SET CXX_MODULES FILES modules/assert.cxx)
  target_include_directories(boost_assert PUBLIC include)
  target_compile_features(boost_assert PUBLIC cxx_std_23)
  set_target_properties(boost_assert PROPERTIES CXX_MODULE_STD 1)
  target_compile_definitions(boost_assert PRIVATE BOOST_CXX20_MODULE)
  target_compile_options(boost_assert PUBLIC -Wno-include-angled-in-module-purview) # TODO: scope this to clang
  target_link_libraries(boost_assert PUBLIC
    Boost::config
  )
else()
  add_library(boost_assert INTERFACE)
  target_include_directories(boost_assert INTERFACE include)
  target_link_libraries(boost_assert
    INTERFACE
    Boost::config
)
endif()


add_library(Boost::assert ALIAS boost_assert)


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
