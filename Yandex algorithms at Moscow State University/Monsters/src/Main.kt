data class Coords(val x: Int, val y: Int) {
    fun getNeighborsCoords() = arrayOf(
        Coords(x - 1, y),
        Coords(x + 1, y),
        Coords(x, y - 1),
        Coords(x, y + 1),
    )
}

fun numOfZabor(): Int {
    val destroyedSet = mutableSetOf<Coords>()

    val numOfDestroyed = readln().trim().toInt()

    var result = 0

    repeat(numOfDestroyed) {
        val str = readln().trim().split(" ")
        val coord = Coords(str[0].toInt(), str[1].toInt())

        destroyedSet.add(coord)
        result += 4
        coord.getNeighborsCoords().forEach {
            if(destroyedSet.contains(it)) {
                result -= 2
            }
        }
    }
    return result
}

fun main() {
    println(numOfZabor())
}
