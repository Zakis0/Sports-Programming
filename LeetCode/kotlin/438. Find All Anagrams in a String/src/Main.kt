//https://leetcode.com/problems/find-all-anagrams-in-a-string/
fun findAnagrams(s: String, p: String): List<Int> {
    val letterCounter = p.groupingBy { it }.eachCount().toMutableMap()
    val result = mutableListOf<Int>()
    s.forEachIndexed { index, char ->
        letterCounter[char]?.let { letterCounter[char] = it - 1 }
        if (index >= p.length) {
            letterCounter[s[index - p.length]]?.let { letterCounter[s[index - p.length]] = it + 1 }
        }
        if (index >= p.length - 1 && letterCounter.values.all { it == 0 }) {
            result.add(index - p.length + 1)
        }
    }
    return result
}
fun main() {
    findAnagrams("abab", "ab").forEach { print("$it ") }
}