# CTest + `gtest_discover_tests`: Wie Tests registriert werden

## 1) Beim Kompilieren
- `TEST(SuiteName, TestName)` in `test_main.cpp` erzeugt intern GoogleTest-Metadaten.
- Diese Metadaten landen im Test-Binary (z. B. `facultyCalulatorTest.exe`).

## 2) In CMake
- `enable_testing()` aktiviert CTest-Unterstützung.
- `add_executable(...Test ...)` baut das Testprogramm.
- `target_link_libraries(... GTest::gtest_main)` liefert `main()` + GTest-Runtime.
- `include(GoogleTest)` lädt CMake-Hilfen für GoogleTest.
- `gtest_discover_tests(<TestTarget>)` aktiviert automatische Test-Discovery.

## 3) Bei `cmake --build ...`
- CMake erzeugt ein Discovery-Skript.
- Das Skript führt das Test-Binary mit `--gtest_list_tests` aus.
- GoogleTest gibt alle `TEST(...)`-Fälle aus (Suite + Name).
- CMake schreibt daraus CTest-Einträge (**ein CTest-Test pro `TEST(...)`**).

## 4) Bei `ctest ...`
- CTest liest die registrierten Einträge (bei dir: 4).
- CTest startet jeden Eintrag separat, typischerweise mit `--gtest_filter=<Suite.Test>`.
- Deshalb siehst du z. B.:

```text
Start 1: FactorialTest.HandlesPositiveInputs
...
Start 4: FactorialTest.HandlesNegativeInputs
```

## 5) Tests registrieren
- Tests werden über die `TEST(...)`-Makros in den Testquellen registriert.
- GoogleTest registriert jeden `TEST(...)`-Fall beim Start des Testprogramms.
- Die Registrierung erfolgt über statische Initialisierung (C++-Konstruktoren).

---

## Beispiel in CMake
```cmake
enable_testing()
add_executable(facultyCalulatorTest test/test_main.cpp src/factorial.cpp)
target_link_libraries(facultyCalulatorTest PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(facultyCalulatorTest)
```

## Debug/Inspektion
- GoogleTest-Fälle direkt aus dem Binary listen:

```powershell
.\build-ninja\facultyCalulatorTest.exe --gtest_list_tests
```

- Registrierte CTest-Einträge anzeigen (ohne Ausführung):

```powershell
ctest --test-dir build-ninja -N
```
