package org.paul.formatters
import org.paul.shapes.*

interface Formatter{}

interface PointFormatter: Formatter {
    fun format(point: Point): String
}

interface CircleFormatter: Formatter {
    fun format(circle: Circle): String
}

interface TriangleFormatter: Formatter {
    fun format(triangle: Triangle): String
}

interface RectangleFormatter: Formatter {
    fun format(rectangle: Rectangle): String
}

class JsonFormatter: PointFormatter, CircleFormatter, TriangleFormatter, RectangleFormatter {
    override fun format(point: Point): String {
        // add type name
        return """{"x": ${point.x}, "y": ${point.y}}"""
    }

    override fun format(circle: Circle): String {
        return """{"center": ${format(circle.center)}, "radius": ${circle.radius}}"""
    }

    override fun format(triangle: Triangle): String {
        return """{"a": ${format(triangle.a)}, "b": ${format(triangle.b)}, "c": ${format(triangle.c)}}"""
    }

    override fun format(rectangle: Rectangle): String {
        return """{"height": ${rectangle.height}, "width": ${rectangle.width}}"""
    }
}

class XmlFormatter: PointFormatter, CircleFormatter, TriangleFormatter, RectangleFormatter {
    override fun format(point: Point): String {
        return "<Point><x>${point.x}</x><y>${point.y}</y></Point>"
    }

    override fun format(circle: Circle): String {
        return "<Circle><center>${format(circle.center)}</center><radius>${circle.radius}</radius></Circle>"
    }

    override fun format(triangle: Triangle): String {
        return "<Triangle><a>${format(triangle.a)}</a><b>${format(triangle.b)}</b><c>${format(triangle.c)}</c></Triangle>"
    }

    override fun format(rectangle: Rectangle): String {
        return "<Rectangle><height>${rectangle.height}</height><width>${rectangle.width}</width></Rectangle>"
    }
}

class YmlFormatter: PointFormatter, CircleFormatter, TriangleFormatter, RectangleFormatter {
    override fun format(point: Point): String {
        return "- x: ${point.x}\n  y: ${point.y}"
    }

    override fun format(circle: Circle): String {
        return "- center:\n${format(circle.center).prependIndent("  ")}\n  radius: ${circle.radius}"
    }

    override fun format(triangle: Triangle): String {
        return "- a:\n${format(triangle.a).prependIndent("  ")}\n- b:\n${format(triangle.b).prependIndent("  ")}\n- c:\n${format(triangle.c).prependIndent("  ")}"
    }

    override fun format(rectangle: Rectangle): String {
        return "- height: ${rectangle.height}\n  width: ${rectangle.width}"
    }
}
