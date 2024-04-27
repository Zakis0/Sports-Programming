//https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal
import java.util.*
class TreeNode(var `val`: Int) {
    var left: TreeNode? = null
    var right: TreeNode? = null
}
fun zigzagRecBfs(node: TreeNode?, result: LinkedList<LinkedList<Int>>, depth: Int = 0): List<List<Int>> {
    if (node != null) {
        if (result.size - 1 < depth) {
            result.add(LinkedList())
        }
        if (depth % 2 == 0) {
            result[depth].addLast(node.`val`)
        }
        else {
            result[depth].addFirst(node.`val`)
        }
        zigzagRecBfs(node.left, result, depth + 1)
        zigzagRecBfs(node.right, result, depth + 1)
    }
    return result
}
fun zigzagLevelOrder(root: TreeNode?): List<List<Int>> {
    return zigzagRecBfs(root, LinkedList<LinkedList<Int>>())
}
fun main() {
    zigzagLevelOrder(
    TreeNode(1).apply {
        left = TreeNode(3).apply {
            left = TreeNode(4)
            right = TreeNode(5)
        }
        right = TreeNode(2).apply {
            left = TreeNode(6)
            right = TreeNode(7)
        }
    }).forEach { depth -> depth.forEach { print("$it ") }; println() }
    zigzagLevelOrder(null).forEach { depth -> depth.forEach { print("$it ") }; println() }
}