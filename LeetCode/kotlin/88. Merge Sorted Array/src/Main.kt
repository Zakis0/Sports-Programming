//https://leetcode.com/problems/merge-sorted-array/
fun merge(nums1: IntArray, m: Int, nums2: IntArray, n: Int): Unit {
    var lastIndex1 = m - 1
    var lastIndex2 = n - 1
    var resultLastIndex = m + n - 1
    while(lastIndex2 >= 0) {
        if (lastIndex1 >= 0 && nums1[lastIndex1] > nums2[lastIndex2]) {
            nums1[resultLastIndex--] = nums1[lastIndex1--]
        }
        else {
            nums1[resultLastIndex--] = nums2[lastIndex2--]
        }
    }
}
fun main() {
    intArrayOf(1,2,3,0,0,0).also {merge(it, 3, intArrayOf(2,5,6), 3); it.forEach { print("$it ") }; println() }
    intArrayOf(6,0,0,0).also {merge(it, 1, intArrayOf(1,2,3), 3); it.forEach { print("$it ") }; println() }
}