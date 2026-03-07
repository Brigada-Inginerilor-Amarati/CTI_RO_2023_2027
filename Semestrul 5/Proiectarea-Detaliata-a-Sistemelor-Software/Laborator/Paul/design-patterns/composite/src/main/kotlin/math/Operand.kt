package org.paul.math

class Operand : Expression {
    private val value: Double

    constructor(value: Double) {
        this.value = value
    }

    override fun evaluate(): Double {
        return value
    }

    override fun print(): String {
        return value.toString()
    }
}