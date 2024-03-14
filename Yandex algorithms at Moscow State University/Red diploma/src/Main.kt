fun isRed(): String {
    val numOfMarks = readln().trim().toInt()
    val marks = readln().trim().split(" ")

    val RED = "Red"
    val BLUE = "Blue"

    var badMarkCounter = 0
    var has3 = false

    marks.forEach {
        when(it.toInt()) {
            3 -> {
                if (has3) {
                    return BLUE
                }
                ++badMarkCounter
                has3 = true
            }
            4 -> {
                ++badMarkCounter
            }
        }
        if (4 * badMarkCounter > numOfMarks) {
            return BLUE
        }
    }
    return RED
}

fun main() {
    println(isRed())
}
