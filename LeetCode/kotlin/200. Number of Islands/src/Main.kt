//https://leetcode.com/problems/number-of-islands
fun BFS(row: Int, col: Int, grid: Array<CharArray>, visited: Array<BooleanArray>) {
    if (visited[row][col]) return
    visited[row][col] = true
    if (col + 1 < grid[0].size && grid[row][col + 1] == '1') BFS(row, col + 1, grid, visited)
    if (col - 1 >= 0 && grid[row][col - 1] == '1') BFS(row, col - 1, grid, visited)
    if (row + 1 < grid.size && grid[row + 1][col] == '1') BFS(row + 1, col, grid, visited)
    if (row - 1 >= 0 && grid[row - 1][col] == '1') BFS(row - 1, col, grid, visited)
}
fun numIslands(grid: Array<CharArray>): Int {
    val visited = Array(grid.size) { BooleanArray(grid[0].size) } //default value is false
    var result = 0
    for (row in grid.indices) {
        for (col in grid[row].indices) {
            if (grid[row][col] == '1' && !visited[row][col]) {
                ++result
                BFS(row, col, grid, visited)
            }
        }
    }
    return result
}
fun main() {
    println(numIslands(arrayOf(
        charArrayOf('1','1','1','1','0'),
        charArrayOf('1','1','0','1','0'),
        charArrayOf('1','1','0','0','0'),
        charArrayOf('0','0','0','0','0'),
    )))
    println(numIslands(arrayOf(
        charArrayOf('1','1','0','0','0'),
        charArrayOf('1','1','0','0','0'),
        charArrayOf('0','0','1','0','0'),
        charArrayOf('0','0','0','1','1'),
    )))
    println(numIslands(arrayOf(
        charArrayOf('1','0','1','1','0','1','1'),
    )))
}