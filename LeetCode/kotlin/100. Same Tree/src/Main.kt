//https://leetcode.com/problems/same-tree/
class TreeNode(var `val`: Int) {
    var left: TreeNode? = null
    var right: TreeNode? = null
}
fun isSameTree(p: TreeNode?, q: TreeNode?): Boolean {
    if (p == null || q == null) return p == q
    return p.`val` == q.`val` && isSameTree(p.left, q.left) && isSameTree(p.right, q.right)
}
fun main() {
    println(isSameTree(TreeNode(1).apply {
        left = TreeNode(2)
        right = TreeNode(3)
    },
        TreeNode(1).apply {
            left = TreeNode(2)
            right = TreeNode(3)
        }))
    println(isSameTree(TreeNode(1).apply {
        left = TreeNode(2)
    },
        TreeNode(1).apply {
            right = TreeNode(2)
        }))
    println(isSameTree(TreeNode(1).apply {
        left = TreeNode(2)
        right = TreeNode(1)
    },
        TreeNode(1).apply {
            left = TreeNode(1)
            right = TreeNode(2)
        }))
}