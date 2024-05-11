//https://leetcode.com/problems/implement-queue-using-stacks
import java.util.*
class MyQueue {
    private val stackIn = Stack<Int>()
    private val stackOut = Stack<Int>()

    fun push(x: Int) {
        stackIn.push(x)
    }
    fun pop(): Int {
        fillStackOutIfEmpty()
        return stackOut.pop()
    }
    fun peek(): Int {
        fillStackOutIfEmpty()
        return stackOut.peek()
    }
    fun empty(): Boolean {
        return stackIn.isEmpty() && stackOut.isEmpty()
    }
    private fun fillStackOutIfEmpty() {
        if (stackOut.isEmpty()) {
            fillStackOut()
        }
    }
    private fun fillStackOut() {
        while (!stackIn.isEmpty()) {
            stackOut.push(stackIn.pop())
        }
    }
    //if we need min, max, gcd, lcm, etc.
    //min = min(stackIn.min(), stackOut.min())
}
fun main() {
    var obj = MyQueue()
    obj.push(1)
    obj.push(2)
    println(obj.peek())
    println(obj.pop())
    println(obj.empty())
}