//https://leetcode.com/problems/one-edit-distance/
import kotlin.math.abs
import kotlin.math.min
fun isOneEditDistance(s: String, t: String): Boolean {
    if (abs(s.length - t.length) > 1) return false
    for (i in 0 ..< min(s.length, t.length)) {
        if (s[i] != t[i]) {
            return if (s.length > t.length) {
                 s.substring(i + 1, s.length) == t.substring(i, t.length)
            } else if (s.length < t.length) {
                s.substring(i, s.length) == t.substring(i + 1, t.length)
            } else {
                s.substring(i + 1, s.length) == t.substring(i + 1, t.length)
            }
        }
    }
    return abs(s.length - t.length) == 1
}
fun main() {
    println(isOneEditDistance("a", ""))
}