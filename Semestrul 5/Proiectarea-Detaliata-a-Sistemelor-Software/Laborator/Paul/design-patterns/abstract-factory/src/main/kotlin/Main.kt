package org.paul

import org.paul.car_parts.*
import org.paul.factories.*

fun main() {
    val engineFactory = ConcreteEngineFactory()
    val carBodyFactory = ConcreteCarBodyFactory()
    val brakeFactory = ConcreteBrakeFactory()
    val robot = Robot(brakeFactory, engineFactory, carBodyFactory)

    try {
        val car = robot.assembleCar("Normal", "Diesel", "Combi")
        println(car)
    } catch (e: CouldNotBuildCarException) {
        println(e.message)
    }
}