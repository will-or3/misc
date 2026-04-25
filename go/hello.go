package main

import (
	"fmt"
	"net/http"
)

func handler(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "./first_web_server.html")
}

func main(){
	http.HandleFunc("/", handler)

	fmt.Println("server running on http://localhost:8080")
	http.ListenAndServe(":8080", nil)
}
