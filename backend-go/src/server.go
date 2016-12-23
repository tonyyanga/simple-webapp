package main

import (
		"net/http"
		"fmt"
		"log"
)

func Server(w http.ResponseWriter, req *http.Request) {
		log.Printf("Receive a request.\n")
		fmt.Fprintf(w, "sndc\n")
}

func main() {
		http.HandleFunc("/", Server)
		log.Fatal(http.ListenAndServe("127.0.0.1:8000", nil))
}
