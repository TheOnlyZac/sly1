# How to Contribute

## Overview

1. Fork the repository on GitHub
2. Clone the forked repository to your local machine
3. Create a new branch for your changes
4. Write your code
5. Commit your changes to your branch
6. Push your branch to your forked repository
7. Create a pull request on GitHub

## Step-by-step

### 1. Fork the repository on GitHub

Click the "Fork" button in the top-right corner of the [GitHub repository](https://github.com/theonlyzac/sly1). This will create a copy of the repository in your own GitHub account.

### 2. Clone the forked repository to your local machine

Open a terminal and navigate to the directory where you want to clone the repository. Then, run the following command:

`git clone https://github.com/theonlyzac/sly1.git`

This will create a new directory called `sly1` in your current directory. This directory will contain the Sly 1 source code.

### 3. Create a new branch for your changes

Navigate to the `sly1` directory and run the following command:

`git checkout -b my-branch-name`

This will create a new branch called `my-branch-name` and switch to it.

### 4. Write your code

Write your code in the `src` directory. You can use any text editor you like, but we recommend [Visual Studio](https://visualstudio.microsoft.com/downloads/).

#### 4b. Match your code

You can follow the [Code Matching Guide](/tools/README.md) to match your code against the Sly 1 May 2002 Prototype. This will tell you if your code is exactly the same as the original code.

Most of the code in the repository is not yet matching, but we are working on it and in the future we may require that your code matches before it can be merged to the main branch.

### 5. Commit your changes to your branch

When you are done writing your code, you can commit your changes to your branch. Use `git add <files>` to add files to the commit, and `git commit -m "commit message"` to commit your changes. You can also use `git commit -am <message>` to add and commit all changes at once.

Use `git status` to see which files you have changed. If a filename is red, it means that the file has been modified, but not added to the commit. If a filename is green, it means that the file has been added to the commit.

### 6. Push your branch to your forked repository

When you are done committing your changes, you can push your branch to your forked repository. Use `git push origin my-branch-name` to push your branch to your forked repository.

### 7. Create a pull request on GitHub

When you are all done writing code and everything is pushed to your branch to your forked repository, you can create a pull request on GitHub. Navigate to your forked repository on GitHub and click the "Pull requests" tab. Then, click the "New pull request" button. Select your branch from the "compare" dropdown menu and click "Create pull request".

Please be patient while we review your code. If everything looks good, we will try to merge your pull request as soon as possible. If anything needs to be changed, we will let you know.

## Style Guide

### General rules

Our code is modeled after the debug symbols from the [May 2002 demo](https://hiddenpalace.org/Sly_Cooper_and_the_Thievius_Raccoonus_(May_19,_2002_prototype)). Please try to follow these guidelines when writing your code:
* Use official names wherever possible.
* Indent with 4 spaces.
* If you must use standard library includes, put them after project includes.

### Symbol Names

For the most part, variables are named according to [Hungarian Notation](https://en.wikipedia.org/wiki/Hungarian_notation). The following prefixes are used to denote the type of a variable/symbol:
* `p` - Pointer
* `n` - Integer/number
* `c` - Integer/count of items
* `f` - Boolean/flag
* `l` - Long
* `d` - Float
* `u` - Unsigned
* `b` - Byte
* `ch` - Char
* `z` - Zero-terminated string
* `C` - Class name

The following prefixes are used to denote the scope of a variable:
* `g_` - Global variable
* `m_` - Class member
* `s_` - Static class member

Here are some examples of symbol names that combine the above prefixes:
* `ccoin`, `clife`, `ccharm` - Count of coins, lives, and charms
* `fSneakyFeet` - Flag that denotes whether Sly's footsteps make guitar noises
* `g_pgsCur` - Global pointer to the game's current GS struct
* `g_pchzArgs` - Global pointer to a zero-terminated char array of arguments
* `CBinaryInputStream` - Name of the class that handles reading data from binary streams
* `m_cbBulkData` - Member variable that stores the count of bytes in a data block

### Capitalization

Please try to stick to the following capitalization schemes:
* Use `ALLCAPS` for struct/enum names.
    * eg. `struct DIFFICULTY`, `enum class FLS`
* Use `UpperCamelCase` for function/class names and enum values.
    * eg. `void OnDifficultyGameLoad()`, `class CTransition`, `FCHT::InfiniteCharms`
* Use `lowerCamelCase` for local variables, function parameters, and class members.
    * eg. `char nextXorChar`, `Coin* pcoin`, `float m_rxScale`
