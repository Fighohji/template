#!/bin/bash

# 编译 C++ 程序
g++ -o std_exec std.cpp
g++ -o main_exec main.cpp
if [ ! -f std_exec ] || [ ! -f main_exec ]; then
    echo "Compilation failed!"
    exit 1
fi
# 运行次数
ITERATIONS=100

# 计数器
count=0

# 生成测试数据并进行对拍
while [ $count -lt $ITERATIONS ]
do
    # 生成随机测试数据
    python3 generator.py > input.txt

    # 运行标准程序和待测程序
    ./std_exec < input.txt > output_std.txt
    ./main_exec < input.txt > output_main.txt

    # 比较输出
    if ! python3 compare.py output_std.txt output_main.txt; then
    # if ! diff -q output_std.txt output_main.txt > /dev/null; then
        echo "Wrong Answer!"
        echo "----------------------"
        echo "Input:" 
        cat input.txt
        echo
        echo "----------------------"
        echo "Correct Output:"
        cat output_std.txt
        echo "----------------------"
        echo "Wrong Output:"
        cat output_main.txt
        break
    fi

    echo "Case $((count + 1)) passed"
    count=$((count + 1))
done

# 删除生成的可执行文件和临时文件
rm std_exec main_exec input.txt output_std.txt output_main.txt

