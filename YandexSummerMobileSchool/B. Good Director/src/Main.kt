fun main() {
    val countMap = mutableMapOf<Pair<Int, Int>, Int>()

    var curPos = Pair(0, 0)
    countMap[curPos] = 1

    readlnOrNull()?.forEach {
        when (it) {
            'L' -> curPos = Pair(curPos.first - 1, curPos.second)
            'R' -> curPos = Pair(curPos.first + 1, curPos.second)
            'U' -> curPos = Pair(curPos.first, curPos.second - 1)
            'D' -> curPos = Pair(curPos.first, curPos.second + 1)
        }
        if (countMap.containsKey(curPos)) {
            countMap[curPos] = countMap[curPos]!! + 1
        }
        else {
            countMap[curPos] = 1
        }
    }
    var result = 0
    for (counter in countMap.values) {
        if (counter > 1) {
            ++result
        }
    }
    println(result)
}