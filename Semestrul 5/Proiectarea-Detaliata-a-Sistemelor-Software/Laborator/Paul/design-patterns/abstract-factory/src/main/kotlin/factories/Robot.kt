package org.paul.factories

import org.paul.Car

class Robot(private val brakeFactory: BrakeFactory, private val engineFactory: EngineFactory, private val carBodyFactory: CarBodyFactory) {
    fun assembleCar(brakeType: String, engineType: String, carBodyType: String): Car {
        try{
            val brake = brakeFactory.create(brakeType)
            val engine = engineFactory.create(engineType)
            val carBody = carBodyFactory.create(carBodyType)
            return Car(engine, carBody, brake)
        } catch (e: UnknownCarPartException) {
            throw CouldNotBuildCarException(e.message ?: "Unknown error")
        }
    }
}