//https://leetcode.com/problems/interval-list-intersections
import kotlin.math.max
import kotlin.math.min
fun intervalIntersection(firstList: Array<IntArray>, secondList: Array<IntArray>): Array<IntArray> {
    var firstListIndex = 0
    var secondListIndex = 0
    val result = mutableListOf<IntArray>()
    while (firstListIndex < firstList.size &&secondListIndex < secondList.size) {
        val firstIntervalStart = firstList[firstListIndex].first()
        val firstIntervalEnd = firstList[firstListIndex].last()
        val secondIntervalStart = secondList[secondListIndex].first()
        val secondIntervalEnd = secondList[secondListIndex].last()
        when {
            firstIntervalEnd < secondIntervalStart -> ++firstListIndex
            secondIntervalEnd < firstIntervalStart -> ++secondListIndex
            else -> {
                result += (intArrayOf(
                    max(firstIntervalStart, secondIntervalStart),
                    min(firstIntervalEnd, secondIntervalEnd)))
                if (firstIntervalEnd < secondIntervalEnd) {
                    ++firstListIndex
                }
                else {
                    ++secondListIndex
                }
            }
        }
    }
    return result.toTypedArray()
}
fun main() {
    intervalIntersection(arrayOf(intArrayOf(0, 2), intArrayOf(5, 10), intArrayOf(13, 23), intArrayOf(24, 25)),
        arrayOf(intArrayOf(1, 5), intArrayOf(8, 12), intArrayOf(15, 24), intArrayOf(25, 26))).forEach { println("${it[0]}, ${it[1]}") }
}