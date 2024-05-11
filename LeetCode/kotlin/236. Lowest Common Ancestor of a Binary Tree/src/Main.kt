//https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree
import java.util.*
class TreeNode(var `val`: Int = 0) {
    var left: TreeNode? = null
    var right: TreeNode? = null
}
fun stackDFS(root: TreeNode?, target: TreeNode?): List<TreeNode>? {
    if (root == null) {
        return null
    }
    val stack = Stack<TreeNode>().apply { push(root) }
    val pathMap = mutableMapOf<TreeNode, List<TreeNode>>()

    pathMap[root] = listOf(root)

    while (stack.isNotEmpty()) {
        val node = stack.pop()
        val currentPath = pathMap[node] ?: continue
        if (node.`val` == target!!.`val`) {
            return currentPath
        }
        node.left?.let {
            stack.push(it)
            pathMap[it] = currentPath + it
        }
        node.right?.let {
            stack.push(it)
            pathMap[it] = currentPath + it
        }
    }
    return null
}

fun pathToNode(root: TreeNode?, target: TreeNode?): List<TreeNode>? {
    val path = mutableListOf<TreeNode>()
    return DFS(root, target, path)
}

fun DFS(node: TreeNode?, target: TreeNode?, path: MutableList<TreeNode>): List<TreeNode>? {
    if (node == null) {
        return null
    }
    path.add(node)
    if (node.`val` == target?.`val`) {
        return path.toList()
    }
    val leftResult = DFS(node.left, target, path)
    if (leftResult != null) {
        return leftResult
    }
    val rightResult = DFS(node.right, target, path)
    if (rightResult != null) {
        return rightResult
    }
    path.removeAt(path.size - 1)
    return null
}

fun lowestCommonAncestor(root: TreeNode?, p: TreeNode?, q: TreeNode?): TreeNode? {
    val pPath = pathToNode(root, p)!!
    val qPath = pathToNode(root, q)!!

    var pIndex = pPath.size - 1
    var qIndex = qPath.size - 1
    while (pPath[pIndex].`val` != qPath[qIndex].`val`) {
        if (pIndex > qIndex) {
            --pIndex
        }
        else {
            --qIndex
        }
    }
    return pPath[pIndex]
}
fun main() {
    println(lowestCommonAncestor(TreeNode(3).apply {
        left = TreeNode(5).apply {
            left = TreeNode(6)
            right = TreeNode(2).apply {
                left = TreeNode(7)
                right = TreeNode(4)
            }
        }
        right = TreeNode(1).apply {
            left = TreeNode(0)
            right = TreeNode(8)
        }
    }, TreeNode(5), TreeNode(1))?.`val`)
    println(lowestCommonAncestor(TreeNode(3).apply {
        left = TreeNode(5).apply {
            left = TreeNode(6)
            right = TreeNode(2).apply {
                left = TreeNode(7)
                right = TreeNode(4)
            }
        }
        right = TreeNode(1).apply {
            left = TreeNode(0)
            right = TreeNode(8)
        }
    }, TreeNode(5), TreeNode(4))?.`val`)
    println(lowestCommonAncestor(TreeNode(1).apply {
        left = TreeNode(2)
    }, TreeNode(1), TreeNode(2))?.`val`)
}