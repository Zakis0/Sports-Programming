//https://leetcode.com/problems/remove-nth-node-from-end-of-list/
class ListNode(var `val`: Int) {
    var next: ListNode? = null
}
fun removeNthFromEnd(head: ListNode?, n: Int): ListNode? {
    var curNode = head
    var numOfNodes = 0
    while (curNode != null) {
        ++numOfNodes
        curNode = curNode.next
    }
    var nodeToDelete = head
    if (numOfNodes - n - 1 == -1) {
        return head?.next
    }
    repeat(numOfNodes - n - 1) {
        nodeToDelete = nodeToDelete!!.next
    }
    nodeToDelete?.next = nodeToDelete!!.next?.next
    return head
}
fun main() {
    var node = removeNthFromEnd(ListNode(1).apply {
        next = ListNode(2).apply {
            next = ListNode(3).apply {
                next = ListNode(4).apply {
                    next = ListNode(5)
                }
            }
        }
    }, 2)
    while (node != null) { print("${node.`val`} ");node = node.next };println()
    node = removeNthFromEnd(ListNode(1), 1)
    while (node != null) { print("${node.`val`} ");node = node.next };println()
    node = removeNthFromEnd(ListNode(1).apply {
        next = ListNode(2)
   }, 1)
    while (node != null) { print("${node.`val`} ");node = node.next };println()
}