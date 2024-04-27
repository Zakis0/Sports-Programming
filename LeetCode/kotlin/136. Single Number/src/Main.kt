//https://leetcode.com/problems/single-number/
fun singleNumber(nums: IntArray): Int {
    var value = 0
    nums.forEach {
        value = value xor it
    }
    return value
}

fun main() {
    println(singleNumber(intArrayOf()))
}