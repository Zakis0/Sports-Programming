//https://leetcode.com/problems/maximize-distance-to-closest-person
import kotlin.math.max
fun maxDistToClosest(seats: IntArray): Int {
    var maxDistance = 0
    var curDistance = 0
    var firstPersonFlag = true
    seats.forEach { seat ->
        if (seat == 1) {
            if (firstPersonFlag) {
                maxDistance = curDistance
                firstPersonFlag = false
            }
            maxDistance = max((curDistance + 1) / 2, maxDistance)
            curDistance = 0
        }
        else {
            ++curDistance
        }
    }
    return max(maxDistance, curDistance)
}
fun main() {
    println(maxDistToClosest(intArrayOf(0, 0, 1)))
}