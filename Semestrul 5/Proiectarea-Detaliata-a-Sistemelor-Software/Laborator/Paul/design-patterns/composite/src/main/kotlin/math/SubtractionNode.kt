package org.paul.math

class SubtractionNode(override val left: Expression, override val right: Expression) : OperatorNode() {
    override fun evaluate(): Double {
        return left.evaluate() - right.evaluate()
    }

    override fun print(): String {
        return "(${left.print()} - ${right.print()})"
    }
}