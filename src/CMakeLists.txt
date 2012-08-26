########## Paths. ##########

include_directories(${CMAKE_SOURCE_DIR}/src/)

include_directories(${GLOG_INCLUDEDIR})

link_directories(${GLOG_LIBDIR})


########## Libraries. ##########

##### Exception. #####

add_library(exception
	SHARED
	lib/exception/exception.cpp
)


########## Modules. ##########


########## Programs. ##########
