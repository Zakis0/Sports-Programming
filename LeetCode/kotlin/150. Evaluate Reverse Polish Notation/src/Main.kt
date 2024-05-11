//https://leetcode.com/problems/evaluate-reverse-polish-notation
import java.util.*
fun evalRPN(tokens: Array<String>): Int {
    val stack = Stack<Int>()
    for (token in tokens) {
        val num = token.toIntOrNull()
        if (num != null) {
            stack.push(num)
            continue
        }
        when (token) {
            "+" -> stack.push(stack.pop() + stack.pop())
            "-" -> {
                val second = stack.pop()
                val first = stack.pop()
                stack.push(first - second)
            }
            "*" -> stack.push(stack.pop() * stack.pop())
            "/" -> {
                val second = stack.pop()
                val first = stack.pop()
                stack.push(first / second)
            }
        }
    }
    return stack.peek()
}
fun main() {
    println(evalRPN(arrayOf("2","1","+","3","*")))
    println(evalRPN(arrayOf("4","13","5","/","+")))
    println(evalRPN(arrayOf("10","6","9","3","+","-11","*","/","*","17","+","5","+")))
}