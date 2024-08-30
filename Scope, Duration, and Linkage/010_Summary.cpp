/*

Notes :

    Duration summary : 

    A variable’s duration determines when it is created and destroyed.

    1. Variables with automatic duration are created at the point of definition, and destroyed when the block they are part of is exited. This includes:
        => Local variables
        => Function parameters
    
    2. Variables with static duration are created when the program begins and destroyed when the program ends. This includes:
        => Global variables
        => Static local variables
    
    3. Variables with dynamic duration are created and destroyed by programmer request. This includes:
        =>Dynamically allocated variables



    Linkage summary

    An identifier’s linkage determines whether a declaration of that same identifier in a different scope refers to the same entity (object, function, reference, etc…) or not.

    1. Local variables have no linkage. Each declaration of an identifier with no linkage refers to a unique object or function.

    An identifier with no linkage means another declaration of the same identifier refers to a unique entity. Entities whose identifiers have no linkage include:
    => Local variables
    => Program-defined type identifiers (such as enums and classes) declared inside a block
    
    2. An identifier with internal linkage means a declaration of the same identifier within the same translation unit refers to the same object or function. Entities whose identifiers have internal linkage include:
    
    => Static global variables (initialized or uninitialized)
    => Static functions
    => Const global variables
    => Unnamed namespaces and anything defined within them.

    3. An identifier with external linkage means a declaration of the same identifier within the entire program refers to the same object or function. Entities whose identifiers have external linkage include:
    => Non-static functions
    => Non-const global variables (initialized or uninitialized)
    => Extern const global variables
    => Inline const global variables
    => Namespaces
    
    Identifiers with external linkage will generally cause a duplicate definition linker error if the definitions are compiled into more than one .cpp file (due to violating the one-definition rule). There are some exceptions to this rule (for types, templates, and inline functions and variables) -- we’ll cover these further in future lessons when we talk about those topics.

    Also note that functions have external linkage by default. They can be made internal by using the static keyword.


*/