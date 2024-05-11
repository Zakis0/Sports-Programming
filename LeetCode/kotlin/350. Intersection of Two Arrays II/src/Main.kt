//https://leetcode.com/problems/intersection-of-two-arrays-ii
inline fun <K> IntArray.groupingBy(crossinline keySelector: (Int) -> K): Grouping<Int, K> {
    return object : Grouping<Int, K> {
        override fun sourceIterator(): Iterator<Int> = this@groupingBy.iterator()
        override fun keyOf(element: Int): K = keySelector(element)
    }
}
fun intersect3(nums1: IntArray, nums2: IntArray): IntArray {
    val counterMap1 = nums1.groupingBy { it }.eachCount()
    val counterMap2 = nums2.groupingBy { it }.eachCount()
    val result = mutableListOf<Int>()
    counterMap1.keys.filter { it in counterMap2.keys }.forEach { key ->
        repeat(Math.min(counterMap1[key]!!, counterMap2[key]!!)) {
            result.add(key)
        }
    }
    return result.toIntArray()
}
fun intersect2(nums1: IntArray, nums2: IntArray): IntArray {
    val sortedNums1 = nums1.sorted()
    val sortedNums2 = nums2.sorted()
    val result = mutableListOf<Int>()

    var index1 = 0
    var index2 = 0

    while (index1 < sortedNums1.size && index2 < sortedNums2.size) {
        if (sortedNums1[index1] == sortedNums2[index2]) {
            result.add(sortedNums1[index1])
            ++index1
            ++index2
            continue
        }
        if (sortedNums1[index1] < sortedNums2[index2]) {
            while (index1 < sortedNums1.size && sortedNums1[index1] < sortedNums2[index2]) {
                ++index1
            }
            continue
        }
        while (index2 < sortedNums2.size && sortedNums2[index2] < sortedNums1[index1]) {
            ++index2
        }
    }
    return result.toIntArray()
}
fun intersect(nums1: IntArray, nums2: IntArray): IntArray {
    val counterMap = nums1.groupingBy { it }.eachCount().toMutableMap()
    val result = mutableListOf<Int>()
    nums2.forEach { value ->
        counterMap[value]?.let {
            if(it > 0) {
                result.add(value)
                counterMap[value] = it - 1
            }
        }
    }
    return result.toIntArray()
}
fun main() {
    intersect(intArrayOf(1,2,2,1), intArrayOf(2,2)).forEach { print("$it ") };println()
    intersect(intArrayOf(4,9,5), intArrayOf(9,4,9,8,4)).forEach { print("$it ") };println()
}