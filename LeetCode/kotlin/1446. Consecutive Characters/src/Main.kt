//https://leetcode.com/problems/consecutive-characters
import kotlin.math.max
fun maxPower(s: String): Int {
    if (s.isEmpty()) return 0
    var curPower = 1
    var maxPower = 1
    for (i in 1 ..< s.length) {
        if (s[i] == s[i - 1]) {
            ++curPower
            maxPower = max(curPower, maxPower)
        }
        else {
            curPower = 1
        }
    }
    return maxPower
}
fun main() {
    println(maxPower("abbcccddddeeeeedcba"))
}