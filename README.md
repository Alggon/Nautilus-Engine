# Nautilus Engine ![Tests](https://github.com/Alggon/Nautilus-Engine/actions/workflows/cmake-c++.yml/badge.svg)

2D C++ Game Engine based on an **Entity-Component** architecture.
Personal project focused on research and learning.

## Principles
- **Entity-Component**: Each entity has a `TransformComponent` and can host other components (rendering, physics, gameplay).
- **Modular**: The engine is a shared DLL; the game code resides in a separate DLL, loaded by the editor at runtime.
- **User-created components** from the editor and the IDE, via a component registry (goal: hot reload).
- **Rendering**: SFML, with an interface designed to allow for changing the backend.
- **Editor**: ImGui (planned).
- **Unit-testing module** : Catch2 and CTest.

## Prerequisites
- Windows
- Visual Studio 2022 (minimal) with CMake C++ Tools for Windows
- Git (SFML downloaded directly with CMake via **FetchContent*)

## Compilation
1. Open the project folder with Visual Studio.
2. Let CMake configure the project.
3. **Build* > **Build All*.
4. Set Editor.exe has startup target and run it.

The executables and DLLs are generated in `out/build/x64-Debug/bin/`.
