# Sly Cooper Decompilation Docs

This branch contains the documentation for the Sly Cooper decompilation. The docs are generated automatically from the codebase using [Doxygen](https://www.doxygen.nl/index.html). It is hosted on GitHub Pages at [theonlyzac.github.io/sly1](https://theonlyzac.github.io/sly1/).

## Generating docs

Clone the repo and install dependencies.

```bash
sudo apt-get install doxygen graphviz
```

Then run `generate.sh`. It will generate the documentation in the `html` directory. Note that the script strips `#include "common.h"` from all header files before generating the docs to make the include graphs less cluttered.

## Previewing docs

You can open `html/index.html` directly in your browser, or host it using node.js/express as follows.

```bash
npm install
npm start
```

## Contributing

If you find any errors in the documentation, please [open an issue](https://github.com/theonlyzac/sly1/issues/new) or make a pull request.

If you are making a pull request to update the documentation files on this branch, don't forget to `git add` the `html` directory before pushing.
