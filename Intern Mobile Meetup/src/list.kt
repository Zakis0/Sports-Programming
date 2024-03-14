//class MList(
//    var value: String? = null,
//    var prev: MList? = null,
//    var next: MList? = null
//)
//
//class phoneList(val maxSize: Int) {
//    val mList: MList = MList()
//
//    private var curSize = 0
//
//    private val mapOfPhones = mutableMapOf<String, MList>()
//    private val setOfPhones = mutableSetOf<String>()
//
//    private val start = mList
//    private var end = mList
//
//    fun add(phone: String) {
//        if (setOfPhones.contains(phone)) {
//            val prev = mapOfPhones[phone]!!.prev
//            mapOfPhones[phone]!!.prev = mapOfPhones[phone]!!.next
//            mapOfPhones[phone]!!.next = prev
//
//            mapOfPhones[phone]!!.next = mList.next
//            mList.next = mapOfPhones[phone]!!
//            mapOfPhones[phone]!!.prev = mList
//        }
//        else {
//            if (curSize < maxSize) {
//                ++curSize
//                setOfPhones.add(phone)
//                val newNode = MList()
//                newNode.value = phone
//
//                mapOfPhones[phone] = newNode
//
//                newNode.next = mList.next
//                mList.next = newNode
//                newNode.prev = mList
//
//                setOfPhones.add(phone)
//            }
//            else {
//                end = end.prev!!
//
//                setOfPhones.remove(end.value)
//                mapOfPhones.remove(end.value)
//
//                setOfPhones.add(phone)
//                val newNode = MList()
//                newNode.value = phone
//
//                mapOfPhones[phone] = newNode
//
//                newNode.next = mList.next
//                mList.next = newNode
//                newNode.prev = mList
//
//                setOfPhones.add(phone)
//            }
//        }
//    }
//
//    fun print() {
//        var curEl = mList
//        repeat(curSize) {
//            println(curEl.value)
//            curEl = curEl.next!!
//        }
//        repeat(maxSize - curSize) {
//            println(EMPTY)
//        }
//    }
//    companion object {
//        const val EMPTY = "<Empty>"
//    }
//}