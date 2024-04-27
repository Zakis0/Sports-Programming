//https://leetcode.com/problems/find-the-duplicate-number/
fun findDuplicate(nums: IntArray): Int {
    var slowPointer = nums[0]
    var fastPointer = nums[0]
    do {
        slowPointer = nums[slowPointer]
        fastPointer = nums[nums[fastPointer]]
    } while (slowPointer != fastPointer)
    var slowPointer2 = nums[0]
    while (slowPointer2 != slowPointer) {
        slowPointer = nums[slowPointer]
        slowPointer2 = nums[slowPointer2]
    }
    return slowPointer
}
fun main() {
    println(findDuplicate(intArrayOf(4,1,3,1,2)))
}