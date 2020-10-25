# System-linear-equations
A program to solve system linear equations.\

**Steps to solve:**\
1. calculate determinant of coefficients matrix
2. inverse the coefficients matrix
3. multiply between coefficients matrix and free numbers matrix
result:
```
x = A^(-1) * B
```

Assumptions:
* Only use 'x', 'y' and 'z' variables.
* Maximum of equations in the system is 3.
* The number of variables is equal to the number of equations.

Examples of a valid input:
```
2x + y - z = 7
x - y - z = -3
x + 2y + 2z = 6
```
```
2x = 10
```
```
6x - 2y = 24
x + 5y = 4
```

Examples of an invalid input:
```
2x + y - z = 7
x - y - z = -3
```
```
2x + y - t = 7
x - y - t = -3
x + 2y + 2t = 6
```
```
2z = 10
```