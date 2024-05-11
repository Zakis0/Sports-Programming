//https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
fun twoSum(numbers: IntArray, target: Int): IntArray {
    var left = 0
    var right = numbers.size - 1
    while (numbers[left] + numbers[right] != target) {
        if (numbers[left] + numbers[right] < target) {
            ++left
        }
        else {
            --right
        }
    }
    return intArrayOf(left + 1, right + 1)
}
fun main() {
    twoSum(intArrayOf(2,7,11,15), 9).also { println("${it[0]} ${it[1]}") }
    twoSum(intArrayOf(2,3,4), 6).also { println("${it[0]} ${it[1]}") }
    twoSum(intArrayOf(-1,0), -1).also { println("${it[0]} ${it[1]}") }
}