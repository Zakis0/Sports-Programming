//https://leetcode.com/problems/lru-cache
import java.util.*
class ConstantTimeQueue<T> {
    private val map = HashMap<T, Node<T>>()
    private val list = MyDoublyLinkedList<T>()

    val size get() = map.size
    val first get() = list.head?.data

    inner class Node<T>(val data: T) {
        var next: Node<T>? = null
        var prev: Node<T>? = null
    }
    private inner class MyDoublyLinkedList<T> {
        var head: Node<T>? = null
        var tail: Node<T>? = null

        fun addFirst(data: T) {
            val newNode = Node(data)
            if (head == null) {
                head = newNode
                tail = newNode
            }
            else {
                newNode.next = head
                head?.prev = newNode
                head = newNode
            }
        }
        fun addLast(data: T) {
            val newNode = Node(data)
            if (tail == null) {
                head = newNode
                tail = newNode
            }
            else {
                tail?.next = newNode
                newNode.prev = tail
                tail = newNode
            }
        }
        fun addFirst(node: Node<T>) {
            if (head == null) {
                head = node
                tail = node
            }
            else {
                node.next = head
                head?.prev = node
                head = node
            }
        }
        fun addLast(node: Node<T>) {
            if (tail == null) {
                head = node
                tail = node
            }
            else {
                tail?.next = node
                node.prev = tail
                tail = node
            }
        }
        fun remove(node: Node<T>) {
            val prevNode = node.prev
            val nextNode = node.next
            if (prevNode == null) head = nextNode else prevNode.next = nextNode
            if (nextNode == null) tail = prevNode else nextNode.prev = prevNode
        }
        fun removeFirst() {
            if (head == null) return
            head = head?.next
            head?.prev = null
            if (head == null) tail = null
        }
        fun removeLast() {
            if (tail == null) return
            tail = tail?.prev
            tail?.next = null
            if (tail == null) head = null
        }
        fun print(addLineBreak: Boolean = true) {
            var curNode = head
            while (curNode != null) {
                print("${curNode.data} ")
                curNode = curNode.next
            }
            if (addLineBreak) println()
        }
    }
    fun addLast(value: T) {
        val node = Node(value)
        map[value] = node
        list.addLast(node)
    }
    fun remove(value: T) {
        val node = map[value] ?: return
        list.remove(node)
        map.remove(value)
    }
    fun removeFirst() {
        list.head?.let { remove(it.data) }
    }
    fun print(addLineBreak: Boolean = true) = list.print(addLineBreak)
}
class LRUCache2(private val capacity: Int) {
    private val queue = ConstantTimeQueue<Int>()
    private val map = mutableMapOf<Int, Int>()
    fun get(key: Int): Int {
        if (map.containsKey(key)) {
            queue.remove(key)
            queue.addLast(key)
            return map[key]!!
        }
        return -1
    }
    fun put(key: Int, value: Int) {
        if (map.containsKey(key)) {
            queue.remove(key)
            queue.addLast(key)
        }
        else {
            if (queue.size == capacity) {
                map.remove(queue.first!!)
                queue.removeFirst()
            }
            queue.addLast(key)
        }
        map[key] = value
    }
    fun print(addLineBreak: Boolean = true) = queue.print(addLineBreak)
}

class LRUCache(private val capacity: Int) {
    private val map = LinkedHashMap<Int, Int>()

    fun get(key: Int): Int {
        if (map.containsKey(key)) {
            val value = map.remove(key)!!
            map[key] = value
            return value
        }
        return -1
    }
    fun put(key: Int, value: Int) {
        if (map.containsKey(key)) {
            map.remove(key)
        }
        else if (map.size == capacity) {
            val leastRecentlyUsed = map.keys.iterator().next()
            map.remove(leastRecentlyUsed)
        }
        map[key] = value
    }
}

fun test1() {
    val lRUCache = LRUCache(2)
    lRUCache.put(1, 1) // cache is {1=1}
    lRUCache.put(2, 2) // cache is {1=1, 2=2}
    println(lRUCache.get(1)) // return 1
    lRUCache.put(3, 3) // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    println(lRUCache.get(2)) // returns -1 (not found)
    lRUCache.put(4, 4) // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    println(lRUCache.get(1)) // return -1 (not found)
    println(lRUCache.get(3)) // return 3
    println(lRUCache.get(4)) // return 4
}

fun test2() {
    val lRUCache = LRUCache(1)
    lRUCache.put(2, 1)
    println(lRUCache.get(2))
}

fun main() {
    test1();println()
    test2();println()
}