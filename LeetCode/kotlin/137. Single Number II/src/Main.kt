//https://leetcode.com/problems/single-number-ii/description/
fun singleNumber(nums: IntArray): Int {
    var ones = 0
    var twos = 0

    for (num in nums) {
        ones = ones xor (num and twos.inv())
        twos = twos xor (num and ones.inv())
    }
    return ones
}

fun main() {
    println(singleNumber(intArrayOf(1, 2, 1, 2, 3, 2, 1)))
}