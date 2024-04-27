//https://leetcode.com/problems/maximize-distance-to-closest-person
import kotlin.math.max
fun maxDistToClosest(seats: IntArray): Int {
    var maxDistance = 0
    var curDistance = 0
    var firstPersonFlag = true
    seats.forEachIndexed { index, seat ->
        if (seat == 1) {
            if (firstPersonFlag) {
                maxDistance = curDistance
                firstPersonFlag = false
            }
            if ((curDistance + 1) / 2 > maxDistance) {
                maxDistance = (curDistance + 1) / 2
            }
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