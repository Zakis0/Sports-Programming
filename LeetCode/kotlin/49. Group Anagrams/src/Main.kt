//https://leetcode.com/problems/group-anagrams
fun groupAnagrams(strs: Array<String>): List<List<String>> {
    val mapOfHash = mutableMapOf<String, MutableList<String>>()
    strs.forEach { str ->
        val sortedString = str.toCharArray().sorted().joinToString("")
        if (mapOfHash[sortedString] == null) {
            mapOfHash[sortedString] = mutableListOf(str)
        }
        else {
            mapOfHash[sortedString]?.add(str)
        }
    }
    return mapOfHash.values.toList()
}
fun main() {
    groupAnagrams(arrayOf("mod","mop","pip","tug","hop","dog","met","zoe","axe","mug","fdr","for","fro","fdr","pap","ray","lop","nth","old","eva","ell","mci","wee","ind","but","all","her","lew","ken","awl","law","rim","zit","did","yam","not","ref","lao","gab","sax","cup","new","job","new","del","gap","win","pot","lam","mgm","yup","hon","khz","sop","has","era","ark")).forEach { it.forEach { print("$it ") }; println() }
}