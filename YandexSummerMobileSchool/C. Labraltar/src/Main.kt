import java.util.*

fun countVowels(str: String): Int {
    var count = 0
    val vowels = listOf('a', 'e', 'i', 'o', 'u')
    str.forEach {
        if (it.lowercaseChar() in vowels) {
            ++count
        }
    }
    return count
}

fun main() {
    val scan = Scanner(System.`in`)
    val n = scan.nextInt()

    val words = mutableListOf<String>()

    repeat(n) {
        words.add(scan.next())
    }

    val cmp = compareBy<String>{ countVowels(it) }.reversed().thenBy{ it.length }
    words.sortedWith(cmp).forEach { println(it) }
}
