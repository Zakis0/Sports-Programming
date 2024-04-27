//https://leetcode.com/problems/validate-binary-search-tree
class TreeNode(var `val`: Int) {
    var left: TreeNode? = null
    var right: TreeNode? = null
}
fun recIsValidBST2(root: TreeNode?, bottomBoundary: Long, topBoundary: Long): Boolean {
    root?.left?.let { if(it.`val` >= Math.min(root.`val`.toLong(), topBoundary) || it.`val` <= bottomBoundary) return false }
    root?.right?.let { if(it.`val` >= topBoundary || it.`val` <= Math.max(root.`val`.toLong(), bottomBoundary)) return false }
    return root?.left?.let {recIsValidBST2(it, bottomBoundary, Math.min(root.`val`.toLong(), topBoundary))} ?: true &&
            root?.right?.let {recIsValidBST2(it, Math.max(root.`val`.toLong(), bottomBoundary), topBoundary)} ?: true
}
fun recIsValidBST(root: TreeNode?, bottomBoundary: Long, topBoundary: Long): Boolean {
    if (root == null) return true
    if (root.`val` in (bottomBoundary + 1)..<topBoundary)
        return recIsValidBST(root.left, bottomBoundary, root.`val`.toLong()) &&
            recIsValidBST(root.right, root.`val`.toLong(), topBoundary)
    return false
}
fun isValidBST(root: TreeNode?) = recIsValidBST(root, Long.MIN_VALUE, Long.MAX_VALUE)
fun main() {
    println(isValidBST(null))
    println(isValidBST(
    TreeNode(4).apply {
        left = TreeNode(2).apply {
            left = TreeNode(1)
            right = TreeNode(3)
        }
        right = TreeNode(6).apply {
            left = TreeNode(5)
            right = TreeNode(7)
        }
    }))
    println(isValidBST(
        TreeNode(2).apply {
            left = TreeNode(1)
            right = TreeNode(3)
        }))
    println(!isValidBST(
        TreeNode(5).apply {
            left = TreeNode(2).apply {
                left = TreeNode(1)
            }
            right = TreeNode(4).apply {
                left = TreeNode(3)
                right = TreeNode(6)
            }
        }))
    println(!isValidBST(
        TreeNode(2).apply {
            right = TreeNode(4).apply {
                left = TreeNode(1)
            }
        }))
    println(!isValidBST(
        TreeNode(5).apply {
            left = TreeNode(4).apply {
                right = TreeNode(5)
            }
        }))
    println(!isValidBST(
        TreeNode(2).apply {
            left = TreeNode(2)
            right = TreeNode(2)
        }))
    println(isValidBST(
        TreeNode(-2147483648).apply {
            right = TreeNode(2147483647)
        }))
}