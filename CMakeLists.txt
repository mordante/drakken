##### Basics #####

cmake_minimum_required(VERSION 2.8)
#set(CMAKE_VERBOSE_MAKEFILE on)
project(drakken)

include(CheckCXXCompilerFlag)

##### Set the options. #####

option(ENABLE_STRICT_COMPILATION "Sets the strict compilation mode" ON)
option(ENABLE_PEDANTIC_COMPILATION "Sets the pedantic compilation mode" ON)


##### Dependencies #####

find_package(Boost REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLOG REQUIRED libglog)

# This test tests for some local modifications to the glog library.
# These changes are not deemed finished enough to send upstream.
file(WRITE
	"${CMAKE_BINARY_DIR}/glog_test/glog_test.cpp"
	"#include <glog/logging.h>\nint main(){FLAGS_log_prefix_format = \"\";}"
)
try_compile(GLOG_HAS_LOG_PREFIX_FORMAT
	"${CMAKE_BINARY_DIR}/glog_test"
	"${CMAKE_BINARY_DIR}/glog_test/glog_test.cpp"
	CMAKE_FLAGS
		-DINCLUDE_DIRECTORIES=${GLOG_INCLUDEDIR}
		-DLINK_DIRECTORIES=${GLOG_LIBDIR}
		-DLINK_LIBRARIES=${GLOG_LIBRARIES}
)

if(GLOG_HAS_LOG_PREFIX_FORMAT)
	add_definitions(-DGLOG_HAS_LOG_PREFIX_FORMAT)
endif(GLOG_HAS_LOG_PREFIX_FORMAT)


##### Set the compiler flags.

# This macro checks whether a compiler supports a compiler flag.
#
# If the flag is supported the flag will be added to the target compiler flags.
# GCC seems to be quite happy to accept flags it does not support when there is
# a `no' in it e.g. -Wno-not_supported_flag but will fail to compile with
# -Wnot_supported_flag. For that case all not-named parameters will be added to
# the target instead.
#
# param target                    The variable to add the compiler flag to.
# param flag                      The compiler flag to test.
# param variable                  The test macro needs a variable to store the
#                                 result of the test, this paramter holds that
#                                 variable.
# param ...                       If this variable is set it will be added to
#                                 target instead of flag when the compiler
#                                 supports flag.
macro(check_compiler_has_flag target flag variable)
	check_cxx_compiler_flag(${flag} ${variable})
	if(${variable})
		if(${ARGC} GREATER 3)
			set(${target} "${${target}} ${ARGN}")
		else(${ARGC} GREATER 3)
			set(${target} "${${target}} ${flag}")
		endif(${ARGC} GREATER 3)
	endif(${variable})
endmacro(check_compiler_has_flag)


### Set the environment compiler flags.

if(NOT DEFINED CXX_FLAGS_USER)

	message(STATUS "Environment compiler flags set to »${CXX_FLAGS_USER}«")
	set(CXX_FLAGS_USER
		"$ENV{CXXFLAGS}"
		CACHE
		STRING
		"The CXXFLAGS environment variable used for the initial generation."
		FORCE
	)

endif(NOT DEFINED CXX_FLAGS_USER)


### Set default project compiler flags

set(CXX_FLAGS_PROJECT)
check_compiler_has_flag(CXX_FLAGS_PROJECT "-std=c++98" HAS_COMPILER_FLAG_STD)
check_compiler_has_flag(CXX_FLAGS_PROJECT "-W" HAS_COMPILER_FLAG_W)
check_compiler_has_flag(CXX_FLAGS_PROJECT "-Wall" HAS_COMPILER_FLAG_WALL)
check_compiler_has_flag(CXX_FLAGS_PROJECT "-fshow-column" HAS_COMPILER_FLAG_FSHOW_COLUMN)


### Set strict compiler flags.

set(CXX_FLAGS_STRICT_COMPILATION)
check_compiler_has_flag(
	CXX_FLAGS_STRICT_COMPILATION
	"-Werror"
	HAS_COMPILER_FLAG_WERROR
)

# This flag is/will be added in gcc-4.8 and fails with BOOST_STATIC_ASSERT
check_compiler_has_flag(
	CXX_FLAGS_STRICT_COMPILATION
	"-Wunused-local-typedefs"
	HAS_COMPILER_FLAG_WUNUSED_LOCAL_TYPEDEFS
	"-Wno-unused-local-typedefs"
)

# This flag is/will be added in gcc-4.8 and fails with png in C++11 mode
check_compiler_has_flag(
	CXX_FLAGS_STRICT_COMPILATION
	"-Wliteral-suffix"
	HAS_COMPILER_FLAG_WLITERAL_SUFFIX
	"-Wno-literal-suffix"
)

# This removes a lot of warnings from Clang regarding unused -I arguments
check_compiler_has_flag(
	CXX_FLAGS_STRICT_COMPILATION
	"-Qunused-arguments"
	HAS_COMPILER_FLAG_QUNUSED_ARGUMENTS
)


### Set pedantic compiler flags.

set(CXX_FLAGS_PEDANTIC_COMPILATION)
check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Wextra"
	HAS_COMPILER_FLAG_WEXTRA
)

check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Winit-self"
	HAS_COMPILER_FLAG_WINIT_SELF
)

check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Wlogical-op"
	HAS_COMPILER_FLAG_WLOGICAL_OP
)

check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Wmissing-declarations"
	HAS_COMPILER_FLAG_WMISSING_DECLARATIONS
)

check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Wredundant-decls"
	HAS_COMPILER_FLAG_WREDUNDANT_DECLS
)

check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Wctor-dtor-privacy"
	HAS_COMPILER_FLAG_WCTOR_DTOR_PRIVACY
)

check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Wnon-virtual-dtor"
	HAS_COMPILER_FLAG_WNON_VIRTUAL_DTOR
)

check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Wdouble-promotion"
	HAS_COMPILER_FLAG_WDOUBLE_PROMOTION
)

check_compiler_has_flag(
	CXX_FLAGS_PEDANTIC_COMPILATION
	"-Wmismatched-tags"
	HAS_COMPILER_FLAG_WMISMATCHED_TAGS
)


### Set the final compiler flags.

set(COMPILER_FLAGS "${CXX_FLAGS_PROJECT}")
if(ENABLE_STRICT_COMPILATION)
	set(COMPILER_FLAGS "${COMPILER_FLAGS} ${CXX_FLAGS_STRICT_COMPILATION}")
endif(ENABLE_STRICT_COMPILATION)
if(ENABLE_PEDANTIC_COMPILATION)
	set(COMPILER_FLAGS "${COMPILER_FLAGS} ${CXX_FLAGS_PEDANTIC_COMPILATION}")
endif(ENABLE_PEDANTIC_COMPILATION)
set(COMPILER_FLAGS "${COMPILER_FLAGS} ${CXX_FLAGS_USER}")

if(NOT "${CMAKE_CXX_FLAGS}" STREQUAL "${COMPILER_FLAGS}")
	message(STATUS "CMake compiler flags set to »${COMPILER_FLAGS}«")
	set(CMAKE_CXX_FLAGS
		"${COMPILER_FLAGS}"
		CACHE
		STRING
		"Global flags used by the CXX compiler during all builds."
		FORCE
	)
endif(NOT "${CMAKE_CXX_FLAGS}" STREQUAL "${COMPILER_FLAGS}")


##### Subdirectories #####

add_subdirectory(doc)
add_subdirectory(src)
