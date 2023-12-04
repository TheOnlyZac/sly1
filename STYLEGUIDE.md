# Style Guide

## Contents

1. [General Rules](#general-rules)
2. [Symbol Names](#symbol-names)
3. [Documentation](#documentation)
4. [Example Code](#example-code)


## General Rules

Please try and follow these general rules when writing your code:

* Indent with 4 spaces, not tabs.
* Put opening curly braces on a new line.
* Don't leave trailing whitespace at the end of lines.
* End every file with a single blank line.

## Symbol Names

For variables/symbols, use the official name from the [Sly 1 May 2002 demo](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)) if it is known. If it is not known, use a clear and descriptive name.

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


## Documentation

Comment your code with [Doxygen-style comments](http://micro-os-plus.github.io/develop/doxygen-style-guide/). They will be used to automatically generate [documentation](https://theonlyzac.github.io/sly1). You don't need to read the whole Doxygen style guide, just follow these rules.

### File Comments

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

### Function Comments

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

#### Class Comments

Put class (and struct) comments before the class declaration in the header file.
```c
/**
 * @brief Full name of the struct/class.
 *
 * A longer summary of the struct/class that goes into more detail
 * if you feel it is necessary.
 */
```

### Todo and Notes

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
