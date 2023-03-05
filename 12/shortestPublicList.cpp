#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
using namespace std;

/***
 * 1. 该算法的思路为：相同部分 + 不同部分 + 相同部分 + 不同部分
 * 2. 以字符串result来储存最终的结果
 * 以 "a b a c" 和 "c a b"进行举例， 从后往前看，
 *     1.1  b和c不同，但以b、c结尾的字符串的最长公共序列的长度为2
 *     1.2  接着从c开始往前移动到a, 观察以a结尾的字符串和上面以b结尾的字符串的最长公共序列是否还为2， 若仍然是2，说明b是字符串所独有的，并不是
 *          公共部分。这时就将 'b' append到result中
 *     1.3  接着开始比较 "a b a" 和 "c a b" ，可以观察到 'a' 和 'b'并不相等，从 'b' 开始往前移动到'a', 字符串 "a b a" 和 "c a" 的最长公共
 *          序列是 1， 而从 'a' 往前移动到 'b' , 两个字符串的最长公共序列仍然是2，说明公共部分在字符串 "a b" 和 "c a b" 之间，这时就可以把'a'
 *          append到result 中，此时result等于 "c a",可以观察到result中的值都是第一个字符串中独有的部分，过完独有的部分后就开始是公共部分的了，
 *     1.4  可观察到'b' 和 'b' 相等，说明 'b' 是公共序列中的一个，这时可把 'b' append到 result中，这时result就为 "c a b", 然后两个字符串的
 *          指针同时往前移动一格，'a' 等于 'a'， 说明'a'也是公共序列中的一个，此时可把 'a' append 到 result 中去，这时result就为 "c a b a",
 *     1.5  第一个字符串就全部遍历完了，最后把第2个字符串剩余的字符依次添加到result中去即可， 最后 result 就为 "c a b a c" , reverse过来就是
 *          "c a b a c"
*/

/*****************用动态规划求解最长公共序列****************************
 * 背景：给定2个字符串 s1 和 s2， 求s1 和 s2的最长公共序列
 * 解读：1. 最长公共序列的位置有三种：首端、尾端和中间
 *      2. 由于有2个字符串，所以可以用一个二维的数组来作为动态规划的数组
 *      3. f[i][j]标识 s1的子串（下标为[0,i])和s2的子串(下标为[0, j])的最长公共序列个数  ->  也就是在[i, j]状态，也就是当前状态的值
 *      4. 当前状态的值是从上一个状态转移过来的，其状态转移方程如下：
 *          f[i][j] = f[i - 1][j - 1] + 1, s1[i] == s2[j]
 *          f[i][j] = max(f[i - 1][j], f[i][j - 1]), s1[i] != s2[j]
 *      5. 由上述的状态转移方程，就能获取到每个状态的最长公共序列长度
*/

/****************举例1： s1 = "a b c d" , s2 = "d b c a"**************
 * 观察：可以看到s1和s2的公共区间在中间位置
 * 预测：最后拼接的result为 "a d c b d a" -> reverse之后为 "a d b c d a"
 * 最后的结果：与预测的一样
 * 结论1：拼接的规则如下：
 *      1. 若公共区间在两个字符串的中间，那么就是 s1前端非公共字符串 + s2前端非公共字符串 + 公共序列 + s1后端非公共字符串 + s2后端非公共字符串
 *      2. 若公共区间在s1的前端，在s2的中间，那么就是 s2的前端非公共字符串 + 公共序列 + s1后端非公共序列 + s2后端非公共序列
 *      ...依次类推
*/

/*****************说明：该题的公共区间所处的位置只有“前、后” “后，前”两种可能*
 * 若一个在前端，一个在后端：s2 前端非公共序列 + 公共序列 + s1 后端非公共序列
 * 若一个在后端，一个在前端：s1 前端非公共序列 + 公共序列 + s2 后端非公共序列
 * */
string shortestCommonSupersequence(string str1, string str2) {
    // 计算状态转移方程
    int m = str1.size();
    int n = str2.size();
    str1 = " " + str1;
    str2 = " " + str2;
    // 构造一个(m + 1, n + 1) 矩阵
    vector<vector<int>> f(m + 10, vector<int>(n + 10));
    // 两重循环对二维数组赋值
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (str1[i] == str2[j]) {
                f[i][j] = f[i - 1][j - 1] + 1;
            } else {
                f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            }
        }
    }
    // 逆向回溯进行拼接
    string res;
    int s1 = m;
    int s2 = n;
    while (s1 != 0 || s2 != 0) {
        if (s1 == 0) {
            res.append(1, str2[s2]);
            --s2;
        } else if (s2 == 0) {
            res.append(1, str1[s1]);
            --s1;
        } else {

            if (str1[s1] != str2[s2]) {
                if (f[s1][s2] == f[s1 - 1][s2]) {
                    res.append(1, str1[s1]);
                    --s1;
                } else if (f[s1][s2] == f[s1][s2 - 1]) {
                    res.append(1, str2[s2]);
                    --s2;
                }
            } else {
                res.append(1, str1[s1]);
                --s1;
                --s2;
            }
        }
    }
    return res;
}

int main() {
    string s1 = "abac";
    string s2 = "cab";
    cout << shortestCommonSupersequence(s1, s2) << endl;
    return 0;
}
 