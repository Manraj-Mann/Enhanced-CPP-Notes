#include <iostream>
/* 
    Notes :  
    
    1. A smart pointer class is a composition class that is designed to manage dynamically allocated memory, and ensure that memory gets deleted when the smart pointer object goes out of scope.

    2. Copy semantics allow our classes to be copied. This is done primarily via the copy constructor and copy assignment operator.

    3. Move semantics mean a class will transfer ownership of the object rather than making a copy. This is done primarily via the move constructor and move assignment operator.

    4. std::auto_ptr is deprecated and should be avoided.

    5. An r-value reference is a reference that is designed to be initialized with an r-value. An r-value reference is created using a double ampersand. It’s fine to write functions that take r-value reference parameters, but you should almost never return an r-value reference.

    6. If we construct an object or do an assignment where the argument is an l-value, the only thing we can reasonably do is copy the l-value. We can’t assume it’s safe to alter the l-value, because it may be used again later in the program. If we have an expression “a = b”, we wouldn’t reasonably expect b to be changed in any way.

    7. However, if we construct an object or do an assignment where the argument is an r-value, then we know that r-value is just a temporary object of some kind. Instead of copying it (which can be expensive), we can simply transfer its resources (which is cheap) to the object we’re constructing or assigning. This is safe to do because the temporary will be destroyed at the end of the expression anyway, so we know it will never be used again!

    8. You can use the delete keyword to disable copy semantics for classes you create by deleting the copy constructor and copy assignment operator.

    9. std::move allows you to treat an l-value as r-value. This is useful when we want to invoke move semantics instead of copy semantics on an l-value.

    10. std::unique_ptr is the smart pointer class that you should probably be using. It manages a single non-shareable resource. std::make_unique() (in C++14) should be preferred to create new std::unique_ptr. std::unique_ptr disables copy semantics.

    11. std::shared_ptr is the smart pointer class used when you need multiple objects accessing the same resource. The resource will not be destroyed until the last std::shared_ptr managing it is destroyed. std::make_shared() should be preferred to create new std::shared_ptr. With std::shared_ptr, copy semantics should be used to create additional std::shared_ptr pointing to the same object.

    12. std::weak_ptr is the smart pointer class used when you need one or more objects with the ability to view and access a resource managed by a std::shared_ptr, but unlike std::shared_ptr, std::weak_ptr is not considered when determining whether the resource should be destroyed.

*/
int main()
{
    return 0;
}