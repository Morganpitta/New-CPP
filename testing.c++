#include <iostream>
#include <vector>

template<typename T>
class BinaryTree
{
    public:
        struct Node
        {
            T data;
            Node *parent;
            Node *left = nullptr;
            Node *right = nullptr;
            
            Node( T data, Node *parent = nullptr )
            {
                this->index = index;
                this->data = data;
                this->parent = parent;
            }
        };

        Node *rootNode;

        BinaryTree()
        {
            rootNode = nullptr;
        }

        void insert( const T &value )
        {
            if ( rootNode == nullptr )
                rootNode = new Node( value, nullptr );
            else
                traverseInsert( rootNode, value );
        }

        void traverseInsert( Node *node, const T &value )
        {
            if ( value < node->data )
            {
                if ( node->left == nullptr ) 
                {
                    node->left = new Node( value, node );
                }
                else
                {
                    traverseInsert( node->left, value );
                }
            }
            else if ( value > node->data )
            {
                if ( node->right == nullptr )
                {
                    node->right = new Node( value, node );
                }
                else
                {
                    traverseInsert( node->right, value );
                }
            }
        }

        void insert( const std::vector<T> &values )
        {
            for ( const T &value: values )
            {
                insert( value );
            }
        }
};

template<typename T>
std::ostream &operator<<(std::ostream &stream, const BinaryTree<T> &tree)
{
    return stream;
}

int main()
{
    BinaryTree<int> tree;

    tree.insert( {1,-1,5,9,0,4} );

    return 0;
}