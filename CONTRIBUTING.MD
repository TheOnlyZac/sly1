# Contributing Guide

Welcome to the Sly Cooper Decompilation Project! Please follow this guide to get started contributing.

# Contents
1. [Beginner's Guide](#beginners-guide)
2. [Code Review Process](#code-review-process)
3. [Style Guide](#third-example)

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
* It follows the [style guide](#Style Guide)
* Nothing is copy/pasted directly from Ghidra

If everything looks good, we will merge your pull request as soon as possible. If anything needs to be fixed, we will let you know.


## Style Guide

Our code is modeled after the debug symbols from the [Sly 1 May 2002 demo](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)). 

### Symbol Names

Try and use official names for symbols wherever they are known. Official symbol names use a loose version of [Hungarian Notation](https://en.wikipedia.org/wiki/Hungarian_notation). If the official name for a symbol is not known you should try and mimic that style, which is as follows.

These prefixes denote the **type** of a symbol:
| Prefix | Type                           | Examples                                                       |
|--------|--------------------------------|----------------------------------------------------------------|
| `p`    | Pointer                        | `CLOCK* pclock` - Pointer an instance of the CLOCK struct      |
| `n`    | Integer/numeric value          | `int nScore` - Numeric score value                             |
| `c`    | Integer/count or quantity      | `int ccoin`- A quantity of coins                               |
| `f`    | Flag (boolean)                 | `int fSneakyFeet` - Footstep noises flag                       |
| `l`    | Long                           | `long lSeconds` - Some time in seconds                         |
| `d`    | Float                          |                                                                |
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

### Spacing

* Indent your code with 4 spaces.
* Put a single new line at the end of the file.
* Remove trailing whitespace.

### Function Comments

Each function should have a [Doxygen-style comment](http://micro-os-plus.github.io/develop/doxygen-style-guide/) before it's declaration in the header file.
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

You should note all parameters and return values using @param and @return, even if they are obvious. However, they can be omitted if the function has no parameters or returns void.

### Examples

This code is clear and conforms to the style guide:
```c
// joy.h

/**
 * @brief Activates the Chetkido password cheat code.
 *
 * Decrypts the string "The password is "Chetkido" using a XOR cipher
 * and displays it in the lower-left corner.
 */
void CheatActivateChetkido()


//joy.c

void CheatActivateChetkido()
{
    char cipherSlice[16];
    char* nextXorChar;
    char outBuffer[64];

    const int gameworld = (int)(g_pgsCur->gameworldCur);
    const int worldlevel = (int)(g_pgsCur->worldlevelCur);
    const int completion = FGameCompletion();

   if (((gameworld << 8 | worldlevel) == 0x400) // curr level is snow approach
       && ((completion & 6) == 6) // save file has 100% completion
       && (g_pgsCur->ccoin == 99) // coin count is 99
       && (g_pgsCur->clife == 0)) // lives count is 0
   {
       // Copy encrypted string into cipher 
       std::strncpy(cipherSlice, sChetkidoCiphertext, 16);
       nextXorChar = cipherSlice;
       
	   /* Decrypt the string "@KFWHJGL" resulting in "chetkido"
	    (XOR cipher with key 0x23) */
       if (cipherSlice[0] != 0)
       {
           while (true)
           {
               *nextXorChar = cipherSlice[0] ^ 0x23;
               nextXorChar++;
               if (*nextXorChar == 0) break;
               cipherSlice[0] = *nextXorChar;
           }
       }

    // Write output string to char buffer and show on-screen
    PrepareGuiText(cornerPopupBlot, out_buffer);
    SetBlotDtVisible(cornerPopupBlot, 10.0);
    PpenIfNotAlready(cornerPopupBlot);
}```

This code does **not** conform to the style guide and should be rewritten:
```cpp
uint32_t CBinaryInputStream::U32Read()
{
    byte bVar1;
    byte bVar2;
    byte bVar3;
    byte bVar4;
    byte* pbVar5;

    uint32_t value{};
    if (m_cb < 4)
        Read(4, &value);

    else {
        pbVar5 = m_pb;
        bVar1 = pbVar5[1];
        bVar2 = *pbVar5;
        bVar3 = pbVar5[2];
        bVar4 = pbVar5[3];
        m_cb = m_cb + -4;
        m_pb = pbVar5 + 4;
        value = (uint32_t)bVar2 + (uint32_t)bVar1 * 0x100 + (uint32_t)bVar3 * 0x10000 + (uint32_t)bVar4 * 0x1000000;
    }
    return value;
}
```
