package org.paul.math

class MultiplicationNode(override val left: Expression, override val right: Expression) : OperatorNode() {
    override fun evaluate(): Double {
        return left.evaluate() * right.evaluate()
    }

    override fun print(): String {
        return "(${left.print()} * ${right.print()})"
    }
}