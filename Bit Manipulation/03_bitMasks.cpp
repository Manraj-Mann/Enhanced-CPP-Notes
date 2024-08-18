#include <iostream>
#include <bitset>
#include <cstdint>

/*
    Note : Bit masking

    1. A bit mask is a predefined set of bits that is used to select which specific bits will be modified by subsequent operations.

        => Defining bit masks in C++14:

        constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
        constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
        constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
        constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
        constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
        constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
        constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
        constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7
    
        Now we have a set of symbolic constants that represents each bit position. We can use these to manipulate the bits .

        => Because C++11 doesn’t support binary literals, we have to use other methods to set the symbolic constants

            1. The first method is to use hexadecimal literals.

            Hexadecimal	0	     1	      2	      3	     4	     5	     6	     7	     8	     9	     A	     B	     C	      D	     E	     F
            Binary	   0000  	0001	0010	0011	0100	0101	0110	0111	1000	1001	1010	1011	1100	1101	1110	1111

            constexpr std::uint8_t mask0{ 0x01 }; // hex for 0000 0001
            constexpr std::uint8_t mask1{ 0x02 }; // hex for 0000 0010
            constexpr std::uint8_t mask2{ 0x04 }; // hex for 0000 0100
            constexpr std::uint8_t mask3{ 0x08 }; // hex for 0000 1000
            constexpr std::uint8_t mask4{ 0x10 }; // hex for 0001 0000
            constexpr std::uint8_t mask5{ 0x20 }; // hex for 0010 0000
            constexpr std::uint8_t mask6{ 0x40 }; // hex for 0100 0000
            constexpr std::uint8_t mask7{ 0x80 }; // hex for 1000 0000

            2. An easier method is to use the left-shift operator to shift a single bit into the proper location:

                constexpr std::uint8_t mask0{ 1 << 0 }; // 0000 0001
                constexpr std::uint8_t mask1{ 1 << 1 }; // 0000 0010
                constexpr std::uint8_t mask2{ 1 << 2 }; // 0000 0100
                constexpr std::uint8_t mask3{ 1 << 3 }; // 0000 1000
                constexpr std::uint8_t mask4{ 1 << 4 }; // 0001 0000
                constexpr std::uint8_t mask5{ 1 << 5 }; // 0010 0000
                constexpr std::uint8_t mask6{ 1 << 6 }; // 0100 0000
                constexpr std::uint8_t mask7{ 1 << 7 }; // 1000 0000

    2. Testing a bit (to see if it is on or off) : 

        (static_cast<bool>(flags & mask0) ? "on\n" : "off\n"

    3. Setting a bit : 

        flags |= mask1; // turn on bit 1

        flags |= (mask4 | mask5); // turn bits 4 and 5 on at the same time

    4. Resetting a bit : 

        To reset (clear) a bit (to value 0), we use Bitwise AND and Bitwise NOT together:

        => flags &= ~mask2; // turn off bit 2

        0000'0100 ==> applying ~ => 1111'1011  applying & will donot change other bits , only unset the desired bit.

        => flags &= ~(mask4 | mask5); // turn bits 4 and 5 off at the same time

    5. Flipping a bit:

        flags ^= mask2; // flip bit 2
    
    6. Bit masks and std::bitset:

        std::bitset supports the full set of bitwise operators. 
        So even though it’s easier to use the functions (test, set, reset, and flip) to modify individual bits, you can use bitwise operators and bit masks if you want.

*/
int main()
{

    return 0;
}