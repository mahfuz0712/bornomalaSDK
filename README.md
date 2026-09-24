# Bornomala SDK

**Build native applications for BornomalaOS using C.**

Bornomala SDK is the official development kit for creating **`.mmr` applications** and packaging them into **`.bsa` installers** for BornomalaOS.

## Features

- Create new projects with one command.
- Build native `.mmr` applications.
- Package apps into `.bsa` installers.
- Automatic project generation.
- SDK installed globally.
- Linux & WSL development support.
- Future BornomalaOS VM support (`bsa run`).

---

## Project Structure

```text
BornomalaSDK/
├── bin/
│   └── bsa
├── sdk/
│   ├── include/
│   ├── linker/
│   └── lib/
├── templates/
├── src/
├── Makefile
└── install.sh
```

After installation:

```text
/usr/local/bin/bsa
/opt/BornomalaSDK/
    sdk/
    templates/
```

Your app projects remain completely independent from the SDK.

Example:

```text
MyApp/
├── src/
├── Manifest.json
├── build/
└── dist/
```

---

## Requirements

### Ubuntu / Debian / WSL

Install required tools.

```bash
sudo apt update

sudo apt install -y \
build-essential \
gcc-x86-64-linux-gnu \
zip \
nasm \
qemu-system-x86
```

Verify:

```bash
gcc --version
x86_64-linux-gnu-gcc --version
```

---

## Installation

Clone the SDK.

```bash
git clone https://github.com/mahfuz0712/BornomalaSDK.git
cd BornomalaSDK
```

Build the CLI.

```bash
make
```

Install globally.

```bash
chmod +x install.sh
./install.sh
```

Verify installation.

```bash
bsa doctor
```

Example output:

```text
=====================================
      Bornomala SDK Doctor
=====================================

GCC                 ✓ Found
Cross GCC           ✓ Found
NASM                ✓ Found
ZIP                 ✓ Found
QEMU                ✓ Found

Preferred Compiler: x86_64-linux-gnu-gcc
```

---

## Create Your First App

Create a new project.

```bash
bsa create HelloWorld
```

Open it.

```bash
cd HelloWorld
```

Generated structure:

```text
HelloWorld/
├── src/
│   ├── main.c
│   ├── app.c
│   ├── ui.c
│   ├── file.c
│   ├── include/
│   └── resources/
├── Manifest.json
└── .gitignore
```

---

## Build

Compile the project.

```bash
bsa build
```

Output:

```text
dist/HelloWorld.mmr
```

---

## Package

Create a Bornomala installer.

```bash
bsa pack
```

Output:

```text
dist/HelloWorld.bsa
```

---

## Manifest

Each project contains a `Manifest.json`.

Example:

```json
{
  "name": "HelloWorld",
  "package": "com.bornomala.helloworld",
  "version": "1.0.0",
  "author": "Unknown",
  "entry": "HelloWorld.mmr",
  "permissions": []
}
```

The SDK automatically reads this file during build and packaging.

---

## Example App

`src/main.c`

```c
#include <mmr.h>
#include <window.h>

int mmr_main(void)
{
    BOS_Window *window =
        bos_window_create(
            900,
            600,
            "Hello World");

    bos_window_show(window);

    return 0;
}
```

---

## SDK API

Current headers:

```text
bos.h
window.h
fs.h
clipboard.h
dialog.h
ui.h
mmr.h
```

Example:

```c
bos_window_create(900,600,"App");
bos_window_show(window);
bos_exit(0);
```

---

## BSA Workflow

```text
bsa create MyApp

↓

Edit source code

↓

bsa build

↓

MyApp.mmr

↓

bsa pack

↓

MyApp.bsa
```

---

## Planned Features

- `bsa run` (BornomalaOS VM preview)
- Incremental builds
- Parallel compilation
- Native ZIP implementation
- Driver SDK
- Service application template
- GUI application template
- Debugger
- Package manager

---

## BornomalaOS Runtime

The SDK only builds applications.

The operating system is responsible for:

- `.mmr` execution
- Process creation
- Memory mapping
- Window management
- `.bsa` installation
- File associations

User experience inside BornomalaOS:

- Double-click **`.mmr`** → Launch application.
- Double-click **`.bsa`** → Android-style installation dialog.

---

## Contributing

Contributions are welcome.

Please keep the SDK:

- clean
- lightweight
- platform-independent
- backward-compatible with the BornomalaOS application ABI.

---

## License

This project is currently under active development.