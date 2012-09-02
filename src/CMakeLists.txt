########## Paths. ##########

include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

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

FLEX_TARGET(compiler_lexer
	modules/compiler/detail/lexer.l
	${CMAKE_CURRENT_BINARY_DIR}/modules/compiler/detail/lexer.cpp
	COMPILE_FLAGS "-P yy_compiler_"
)
BISON_TARGET(compiler_parser
	modules/compiler/detail/parser.y
	${CMAKE_CURRENT_BINARY_DIR}/modules/compiler/detail/parser.cpp
	VERBOSE ${CMAKE_CURRENT_BINARY_DIR}/modules/compiler/detail/parser.log
	COMPILE_FLAGS "-p yy_compiler_"
)
ADD_FLEX_BISON_DEPENDENCY(compiler_lexer compiler_parser)

# Make sure the wanted output directory is created.
# Flex and Bison will not create the output directory and thus fail.
add_custom_target(compiler_mkdir
	COMMAND ${CMAKE_COMMAND} -E
		make_directory ${CMAKE_CURRENT_BINARY_DIR}/modules/compiler/detail
)

set_source_files_properties(
	${BISON_compiler_parser_OUTPUT_HEADER}
	PROPERTIES
		OBJECT_DEPENDS compiler_mkdir
)

add_library(libcompiler
	SHARED
	${FLEX_compiler_lexer_OUTPUTS}
	${BISON_compiler_parser_OUTPUTS}
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
	modules/compiler/detail/symbol/table.cpp
	modules/compiler/detail/symbol/variable.cpp
	# General
	modules/compiler/engine.cpp
	modules/compiler/exception.cpp
)

# The output files of both Flex and Bison have several warnings so disable
# strict compilation for these files.
if(HAS_COMPILER_FLAG_WERROR)
	set_source_files_properties(
		${FLEX_compiler_lexer_OUTPUTS}
		${BISON_compiler_parser_OUTPUTS}
		PROPERTIES COMPILE_FLAGS
			"-Wno-error"
	)
endif(HAS_COMPILER_FLAG_WERROR)

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
