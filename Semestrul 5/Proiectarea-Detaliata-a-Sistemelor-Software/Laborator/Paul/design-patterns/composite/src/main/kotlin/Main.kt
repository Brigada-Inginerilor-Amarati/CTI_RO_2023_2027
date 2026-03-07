package org.paul
import org.paul.math.*
/*
7. Composite Pattern
Implement a system that allows us to create arithmetic expressions like:
● 3
● (3 + 7)
● (3 * 7)
● (3 * (7 - 5))
● ((3 + (7 + 5))*3)
Implement the hierarchy of expressions that provides a service for printing an expression as
well as a service for computing the value of an expression.
*/

fun main() {
    val op1 = Operand(3.0)
    val op2 = Operand(7.0)
    val op3 = Operand(5.0)

    val ex1 = AdditionNode(op1, op2) // (3 + 7)
    println("${ex1.print()} = ${ex1.evaluate()}")

    val ex2 = MultiplicationNode(op1, op2)
    println("${ex2.print()} = ${ex2.evaluate()}")

    val ex3 = MultiplicationNode(op3, SubtractionNode(op2, op3)) // (5 * (7 - 5))
    println("${ex3.print()} = ${ex3.evaluate()}")

    val ex4 = MultiplicationNode(AdditionNode(op1, AdditionNode(op2, op3)), op1) // ((3 + (7 + 5))*3)
    println("${ex4.print()} = ${ex4.evaluate()}")
}