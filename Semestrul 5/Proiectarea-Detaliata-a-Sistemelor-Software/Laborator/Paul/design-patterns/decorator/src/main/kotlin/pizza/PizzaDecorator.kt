package org.paul.pizza

abstract class PizzaDecorator(private val pizza: Pizza) : Pizza {
    override fun getCost(): Double {
        return pizza.getCost()
    }

    override fun getDescription(): String {
        return pizza.getDescription()
    }
}
