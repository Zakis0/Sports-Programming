//https://leetcode.com/problems/subarray-sum-equals-k/
fun subarraySum(nums: IntArray, k: Int): Int {
    val map = HashMap<Int, Int>()
    var count = 0
    var sum = 0
    map[0] = 1
    for (num in nums) {
        sum += num
        count += map[sum - k] ?: 0
        map[sum] = (map[sum] ?: 0) + 1
    }
    return count
}
fun main() {
    println(subarraySum(intArrayOf(1,1,1), 2))
    println(subarraySum(intArrayOf(1,2,3), 3))
    println(subarraySum(intArrayOf(1), 0))
    println(subarraySum(intArrayOf(-1,-1,1), 0))
    println(subarraySum(intArrayOf(-1,-1,1), -1))
}