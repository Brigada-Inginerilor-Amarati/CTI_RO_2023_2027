package org.paul
import org.paul.operations.*
/*
1. Strategy Pattern
We need to implement using the Strategy Pattern a system that provides the basic operations
with integers (+, -, /, *). The two integer values are read and afterwards the user enters the
given operation and the result is displayed.
*/

fun main() {
    println("Enter two integers:")
    val a = readln().toInt()
    val b = readln().toInt()
    println("Enter operation (+, -, /, *):")
    val operation = readln()
    val result = when (operation) {
        "+" -> a + b
        "-" -> a - b
        "/" -> a / b
        "*" -> a * b
        else -> throw IllegalArgumentException("Invalid operation")
    }
    println("Result: $result")
}