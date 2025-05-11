# Go Memory Model Examples

This module contains multiple examples demonstrating Go's memory model and concurrency primitives.

## Structure

Each subdirectory contains its own `main.go` file which is a separate executable:

- `data_races/` - Demonstrates data races when multiple goroutines write to shared memory
- `go_routine_destruction/` - Shows how to properly clean up goroutines
- `channels_example/` - Demonstrates using channels for coordination between goroutines
- `atomic_operations/` - Shows how to use atomic operations to avoid race conditions

## Running Examples

You can run any example by specifying its directory path:

```bash
# Run the data races example
go run ./data_races

# Run the goroutine destruction example
go run ./go_routine_destruction

# Run the channels example
go run ./channels_example

# Run the atomic operations example
go run ./atomic_operations
```

## Running with Race Detection

Go provides a built-in race detector that can help identify data races:

```bash
go run -race ./data_races
go run -race ./atomic_operations
```

## Building Binaries

You can also build binaries for each example:

```bash
# Build all examples
go build ./...

# Build a specific example
go build -o data_races_example ./data_races
```

## Note on Go Modules

This project demonstrates how a single Go module can contain multiple executables by organizing them into separate directories, each with its own `main.go` file. 
