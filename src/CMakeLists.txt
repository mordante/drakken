########## Paths. ##########

include_directories(${CMAKE_SOURCE_DIR}/src/)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${GLOG_INCLUDEDIR})

link_directories(${GLOG_LIBDIR})


########## Libraries. ##########

##### Exception. #####

add_library(exception
	SHARED
	lib/exception/exception.cpp
)


########## Modules. ##########

##### Compiler. #####

# definition xxx
# declaration xxx
# statement xxx
# expression xxx
# value xxx


add_library(libcompiler
	SHARED
	# Nodes
	modules/compiler/detail/node.cpp
	modules/compiler/detail/node/argument_list.cpp
	modules/compiler/detail/node/definition_integer_variable.cpp
	modules/compiler/detail/node/definition_method.cpp
	modules/compiler/detail/node/expression_binary_operation.cpp
	modules/compiler/detail/node/expression_unary_operation.cpp
	modules/compiler/detail/node/identifier.cpp
	modules/compiler/detail/node/node.cpp
	modules/compiler/detail/node/nop.cpp
	modules/compiler/detail/node/program.cpp
	modules/compiler/detail/node/qualified_identifier.cpp
	modules/compiler/detail/node/rvalue_integer.cpp
	modules/compiler/detail/node/rvalue_string.cpp
	modules/compiler/detail/node/rvalue_variable.cpp
	modules/compiler/detail/node/statement_assign.cpp
	modules/compiler/detail/node/statement_list.cpp
	modules/compiler/detail/node/statement_procedure_call.cpp
	modules/compiler/detail/node/value.cpp
	# Symbol table
	modules/compiler/detail/symbol/named_scope.cpp
	modules/compiler/detail/symbol/procedure.cpp
	modules/compiler/detail/symbol/variable.cpp
	# General
	modules/compiler/exception.cpp
)

target_link_libraries(libcompiler
	exception
	${GLOG_LIBRARIES}
)

########## Programs. ##########

add_executable(drakken
	drakken/drakken.cpp
)

target_link_libraries(drakken
	${GLOG_LIBRARIES}
)
