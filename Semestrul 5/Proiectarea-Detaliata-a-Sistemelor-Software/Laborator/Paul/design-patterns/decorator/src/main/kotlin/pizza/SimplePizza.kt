package org.paul.pizza

class SimplePizza : Pizza {
    override fun getCost(): Double {
        return COST
    }

    override fun getDescription(): String {
        return "Simple Pizza (ketchup, mozzarella)"
    }

    companion object {
        private const val COST = 10.0
    }
}