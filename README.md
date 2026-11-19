# Swipeboxing
Simple game based off the shadowboxing trend. Created in C++ with Raylib

## Build and run

Install a C++14 compiler, GNU Make, and Raylib 5.0 or newer (including its
development headers and libraries). On Linux, also install the OpenGL and X11
development libraries required by your Raylib build.

From the project root, build and run with:

```sh
make
./NextWorld
```

In VS Code, select **Debug** to build a debug version with F5, or **Run** to
build and launch a release version without debugging. Both configurations use
the project root as the working directory so the `resources/` assets can be
found. The debug and release builds have separate executable names so switching
between them does not reuse a binary built with the other mode.

Install the recommended **C/C++** extension (`ms-vscode.cpptools`) when VS Code
prompts you, or install it from Extensions before launching. It provides the
`cppdbg` debugger used by the Run and Debug configurations.

On Windows, the build tasks expect the Raylib distribution and MinGW toolchain
at `C:/raylib/raylib` and `C:/raylib/w64devkit/bin`. Update those paths in
`.vscode/tasks.json` if your installation is elsewhere.
