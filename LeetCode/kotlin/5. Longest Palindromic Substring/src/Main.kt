//https://leetcode.com/problems/longest-palindromic-substring
data class Info(
    var palindromeStart: Int = 0,
    var palindromeEnd: Int = 0,
    var resultPalindromeStartIndex: Int = 0,
    var resultPalindromeEndIndex: Int = 0
)
fun checkPalindrome(s: String, info: Info) {
    while (info.palindromeStart >= 0 && info.palindromeEnd < s.length) {
        if (s[info.palindromeStart] == s[info.palindromeEnd]) {
            --info.palindromeStart
            ++info.palindromeEnd
        }
        else {
            if (info.palindromeEnd - info.palindromeStart - 1 >
                info.resultPalindromeEndIndex - info.resultPalindromeStartIndex) {
                info.resultPalindromeStartIndex = info.palindromeStart + 1
                info.resultPalindromeEndIndex = info.palindromeEnd
            }
            break
        }
    }
    if (info.palindromeEnd - info.palindromeStart - 1 >
        info.resultPalindromeEndIndex - info.resultPalindromeStartIndex) {
        info.resultPalindromeStartIndex = info.palindromeStart + 1
        info.resultPalindromeEndIndex = info.palindromeEnd
    }
}
fun longestPalindrome(s: String): String {
    val info = Info()
    s.forEachIndexed { index, _ ->
        checkPalindrome(s, info.apply {
            palindromeStart = index
            palindromeEnd = index + 1
        })
        checkPalindrome(s, info.apply {
            palindromeStart = index - 1
            palindromeEnd = index + 1
        })
    }
    return s.substring(info.resultPalindromeStartIndex, info.resultPalindromeEndIndex)
}
fun main() {
    println(longestPalindrome("cbbd"))
}