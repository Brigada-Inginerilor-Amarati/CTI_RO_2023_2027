package org.paul.factories
import org.paul.car_parts.*

interface CarPartFactory{
    fun create(type: String): CarPart
    fun showAvailableTypes(): List<String>
}

interface EngineFactory : CarPartFactory {
    override fun create(type: String): Engine
}

interface BrakeFactory : CarPartFactory {
    override fun create(type: String): Brake
}

interface CarBodyFactory : CarPartFactory {
    override fun create(type: String): CarBody
}

class ConcreteEngineFactory() : EngineFactory {
    override fun showAvailableTypes(): List<String> {
        return listOf("TSI1.2", "TSI1.8", "Diesel")
    }

    override fun create(type: String): Engine {
        return when (type) {
            "TSI1.2" -> TSI12Engine()
            "TSI1.8" -> TSI18Engine()
            "Diesel" -> DieselEngine()
            else -> throw UnknownCarPartException(type)
        }
    }
}

class ConcreteBrakeFactory() : BrakeFactory {
    override fun showAvailableTypes(): List<String> {
        return listOf("Normal", "HillHoldControl")
    }

    override fun create(type: String): Brake {
        return when (type) {
            "Normal" -> NormalBrake()
            "HillHoldControl" -> HillHoldControlBrake()
            else -> throw UnknownCarPartException(type)
        }
    }
}

class ConcreteCarBodyFactory() : CarBodyFactory {
    override fun showAvailableTypes(): List<String> {
        return listOf("Simple", "Sport", "Combi")
    }

    override fun create(type: String): CarBody {
        return when (type) {
            "Simple" -> SimpleBody()
            "Sport" -> SportBody()
            "Combi" -> CombiBody()
            else -> throw UnknownCarPartException(type)
        }
    }
}
