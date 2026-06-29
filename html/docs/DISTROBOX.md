# Using Distrobox for Non-Debian Distributions

If you're using a non-Debian Linux distribution (such as Fedora, Arch, openSUSE, etc.), you can use [Distrobox](https://distrobox.it/) to create a Debian container and follow the standard setup instructions.

## What is Distrobox?

Distrobox is a tool that lets you create and manage containerized Linux environments that integrate seamlessly with your host system. Unlike traditional containers, Distrobox containers share your home directory to allow collaboration with the host system. You can edit the code in your favorite editor and build the project in the container using those same files.

This makes it perfect for development work where you need a specific distribution's tooling.

## Installing Distrobox

### Fedora:
```bash
sudo dnf install distrobox
```

### Arch Linux:
```bash
sudo pacman -S distrobox
```

### openSUSE:
```bash
sudo zypper install distrobox
```

## Setting up the Debian Container

### 1. Create the container

Create a Debian container. It can be named anything but for this example we use `sly1-dev`:

```bash
distrobox create --name sly1-dev --init --image debian:latest --additional-packages "git"
```

This downloads the latest Debian image and creates a new container.

### 2. Enter the container

```bash
distrobox enter sly1-dev
```

The first time you enter, Distrobox will set up the container environment.

### 3. Verify you're in the container

Your terminal prompt should change to indicate you're in the container (typically showing `user@sly1-dev`). You can further verify with:

```bash
cat /etc/os-release
```

Which should show Debian information.

## Following the Setup Instructions

Once inside the container, you can follow the [README instructions](../README.md#-quickstart).

Again, your home directory is shared between the host and container, so you can clone the repository using either.

## Exiting the Container

When you're done working, simply exit the container:

```bash
exit
```

Or press `Ctrl+D`.

## Working with the Container

### Re-entering the container

Whenever you want to build the project, just enter the container again:

```bash
distrobox enter sly1-dev
cd ~/path/to/sly1
```

### Running commands from outside

You can also run commands inside the container without entering it:

```bash
distrobox enter sly1-dev -- ./scripts/build.sh
```

### Stopping the container

Containers are automatically stopped when not in use. To manually stop:

```bash
distrobox stop sly1-dev
```

### Removing the container

If you need to start fresh:

```bash
distrobox rm sly1-dev
```

This deletes the container and any packages installed within it. You will need to complete the setup instructions again if you create a new container.

## Troubleshooting

### Run.sh is not finding PCSX2

If PCSX2 is installed on the host system via package manager the container will not be able to find it. Either exit the container or install PCSX2 in a way the container can access, such as the container package manager, Flatpak or AppImage.
