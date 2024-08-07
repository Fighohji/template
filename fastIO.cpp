namespace FastIOT {
const int bsz = 1 << 18;
char bf[bsz], *head, *tail;
inline char gc() {
    if (head == tail) tail = (head = bf) + fread(bf, 1, bsz, stdin);
    if (head == tail) return 0;
    return *head++;
}
template <typename T>
inline void read(T &x) {
    T f = 1;
    x = 0;
    char c = gc();
    for (; c > '9' || c < '0'; c = gc())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = gc())
        x = (x << 3) + (x << 1) + (c ^ 48);
    x *= f;
}
template <typename T>
inline void print(T &x) {
    if (x < 0) putchar(45), x = -x;
    if (x > 9) print(x / 10);
    puchar(x % 10 + 48);
}
template <typename T>
inline void println(T &x) {
    print(x);
    putchar('\n');
}
} // namespace FastIOT
using namespace FastIOT;
