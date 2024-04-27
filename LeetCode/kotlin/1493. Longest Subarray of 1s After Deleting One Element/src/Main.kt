//https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element
import kotlin.math.max
fun longestSubarray2(nums: IntArray): Int {
    if (!nums.contains(0)) {
        return nums.size - 1
    }
    var curOnesCounter = 0
    val numOfOnesAtSegment = Array(nums.size) { 0 }
    for (i in nums.indices) {
        if (nums[i] == 0 || i == nums.size - 1) {
            var j = i
            if (i == nums.size - 1 && nums.last() == 1) {
                ++j
                ++curOnesCounter
            }
            while (--j >= 0 && nums[j] != 0) {
                numOfOnesAtSegment[j] = curOnesCounter
            }
            curOnesCounter = 0
        }
        else {
            ++curOnesCounter
        }
    }
    var maxLength = 0
    nums.forEachIndexed { index, num ->
        if (num == 0) {
            val leftCounter = if (index > 0) numOfOnesAtSegment[index - 1] else 0
            val rightCounter = if (index + 1 < nums.size) numOfOnesAtSegment[index + 1] else 0
            maxLength = max(leftCounter + rightCounter, maxLength)
        }
    }
    return maxLength
}
fun longestSubarray(nums: IntArray): Int {
    var curWindowSize = 0
    var prevWindowSize = 0
    var maxWindowSize = 0

    nums.forEach { num ->
        if (num == 0) {
            maxWindowSize = max(curWindowSize + prevWindowSize, maxWindowSize)
            prevWindowSize = curWindowSize
            curWindowSize = 0
        }
        else {
            ++curWindowSize
        }
    }
    if (curWindowSize == nums.size) {
        return nums.size - 1
    }
    return max(curWindowSize + prevWindowSize, maxWindowSize)

}
fun main() {
    println(longestSubarray(intArrayOf(1,1,0,1)))
}