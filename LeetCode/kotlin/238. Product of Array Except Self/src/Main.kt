//https://leetcode.com/problems/product-of-array-except-self
fun productExceptSelf2(nums: IntArray): IntArray {
    val result = IntArray(nums.size) { 1 }
    var prefix = 1
    var sufix = 1
    for (i in nums.indices) {
        result[i] *= prefix
        prefix *= nums[i]
        result[nums.lastIndex - i] *= sufix
        sufix *= nums[nums.lastIndex - i]
    }
    return result
}
fun productExceptSelf(nums: IntArray): IntArray {
    val result = IntArray(nums.size)
    var prod = 1
    var i = nums.size
    while (i > 0) {
        i--
        result[i] = prod
        prod *= nums[i]
    }
    prod = 1
    while (i < nums.size) {
        result[i] *= prod
        prod *= nums[i]
        i++
    }
    return result
}
fun main() {
    productExceptSelf(intArrayOf(1,2,3,4)).forEach { print("$it ") };println()
    productExceptSelf(intArrayOf(-1,1,0,-3,3)).forEach { print("$it ") };println()
}