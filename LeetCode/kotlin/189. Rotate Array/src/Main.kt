//https://leetcode.com/problems/rotate-array/
fun rotate2(nums: IntArray, k: Int): Unit {
    val rotation = k % nums.size
    nums.reverse()
    nums.reverse(0, rotation)
    nums.reverse(rotation, nums.size)
}
fun rotate(nums: IntArray, k: Int): Unit {
    var curIndex = 0
    var valueToSwap: Int = nums[0]
    var operationsCount = 0
    var curLoopFinishedIndex = 0
    do {
        curIndex = (curIndex + k) % nums.size

        val valueToMove = nums[curIndex]
        nums[curIndex] = valueToSwap
        valueToSwap = valueToMove

        if (curIndex == curLoopFinishedIndex) {
            curIndex = (curIndex + 1) % nums.size
            valueToSwap = nums[curIndex]
            curLoopFinishedIndex = curIndex
        }
    } while (++operationsCount < nums.size)
}
fun main() {
    intArrayOf(1,2,3,4,5,6,7).also {rotate(it, 3); it.forEach{print("$it ")} };println()
    intArrayOf(-1,-100,3,99).also {rotate(it, 2); it.forEach{print("$it ")} };println()
}