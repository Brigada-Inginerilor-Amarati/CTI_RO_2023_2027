package org.paul.math

abstract class OperatorNode: Expression {
    abstract val left: Expression
    abstract val right: Expression
}