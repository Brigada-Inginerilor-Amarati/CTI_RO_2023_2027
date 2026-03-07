package org.paul
import org.paul.formatters.*
import org.paul.shapes.*

fun main() {
    val triangle = Triangle(Point(0, 0), Point(1, 0), Point(0, 1))
    val circle = Circle(Point(5, 5), 10.0)
    val rectangle = Rectangle(4.0, 6.0)

    val jsonFormatter = JsonFormatter()
    val xmlFormatter = XmlFormatter()
    val ymlFormatter = YmlFormatter()

    println("Triangle in JSON:\n${triangle.export(jsonFormatter)}\n")
    println("Circle in XML:\n${circle.export(xmlFormatter)}\n")
    println("Rectangle in YML:\n${rectangle.export(ymlFormatter)}\n")
}
