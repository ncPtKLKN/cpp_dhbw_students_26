cmake_minimum_required(VERSION 3.16)

# Name des Projekts/Targets, damit wir ihn unten mehrfach wiederverwenden koennen.
set(This bowling_kata)

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


# CTest-Unterstuetzung aktivieren.
enable_testing()

set(Headers
    src/game.hpp
)

set(Sources
    src/game.cpp
)

# Produktionscode als eigene Bibliothek.
add_library(${This} STATIC ${Sources} ${Headers})
add_subdirectory(test)

# Kleines Konsolenprogramm zum manuellen Ausprobieren der Kata-Logik.
add_executable(${This}_app src/main.cpp)
target_link_libraries(${This}_app PRIVATE ${This})
