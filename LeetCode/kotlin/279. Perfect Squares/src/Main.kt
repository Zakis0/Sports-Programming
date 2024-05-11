import kotlin.math.floor
import kotlin.math.sqrt

//https://leetcode.com/problems/perfect-squares/
fun numSquares(n: Int): Int {
    var value = n
    var counter = 0
    while (value > 0) {
        if (value % 2 == 1) {}
        val root = floor(sqrt(value.toDouble())).toInt()
        value -= root * root
        ++counter
    }
    return counter
}
fun main() {
    println(numSquares(12))
    println(numSquares(13))
}