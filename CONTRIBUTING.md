# Contributing

Welcome to the Sly Cooper Decompilation Project! This guide will help you get started with contributing to the project.

# Contents

1. [Beginner's Guide](#beginners-guide)
2. [Writing Tests](#writing-tests)
3. [Code Review Process](#code-review-process)


## Beginner's Guide

If you are new to using Git, follow these steps to get started. If you already familiar with Git, skip to the next section.

### 1. Fork the repository on GitHub

Click the "Fork" button in the top-right corner of the [GitHub repository](https://github.com/theonlyzac/sly1). This will create a copy of the repository on your own GitHub account.

### 2. Clone the forked repository to your machine

Use a terminal or GitHub GUI to clone the forked repo to your machine.

### 3. Create a new branch for your changes

Navigate to the `sly1` directory and run the following command:

`git checkout -b branch-name`

Replace `branch-name` with whatever you want to call your working branch. This will automatically create a new branch and switch to it.

### 4. Write your code

Write your code in the `src/P2` directory. You can use any text editor you like, but we recommend [Visual Studio](https://visualstudio.microsoft.com/downloads/).

#### 4b. Write test cases

If you are adding new code, it is strongly reocmmended that you also write unit tests for it. See the [unit tests section](#writing-tests) for more information.

<!-- #### 4b. Match your code

You can follow the [Code Matching Guide](/tools/README.md) to match your code against the Sly 1 May 2002 Prototype. This will tell you if your code is exactly the same as the original code.

Most of the code in the repository is not yet matching, but we are working on it and in the future we may require that your code matches before it can be merged to the main branch. -->

### 4. Commit the changes to your branch

Whenever you feel you have reached a stop where you would like to save your progress you should commit your changes the working branch. First use `git add <files>` to add files to the commit, then `git commit -m "commit message"` to commit your changes with a message saying what you did.

Use `git status` to see which files you have changed. If a filename is red, it means that the file has been modified, but not added to the commit. If a filename is green, it means that the file has been added to the commit.

### 6. Push the commits to your fork

When you are done committing your changes, you can push your branch to your forked repo. Use `git push origin branch-name` to push your branch to your forked repository.

### 7. Create a pull request on GitHub

When you are have pushed all commits to your fork and are ready to submit your code, create a pull request on GitHub. Go to your forked repository on GitHub and click the "Pull requests" tab. Then click the "New pull request" button. Select your branch from the "compare" dropdown menu and click "Create pull request".


## Writing Tests

Since the process for function matching is not fully set up yet, it is strongly recommended that you write tests for any new code you add to ensure it behaves the same way as the original code. Each test is a program with a main function; the test passes if the program exits with a return code of 0.

To write a new test, create a new source file in the `test` directory under a subdirectory for the system you are testing. For example, if you are testing the `clock` system, create a new source file in `test/clock`. The name of the source file should be the same as the name of the test, e.g. `test/clock/set_clock_rate.cpp`.

You can use the `JtAssert(condition)` macro (from `test/test.h`) to assert that a condition is true. If the condition is false, the test will fail and the test runner will print the file and line number where the assertion failed.

```cpp
JtAssert(1 == 1); // Passes
JtAssert(1 == 2); // Fails
```

<!-- TODO: Add a way to run the tests -->

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

After you create a pull request, a code reviewer will review it before it can be merged into the main branch. We are a volunteer-driven project, so please be patient while we review your code. These are the main things we will look for in your code:

* It compiles and runs without any errors
* It follows the [style guide](/STYLEGUIDE.md), or is at least clean and readible
* Nothing is copy/pasted directly from Ghidra

If everything looks good, we will merge your pull request as soon as possible. If anything needs to be fixed, we will let you know.


## Conclusion

Thank you for reading, and we appreciate any contributions you make to the project!

When in doubt, just try and follow the style of the existing code, and do your best to make your code clean and readable. The project is 100% volunteern-driven, so perfection is not required.

If you have any questions or concerns, feel free to ask in the [Discord server](https://discord.gg/2Y8b8Z2) or [open an issue](https://github.com/TheOnlyZac/sly1/issues/new).
