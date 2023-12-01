# Contributing

Welcome to the Sly Cooper Decompilation Project! Please follow this guide to get started contributing.

# Contents
1. [Beginner's Guide](#beginners-guide)
2. [Code Review Process](#code-review-process)
3. [Style Guide](#style-guide)
4. [Code Examples](#code-examples)
5. [Writing Tests](#writing-tests)

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

Write your code in the `src` directory. You can use any text editor you like, but we recommend [Visual Studio](https://visualstudio.microsoft.com/downloads/).

#### 4b. Write test cases

If you are adding new code, it is strongly reocmmended that you also write unit tests for it. Unit tests use CTest and are located in the `test` directory. See the [unit tests section](#writing-tests) for more information.

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


## Code Review Process

After you create a pull request, a code reviewer will reviwer it before it can be merged into the main branch. We are a volunteer-driven project, so please be patient while we review your code. These are the main things we will look for in your code:

* It compiles and runs without any errors
* It follows the [style guide](#style-guide), or is at least clean and readble
* Nothing is copy/pasted directly from Ghidra

If everything looks good, we will merge your pull request as soon as possible. If anything needs to be fixed, we will let you know.


## Style Guide

### Formatting

Please try and follow these general rules when writing your code:

* Indent with 4 spaces, not tabs.
* Put opening curly braces on a new line.
* Don't leave trailing whitespace at the end of lines.
* End every file with a single blank line.

### Symbol Names

For variables/symbols, use the official name from the [Sly 1 May 2002 demo](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)) if it is known. If it is not known, use clear and descriptive name.

When naming symbols, mimic the style of the official symbol names, Official names use a loose version of [Hungarian Notation](https://en.wikipedia.org/wiki/Hungarian_notation). The most important part is the prefixes used to denote the **type** and **scope** of a symbol, as shown below.

These prefixes denote the **type** of a symbol:

| Prefix | Type                           | Examples                                                       |
|--------|--------------------------------|----------------------------------------------------------------|
| `p`    | Pointer                        | `CLOCK* pclock` - Pointer an instance of the CLOCK struct      |
| `n`    | Integer/numeric value          | `int nScore` - Numeric score value                             |
| `c`    | Integer/count or quantity      | `int ccoin`- A quantity of coins                               |
| `f`    | Flag (boolean)                 | `int fSneakyFeet` - Footstep noises flag                       |
| `l`    | Long                           | `long lTime` - A time in seconds                               |
| `d`    | Float                          | `float dTime` - A time in seconds                              |
| `ch`   | Char                           | `char chCur` - Current character in a loop                     |
| `b`    | Byte                           | `byte bData` - A single byte of data                           |
| `u`    | Unsigned                       | `float uSuck` - Unsigned value representing the player's suck score |
| `z`    | Zero-terminated string         | `char chzBuffer[64]` - Zero-terminated string buffer           |
| `C`    | Class                          | `class CBinaryInputStream` - Class that reads data from binary streams |

These prefixes denote the **scope** of a variable:

| Prefix | Type                           | Examples                                                       |
|--------|--------------------------------|----------------------------------------------------------------|
| `g_`   | Global variable                | `LM g_lmZeroOne` - A global LM struct                          |
| `m_`   | Class member                   | `int m_cbRaw` - Count of raw bytes on a CBinaryInputStream     |
| `s_`   | Static class member            | `TICK s_tickLastRaw` - Static value for last raw tick on CLOCK struct |

Examples of combining these prefixes:
* `g_pgsCur` - Pointer to the current global GS struct
* `g_pchzArgs` - Pointer a global zero-terminated char array of arguments
* `m_cbBulkData` - Class member variable that stores the count of bytes in a data block

### Capitalization

Use `ALLCAPS` for struct/enum names.
* e.g. `struct DIFFICULTY`, `enum FLS`

Use `UpperCamelCase` for function names, classes and enum values.
* e.g. `void OnDifficultyGameLoad()`, `class CBinaryInputStream`, `FCHT_InfiniteCharms`

Use `lowerCamelCase` for local variables, function parameters, and class members.
* e.g. `char nextXorChar`, `Coin* pcoin`, `float m_rxScale`

### Comments

Please comment your code with [Doxygen-style comments](http://micro-os-plus.github.io/develop/doxygen-style-guide/). They will be used to automatically generate [documentation](https://theonlyzac.github.io/sly1). You don't need to read the whole style guide, just follow these rules.

#### File Comments

Put file comments at the top of each file, before any includes.
```c
/**
 * @file filename.xyz
 * @brief A brief description of the file.
 *
 * A longer description of the file that goes into more detail
 * if you feel it is necessary.
 */
```

#### Function Comments

Put function comments before the declaration of each function in the header files.
```c
/**
 * @brief A brief summary of the function.
 *
 * A longer summary of the function that goes into more detail
 * if you feel it is necessary.
 *
 * @param param1 Description of the first parameter
 * @param param2 Description of the second parameter
 * ...
 *
 * @return What the function returns, if not void
 */
int ExampleFunction(param1, param2 ...);
```

Document all parameters and return values using `@param` and `@return`/`@retval`, even if they are obvious. You can omit them if the function has no parameters or returns void.

#### Structs/Classes

Put the struct/class comment before it's declaration in the header file.
```c
/**
 * @brief Full name of the struct/class.
 *
 * A longer summary of the struct/class that goes into more detail
 * if you feel it is necessary.
 */
```

#### Todo and Notes

Use `@todo` to mark something that needs to be done in the future.
```c
/**
 * ...
 * @todo Implement this function.
 * ...
 */
```

Use `@note` to add a note which will be differentiated form the rest of the comment.
```
/**
 * ...
 * @note The name of this struct is not official.
 * ...
 */
```


## Example Code

This code is clear and conforms to the style guide:
```c
// joy.h

/**
 * @brief Activates a cheat code.
 *
 * Sets the given flag on the global fcht variable. Also reloads the level if
 * is is a reload code.
 *
 * @param nparam Cheat code to check
*/
void AddFcht(int nParam);


//joy.cpp

void AddFcht(int nParam)
{
    g_grfcht |= nParam & ~(int)FCHT_ResetWorld;

    // Check if reload flag is set
    if ((nParam & 0x4000) != 0)
    {
        ResetWorld(FTRANS::None);
    }
}
```

This code does **not** conform to the style guide and should be rewritten:
```cpp
// vec.h

// Sets the vector cylinderically
void SetVectorCylind(float x, float y, float z, VECTOR* pvec);


// vec.cpp
void SetVectorCylind(float param_1, float param_2, float param_3, VECTOR* param_4)
{
    float local_40;
    float local_3c;

    //CalculateSinCos(param_1, &local_40, (float*)((uint32_t)&local_40 | 4));
    param_4->z = param_3;
    param_4->x = local_3c * param_2;
    param_4->y = local_40 * param_2;
    return;
}
```

## Unit Tests

Since we do not yet have a process for function matching, it is strongly recommended that you write tests for any new code you add to ensure it behaves the same way as the original code.

Unit tests are implemented using CTest. Each test is a program with a main function; the test passes if the program exits with a return code of 0.

### Write the test

To write a new test, create a new source file in the `test` directory under a subdirectory for the system you are testing. For example, if you are testing the `clock` system, create a new source file in `test/clock`. The name of the source file should be the same as the name of the test, e.g. `test/clock/set_clock_rate.cpp`.

You can use the `JtAssert(condition)` macro (from `test/test.h`) to assert that a condition is true. If the condition is false, the test will fail and the test runner will print the file and line number where the assertion failed.

```cpp
JtAssert(1 == 1); // Passes
JtAssert(1 == 2); // Fails
```

### Add the test to CMake

After writing the test, create or edit the `CMakeLists.txt` in the subdirectory for the system you are testing to call the `add_unit_test` command as follows:

```cmake
add_unit_test(PARALLEL TRUE NAME system.test_name SOURCES test_name.cpp LIBS ${P2_LIB_TARGET})
```

- `system` should be the same as the name of the directory where you are adding the test.
- `test_name` should be a unique name for the test which is the same as the source file containing the test.
- `PARALLEL` specifies whether the test can be run in parallel with other tests. If `TRUE`, the test will be run in parallel with other tests. If `FALSE`, the test will be run in serial with other tests.

### Run the tests

The test runner is a program called `check` which runs each test and reports the results. It is built automatically when you build the `check` target.

## Example Test

### test/clock/set_clock_rate.cpp
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

### test/clock/CMakeLists.txt
```
add_unit_test(PARALLEL TRUE NAME clock.set_clock_rate SOURCES set_clock_rate.cpp LIBS ${P2_LIB_TARGET})
``````
