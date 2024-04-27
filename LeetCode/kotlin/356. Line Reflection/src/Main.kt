//https://leetcode.com/problems/line-reflection/description/
import kotlin.math.max
import kotlin.math.min
fun isReflected(points: Array<Pair<Int, Int>>): Boolean {
    val pointsSet = mutableSetOf<Pair<Int, Int>>()
    var maxX = points.first().first
    var minX = points.first().first
    points.forEach { point ->
        maxX = max(maxX, point.first)
        minX = min(minX, point.first)
        pointsSet.add(point)
    }
    val centerLineX = (maxX + minX) / 2
    points.forEach { point ->
        val reflectedPoint = Pair(2 * centerLineX - point.first, point.second)
        if (!pointsSet.contains(reflectedPoint)) {
            return false
        }
    }
    return true
}

fun main() {
    println(isReflected(arrayOf(Pair(1, 1), Pair(3, 1))))
}