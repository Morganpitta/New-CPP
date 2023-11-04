#if !defined( ID_HPP )
#define ID_HPP

    typedef unsigned int Id;

    class IdGenerator
    {
        public:
            Id nextId;
            
            IdGenerator()
            {
                this->nextId = 0;
            }

            Id getNextId()
            {
                return nextId++;
            }
    };

#endif /* ID_HPP */