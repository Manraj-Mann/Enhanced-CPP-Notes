#include <iostream>
/* 
    Notes :  
    
    1. For members not marked as static, this process is sometimes called non-static member initialization. The initialization value is called a default member initializer.

    2. Using default member initializers (or other mechanisms that we’ll cover later), structs and classes can self-initialize even when no explicit initializers are provided!

    3. Explicit initialization values take precedence over default values - 

        struct Something
        {
            int x;       // no default initialization value (bad)
            int y {};    // value-initialized by default
            int z { 2 }; // explicit default value
        };

        Something s2 { 5, 6, 7 }; // use explicit initializers for s2.x, s2.y, and s2.z (no default values are used)

    4. Missing initializers in an initializer list when default values exist - 

        If an aggregate is initialized but the number of initialization values is fewer than the number of members, then all remaining members will be value-initialized. However, if a default member initializer is provided for a given member, that default member initializer will be used instead.

        struct Something
        {
            int x;       // no default initialization value (bad)
            int y {};    // value-initialized by default
            int z { 2 }; // explicit default value
        };

        Something s3 {}; // value initialize s3.x, use default values for s3.y and s3.z

        In the above case, s3 is list initialized with an empty list, so all initializers are missing. This means that a default member initializer will be used if it exists, and value initialization will occur otherwise. Thus, s3.x (which has no default member initializer) is value initialized to 0, s3.y is value initialized by default to 0, and s3.z is defaulted to value 2.

    5. Provide a default value for all members. This ensures that your members will be initialized even if the variable definition doesn’t include an initializer list.

    6. For aggregates, prefer value initialization (with an empty braces initializer) to default initialization (with no braces).

    



*/
int main()
{
    return 0;
}