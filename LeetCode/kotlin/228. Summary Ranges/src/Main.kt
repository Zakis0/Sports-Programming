//https://leetcode.com/problems/summary-ranges/description/

fun summaryRanges(nums: IntArray): List<String> {
    val result = mutableListOf<String>()

    var startValue = if(nums.isNotEmpty()) nums.first() else 0
    var isSingleNumber = true

    for (i in nums.indices) {
        if (i != nums.size - 1 && nums[i + 1] - nums[i] == 1) {
            if (isSingleNumber) {
                startValue = nums[i]
                isSingleNumber = false
            }
        }
        else {
            if (isSingleNumber) {
                result.add(nums[i].toString())
            }
            else {
                result.add("$startValue->${nums[i]}")
                isSingleNumber = true
            }
        }
    }
    return result
}

fun main() {
    summaryRanges(intArrayOf()).forEach { println(it) }
}