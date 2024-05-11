//https://leetcode.com/problems/search-in-rotated-sorted-array/
fun search(nums: IntArray, target: Int): Int {
    var left = 0
    var right = nums.size - 1
    while (left <= right) {
        val mid = (left + right) / 2
        if (nums[mid] == target) {
            return mid
        }
        if (nums[left] <= nums[mid]) {
            if (nums[mid] < target || target < nums[left]) {
                left = mid + 1
            }
            else {
                right = mid - 1
            }
        }
        else {
            if (target < nums[mid] || nums[right] < target) {
                right = mid - 1
            }
            else {
                left = mid + 1
            }
        }
    }
    return -1
}
fun main() {
    println(search(intArrayOf(4,5,6,7,0,1,2), 0))
}