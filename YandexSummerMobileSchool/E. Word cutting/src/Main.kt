import java.util.*
import kotlin.math.max
import kotlin.math.min

fun main() {
    val scan = Scanner(System.`in`)
    val n = scan.nextInt()
    val l = scan.nextInt()
    val r = scan.nextInt()
    val str = scan.next()

    val valueAtIndex = Array(n) { 0 }
    val canWordEndsWithIndex = Array(n) { false }
    val lastWordEndIndex = Array(n) { -1 }
    val answerIndex = mutableListOf<Int>()

    for (i in l - 1..< n) {
        var maxChar = str!![i] - 'a'
        var minChar = str[i] - 'a'
        for (j in i downTo i - l + 1) {
            minChar = min(minChar, str[j] - 'a')
            maxChar = max(maxChar, str[j] - 'a')
        }
        for (j in i - l downTo i - r) {
            if (j == -1) {
                canWordEndsWithIndex[i] = true
                if (valueAtIndex[i] <= maxChar - minChar) {
                    valueAtIndex[i] = maxChar - minChar
                    lastWordEndIndex[i] = j
                }
                break
            }
            if (canWordEndsWithIndex[j]) {
                canWordEndsWithIndex[i] = true
                if (valueAtIndex[i] <= valueAtIndex[j] + maxChar - minChar) {
                    valueAtIndex[i] = valueAtIndex[j] + maxChar - minChar
                    lastWordEndIndex[i] = j
                }
            }
            minChar = min(minChar, str[j] - 'a')
            maxChar = max(maxChar, str[j] - 'a')
        }
    }
    if (!canWordEndsWithIndex.last()) {
        println("NO SOLUTION")
        return
    }

    var index = n - 1
    while (index != -1) {
        answerIndex.add(index)
        index = lastWordEndIndex[index]
    }

    println(valueAtIndex.last())
    println(answerIndex.size)

    var prevIndex = 0
    for (i in answerIndex.size - 1 downTo 0) {
        for (j in prevIndex.. answerIndex[i]) {
            print(str[j])
        }
        prevIndex = answerIndex[i] + 1
        println()
    }
}