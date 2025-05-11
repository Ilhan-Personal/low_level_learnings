package main

import (
	"sync"
)

var l sync.Mutex
var name string

func f() {
	name = "arza"
	l.Unlock()
}

func main() {
	// driver code
	l.Lock()
	go f()
	l.Lock()
	print(name)
}
