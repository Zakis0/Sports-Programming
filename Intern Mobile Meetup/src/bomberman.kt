const val EMPTY = '.'
const val WALL = 'W'
const val ENEMY = 'B'

fun printMap(enemyCounterMap: Array<Array<Int>>) {
    enemyCounterMap.forEach {  row ->
        row.forEach {
            print("$it ")
        }
        println()
    }
}
fun printMap(enemyCounterMap: Array<Array<Char>>) {
    enemyCounterMap.forEach {  row ->
        row.forEach {
            print("$it ")
        }
        println()
    }
}

fun bomberman() {
    val input = readln().trim().split(" ")
    val n = input[0].toInt()
    val m = input[1].toInt()

    val enemyMap = Array(n) { Array(m) { '.' } }

    var maxEnemy = -1
    var bombPoint: Pair<Int, Int> = Pair(-1, -1)

    for (i in 0..< n) {
        val str = readln()
        for (j in 0..<m) {
            enemyMap[i][j] = str[j]
        }
    }

    val enemyCounterMap = Array(n) { Array(m) { 0 } }

    var enemyCounter = 0

    for (i in 0..< n) {
        enemyCounter = 0
        for (j in 0..< m) {
            if (enemyMap[i][j] == ENEMY) {
                ++enemyCounter
            }
            if (enemyMap[i][j] == WALL || (j == m - 1)) {
                var k = j
                if (enemyMap[i][j] == WALL || enemyMap[i][j] == ENEMY) {
                    enemyCounterMap[i][j] = -1
                }
                else {
                    enemyCounterMap[i][j] += enemyCounter
                }
                while (k > 0 && enemyMap[i][k - 1] != WALL) {
                    --k
                    if (enemyMap[i][k] == ENEMY) {
                        enemyCounterMap[i][k] = -1
                        continue
                    }
                    enemyCounterMap[i][k] += enemyCounter
                }
                enemyCounter = 0
            }
        }
    }
    for (j in 0..< m) {
        enemyCounter = 0
        for (i in 0..< n) {
            if (enemyMap[i][j] == ENEMY) {
                ++enemyCounter
            }
            if (enemyMap[i][j] == WALL || (i == n - 1)) {
                var k = i
                if (enemyMap[i][j] == WALL || enemyMap[i][j] == ENEMY) {
                    enemyCounterMap[i][j] = -1
                }
                else {
                    enemyCounterMap[i][j] += enemyCounter
                }
                while (k > 0 && enemyMap[k - 1][j] != WALL) {
                    --k
                    if (enemyMap[k][j] == ENEMY) {
                        enemyCounterMap[k][j] = -1
                        continue
                    }
                    enemyCounterMap[k][j] += enemyCounter
                }
                enemyCounter = 0
            }
        }
    }
    for (j in 0..< m) {
        for (i in 0..<n) {
            if (enemyCounterMap[i][j] > maxEnemy) {
                maxEnemy = enemyCounterMap[i][j]
                bombPoint = Pair(i, j)
            }
        }
    }
    println("${bombPoint.first + 1} ${bombPoint.second + 1}")
}