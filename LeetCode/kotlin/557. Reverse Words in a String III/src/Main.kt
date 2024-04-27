// https://leetcode.com/problems/reverse-words-in-a-string-iii/
fun reverseWords(s: String): String {
    return s.split(" ").joinToString(" ") { it.reversed() }
}

fun main() {
    val s = "Let's take LeetCode contest"
    reverseWords(s).also { println(it) }
}