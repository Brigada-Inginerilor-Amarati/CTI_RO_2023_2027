package org.paul.car_parts

interface Brake : CarPart {
}

class NormalBrake : Brake {
    override fun toString(): String {
        return "Normal Brake"
    }
}

class HillHoldControlBrake : Brake {
    override fun toString(): String {
        return "Hill Hold Control Brake"
    }
}