package org.paul.car_parts

interface Engine : CarPart {
}

class TSI12Engine : Engine {
    override fun toString(): String {
        return "TSI 1.2L Engine"
    }
}

class TSI18Engine : Engine {
    override fun toString(): String {
        return "TSI 1.8L Engine"
    }
}

class DieselEngine : Engine {
    override fun toString(): String {
        return "Diesel Engine"
    }
}
