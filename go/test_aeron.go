package main

import (
	"fmt"
	"time"
)

// #cgo CXXFLAGS: -O2 -std=c++11
// #cgo LDFLAGS: ../build/libaeron_client_cgo.a -lstdc++
// #include "../aeron.h"
import "C"

func main() {
	fmt.Printf("hi go\n")
	dir := "/dev/shm/yi-quas"
	channel := "aeron:udp?endpoint=localhost:40123"
	C.aeron_initialize(C.CString(dir))
	pubIdx := C.aeron_add_publication(C.CString(channel), 10)

	msg := "hellogo"
	msgc := C.CString(msg)
	for {

		C.aeron_publish(pubIdx, msgc, 8)
		time.Sleep(time.Second * 1)
	}
}
