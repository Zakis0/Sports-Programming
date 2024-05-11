//https://leetcode.com/problems/symmetric-tree/
class TreeNode(var `val`: Int) {
    var left: TreeNode? = null
    var right: TreeNode? = null
}
fun isSymmetricSplit(leftTree: TreeNode?, rightTree: TreeNode?): Boolean {
    if (leftTree == null || rightTree == null) return leftTree == rightTree
    return leftTree.`val` == rightTree.`val` &&
            isSymmetricSplit(leftTree.left, rightTree.right) &&
            isSymmetricSplit(leftTree.right, rightTree.left)
}
fun isSymmetric(root: TreeNode?): Boolean {
    return isSymmetricSplit(root?.left, root?.right)
}
fun main() {
    println(isSymmetric(TreeNode(1).apply {
        left = TreeNode(2).apply {
            left = TreeNode(3)
            right = TreeNode(4)
        }
        right = TreeNode(2).apply {
            left = TreeNode(4)
            right = TreeNode(3)
        }
    }))
    println(isSymmetric(TreeNode(1).apply {
        left = TreeNode(2).apply {
            right = TreeNode(3)
        }
        right = TreeNode(2).apply {
            right = TreeNode(3)
        }
    }))
}