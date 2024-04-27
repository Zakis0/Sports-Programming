fun missingNumber(nums: IntArray): Int {
    return ((nums.size + 1) * nums.size shr 1) - nums.sum()
}

fun main() {
    println(missingNumber(intArrayOf(2, 0)))
}