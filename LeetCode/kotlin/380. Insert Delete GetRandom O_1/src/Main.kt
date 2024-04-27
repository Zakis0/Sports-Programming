//https://leetcode.com/problems/insert-delete-getrandom-o1
class RandomizedSet2 {
    val map = mutableMapOf<Int, Boolean>()
    fun insert(`val`: Int) = map.put(`val`, true) == null
    fun remove(`val`: Int) = map.remove(`val`) != null
    fun getRandom() = map.keys.random()
}
class RandomizedSet {
    val set = mutableSetOf<Int>()
    fun insert(`val`: Int) = set.add(`val`)
    fun remove(`val`: Int) = set.remove(`val`)
    fun getRandom() = set.random()
}
fun main() {
    var obj = RandomizedSet()
    println(obj.insert(4))
    println(obj.insert(2))
    println(obj.remove(2))
    println(obj.insert(2))
    println(obj.insert(2))
    println(obj.remove(6))
    println("Values: ${obj.set}")

    val probabilityMap = mutableMapOf<Int, Int>()
    val n = 1000000
    repeat(n) {
        val value = obj.getRandom()
        if (probabilityMap[value] == null) probabilityMap[value] = 1 else probabilityMap[value] = probabilityMap[value]!! + 1
    }
    probabilityMap.forEach { (value, frequency) -> println("$value: ${frequency.toDouble() / n}") }
}