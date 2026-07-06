# Build- und Run-Befehle (Windows, VS Code, CMake)

> Wechseln Sie in den jeweiligen Ordner (z. B. `8_Test_Driven_Development/81_Motivation`) und führen Sie die Befehle in einer PowerShell aus.

## Variante 1: Ninja

### Einmalig konfigurieren und bauen

```powershell
cmake -S . -B build-ninja -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build-ninja
ctest --test-dir build-ninja --output-on-failure
echo 5 | .\build-ninja\facultyCalulator.exe
```

### Alltag

```powershell
cmake --build build-ninja
ctest --test-dir build-ninja --output-on-failure
```

### Sauber neu konfigurieren

```powershell
Remove-Item -Recurse -Force .\build-ninja
cmake -S . -B build-ninja -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build-ninja
ctest --test-dir build-ninja --output-on-failure
```

## Variante 2: MinGW Makefiles (mit mingw32-make)

### Einmalig konfigurieren und bauen

```powershell
cmake -S . -B build-mingw -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build-mingw
ctest --test-dir build-mingw --output-on-failure
echo 5 | .\build-mingw\facultyCalulator.exe
```

### Alltag

```powershell
cmake --build build-mingw
ctest --test-dir build-mingw --output-on-failure
```

### Sauber neu konfigurieren

```powershell
Remove-Item -Recurse -Force .\build-mingw
cmake -S . -B build-mingw -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build-mingw
ctest --test-dir build-mingw --output-on-failure
```

## Variante 3: MSYS Makefiles (mit make)

Hinweis: Diese Variante funktioniert am zuverlässigsten in einer MSYS2-Shell. In PowerShell kann sie ebenfalls laufen, ist aber je nach Umgebungsvariablen empfindlicher.

### Einmalig konfigurieren und bauen

```powershell
cmake -S . -B build-msys -G "MSYS Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build-msys
ctest --test-dir build-msys --output-on-failure
echo 5 | .\build-msys\facultyCalulator.exe
```

### Alltag

```powershell
cmake --build build-msys
ctest --test-dir build-msys --output-on-failure
```

### Sauber neu konfigurieren

```powershell
Remove-Item -Recurse -Force .\build-msys
cmake -S . -B build-msys -G "MSYS Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build-msys
ctest --test-dir build-msys --output-on-failure
```

## VS Code Command Palette

1. CMake: Select a Kit
2. CMake: Configure
3. CMake: Build
4. CMake: Run Tests
