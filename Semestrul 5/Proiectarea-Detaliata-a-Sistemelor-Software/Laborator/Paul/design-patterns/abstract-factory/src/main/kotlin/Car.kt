package org.paul

import org.paul.car_parts.*;
import org.paul.factories.*;

class Car(private val engine: Engine, private val carBody: CarBody, private val brake:
Brake) {
    override fun toString(): String {
        return "Car with engine: $engine, body: $carBody, brake: $brake"
    }
}