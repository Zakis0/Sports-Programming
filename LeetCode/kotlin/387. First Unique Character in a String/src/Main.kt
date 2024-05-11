//https://leetcode.com/problems/first-unique-character-in-a-string/
data class MyPair(var counter: Int, var index: Int)
fun firstUniqChar2(s: String): Int {
    val map = LinkedHashMap<Char, MyPair>()
    s.forEachIndexed { index, letter ->
        map[letter]?.let { ++map[letter]!!.counter } ?: map.put(letter, MyPair(1, index))
    }
    map.keys.forEach {
        if (map[it]!!.counter == 1) {
            return map[it]!!.index
        }
    }
    return -1
}
fun firstUniqChar(s: String): Int {
    val frequencies = IntArray(26)
    val positions = IntArray(26)
    var letterIndex: Int
    var minPos = s.length
    s.forEachIndexed { index, letter ->
        letterIndex = letter - 'a'
        ++frequencies[letterIndex]
        positions[letterIndex] = index
    }
    frequencies.forEachIndexed { index, frequency ->
        if (frequency == 1) {
            minPos = Math.min(positions[index], minPos)
        }
    }
    return if (minPos == s.length) -1 else minPos
}
fun main() {
    println(firstUniqChar("leetcode"))
    println(firstUniqChar("loveleetcode"))
    println(firstUniqChar("aabb"))
}