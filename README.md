# Purdue Robomasters Control Template

This repository is a template for Purdue Robomasters robot projects.

## Repository Initialization Guide
First, use the template by clicking the green "Use this template" button in the top right. Then click the "New Repository" button and initalize your own repository. Then on your computer, run these commands:
```bash
git clone <url-to-your-repo>
cd <folder-you-cloned>
git submodule update --init --recursive
```

## Environment Setup

### Install Tools

**Installed your favorite text editor** 
- **VSCode**: Download VSCode from [here](https://code.visualstudio.com/download).
- **Neovim**: Install Neovim from [here](https://github.com/neovim/neovim#install-from-package)

**Package Manager**
- **Windows**: Install [MSYS2](https://www.msys2.org/).
- **Mac**: Install [homebrew](https://docs.brew.sh/Installation). 
- **Linux**: Use the one that comes with your system (eg. ```apt, dnf/yum, pacman```) 

**Arm GNU Tools and OpenOCD** 

- **Windows**: OpenOCD, arm-none-eabi-gcc, and gdb-multiarch by running these commands in MSYS2 terminal. The default installation path is `C:\msys64`, run `C:\msys64\msys2.exe`.

```powershell
pacman -S mingw-w64-x86_64-make
pacman -S mingw-w64-x86_64-openocd
pacman -S mingw-w64-x86_64-arm-none-eabi-gcc
pacman -S mingw-w64-x86_64-gdb-multiarch
```

> Refer to the [Common Issues](#common-issues) section for local pointer to OpenOCD and GNU toolchain.

- **MacOS**: Run these commands in your terminal.

```zsh
brew install gcc-arm-embedded
brew install openocd
```

- **Linux**: Run these commands in your terminal.

```bash
sudo apt update
sudo apt upgrade
sudo apt install openocd
sudo apt install gcc-arm-none-eabi gdb-arm-none-eabi
```

**Check installation and environment variables**:

- **Windows**: Add `C:\msys64\mingw64\bin` to `PATH`.
- **MacOS/Linux**: Check tool path installation using `which` (eg. `which openocd`). Remember the path for `arm-non-eabi-gdb`, as this will be used to configure the debug extension.

### Set Up VSCode

**Install VSCode extensions**:

- Install the VSCode extension [Cortex-Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug) to enable ARM microcontroller debugging.
- Edit the extension setting .json file.

**Modify Extension settings**: Add GDB path by opening your VSCode `settings.json` in VSCode and add the following to the end of the file. The default installation paths are shown, but you should use the path you found by using `which`.

- **Windows**: `"cortex-debug.gdbPath": "c:/msys64/mingw64/bin/gdb-multiarch.exe"`.
- **MacOS**: `"cortex-debug.gdbPath": "/opt/homebrew/bin/arm-none-eabi-gdb"`.
- **Linux**: `"cortex-debug.gdbPath": "/usr/bin/gdb-multiarch"`.

**[Optional] VSCode IntelliSense Configuration**: Adding this to `c_cpp_properties.json` will link the standard library header files (eg. `stdint.h`, `stdlib.h`, `math.h`).

```
"C_Cpp.default.compilerPath": "C:/msys64/mingw64/bin/arm-none-eabi-gcc.exe"
``` 

### Set Up Neovim

**Install Extensions**:

- Use lazy.nvim, mason, lspconfig, luasnip, and nvim-cmp to install clangd 
- Add conform for formatting
- Configure with compile_commands.json, .clangd, and .clang-format file 

Example config [here](https://github.com/ironic1234/embedded-workflow)

**Debugging**:
Coming soon
