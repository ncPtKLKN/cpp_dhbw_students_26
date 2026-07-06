# Bowling Kata

## What?

This repository is the implementation of a cpp kata, i.e. a short implementation task to practice test-driven development. The idea is to implement the tests one by one, never writing any source code w/o a failing test. Then making the test pass and then refactor the code for a clean implementation.

The task here is to implement a class "Game", that is supposed to calculate the score of a bowling game. You provide the rolled pins in each round and can ask for the total score.

## How?
If you want to try this yourself, start with the first test, make it pass then move to the next. In this repository you will find two implementation of game (game and a second version gameV2). gameV2 is a shorter implementation, but needs to have all the rolled results to provide the score. game will calculate the current score with each roll, which comes at the cost of a slightly more complex implementation.

Recommended classroom workflow (strict TDD):

1. Write exactly one failing test (`Red`).
2. Implement the smallest possible production change to pass that test (`Green`).
3. Refactor tests and production code while all tests stay green (`Refactor`).
4. Repeat with the next rule (normal frame, spare, strike, perfect game, invalid/incomplete input).


## Setup
This example uses googletest via CMake FetchContent. You do not need a manual /lib/googletest checkout.

Configure and build:

```powershell
cmake -S . -B build-ninja -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build-ninja
```

Run tests:

```powershell
ctest --test-dir build-ninja --output-on-failure
```

## Start the program / play the game

This kata now includes a small console app target (`bowling_kata_app`) for
manual play.

Build (if not already built):

```powershell
cmake -S . -B build-ninja -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build-ninja
```

Run the app:

```powershell
.\build-ninja\bowling_kata_app.exe
```

Gameplay:

- Enter the number of pins for each roll (`0` to `10`)
- Enter `-1` to end input
- The program prints the current total score

## Why two CMakeLists files?

This example uses two CMakeLists files on purpose to separate responsibilities:

- `CMakeLists.txt` in the project root configures the whole project, defines the production target (`bowling_kata`), and includes the test folder.
- `test/CMakeLists.txt` defines the test executable, links GoogleTest plus production code, and registers tests for CTest.

This keeps production build logic and test build logic cleanly separated and makes the project easier to grow over time.

## Why TEST_F and not TEST?

In this example we use a test fixture class (`GameTest`) in `test/gameTest.cpp`.
The fixture provides shared setup and helper functionality:

- shared object state (`m_game`)
- optional lifecycle hook (`SetUp()`)
- helper methods (`rollOnlyThisNumber(...)`)

`TEST_F` is required when a test should use that fixture state or those helper methods.
`TEST` is for independent tests without fixture state.
