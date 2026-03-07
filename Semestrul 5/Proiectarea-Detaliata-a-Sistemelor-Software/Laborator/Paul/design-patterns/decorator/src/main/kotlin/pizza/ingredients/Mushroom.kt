package org.paul.pizza.ingredients

import org.paul.pizza.Pizza
import org.paul.pizza.PizzaDecorator

class Mushroom(pizza: Pizza) : PizzaDecorator(pizza) {
    override fun getCost(): Double {
        return super.getCost() + COST
    }

    override fun getDescription(): String {
        return super.getDescription() + ", Mushroom"
    }

    companion object {
        private const val COST = 4.0
    }
}
