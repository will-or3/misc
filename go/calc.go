package main

import (
	"fmt"
)

func int_input(prompt string) int {
	var x int
	fmt.Printf("%s", prompt)
	fmt.Scan(&x)
	return x
}

func char_input(prompt string) rune {
	var s string
	fmt.Printf("%s", prompt)
	fmt.Scan(&s)
	c := rune(s[0])
	return c
}

func two_num_calc(x int, y int, op rune) int {
	switch op {
	case '+':
		return x + y
	case '-':
		return x - y
	case '*':
		return x * y
	case '/':
		return x / y
	default:
		fmt.Println("error")
		return 0
	}
}
	
func main(){
	int_input("enter second # >:")a := int_input("enter first # >:")
	op := char_input("operation >:")
	b := int_input("enter second # >:")
	fmt.Printf("\n%d\n", two_num_calc(a, b, op))
}
