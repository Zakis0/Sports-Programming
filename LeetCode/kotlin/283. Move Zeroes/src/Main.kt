//https://leetcode.com/problems/move-zeroes/description/
fun moveZeroes(nums: IntArray): Unit {
    var zeroIndex = -1

    for (i in nums.indices) {
        if (nums[i] == 0) {
            if (zeroIndex == -1) {
                zeroIndex = i
            }
        }
        else {
            if (zeroIndex != -1) {
                nums[zeroIndex] = nums[i].also { nums[i] = nums[zeroIndex] }
                for (j in zeroIndex + 1 .. i) {
                    if (nums[j] == 0) {
                        zeroIndex = j
                        break
                    }
                }
            }
        }
    }
}

fun main() {
    val arr = intArrayOf(0,1,0,3,12)
    moveZeroes(arr)
    println(arr.contentToString())
}