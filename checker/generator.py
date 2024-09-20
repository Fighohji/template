import random
import string


def generate_seq(length, value_range=(0, 1000000000), value_type=int):
    """
    生成一个随机序列，根据指定的长度、范围和数值类型。

    参数:
    - length (int): 序列的长度。
    - value_range (tuple): 序列元素的范围，格式为 (min, max)，闭合区间。
    - value_type (type): 数值类型，可以是 int、float。

    返回:
    - list: 生成的随机序列。
    """
    # 初始化序列
    sequence = []

    # 根据数值类型选择生成函数
    if value_type == int:
        def generator(): return random.randint(value_range[0], value_range[1])
    elif value_type == float:
        def generator(): return random.uniform(value_range[0], value_range[1])
    else:
        raise ValueError(
            "Unsupported value type. Only 'int' and 'float' are supported.")

    # 生成序列
    for _ in range(length):
        value = generator()
        sequence.append(value)

    return sequence


def generate_str(length, charset=string.ascii_lowercase):
    """
    生成一个随机字符串，根据指定的长度和字符集。

    参数:
    - length (int): 字符串的长度。
    - charset (str): 可选字符集，默认包含所有小写字母

    可选集合:
    string.ascii_lowercase, string.ascii_uppercase, string.digits

    返回:
    - str: 生成的随机字符串。
    """
    if length < 0:
        raise ValueError("长度不能为负数")
    if not charset:
        raise ValueError("字符集不能为空")

    # 生成随机字符串
    return ''.join(random.choice(charset) for _ in range(length))


def generate_tree(size, edge_weight_range=None):
    """
    生成一个随机树结构，使用邻接列表表示。

    参数:
    - size (int): 树的大小，即节点的数量。
    - edge_weight_range (tuple): 可选参数，边权的范围 [l, r]，
      默认为 None，表示无边权。

    返回:
    - list: 生成的树结构，以边的列表返回。
    """
    if size < 1:
        raise ValueError("树的大小必须至少为 1")

    # 初始化邻接列表
    edges = []

    # 生成随机树的边
    for node in range(2, size + 1):
        # 随机选择一个父节点，确保无环生成
        parent = random.randint(1, node - 1)

        if edge_weight_range:
            # 生成边权范围内的随机权重
            weight = random.randint(edge_weight_range[0], edge_weight_range[1])
            edges.append((parent, node, weight))
        else:
            edges.append((parent, node))

    return edges


def generate_graph(num_nodes, num_edges, allow_cycles=False, connected=True, directed=False, edge_weight_range=None):
    """
    生成一个随机图，满足指定的参数条件。

    参数:
    - num_nodes (int): 图中的节点数量。
    - num_edges (int): 图中的边的数量。
    - allow_cycles (bool): 是否允许有环, 默认无环。
    - connected (bool): 是否保证连通（先生成一个树再加边），默认保证连通
    - directed (bool): 是否为有向图。默认为 False（无向图）。
    - edge_weight_range (tuple): 边权范围 [l, r]，若无边权则不用设置，默认为None。

    返回:
    - list: 边列表，每条边用元组表示 (u, v) 或 (u, v, w)。
    """
    if num_nodes < 1:
        raise ValueError("节点数量必须至少为 1")
    if num_edges < 0:
        raise ValueError("边的数量不能为负数")
    if connected and num_edges < num_nodes - 1:
        raise ValueError("连通图边数不能超过节点数减一")
    if not allow_cycles and num_edges > num_nodes - 1:
        raise ValueError("无环图的边数不能超过节点数减一")
    if directed and num_edges > num_nodes * (num_nodes - 1):
        raise ValueError("有向图的边数过多")
    if not directed and num_edges > num_nodes * (num_nodes - 1) // 2:
        raise ValueError("无向图的边数过多")

    # 用集合来存储已添加的边，以防止重复边和自环
    edges = set()

    # 生成树结构保证连通性（如果没有环）
    if connected:
        edges = set(generate_tree(num_nodes, edge_weight_range))

    if not allow_cycles:
        return random.sample(generate_tree(num_nodes, edge_weight_range), num_edges)

    if not directed:

        deg = [num_nodes - 1 for i in range(num_nodes)]
        for i in edges:
            deg[i[0]] -= 1
            deg[i[1]] -= 1

        available_nodes = set([i for i in range(num_nodes) if deg[i] > 0])
        # 添加随机边直到达到指定边数
        while len(edges) < num_edges:

            u, v = random.sample(list(available_nodes), 2)

            edge = (min(u, v) + 1, max(u, v) + 1)  # 无向图存储为无序元组

            if edge in edges:
                continue  # 避免重边

            deg[u] -= 1
            deg[v] -= 1

            if deg[u] == 0:
                available_nodes.remove(u)
            if deg[v] == 0:
                available_nodes.remove(v)

            if edge_weight_range:
                w = random.randint(edge_weight_range[0], edge_weight_range[1])
                edges.add((u + 1, v + 1, w))
            else:
                edges.add(edge)

    else:

        deg_in = [num_nodes - 1 for i in range(num_nodes)]
        deg_out = [num_nodes - 1 for i in range(num_nodes)]
        for i in edges:
            deg_in[i[1]] -= 1
            deg_out[i[0]] -= 1
        available_in_nodes = set([i for i in range(num_nodes) if deg[i] > 0])
        available_out_nodes = set([i for i in range(num_nodes) if deg[i] > 0])

        # 添加随机边直到达到指定边数
        while len(edges) < num_edges:

            v = random.sample(list(available_in_nodes), 1)
            u = random.sample(list(available_out_nodes), 1)

            if u == v:
                continue

            edge = (u + 1, v + 1)

            if edge in edges:
                continue  # 避免重边

            deg_in[v] -= 1
            deg_out[u] -= 1

            if deg_in[v] == 0:
                available_in_nodes.remove(v)
            if deg_out[u] == 0:
                available_out_nodes.remove(u)

            if edge_weight_range:
                w = random.randint(edge_weight_range[0], edge_weight_range[1])
                edges.add((u + 1, v + 1, w))
            else:
                edges.add(edge)
    # 转换为列表并返回
    return list(edges)


if __name__ == "__main__":

    print("seq:")
    seq = generate_seq(length=10, value_range=(2, 11), value_type=int)
    print(' '.join(map(str, seq)))

    print("str:")
    s = generate_str(length=10, charset=string.ascii_lowercase)
    print(s)

    print("tree:")
    t = generate_tree(size=10, edge_weight_range=(1, 10))
    for u, v, w in t:
        print(u, v, w)

    print("graph:")
    g = generate_graph(num_nodes=5, num_edges=3, allow_cycles=False,
                       connected=False, directed=False, edge_weight_range=(1, 10))
    for u, v, w in g:
        print(u, v, w)
