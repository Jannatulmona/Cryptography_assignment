
# Number Theory and Algorithms Using Python

---

## Student Information

- **Name:** Jannatul Mawa Mona
- **Student ID:** IT23029
- **Department:** Information and Communication Technology (ICT)
- **University:** Mawlana Bhashani Science and Technology University (MBSTU)

## Google Colab Notebook

[**Open Assignment in Google Colab**](https://colab.research.google.com/drive/1_wqulye7fZd_hq_WemTuSICWNlc1Yika?usp=sharing)

---

# Assignment Questions and Solutions

## Question 1: Extended Euclidean Algorithm

**Problem:** Implement a function that calculates the GCD of two numbers using the Extended Euclidean Algorithm.

### Explanation

The Extended Euclidean Algorithm is used to calculate the Greatest Common Divisor (GCD) of two integers. It also finds two integers `x` and `y` such that:

$$
ax+by=GCD(a,b)
$$

### Python Implementation

```python
def extended_euclid(a, b):
    old_r, r = a, b
    old_x, x = 1, 0
    old_y, y = 0, 1

    while r != 0:
        q = old_r // r

        old_r, r = r, old_r - q * r
        old_x, x = x, old_x - q * x
        old_y, y = y, old_y - q * y

    return old_r, old_x, old_y


gcd, x, y = extended_euclid(48, 18)

print("GCD =", gcd)
print("x =", x)
print("y =", y)
```

### Output

```text
GCD = 6
x = -1
y = 3
```

### Verification

Using the equation:

$$
ax+by=GCD(a,b)
$$

Substituting the values:

$$
48(-1)+18(3)=-48+54=6
$$

Therefore, **GCD(48, 18) = 6**.

**Time Complexity:** $O(\log(\min(a,b)))$, for positive integers.

---

## Question 2: Least Common Multiple (LCM)

**Problem:** Write an efficient algorithm to find the LCM of two positive integers using the relationship between GCD and LCM.

### Explanation

LCM is the smallest positive integer that is divisible by both given numbers.

The relationship between GCD and LCM is:

$$
LCM(a,b)=\frac{a\times b}{GCD(a,b)}
$$

First, we calculate GCD using Euclid's Algorithm. Then, we use the formula to calculate LCM.

### Python Implementation

```python
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


def lcm(a, b):
    return (a * b) // gcd(a, b)


a = 12
b = 18

print("GCD =", gcd(a, b))
print("LCM =", lcm(a, b))
```

### Output

```text
GCD = 6
LCM = 36
```

### Calculation

Using the formula:

$$
LCM(a,b)=\frac{a\times b}{GCD(a,b)}
$$

Substituting the values:

$$
LCM(12,18)=\frac{12\times18}{6}
$$

$$
LCM(12,18)=36
$$

Therefore, **the LCM is 36**.

**Time Complexity:** $O(\log(\min(a,b)))$.

---

## Question 3: Solving Diophantine Equations

**Problem:** Use the Extended Euclidean Algorithm to solve Diophantine equations efficiently.

### Explanation

A linear Diophantine equation is an equation of the form:

$$
ax+by=c
$$

Here, we need to find integer values of `x` and `y` that satisfy the equation.

An integer solution exists if and only if:

$$
GCD(a,b)\mid c
$$

We use the Extended Euclidean Algorithm to find an initial solution and multiply its coefficients by $c/GCD(a,b)$.

### Python Implementation

```python
def extended_euclid(a, b):
    old_r, r = a, b
    old_x, x = 1, 0
    old_y, y = 0, 1

    while r != 0:
        q = old_r // r

        old_r, r = r, old_r - q * r
        old_x, x = x, old_x - q * x
        old_y, y = y, old_y - q * y

    return old_r, old_x, old_y


def solve_diophantine(a, b, c):
    g, x, y = extended_euclid(a, b)

    if c % g != 0:
        return None

    k = c // g

    return x * k, y * k


a = 12
b = 18
c = 6

answer = solve_diophantine(a, b, c)

if answer is None:
    print("No integer solution")
else:
    x, y = answer
    print("x =", x)
    print("y =", y)
    print("Verification =", a*x + b*y)
```

### Output

```text
x = -1
y = 1
Verification = 6
```

### Verification

The given equation is:

$$
12x+18y=6
$$

Substituting $x=-1$ and $y=1$:

$$
12(-1)+18(1)=-12+18
$$

$$
=6
$$

Therefore, **x = -1 and y = 1** are valid integer solutions.

**Time Complexity:** $O(\log(\min(a,b)))$, for positive integers.

---

## Question 4: Modular Inverse and Modular Division

**Problem:** Use the Extended Euclidean Algorithm to calculate modular inverses and implement an efficient algorithm for modular division.

### Explanation

The modular inverse of `b` modulo `m` is a number `x` satisfying:

$$
(b\times x)\bmod m=1
$$

A modular inverse exists if:

$$
GCD(b,m)=1
$$

Modular division is calculated using:

$$
\frac{a}{b}\bmod m=(a\times b^{-1})\bmod m
$$

### Python Implementation

```python
def extended_euclid(a, b):
    old_r, r = a, b
    old_x, x = 1, 0
    old_y, y = 0, 1

    while r != 0:
        q = old_r // r

        old_r, r = r, old_r - q * r
        old_x, x = x, old_x - q * x
        old_y, y = y, old_y - q * y

    return old_r, old_x, old_y


def modular_division(a, b, m):
    g, x, y = extended_euclid(b, m)

    if g != 1:
        return "Modular inverse does not exist"

    inverse = x % m

    return (a * inverse) % m


print("Result =", modular_division(10, 3, 7))
```

### Output

```text
Result = 1
```

### Calculation

First, find the modular inverse of 3 modulo 7:

$$
3\times5=15
$$

$$
15\bmod7=1
$$

Therefore:

$$
3^{-1}\bmod7=5
$$

Now, perform modular division:

$$
10/3\bmod7=(10\times5)\bmod7
$$

$$
=50\bmod7=1
$$

Therefore, **the result is 1**.

**Time Complexity:** $O(\log m)$.

---

## Question 5: Fast Modular Exponentiation

**Problem:** Implement `FastModularExponentiation(b, e, m)` to calculate $b^e\bmod m$ using approximately $\log e$ modular multiplications. Python's built-in exponentiation functions are not allowed.

### Explanation

Fast Modular Exponentiation is an efficient technique for calculating large powers modulo a number.

Instead of multiplying the base repeatedly, we use the **Square-and-Multiply** method.

The main idea is:

- If the exponent is odd, multiply the result by the base.
- Square the base at every iteration.
- Divide the exponent by 2.

### Python Implementation

```python
def FastModularExponentiation(b, e, m):
    result = 1
    b = b % m

    while e > 0:

        if e % 2 == 1:
            result = (result * b) % m

        b = (b * b) % m
        e = e // 2

    return result


print("Result =", FastModularExponentiation(2, 10, 7))
```

### Output

```text
Result = 2
```

### Calculation

We need to calculate:

$$
2^{10}\bmod7
$$

First:

$$
2^{10}=1024
$$

Then:

$$
1024\bmod7=2
$$

Therefore, **the result is 2**.

**Time Complexity:** $O(\log e)$.

**Note:** The implementation does not use Python's `pow()` or the `**` operator.

---

## Question 6: Chinese Remainder Theorem (CRT)

**Problem:** Implement an algorithm to construct a number using the Chinese Remainder Theorem.

### Explanation

The Chinese Remainder Theorem (CRT) is used to find a number that satisfies multiple modular equations.

For example:

$$
x\bmod3=2
$$

$$
x\bmod5=3
$$

The number 8 satisfies both equations.

$$
8\bmod3=2
$$

$$
8\bmod5=3
$$

Therefore:

$$
\boxed{x=8}
$$

For pairwise coprime moduli, CRT guarantees a unique solution modulo the product of the moduli.

### Python Implementation

```python
def extended_euclid(a, b):
    old_r, r = a, b
    old_x, x = 1, 0

    while r != 0:
        q = old_r // r
        old_r, r = r, old_r - q * r
        old_x, x = x, old_x - q * x

    return old_r, old_x


def chinese_remainder(remainders, moduli):
    M = 1

    for m in moduli:
        M *= m

    result = 0

    for a, m in zip(remainders, moduli):
        Mi = M // m

        g, inverse = extended_euclid(Mi, m)

        if g != 1:
            return "Moduli must be pairwise coprime"

        inverse = inverse % m

        result += a * Mi * inverse

    return result % M


remainders = [2, 3]
moduli = [3, 5]

answer = chinese_remainder(remainders, moduli)

print("CRT Solution =", answer)
```

### Output

```text
CRT Solution = 8
```

### Verification

The obtained solution is **x = 8**.

**First condition:**

Dividing 8 by 3 gives a remainder of 2.

$$
8\bmod3=2
$$

**Second condition:**

Dividing 8 by 5 gives a remainder of 3.

$$
8\bmod5=3
$$

Both conditions are satisfied.

Therefore, the final CRT solution is:

$$
\boxed{x=8}
$$

**Time Complexity:** The implementation performs $n$ Extended Euclidean computations for $n$ pairwise coprime moduli.

---

# Conclusion

In this assignment, six important number-theoretic algorithms were implemented using Python.

1. Extended Euclidean Algorithm was used to calculate GCD and Bézout coefficients.
2. The relationship between GCD and LCM was used to calculate LCM efficiently.
3. Extended Euclid was applied to solve linear Diophantine equations.
4. Modular inverse was used to perform modular division.
5. Fast Modular Exponentiation was implemented using the square-and-multiply method.
6. Chinese Remainder Theorem was implemented to construct a number satisfying multiple modular equations.

These algorithms are important in number theory, cryptography, and computer science.

---

## Tools and Technologies

- **Programming Language:** Python
- **Platform:** Google Colab / Jupyter Notebook
- **Version Control:** Git and GitHub

---

**End of Assignment**
