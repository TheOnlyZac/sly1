macro(add_unit_test)
	set(options PARALLEL)
	set(oneValueArgs NAME)
	set(multiValueArgs SOURCES LIBS)
	cmake_parse_arguments(TEST "${options}" "${oneValueArgs}"
								"${multiValueArgs}" ${ARGN})
	message(STATUS "Generating Test ${TEST_NAME}... (${TEST_SOURCES})")
	add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCES})
	target_link_libraries(${TEST_NAME} ${TEST_LIBS})
	if(TEST_PARALLEL AND HAVE_MPI)
		set(TESTCOMMAND ${MPIEXEC})
		set(TESTARGS ${MPIEXEC_NUMPROC_FLAG} 3 ${MPIEXEC_PREFLAGS}
					"./${TEST_NAME}" ${MPIEXEC_POSTFLAGS})
		set(TESTCOMMAND ${TESTCOMMAND} ${TESTARGS})
	else()
		set(TESTCOMMAND ${TEST_NAME})
	endif()
	add_test(NAME ${TEST_NAME}
			WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
			COMMAND ${TESTCOMMAND})

		get_property(TESTNAMES GLOBAL PROPERTY TESTNAMES)
		set_property(GLOBAL PROPERTY TESTNAMES ${TESTNAMES} ${TEST_NAME})
endmacro(add_unit_test)
