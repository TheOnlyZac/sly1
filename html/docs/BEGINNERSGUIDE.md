# Beginner's Guide

If you are new to using Git, follow these steps to get started. If you already familiar with Git, go ahead and read the [contributing guide](/docs/CONTRIBUTING.md) instead.

**1. Fork the repository on GitHub**

Click the "Fork" button in the top-right corner of the [GitHub repository](https://github.com/theonlyzac/sly1). This will create a copy of the repository on your own GitHub account.

**2. Clone the forked repository to your machine**

Use a terminal or GitHub GUI to clone the forked repo to your machine.

**3. Create a new branch for your changes**

Navigate to the `sly1` directory in the terminal, and run the following command:

```sh
git checkout -b branch-name
```

Replace `branch-name` with whatever you want to call your working branch. This will automatically create a new branch and switch to it.

**4. Write & match your code**

Follow the [Contributing Guide](/docs/CONTRIBUTING.md) to find functions to match, and write your code. You can use any text editor you like, but we recommend [VS Code](https://code.visualstudio.com/).

**5. Commit the changes to your branch**

Whenever you would like to save your progress to the fork, use these commands to add the files to a commit with a message describing what you did:

```sh
git add file_you_changed.txt
git commit -m "Describe what you did here"
```

If you don't care about adding specific files and just want to commit every file you changed, you can use this command instead:

```sh
git commit -am "Describe what you did here"
```

The commits are not backed up to GitHub until you `git push` to the repo in the next step.

**6. Push the commits to your fork**

When you are done making commits, push your branch to your forked repo.

```sh
git push origin branch-name
````

**7. Create a pull request on GitHub**

When you are have pushed all commits to your fork and are ready to submit your code, create a pull request on GitHub.
1. Go to your forked repository on GitHub and click the "Pull requests" tab.
2. Click the "New pull request" button.3
3. Select your branch from the "compare" dropdown menu.
4. Click "Create pull request".
6. Add a title and brief description stating what you did for the person reviewing it.


**8. Wait for someone to review your code**

A code reviewer will review your PR and either merge it into the main branch, or let you know if there are any issues that need be addressed. If you need to fix something, any commits you push to the same branch will be automatically added to the pull request until it is merged, at which point you will have to make another pull request if you continue working.
