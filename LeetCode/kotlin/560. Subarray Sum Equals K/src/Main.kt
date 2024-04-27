//https://leetcode.com/problems/subarray-sum-equals-k/
import kotlin.math.abs
fun subarraySum(nums: IntArray, k: Int): Int {
    var leftWindow = 0
    var rightWindow = 0
    var result = 0
    var curSum = nums.first()
    while (true) {
        if (curSum == k) {
            ++result
        }
        if (rightWindow == nums.size - 1 && curSum < k || leftWindow == nums.size - 1) break
        if (abs(curSum + nums[rightWindow] - k) < abs(curSum - nums[leftWindow] - k)) {
            curSum += nums[++rightWindow]
        }
        else {
            curSum -= nums[leftWindow++]
        }
        if (leftWindow > rightWindow) {
            curSum += nums[++rightWindow]
        }
    }
    return result
}
fun main() {
    println(subarraySum(intArrayOf(-1,-1,1), 0))
}