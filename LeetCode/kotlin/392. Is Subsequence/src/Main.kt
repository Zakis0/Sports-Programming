//https://leetcode.com/problems/is-subsequence/description/
fun isSubsequence(s: String, t: String): Boolean {
    var subSequenceIndex = 0
    if (s.isEmpty()) {
        return true
    }
    if (s.length > t.length) {
        return false
    }
    t.forEach {
        if (it == s[subSequenceIndex]) {
            if (++subSequenceIndex == s.length) {
                return true
            }
        }
    }
    return false
}
fun main() {
    println(isSubsequence("daaaaa","aasd"))
}