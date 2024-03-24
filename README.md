# CalTrain

This lab aims to get familiar with concurrent programming.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- pthread library

### Installation

1. Clone the repository:
```
git clone <repository_url>
```

2. Compile the project:
```
make all
```

### Usage

To run the benchmark, execute the compiled binary with the following command:
```
./caltrain
```

### Testing
To run the tests, execute the `repeat.sh` script located in the project root directory. This script runs the program multiple times, i.e. 1000 times, and saves the output to `test` directory. If there is any error it would be printed out in the terminal.
```
./repeat.sh
```

## File Structure

- `src/caltrain.h`: Header file containing function declarations.
- `src/caltrain.c`: Source file containing function definitions.
- `src/caltrain-runner.c`: Source file containing the main function to run the program as well as the program logic.
- `test/` : The directory containing the test results.
- `repeat.sh`: Bash script to test the program.
- `Makefile`: Makefile for compiling the shell program.
- `README.md`: This file providing information about the program.

