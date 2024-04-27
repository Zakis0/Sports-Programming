//https://leetcode.com/problems/valid-parentheses/
fun getPairBracket(c: Char) = when(c) {
    ')' -> '('
    ']' -> '['
    else -> '{'
}
fun isValid(s: String): Boolean {
    val deque = ArrayDeque<Char>()
    for (c in s) {
        if (c in setOf('(', '[', '{')) {
            deque.addLast(c)
        }
        else {
            if (deque.isEmpty() || deque.last() != getPairBracket(c)) {
                return false;
            }
            else {
                deque.removeLast()
            }
        }
    }
    return deque.isEmpty()
}
fun main() {
    println(isValid("(((()))){{}}"))
}