class MList(
    var value: String? = null,
    var prev: MList? = null,
    var next: MList? = null
)

class phoneList(val maxSize: Int) {
    val mList: MList = MList()

    private var curSize = 0

    private val mapOfPhones = mutableMapOf<String, MList>()
    private val setOfPhones = mutableSetOf<String>()

    private var end: MList

    init {
        end = MList()
        mList.next = end
        end.prev = mList
    }

    fun add(phone: String) {
        if (setOfPhones.contains(phone)) {
            val prev = mapOfPhones[phone]!!.prev
            mapOfPhones[phone]!!.prev = mapOfPhones[phone]!!.next
            mapOfPhones[phone]!!.next = prev

            mapOfPhones[phone]!!.next = mList.next
            mList.next = mapOfPhones[phone]!!
            mapOfPhones[phone]!!.prev = mList
        }
        else {
            if (curSize < maxSize) {
                ++curSize
                setOfPhones.add(phone)
                val newNode = MList()
                newNode.value = phone

                mapOfPhones[phone] = newNode

                newNode.next = mList.next
                mList.next = newNode
                newNode.prev = mList

                setOfPhones.add(phone)
            }
            else {
                setOfPhones.remove(end.prev!!.value)
                mapOfPhones.remove(end.prev!!.value)

                end = end.prev!!

                setOfPhones.add(phone)
                val newNode = MList()
                newNode.value = phone

                mapOfPhones[phone] = newNode

                newNode.next = mList.next
                mList.next = newNode
                newNode.prev = mList

                setOfPhones.add(phone)
            }
        }
    }

    fun print() {
        var curEl = mList
        repeat(curSize) {
            curEl = curEl.next!!
            println(curEl.value)
        }
        repeat(maxSize - curSize) {
            println(EMPTY)
        }
    }
    companion object {
        const val EMPTY = "<Empty>"
    }
}

fun recent() {
    val input = readln().trim().split(" ")
    val m = input[0].toInt()
    val n = input[1].toInt()
    val phoneList = phoneList(m)

    repeat(n) {
        val phone = readln().trim()
        phoneList.add(phone)
    }

    phoneList.print()
}