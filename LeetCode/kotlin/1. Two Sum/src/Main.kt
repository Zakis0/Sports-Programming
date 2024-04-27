//https://leetcode.com/problems/two-sum/
fun twoSum(nums: IntArray, target: Int): IntArray {
    val map = mutableMapOf<Int, Int>()
    nums.forEachIndexed { index, value ->
        if (map.contains(target - value)) {
            return intArrayOf(map[target - value]!!, index)
        }
        map[value] = index
    }
    return intArrayOf()
}

fun main() {
    twoSum(intArrayOf(6, 0), 6).forEach { print("$it ") }
}