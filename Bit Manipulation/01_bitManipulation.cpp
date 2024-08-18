#include <iostream>
#include <bitset>

/*
    Notes : Bit Manipulation

    1. To define a set of bit flags, we’ll typically use an unsigned integer of the appropriate size (8 bits, 16 bits, 32 bits, etc… depending on how many flags we have), or std::bitset.

    std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags

    2. Given a sequence of bits, we typically number the bits from right to left, starting with 0 (not 1). Each number denotes a bit position.

        76543210  Bit position
        00000101  Bit sequence
    
    3. std::bitset provides 4 key member functions that are useful for doing bit manipulation:

        => test() allows us to query whether a bit is a 0 or 1.
        => set() allows us to turn a bit on (this will do nothing if the bit is already on).
        => reset() allows us to turn a bit off (this will do nothing if the bit is already off).
        => flip() allows us to flip a bit value from a 0 to a 1 or vice versa.

    4. std::bitset doesn’t make this easy. In order to do this, or if we want to use unsigned integer bit flags instead of std::bitset, we need to turn to more traditional methods.

    5. One potential surprise is that std::bitset is optimized for speed, not memory savings. 
       The size of a std::bitset is typically the number of bytes needed to hold the bits, rounded up to the nearest sizeof(size_t), which is 4 bytes on 32-bit machines, and 8-bytes on 64-bit machines.

    6. Querying std::bitset : 

        There are a few other member functions that are often useful:

        size() returns the number of bits in the bitset.
        count() returns the number of bits in the bitset that are set to true.
        all() returns a Boolean indicating whether all bits are set to true.
        any() returns a Boolean indicating whether any bits are set to true.
        none() returns a Boolean indicating whether no bits are set to true.

*/

int main()
{
    std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags
    uint8_t biset8; // unsigned int

    mybitset.set(1);

    std::cout<<mybitset<<std::endl;

    std::bitset<8> bits{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
    bits.set(3);   // set bit position 3 to 1 (now we have 0000 1101)
    bits.flip(4);  // flip bit 4 (now we have 0001 1101)
    bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)

    std::cout << "All the bits: " << bits<< '\n';
    std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
    std::cout << "Bit 4 has value: " << bits.test(4) << '\n';

    // check the size
    std::cout<<"SIZE : "<<sizeof(bits)<<std::endl; // 8 in my system 8 bits -> 8 bytes


    return 0;
}