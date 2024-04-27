import java.util.*

fun main() {
    val scan = Scanner(System.`in`)
    val a = scan.nextLong()
    val b = scan.nextLong()
    val c = scan.nextLong()

    if (a + b - c == 0L ||
        a + c - b == 0L ||
        b + c - a == 0L) {
        println("YES")
    }
    else {
        println("NO")
    }
}