import java.util.*

fun main() {
    val scan = Scanner(System.`in`)
    val n = scan.nextInt()
    val k = scan.nextInt()

    val melons = Array(n) { 0L }

    for (i in 0..< n) {
        melons[i] = scan.nextLong()
    }

    melons.sort()

    var counter = 0

    var left = 0
    var right = n - 1

    while (left <= right) {
        if (melons[right] > k) {
            println("Impossible")
            return
        }
        ++counter
        if (left - right != 0 && melons[right] + melons[left] <= k) {
            ++left
        }
        --right
    }
    println(counter)
}