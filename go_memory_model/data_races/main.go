package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	var sharedVar int

	var wg sync.WaitGroup

	const numWorkers = 3
	wg.Add(numWorkers)

	for i := 0; i < numWorkers; i++ {
		workerID := i
		go func() {
			defer wg.Done()
			for j := 0; j < 1000; j++ {
				current := sharedVar

				time.Sleep(time.Nanosecond)

				sharedVar = current + 1 + workerID
				fmt.Printf("Worker %d: wrote value %d\n", workerID, sharedVar)
			}
		}()
	}

	// Wait for all goroutines to complete
	wg.Wait()

	// Print the final value - this will be unpredictable due to race conditions
	fmt.Printf("Final value of sharedVar: %d\n", sharedVar)
	fmt.Println("Note: Run this program with -race flag to detect data races")
	fmt.Println("Example: go run -race main.go")
}
