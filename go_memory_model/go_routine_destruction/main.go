package main

import (
	"time"
)

// the exit of a goroutine is not guaranteed to be syncronized
// the print statement may print an empty string

var a string

func hello() {
	go func() {
		a = "hello"
	}()
	print(a)
}

func main() {
	hello()
	time.Sleep(1 * time.Second)
}
