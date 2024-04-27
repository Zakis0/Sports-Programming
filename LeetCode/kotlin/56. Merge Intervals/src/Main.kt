//https://leetcode.com/problems/merge-intervals
import kotlin.math.min
import kotlin.math.max
fun merge2(intervals: Array<IntArray>): Array<IntArray> {
    intervals.sortWith(compareBy( {it[0]}, {it[1]} ))
    val result = mutableListOf<IntArray>().apply {
        add(intArrayOf(intervals[0][0], intervals[0][1]))
    }
    for (i in 1 ..< intervals.size) {
        if (result.last()[0] <= intervals[i][1] &&
            intervals[i][0] <= result.last()[1]
        ) {
            result.last()[0] = min(result.last()[0], intervals[i][0])
            result.last()[1] = max(result.last()[1], intervals[i][1])
        }
        else {
            result.add(intArrayOf(intervals[i][0], intervals[i][1]))
        }
    }
    return result.toTypedArray()
}
fun merge(intervals: Array<IntArray>): Array<IntArray> {
    val start = IntArray(10001)
    val end = IntArray(10001)
    var globalRightBound = 0

    for (i in intervals.indices) {
        ++start[intervals[i][0]]
        ++end[intervals[i][1]]
        globalRightBound = max(globalRightBound, intervals[i][1])
    }
    var interval = IntArray(2)
    var boundaryCounter = 0
    val result = mutableListOf<IntArray>()
    for (i in 0 .. globalRightBound) {
        if (start[i] > 0) {
            if (boundaryCounter == 0) {
                interval = IntArray(2)
                interval[0] = i
                result.add(interval)
            }
            boundaryCounter += start[i]
        }
        if (end[i] > 0) {
            boundaryCounter -= end[i]
            if (boundaryCounter == 0) {
                interval[1] = i
                result[result.size - 1] = interval
            }
        }
    }
    return result.toTypedArray()
}
fun main() {
    merge(arrayOf(intArrayOf(1, 3), intArrayOf(2, 6), intArrayOf(8, 10), intArrayOf(15, 18))).forEach { it.forEach { print("$it ") }; println() };println("___________")
    merge(arrayOf(intArrayOf(1, 4), intArrayOf(4, 6))).forEach { it.forEach { print("$it ") }; println() };println("___________")
    merge(arrayOf(intArrayOf(1, 4))).forEach { it.forEach { print("$it ") }; println() };println("___________")
    merge(arrayOf(intArrayOf(1, 4), intArrayOf(0, 4))).forEach { it.forEach { print("$it ") }; println() };println("___________")
    merge(arrayOf(intArrayOf(1, 4), intArrayOf(0, 1))).forEach { it.forEach { print("$it ") }; println() };println("___________")
    merge(arrayOf(intArrayOf(1, 4), intArrayOf(0, 2), intArrayOf(3, 5))).forEach { it.forEach { print("$it ") }; println() };println("___________")
    merge(arrayOf(intArrayOf(1, 2), intArrayOf(3, 4), intArrayOf(5, 6), intArrayOf(0, 10))).forEach { it.forEach { print("$it ") }; println() };println("___________")
}