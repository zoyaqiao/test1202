#include <iostream>
#include <limits.h>
// 快速乘，把乘数转换成二进制
// a * 11 = a * (1011) = a* 2^0 + a * 2^1 + a * 2^3
///
using namespace std;
long long ksc(long long a, long long b) {
    long long ans = 0;
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