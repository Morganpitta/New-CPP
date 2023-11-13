/*
#include <iostream>
#include <map>

template<typename T>
class BinaryTree
{
    public:

        typedef int NodeId;
        static const NodeId NullNode = -1; 
        
        struct Node
        {
            NodeId id;
            T data;
            NodeId parentNode = NullNode;
            NodeId leftNode   = NullNode;
            NodeId rightNode  = NullNode;
        };

        std::map<NodeId, Node> nodes;
        NodeId rootNode;
        std::size_t nextId = 0;

        Node *getNode( NodeId id )
        {
            if ( this->nodes.count( id ) == 0 )
                return nullptr;
            return &this->nodes[id];
        }

        void insert( T data )
        {
            NodeId id = this->rootNode;
            if ( id == NullNode )
            {
                id = nextId++;
                this->rootNode = id;
                nodes[id] = {id,data};
                return;
            }
            while ( true )
            {
                if ( data < getNode(id)->data )
                {
                    id = getNode(id)->leftNode;
                }
            }
        }
};
*/


#include <fstream>

int main()
{
    std::fstream file;
    file.open( "file.txt", std::ios::in | std::ios::out );
    if (!file.is_open())
        return 1;

    std::string line;
    while ( std::getline(file, line) )
    {
        
    }

}