//https://leetcode.com/problems/find-the-difference/
fun findTheDifference(s: String, t: String): Char {
    var sumOfCharCodesS = s.map { it.code }.sum()
    var sumOfCharCodesT = t.map { it.code }.sum()
    return (sumOfCharCodesT - sumOfCharCodesS).toChar()
}
fun main() {
    println(findTheDifference("abcd", "abcde"))
}