/*

    1. Universal References : 

        template <typename T>
        void foo(T&& widget)
        {
            // some work
        }

        => Deduction for the l-value and r-value happens as follows


        1. L value : 

            widget w;
            foo(w);

            T = widget& 

            paramtype = widget& && ==> widget & (due to reference collapse)

            void foo(widget& widget)
            {
                // some work
            }

        
        2. R value : 

            foo ( widget {} );

            T = widget 

            paramtype = widget&&
            
            void foo(widget && widget)
            {
                // some work
            }

        => Example : make_unique , make_shared etc.

        ==> Why need ? At the times when you need handle all types of values. 

    
    2. What/Why is Perfect Forwarding : 

            template<typename T , typename Args>
            unique_ptr<T> make_unique(???)
            {
                return unique_ptr<T>( new T(???));
            }

            How to handle above ?

            1. unique_ptr<T> make_unique(Args args) ? This will create copy
            2. unique_ptr<T> make_unique(Args &args) ? This will fail to handle r values
            3. unique_ptr<T> make_unique(Args const & args ) ? This will be strict with handling of const.

            4. The solution for this is Universal References: 

                unique_ptr<T> make_unique(Args && agrs) handle all types

                Signature : 

                template<typename T , typename Args>
                unique_ptr<T> make_unique(Args && args)
                {
                    return unique_ptr<T>( new T(agrs) );
                }

                but this causes another problem , args has a name now and this becomes an l value.
                It will call the l value methods here like copy construtor.

                Can I solve this using move ? Move will "unconditionally" move no matter weather its l value or r value ,
                so it can cause problems in case of l values.
                
                The solution for this is Perfect Forwarding which will do a conditional forwarding.

                => std::move - casts unconditionally both l value and r values to r values ref.

                => std::forward - casts conditionally to r values,
                               if value is l value casts it to l value ref , if r value then r value ref.

                template<typename T , typename Args>
                unique_ptr<T> make_unique(Args && args)
                {
                    return unique_ptr<T>( new T(std::forward<Args>(args)) );
                } 


                Final for any number of params:
                
                template<typename T , typename... Args>
                unique_ptr<T> make_unique(Args &&... args)
                {
                    return unique_ptr<T>( new T(std::forward<Args>(args)...) );
                } 

    3. What std::forward does ?

        template <typename T>
        T&& forward( std::remove_reference_t<T> & t ) noexcept
        {
            return static_cast<T&&>(t);
        }

        1. For l value : 

            T = widget&

            paramtype = std::remove_reference_t<widget&> & t ===> widget & t 

            widget& forward(widget & t) noexcept
            {
                return static_cast<widget&>(t);
            }

        2. For r value : 

*/

/*

        1. Rule of Reference Collapsing : As soon as we get one l value reference we get a l value ref.

            &  &&  -> &
            && &   -> &
            &  &   -> & 
            && &&  -> &&
*/