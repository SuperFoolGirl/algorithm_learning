// 解一元同余方程组
// 给定以下方程组：
// x ≡ a1 (mod m1)
// x ≡ a2 (mod m2)
// ...
// x ≡ ak (mod mk)
// 满足 m1,m2,...,mk 两两互质
// 求解x

// 令 M = m1 * m2 * ... * mk
// 对每个 i (1 <= i <= k)，令 Mi = M / mi，由两两互质的性质可得Mi与mi互质
// 根据中国剩余定理，x 的解可以表示为
// x ≡ a1 * M1 * inv(M1, m1) + a2 * M2 * inv(M2, m2) + ... + ak * Mk * inv(Mk, mk) (mod M)
// 其中 inv(Mi, mi) 表示 Mi 在模 mi 意义下的逆元
// 回顾逆元：在gcd(M, mi) = 1 的前提下，找到 Mi·x ≡ 1(mod mi)的x
