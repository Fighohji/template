import sys


def squish_compare(file1, file2):
    """Compare two files using the squish method."""
    try:
        with open(file1, 'r', encoding='utf-8') as f1, open(file2, 'r', encoding='utf-8') as f2:
            # 读取并压缩每个文件的内容
            content1 = [squish_line(line)
                        for line in f1 if squish_line(line) != ""]
            content2 = [squish_line(line)
                        for line in f2 if squish_line(line) != ""]

        # 比较压缩后的内容
        if content1 == content2:
            return True
        else:
            return False
    except FileNotFoundError as e:
        print(f"Error: {e}")
        return False


def squish_line(line):
    """Squish a single line by removing excess whitespace."""
    # 将多个空白符压缩为单个空格，并去除首尾空白
    return ' '.join(line.split())


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python compare.py <file1> <file2>")
        sys.exit(1)

    file1 = sys.argv[1]
    file2 = sys.argv[2]

    if squish_compare(file1, file2):
        sys.exit(0)  # 成功匹配，返回 0
    else:
        sys.exit(1)  # 匹配失败，返回 1
