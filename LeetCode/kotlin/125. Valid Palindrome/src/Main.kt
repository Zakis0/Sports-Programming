//https://leetcode.com/problems/valid-palindrome
fun isPalindrome(s: String): Boolean {
    val alphanumericS = s.filter { it.isDigit() || it.isLetter() }.lowercase()
    return (alphanumericS.substring(0, alphanumericS.length / 2) ==
        alphanumericS.substring(
            if(alphanumericS.length % 2 == 1) 1 + alphanumericS.length / 2
            else alphanumericS.length / 2, alphanumericS.length).reversed())
}
fun main() {
    println(isPalindrome("A man, a plan, a canal: Panama"))
    println(isPalindrome("race a car"))
    println(isPalindrome(" "))
}