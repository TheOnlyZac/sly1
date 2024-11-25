# Scripts

This directory contains the following scripts used to setup and build the project.
- `build.sh`
- `check_progress.sh`
- `quickstart.sh`
- `setup_progd_linux.sh`

There are a few others, but they are not used in the normal contributing workflow.

## build.sh

Runs a clean reconfigure (deletes build files and splits the binary), then builds the project. Will warn you if `disc/SCUS_971.98` is not present.

## check_progress.sh

Checks the progress of the project by comparing the number of bytes in the original game binary to the number of bytes that have been matched. The output will be in this format:

```
Category                    : DecompedSize /    Total   OfFolder%  (             OfTotal%)
all                         :        10516 /  1143680     0.9195%  (  0.9195% / 100.0000%)

sce                         :            0 /   116164     0.0000%  (  0.0000% /  10.1570%)
P2                          :        10516 /  1005644     1.0457%  (  0.9195% /  87.9305%)
data                        :            0 /    21872     0.0000%  (  0.0000% /   1.9124%)
```

The value that we consider the progress of the project is row "`P2`", column "`OfFolder%`". This is the percentage of the game engine code that has been matched.

## quickstart.sh

Installs the necessary dependencies using pip/apt and sets up the build environment. You only need to run this script once.

## setup_progd_linux.sh

Installs the compiler needed to build the project on Linux. `quickstart.h` will run this script for you, so you don't need to run both.

There is a similar script for Windows, but the compiler
