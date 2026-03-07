package org.paul.car_parts

interface CarBody : CarPart {
}

class SimpleBody : CarBody {
    override fun toString(): String {
        return "Simple Body"
    }
}

class SportBody : CarBody {
    override fun toString(): String {
        return "Sport Body"
    }
}

class CombiBody : CarBody {
    override fun toString(): String {
        return "Combi Body"
    }
}
