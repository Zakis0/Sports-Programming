//https://leetcode.com/problems/add-strings/
fun addStrings2(num1: String, num2: String): String {
    val minNum: String
    val maxNum: String
    if (num1.length > num2.length) {
        minNum = num2
        maxNum = num1
    }
    else {
        minNum = num1
        maxNum = num2
    }
    val result = StringBuilder()
    var remainder = 0
    for (i in minNum.indices) {
        val digit1 = num1[num1.length - i - 1]
        val digit2 = num2[num2.length - i - 1]
        val sum = digit1.digitToInt() + digit2.digitToInt() + remainder
        remainder = sum / 10
        result.insert(0, sum.rem(10))
    }
    for (i in minNum.length ..< maxNum.length) {
        val digit = maxNum[maxNum.length - i - 1]
        val sum = digit.digitToInt() + remainder
        remainder = sum / 10
        result.insert(0, sum.rem(10))
    }
    if (remainder != 0) {
        result.insert(0, remainder)
    }
    return result.toString()
}
fun addStrings(num1: String, num2: String): String {
    val minNum: String
    val maxNum: String
    if (num1.length > num2.length) {
        minNum = num2
        maxNum = num1
    }
    else {
        minNum = num1
        maxNum = num2
    }
    val result = StringBuilder()
    var remainder = 0
    var sum: Int
    for (i in minNum.indices) {
        sum = num1[num1.length - i - 1].digitToInt() + num2[num2.length - i - 1].digitToInt() + remainder
        remainder = if (sum > 9) 1 else 0
        result.insert(0, if (sum > 9) sum - 10 else sum)
    }
    for (i in minNum.length ..< maxNum.length) {
        sum = maxNum[maxNum.length - i - 1].digitToInt() + remainder
        remainder = if (sum > 9) 1 else 0
        result.insert(0, if (sum > 9) sum - 10 else sum)
    }
    if (remainder != 0) {
        result.insert(0, 1)
    }
    return result.toString()
}
fun main() {
    println(addStrings("11", "123"))
}
