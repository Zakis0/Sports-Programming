//https://leetcode.com/problems/permutation-in-string/
fun checkInclusion(s1: String, s2: String): Boolean {
    val s1CharCounter = IntArray(26)
    val s2CharCounter = IntArray(26)
    s1.forEach {
        ++s1CharCounter[it - 'a']
    }
    var windowLeft = 0
    for (windowRight in s2.indices) {
        ++s2CharCounter[s2[windowRight] - 'a']
        if (windowRight - windowLeft + 1 > s1.length) {
            --s2CharCounter[s2[windowLeft] - 'a']
            ++windowLeft
        }
        if (s1CharCounter.contentEquals(s2CharCounter)) {
            return true
        }
    }
    return false
}
fun main() {
    println(checkInclusion("mod", "axe"))
}