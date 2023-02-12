/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */
#endif

//1

/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 *
 * All logical operation can be represented by NAND.
 * A NAND operator results in false when all true.
 *   A NAND B = NOT (A AND B)
 *   A XOR B = (A NAND (A NAND B)) NAND (B NAND (A NAND B))
 */
int bitXor(int x, int y) {
  int x_nand_y, x_nand_xnandy, y_nand_xnandy;
  x_nand_y = ~(x & y);
  x_nand_xnandy = ~(x & x_nand_y);
  y_nand_xnandy = ~(y & x_nand_y);
  return ~(x_nand_xnandy & y_nand_xnandy);
}

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 *
 * Assume that this is a 32-bits machine.
 */
int tmin(void) {
  return 1 << 31;
}

//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int zero, neg;
  zero = ~(x+1) ^ x;  // Gets zero if tmax or -1
  neg = !(~x);  // Gets 1 if -1, else 0
  return !(zero | neg);
}

/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 *
 * Compare every 8-bits with 10101010.
 */
int allOddBits(int x) {
  return !((x & (x>>8) & (x>>16) & (x>>24) & 0xAA) ^ 0xAA);
}

/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x) + 1;
}

//3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int higher4, lower4;
  higher4 = (x>>4) ^ 0x3;
  lower4 = ((x & 0xF) + 0x6) >> 4;  // Not carrying
  return !(higher4|lower4);
}

/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int flag, mask;
  flag = !!x;  // 1 if x is true, else false
  mask = (~flag) + 1;  // 1111 if true, else 0000
  return (mask & y) | (~mask & z);
}

/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 *
 *  (x < 0 && y > 0) || ((-x + y >= 0) && !(x > 0 && y < 0))
 *  x <= y => y - x <= 0, except when overflows.
 */
int isLessOrEqual(int x, int y) {
  int x_less_0, y_greater_0, neg_x, sum, x_greater_0, y_less_0;
  x_less_0 = x>>31;
  y_greater_0 = !(y>>31);
  neg_x = ~x + 1;
  sum = neg_x + y;
  x_greater_0 = !(x>>31);
  y_less_0 = y>>31;
  return (x_less_0 & y_greater_0) | (!(sum>>31) & !(x_greater_0 & y_less_0));
}

//4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  int neg_x, sign_bit;
  neg_x = ~x + 1;
  sign_bit = (x|neg_x)>>31;  // arithmatic right shift
  return sign_bit + 1;
}

/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 *
 * howManyBits(-5) = howManyBits(4)
 * howManyBits(x) = howManyBits(-x - 1) = howManyBits(~x), if x < 0
 * First, turn x to ~x if x < 0, else keep x unchanged.
 * Second, divide and conquer. For example, if higher 16bits is not 0, we need at least 16bits.
 * !!(x>>16) to see if higher 16bits have value. << 4 to get 16 or 0.
 * We keep dividing into case 8bits, 4bits, etc.
 * When it comes to 1bit, we simply keep the value of x at pos0.
 * Finally, add 1 sign bit as we represent any value x as positive integer in two's complement.
 */
int howManyBits(int x) {
  int sign, pos16, pos8, pos4, pos2, pos1, pos0;
  sign = x>>31;
  x = x ^ sign;  // ~x if x < 0
  pos16 = !!(x>>16) << 4;
  x = x>>pos16;
  pos8 = !!(x>>8) << 3;
  x = x>>pos8;
  pos4 = !!(x>>4) << 2;
  x = x>>pos4;
  pos2 = !!(x>>2) << 1;
  x = x>>pos2;
  pos1 = !!(x>>1);
  x = x>>pos1;
  pos0 = x;
  return pos16 + pos8 + pos4 + pos2 + pos1 + pos0 + 1;
}

//float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned sign, exp, frac;
  sign = (uf>>31) & 0x1;
  exp = (uf>>23) & 0xFF;
  frac = uf & 0x7FFFFF;

  // Special: NaN returns NaN, Infinity*2 returns Infinity.
  if (exp == 0xFF) return uf;
  // Denormal
  else if (exp == 0x00) return (sign<<31) | (exp<<23) | (frac<<1);
  // Normal
  else return (sign<<31) | ((exp+1)<<23) | frac;
}

/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned sign, exp, frac;
  int E, M, value;

  sign = (uf>>31) & 0x1;
  exp = (uf>>23) & 0xFF;
  frac = uf & 0x7FFFFF;

  E = exp - 127;

  // Special form || Int overflow
  if (exp == 0xFF || E >= 31)
    return 0x80000000u;
  // Float < 0, round to 0
  else if (E < 0)
    return 0;
  // Normal and float > 0
  else {
    M = (1<<23) | frac;  // Left shift 23
    if (E >= 23)
      value = M<<(E-23);
    else
      value = M>>(23-E);

    if (sign)
      return -value;
    else
      return value;
  }
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    // Too large, return +INF
    if (x > 127)
      return 0xFF<<23;
    // Smaller than denorm
    else if (x < -(126+23))
      return 0;
    // 2^(x+126+23) = frac
    else if (x < -126)
      return 1<<(x+126+23);
    // Normal
    else
      return (x+127)<<23;
    return 2;
}
