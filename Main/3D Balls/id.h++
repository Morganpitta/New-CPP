#if !defined( ID_HPP )
#define ID_HPP

    typedef unsigned int Id;

    class IdGenerator
    {
        public:
            Id lastId;
            
            IdGenerator()
            {
                this->lastId = 0;
            }

            Id getNextId()
            {
                return lastId++;
            }
    };

#endif /* ID_HPP */