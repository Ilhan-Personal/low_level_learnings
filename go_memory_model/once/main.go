// The sync package provides a safe mechanism for initialization in the presence of multiple goroutines through the use of the Once type. Multiple threads can execute once.Do(f) for a particular f, but only one will run f(), and the other calls block until f() has returned.
// The completion of a single call of f() from once.Do(f) is synchronized before the return of any call of once.Do(f).

package main

import (
	"fmt"
	"sync"
	"time"
)

var a string
var counter int
var once sync.Once

func setup() {
	a = "hello, world"
	counter++
}

func doprint() {
	once.Do(setup)
	fmt.Println(a)
	fmt.Println(counter)
}

func twoprint() {
	go doprint()
	go doprint()
}

func main() {
	twoprint()
	time.Sleep(100 * time.Millisecond)
}
