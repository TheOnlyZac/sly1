/**
 * @file test.h
 *
 * @brief Contains macros for testing and debugging.
*/
#ifndef TEST_H
#define TEST_H

#include <stdexcept>
#include <exception>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Custom assert macro that doesn't call abort
#define JtAssert(assertion) \
{ \
	if (!(assertion)) \
	{ \
		printf( \
			"\nAn assertion failure has occurred\n" \
			"========================================\n" \
			"Assertion: %s\n" \
			"File: %s\nLine %d, in %s\n" \
			"========================================\n\n", \
			#assertion, __FILENAME__, __LINE__, __FUNCTION__); \
		exit(1); \
	} \
}

#endif // TEST_H
