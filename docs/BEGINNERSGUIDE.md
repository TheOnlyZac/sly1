# Beginner's Guide

If you are new to using Git, follow these steps to get started. If you already familiar with Git, go ahead and read the [contributing guide](/docs/CONTRIBUTING.md) instead.

**1. Fork the repository on GitHub**

Click the "Fork" button in the top-right corner of the [GitHub repository](https://github.com/theonlyzac/sly1). This will create a copy of the repository on your own GitHub account.

**2. Clone the forked repository to your machine**

Use a terminal or GitHub GUI to clone the forked repo to your machine.

**3. Create a new branch for your changes**

Navigate to the `sly1` directory and run the following command:

```sh
git checkout -b branch-name
```

Replace `branch-name` with whatever you want to call your working branch. This will automatically create a new branch and switch to it.

**4. Write your code**

Write your code in the `src/P2` directory. You can use any text editor you like, but we recommend [Visual Studio](https://visualstudio.microsoft.com/downloads/).

**4b. Write test cases**

If you are adding new code, it is strongly recommended that you also write unit tests for it. See the [contributing guide](/docs/CONTRIBUTING.md#writing-tests) for more information.

**4c. Match your code**

You can follow the [Code Matching Guide](/tools/codematcher/README.md) to match your code against the Sly 1 May 2002 Prototype. This will tell you if your code is exactly the same as the original code. This is not perfect because the prototype is not the same as the final release, but it is still a good way to make sure your code is correct.

**5. Commit the changes to your branch**

Whenever you feel you have reached a point where you would like to save your progress, you should *commit* your changes the working branch with the following command.

```sh
git commit -am "What you did"
```

If you only want to commit certain files, first add the them to the commit with `git add <files>`, then commit with `git commit -m "What you did"`.

Use `git status` to see which files you've changed. If a file is red, it means that the file has been modified, but not added to the commit. If a filename is green, it means that the file has been added to the commit.

**6. Push the commits to your fork**

When you are done making commits, push your branch to your forked repo. Use `git push origin branch-name` to push your branch to your forked repository.

**7. Create a pull request on GitHub**

When you are have pushed all commits to your fork and are ready to submit your code, create a pull request on GitHub. Go to your forked repository on GitHub and click the "Pull requests" tab. Then click the "New pull request" button. Select your branch from the "compare" dropdown menu and click "Create pull request".
