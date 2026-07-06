cmake_minimum_required(VERSION 3.16)

# Name des Projekts/Targets, damit wir ihn unten mehrfach wiederverwenden koennen.
set(This isPalindrom)

project(${This})

# Wir verwenden C++11
set(CMAKE_CXX_STANDARD 11)
# Erzeugt compile_commands.json (hilfreich fuer IntelliSense und Tools).
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Externe Abhaengigkeiten direkt beim Konfigurieren laden.
include(FetchContent)
FetchContent_Declare(
  googletest
  # Feste Version, damit das Beispiel reproduzierbar bleibt.
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  # Unterdrueckt Warnungen zu Zeitstempeln beim Entpacken.
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# GoogleTest wird im Build-Verzeichnis verfuegbar gemacht.
FetchContent_MakeAvailable(googletest)



# Add executable
# Hauptprogramm (Produktionscode)
add_executable(${This} src/main.cpp src/isPalindrom.cpp)
# Header-Dateien aus inc/ fuer dieses Target sichtbar machen.
target_include_directories(${This} PUBLIC inc)


# Add test
# CTest-Unterstuetzung aktivieren.
include(ctest)
enable_testing()

# Eigenes Test-Binary mit Testcode + zu testendem Produktionscode.
add_executable(${This}Test test/test_main.cpp src/isPalindrom.cpp)
target_include_directories(${This}Test PUBLIC inc)
# Linkt GoogleTest inkl. main()-Einstiegspunkt fuer Tests.
target_link_libraries(${This}Test GTest::gtest_main)
include(GoogleTest)
# Registriert jeden TEST(...) Fall als einzelnen CTest-Test.
gtest_discover_tests(${This}Test DISCOVERY_TIMEOUT 60)