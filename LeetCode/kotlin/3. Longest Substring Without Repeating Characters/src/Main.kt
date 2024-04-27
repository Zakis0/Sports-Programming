//https://leetcode.com/problems/longest-substring-without-repeating-characters
import kotlin.math.max
fun lengthOfLongestSubstring(s: String): Int {
    val charSet = LinkedHashSet<Char>()
    var result = 0
    for(c in s) {
        while(charSet.contains(c)) {
            result = max(result, charSet.size)
            charSet.remove(charSet.first())
        }
        charSet.add(c)
    }
    return max(result, charSet.size)
}
fun main() {
    println(lengthOfLongestSubstring("asdasddaas"))
}