# Contributing

Welcome to the **Sly Cooper Decompilation Project**! This guide will help you start contributing to the project. We are a volunteer-driven project, so we appreciate any contributions you make.

# Contents

1. [Getting Started](#getting-started)
2. [Function Matching](#function-matching)
3. [Writing Tests](#writing-tests)
4. [Code Review Process](#code-review-process)
5. [Conclusion](#conclusion)


## Getting Started

If you have never used Git before, follow the steps in the [Beginner's Guide](/docs/BEGINNERSGUIDE.md) to learn how to fork the repo, make changes, and submit a pull request. If you are already familiar with Git, go ahead and read the rest of this guide instead.

For instructions on how to build and run the project, see the [README](/README.md).


## Function Matching

The goal of this project is to match the original code as closely as possible. This means writing code that compiles to the same assembly as the original code, or at least has identical behavior at runtime.

We use [CodeMatcher](https://github.com/felinis/CodeMatcher) to match our code against the original code. CodeMatcher can compile and match the entire source tree or just one file at a time. Matching against the release elf is not fully set up yet, so for now we are matching against the [May 19 2002 prototype](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)). For instructions on using CodeMatcher, see the [Code Matching Guide](/tools/codematcher/README.md).

If you are adding new code, it is strongly recommended that you run CodeMatcher before submitting a pull request. We will accept pull requests that don't match as long as the code is clean and readable, but in the future we may require that your code matches before merging it into the main branch.


## Writing Tests

Since the process for matching against the release elf is not fully set up yet, we recommended that you write tests for any new code you add to ensure it behaves the same way as the original code. Each test is a program with a main function; The test passes if the program runs successfuly without any errors.

To write a new test, create a new source file in the `test` directory under a subdirectory for the system you are testing. For example, if you are testing the `clock` system, create a new source file in `test/clock`. The name of the source file should be the same as the name of the test, e.g. `test/clock/set_clock_rate.cpp`.

You can use the `JtAssert(condition)` macro (from `test/test.h`) to assert that a condition is true. If the condition is false, the test will fail and the test runner will print the file and line number where the assertion failed.

```cpp
JtAssert(1 == 1); // Passes
JtAssert(1 == 2); // Fails
```

<!-- ### Running tests

TODO: Add a way to compile and run the tests -->

### Example Test

**test/clock/set_clock_rate.cpp**
```
#include <clock.h>
#include <test/test.h>

int main()
{
	SetClockRate(1.0);
	JtAssert(g_rtClock == 1.0f);
	JtAssert(g_clock.fEnabled);

	SetClockRate(0.5);
	JtAssert(g_rtClock == 0.5f);
	JtAssert(g_clock.fEnabled);

	SetClockRate(0);
	JtAssert(g_rtClock == 0.f);
	JtAssert(!g_clock.fEnabled);

	SetClockRate(-1);
	JtAssert(g_rtClock == -1.f);
	JtAssert(!g_clock.fEnabled);

	return 0;
}
```


## Code Review Process

Once you create a pull request, a code reviewer will need to approve it before it can be merged into the main branch. We are a volunteer-driven project, so please be patient while we review your code. These are the main things we will look for in your code:

* It compiles and runs without any errors.
* It follows the [style guide](/docs/STYLEGUIDE.md), or is at least clean and readible.
* Nothing is copy/pasted directly from Ghidra.

If everything looks good, we will merge your pull request as soon as possible. If anything needs to be fixed, we will let you know.


## Conclusion

Thank you for reading, and we appreciate any contributions you make to the project!

When in doubt, just try and follow the style of the existing code, and do your best to write clean and readable code. The project is 100% volunteern-driven, so perfection is not required. The most important thing is to have fun and learn something new about the game!

If you have any questions or concerns, feel free to ask in the [Discord server](https://discord.gg/2Y8b8Z2) or [open an issue](https://github.com/TheOnlyZac/sly1/issues/new) on GitHub.
