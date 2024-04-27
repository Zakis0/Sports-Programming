//https://leetcode.com/problems/single-number-iii/description/
fun singleNumber(nums: IntArray): IntArray {
    var answerXOR = 0
    nums.forEach {
        answerXOR = answerXOR xor it
    }
    var temp = answerXOR
    var offset = 0

    for (i in 0..31) {
        if (temp and 1 == 1) {
            break
        }
        temp = temp shr 1
        ++offset
    }

    var x = answerXOR
    val mask = 1 shl offset
    nums.forEach {
        if (it and mask != 0) {
            x = x xor it
        }
    }
    return intArrayOf(x, answerXOR xor x)
}

fun main() {
    singleNumber(intArrayOf(-1638685546,-2084083624,-307525016,-930251592,-1638685546,1354460680,623522045,-1370026032,-307525016,-2084083624,-930251592,472570145,-1370026032,1063150409,160988123,1122167217,1145305475,472570145,623522045,1122167217,1354460680,1145305475)).forEach { println("$it ") }
}