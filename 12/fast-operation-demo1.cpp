#include <iostream>
#include <limits.h>
// 快速乘，把乘数转换成二进制
// a * 11 = a * (1011) = a* 2^0 + a * 2^1 + a * 2^3
///
using namespace std;
/* 算法：
1. a * b 的本质是 b个a 相加
2. 举例说明：3 * 4
    ---->  3 + 3 = 6    ->  2个3相加   ->  3*2^1
    ---->  6 + 6 = 12   ->  4个3相加   ->  3*2^2
    4 用科学计数法表示就是 2^2
    那么计算机是如何得出这个结论的呢？
    4 用二进制表示就是  100  ->  (0* 2^0 + 0* 2^1 + 1* 2^2)

    所以 3*4 就是 3 * 2^2  ->  2次自增
    a* 2^b   ->  就是a 进行b次自增
*/

/*****************a* b 如何进行快速乘***********************
 * 1. 把 a * b 转换为 a * (2^b1 + 2^b2 + 2^b3)
 * 2. a* 2^b1 从a开始一共进行b1次自增
 *    a* 2^b2 从a开始一共进行b2次自增
 *    a* 2^b3 从a开始一共进行b3次自增
 *    a * b就是三次自增的和
   3. 将b转换为科学计数的方式，可以用 & 
   4. 总思路(举例说明):
        1) a* b  ->  a* (111011101)
        2）最高位就是 a 进行了9次自增
        3）最后的结果是 a 进行了9次自增，8次自增，7次自增，5次自增，4次自增，3次自增，1次自增的结果之和
*/
long long ksc(long long a, long long b) {
    long long ans = 0;   // 初始化的必要性
    while (b != 0) {

        if (b & 1 != 0) {
            ans += a;
        }
        a += a;
        b >>= 1;
    }
    return ans;
}

// 实现快速幂运算的具体代码
/*
* a^b = a^(2^b1 + 2^b2 + 2^b3) = a^2^b1 * a^2^b2 * a^2^b3
* a^2^b1  ->  a进行b1次自乘
  a^2^b2  ->  a进行b2次自乘
  a^2^b3  ->  a进行b3次自乘
*/
/**
 * 算法如下所示：
 * 1. 首先将 b 分解成二进制的形式
 * 2. 根据 b 最高位（该位的值为1）的位数，让a依次自乘，获取每一位所对应的值
 * 3. 最后把二进制形式中1所对应值加在一起，就可得出最后的值
*/
long long ksm(long long a, long long b) {
    long long ans = 1;
    long long base = a;
    while (b != 0) {
        if (b & 1 != 0) {
            ans *= base;
        }
        base *= base;
        b >>= 1;
    }
    return ans;
}

// 整数除法
int divide (int a, int b) {
    // 考虑被除数为最小值的情况
    if (a == INT_MIN) {
        if (b == 1) {
            return INT_MIN;
        }
        if (b == -1) {
            return INT_MAX;
        }
    }
    // 考虑除数为最小值的情况
    if (b == INT_MIN) {
        return a == INT_MIN ? 1 : 0;
    }
    // 考虑除数为0的情况
    if (a == 0) {
        return 0;
    }
    // 一般情况，使用二分查找
    // 将所有正数取相反数，这样就只要考虑一种情况
    bool rev = false;
    if (a > 0) {
        a = -a;
        rev = !rev;
    }
    if (b > 0) {
        b = -b;
        rev = !rev;
    }
    // 快速乘
    // y->b, z->mid, x->a
    // y = 2, z = 3, x = 6
    auto quickAdd = [](int y, int z, int x) {
        // x和y是负数，z是正数
        // 需要判断 x * z >= y是否成立
        int result = 0; 
        int add = y;
        while (z != 0) {
            if (z & 1 == 1) {
                if (result < x - add) {
                    return false;
                }
                result += add;
            }
            if (z != 1) {
                if (add < x - add) {
                    return false;
                }
                add += add;
            }
            z >>= 1;
        }
        return true;
    };
    int left = 1;
    int right = INT_MAX;
    int ans = 0;
    while (left <= right) {
        // 注意溢出，并且不能使用除法
        int mid = left + ((right - left) >> 1);
        bool check = quickAdd(b, a, mid);
        if (check) {
            ans = mid;
            // 注意溢出
            if (mid == INT_MAX) {
                break;
            }
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return rev ? -ans : ans;
}


int main() {
    long long a = 2;
    long long b = 3;

    auto res1 = ksc(a, b);
    cout << "res1 " << res1 << endl;

    auto res2 = ksm(a, b);
    cout << "res2 " << res2 << endl;

    // 正数除法
    auto res3 = divide(a, b);
    cout << "res3 " << res3 << endl;
}