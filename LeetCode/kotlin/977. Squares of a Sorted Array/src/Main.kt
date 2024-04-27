import kotlin.math.abs

//https://leetcode.com/problems/squares-of-a-sorted-array/description/
fun sortedSquares(nums: IntArray): IntArray {
    val result = IntArray(nums.size) { -1 }
    val indexOfStartNotNegativeSubArray = nums.indexOfFirst { it >= 0 }

    var negativeSubArrayCurIndex = indexOfStartNotNegativeSubArray - 1
    var notNegativeSubArrayCurIndex = indexOfStartNotNegativeSubArray

    if (negativeSubArrayCurIndex == -2) {// no not negative numbers
        negativeSubArrayCurIndex = nums.size - 1
    }

    var resultCurIndex = 0

    while (resultCurIndex != nums.size) {
        if (indexOfStartNotNegativeSubArray == -1 ||
            notNegativeSubArrayCurIndex == nums.size ||
            (negativeSubArrayCurIndex >= 0 &&
                abs(nums[negativeSubArrayCurIndex]) <
                nums[notNegativeSubArrayCurIndex])) {
            result[resultCurIndex] = nums[negativeSubArrayCurIndex] * nums[negativeSubArrayCurIndex]
            --negativeSubArrayCurIndex
        }
        else {
            if (notNegativeSubArrayCurIndex < nums.size) {
                result[resultCurIndex] = nums[notNegativeSubArrayCurIndex] * nums[notNegativeSubArrayCurIndex]
                ++notNegativeSubArrayCurIndex
            }
        }
        ++resultCurIndex
    }
    return result
}

fun main() {
    sortedSquares(intArrayOf(-10000,-9999,-7,-5,0,0,10000)).also { println(it.contentToString()) }
}