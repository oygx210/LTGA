# Test_1

* [1st version](#20201208-1st-version)

* [2nd version](#20201208-2nd-version)

* [3rd version](#20201214-3rd-version)

* [4th version](#20201215-4th-version)

另找一个算例进行测试

## 20201208 1st version

移植LTGA_5，验证成功。

## 20201208 2nd version

PSO求解6变量优化问题，没有找到可行解。

## 20201214 3rd version

* 将搜索空间改为范围2，借用PSO算法进行随机搜索

    引力辅助时间[0,1]，引力辅助半径固定为r_min，旋转角固定为pi/2，xyz方向速度分量范围为[-0.1,0.1]

    并行随机搜索500次，用时2606秒，没有找到可行解。

* 将搜索空间改为范围3，借用PSO算法进行随机搜索

    引力辅助时间[0,1]，引力辅助半径固定为r_min，旋转角固定为pi/2，xyz方向速度分量范围为[-0.2,0.2]

    并行随机搜索500次，用时4188秒，没有找到可行解。

## 20201215 4th version

* 将转移时间改为6年，进行随机搜索

    引力辅助时间[0,1]，引力辅助半径固定为r_min，旋转角固定为pi/2，xyz方向速度分量范围为[-0.2,0.2]

    并行随机搜索500次，用时7271秒，找到可行解，剩余质量为14967.607kg。

    之前搜索不到可行解的原因很可能是问题本身无法求解/很难求解。