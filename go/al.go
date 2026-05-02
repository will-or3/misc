package main

import (
    "fmt"
    "time"
    "slices"
    "sync"
    "runtime"
    )

func Algorithm(x int){
    start := time.Now()
    
    x = (x * (x + 1) / 2)
    
    duration := time.Since(start)
    fmt.Printf("%d\n", x)
    fmt.Println(duration)
}

func CS(x int){
    start := time.Now()
    
    y := 0
    cap := x
    for i:=0; i < cap; i++{
        y += x
        x--
    }
    
    duration := time.Since(start)
    fmt.Printf("\n%d\n", y)
    fmt.Println(duration)
} 

func Sorter(){
    arr := []int{401241, 121, 121, 2, 1, 421, 24, 12, 1, 
        1, 8765, 3, 2, 0, 0, 1, 2, 4, 6, 7, 8, 1, 2, 4}
    
    for i, v := range arr {
        fmt.Printf("[%d] = %d\n", i, v)
    }
    fmt.Printf("\n----------------\n")

    slices.Sort(arr)

    for i, v := range arr {
        fmt.Printf("[%d] = %d\n", i, v)
    }
}

func what_go_was_made_for(name string, wg *sync.WaitGroup){
    defer wg.Done()

    for i := 1; i <= 100; i++ {
        fmt.Printf("worker >>: %s :: %d\n", name, i)
    }
}

func fair(name string, wg *sync.WaitGroup){
    defer wg.Done()

    for i := 1; i <= 100; i++ {
        fmt.Printf("worker >>: %s :: %d\n", name, i)
        runtime.Gosched()
    }
}

func main() {
    x := 100000000
    Algorithm(x)
    CS(x)

    var wg sync.WaitGroup //
    
    wg.Add(2)

    go what_go_was_made_for("A", &wg)
    go what_go_was_made_for("B", &wg)

    wg.Wait()
}
