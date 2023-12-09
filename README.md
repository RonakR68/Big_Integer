# Big Integer Operations

This C++ program provides functionalities for performing operations on big integers, including addition, subtraction, multiplication, division, exponentiation, GCD calculation, and factorial computation.

## Overview

The program is structured to handle large integers by implementing them as strings. It includes various mathematical operations and can be used for solving mathematical expressions involving big integers.

## Functionalities:

#### 1. Solve Expression

Allows the user to input a mathematical expression involving big integers and operators (+, -, x, /). The program evaluates the expression and returns the result.

#### 2. Exponentiation

Computes the power of a big integer.

#### 3. Greatest Common Divisor (GCD)

Finds the GCD of two big integers.

#### 4. Factorial

Calculates the factorial of a given integer.

## How To Run:

1. Clone the Repository:
git clone https://github.com/RonakR68/Big_Integer.git

2. Navigate to the Project Directory:
cd Big_Integer

3. Compile the code:
g++ -o bigint bigint.cpp

4. Run the Executable:
./bigint

5. Choose the Operation:
Enter the operation code (1-4) to perform the desired operation.

6. Provide Input:
Follow the on-screen prompts to input data based on the chosen operation.

## Assumptions
1. Negative numbers won’t be present in the intermediate or final output for any operation.

2. There are no brackets in the input.

3. Performs Integer division operation between two big integers, disregarding the remainder.

4. Addition, Subtraction, Multiplication and Division follows the same precedence and associativity rules as in Java/cpp.

5. Division by zero, gcd(0, x), gcd(x, 0) etc. will not be an input.






