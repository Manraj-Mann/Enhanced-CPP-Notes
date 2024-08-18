#include <iostream>
#include <bitset>
#include <cstdint>

/*
    Note :  
    
    1. Bitwise Operator = C++ provides 6 bit manipulation operators, often called bitwise operators:

    1. left shift	<<	x << y	all bits in x shifted left y bits
    2. right shift	>>	x >> y	all bits in x shifted right y bits
    3. bitwise NOT	~	~x	all bits in x flipped
    4. bitwise AND	&	x & y	each bit in x AND each bit in y
    5. bitwise OR	|	x | y	each bit in x OR each bit in y
    6. bitwise XOR	^	x ^ y	each bit in x XOR each bit in y]
    
    2. Bitwise assignment operators

        Similar to the arithmetic assignment operators, C++ provides bitwise assignment operators in order to facilitate easy modification of variables.

        Operator	           Symbol	Form	Operation
        Left shift assignment	<<=	x   <<= y	Shift x left by y bits
        Right shift assignment	>>=	x   >>= y	Shift x right by y bits
        Bitwise OR assignment	|=	x   |= y	Assign x | y to x
        Bitwise AND assignment	&=	x   &= y	Assign x & y to x
        Bitwise XOR assignment	^=	x   ^= y	Assign x ^ y to x

    3.  Bitwise operators will promote operands with narrower integral types to int or unsigned int.
        operator~ and operator<< are width-sensitive and may produce different results depending on the width of the operand.
        static_cast the result of such bitwise operations back to the narrower integral type before using to ensure correct results.
    
    */


// "rotl" stands for "rotate left"
std::bitset<4> rotl(std::bitset<4> bits)
{
    bool isFirst = bits.test(bits.size()-1);
    bits <<= 1;
    // check if the bit at front is set 
    if(isFirst)
    {
        bits.set(0);
    }
    return bits;
}

// "rotl" stands for "rotate left"
std::bitset<4> rotl2(std::bitset<4> bits)
{
    std::bitset<4> mask = {0b1000};
    std::bitset<4> mask2 = {0b0001};

    bool isFirst =  (mask & bits)[3];
    bits <<= 1;
    // check if the bit at front is set 
    if(isFirst)
    {
        bits |= mask2;
    }
    return bits;
}

// "rotl" stands for "rotate left"
std::bitset<4> rotl3(std::bitset<4> bits)
{
    // use the fact that bit operation gives temp object
    return (bits << 1) | (bits>>3);
}



int main()
{
    std::uint8_t c { 0b00001111 };

    std::cout << std::bitset<32>(static_cast<std::uint8_t>(~c)) << '\n';     // correct: prints 00000000000000000000000011110000
    std::cout << std::bitset<32>(static_cast<std::uint8_t>(c << 6)) << '\n'; // correct: prints 0000000000000000000011000000
    std::uint8_t cneg { static_cast<std::uint8_t>(~c) };                     // compiles
    c = static_cast<std::uint8_t>(~c);                                       // no warning

    std::bitset<4> bits1{ 0b1001 };
	std::cout << rotl(bits1) << '\n';
	std::cout << rotl2({0b1011}) << '\n';
	std::cout << rotl3({0b1011}) << '\n';

    return 0;

}