package org.paul

import org.paul.pizza.*
import org.paul.pizza.ingredients.*

fun main() {
    val simplePizza = SimplePizza()
    println("${simplePizza.getDescription()} Cost: ${simplePizza.getCost()}")

    val hamPizza = Ham(simplePizza)
    println("${hamPizza.getDescription()} Cost: ${hamPizza.getCost()}")

    val cheeseHamPizza = ExtraCheese(hamPizza)
    println("${cheeseHamPizza.getDescription()} Cost: ${cheeseHamPizza.getCost()}")

    val allIngredientsPizza = Salami(Mushroom(ExtraCheese(Ham(SimplePizza()))))
    println("${allIngredientsPizza.getDescription()} Cost: ${allIngredientsPizza.getCost()}")
}