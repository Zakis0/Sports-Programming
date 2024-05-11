//https://leetcode.com/problems/string-compression/
fun compress(chars: CharArray): Int {
    var result = 0
    var letterLength = 1
    for (i in 1 .. chars.size) {
        if (i == chars.size || chars[i] != chars[i - 1]) {
            if (letterLength == 1) {
                chars[result++] = chars[i - 1]
            }
            else {
                chars[result++] = chars[i - 1]
                letterLength.toString().forEach {
                    chars[result++] = it
                }
            }
            letterLength = 1
        }
        else {
            ++letterLength
        }
    }
    return result
}
fun main() {
    charArrayOf('a','a','b','b','c','c','c').also { val l = compress(it); for (i in 0..< l) print(it[i]) };println()
    charArrayOf('a').also { val l = compress(it); for (i in 0..< l) print(it[i]) };println()
    charArrayOf('a','b','b','b','b','b','b','b','b','b','b','b','b').also { val l = compress(it); for (i in 0..< l) print(it[i]) };println()
}