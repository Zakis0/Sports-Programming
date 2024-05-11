//https://leetcode.com/problems/implement-rand10-using-rand7/
fun rand10(): Int {
    // rand7() -> rand49() -> rand40() -> rand10()
    var result = 40;
    //rand49() -> rand40()
    while (result >= 40) {
        // rand7() -> rand49()
        // rand(N^2) = N(rand(N) - 1) + rand(N)
        result = 7 * (rand7() - 1) + (rand7() - 1)
    }
    //rand40() -> rand10()
    return result % 10 + 1;
}
fun main() {
    
}