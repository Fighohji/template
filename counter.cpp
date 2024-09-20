auto start = chrono::high_resolution_clock::now();

auto end = chrono::high_resolution_clock::now();

// 计算耗时（单位为毫秒）
chrono::duration<double, milli> duration = end - start;

cerr << "耗时: " << duration.count() << " 毫秒\n";
