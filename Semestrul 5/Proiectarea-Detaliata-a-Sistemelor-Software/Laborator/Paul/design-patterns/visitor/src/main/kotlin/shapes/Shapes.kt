package org.paul.shapes
import org.paul.formatters.*

interface Exportable {
    fun export(formatter: Formatter): String
}

data class Point(val x: Int, val y: Int): Exportable {
    override fun export(formatter: Formatter): String {
        return when(formatter){
            is PointFormatter -> formatter.format(this)
            else -> throw IllegalArgumentException("Unsupported formatter for Point")
        }
    }
}

data class Circle(val center: Point, val radius: Double){
    fun export(formatter: Formatter): String {
        return when(formatter){
            is CircleFormatter -> formatter.format(this)
            else -> throw IllegalArgumentException("Unsupported formatter for Circle")
        }
    }
}

data class Triangle(val a: Point, val b: Point, val c: Point){
    fun export(formatter: Formatter): String {
        return when(formatter){
            is TriangleFormatter -> formatter.format(this)
            else -> throw IllegalArgumentException("Unsupported formatter for Triangle")
        }
    }
}

data class Rectangle(val height: Double, val width: Double){
    fun export(formatter: Formatter): String {
        return when(formatter){
            is RectangleFormatter -> formatter.format(this)
            else -> throw IllegalArgumentException("Unsupported formatter for Rectangle")
        }
    }
}