import java.util.*

//https://leetcode.com/problems/jewels-and-stones/
fun numJewelsInStones2(jewels: String, stones: String): Int {
    val jewelsSet = mutableSetOf<Char>()
    jewels.forEach { jewel ->
        jewelsSet.add(jewel)
    }
    var counter = 0
    stones.forEach { stone ->
        if (jewelsSet.contains(stone)) {
            ++counter
        }
    }
    return counter
}
fun numJewelsInStones(jewels: String, stones: String): Int {
    return stones.count { it in jewels}
}
fun main() {
    println(numJewelsInStones("aA", "aAAbbbb"))
}