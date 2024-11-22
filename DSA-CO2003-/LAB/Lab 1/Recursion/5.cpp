int findGCD(int a, int b) {
    // Trường hợp cơ sở: nếu b == 0, GCD là a
    if (b == 0)
        return a;
    
    // Đệ quy: GCD(a, b) = GCD(b, a % b)
    return findGCD(b, a % b);
}