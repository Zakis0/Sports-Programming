fun getSumOfDigits(num: Int): Int {
    var res = 0
    num.toString().forEach {
        res += it.digitToInt()
    }
    return res
}

fun onceAtBus(): Int {
    val int = readln().trim().toInt()

    var left = int / 1000
    var right = int % 1000

    var sumOfLeft = getSumOfDigits(left)

    while (true) {
        if (sumOfLeft == getSumOfDigits(right)) {
            break
        }
        ++right
        if (right == 1000) {
            ++left
            sumOfLeft = getSumOfDigits(left)
            right = 0
        }
    }
    return left * 1000 + right
}