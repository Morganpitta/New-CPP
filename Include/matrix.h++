#if !defined( MATRICES_HPP )
#define MATRICES_HPP

    #include "SFML/System.hpp"
    #include "assert.h++"
    #include <iostream>

    struct MatrixPosition
    {
        int row;
        int column;

        MatrixPosition( int row, int column ): row(row), column(column)
        {
            
        }

        MatrixPosition( sf::Vector2i vector ): row(vector.x), column(vector.y)
        {
            
        }

        bool operator==( MatrixPosition left )
        {
            return this->row == left.row && this->column == left.column;
        }
    };

    template<typename T>
    class Matrix
    {
        protected:
            std::vector<T> value;
        public:
            int rows;
            int columns;

            Matrix( int rows = 0, int columns = 0 )
            {
                assertCondition( rows >= 0, "Cannot have a negative number of rows");
                assertCondition( columns >= 0, "Cannot have a negative number of columns");

                setDimensions(rows, columns);
            }

            Matrix( int rows, int columns, std::vector<T> value )
            {
                assertCondition( rows >= 0, "Cannot have a negative number of rows");
                assertCondition( columns >= 0, "Cannot have a negative number of columns");

                set( rows, columns, value );
            }

            Matrix( MatrixPosition dimensions = {0,0} )
            {
                assertCondition( dimensions.row >= 0, "Cannot have a negative number of rows");
                assertCondition( dimensions.column >= 0, "Cannot have a negative number of columns");

                setDimensions(dimensions.row, dimensions.column);
            }

            Matrix( MatrixPosition dimensions, std::vector<T> value )
            {
                assertCondition( dimensions.row >= 0, "Cannot have a negative number of rows");
                assertCondition( dimensions.column >= 0, "Cannot have a negative number of columns");

                set( dimensions.row, dimensions.column, value);
            }

            std::string toString() const
            {
                std::string string = "{ ";

                for ( int index = 0; index < value.size(); index++ )
                {
                    if ( index != 0 )
                    {
                        string += ", ";
                        if ( index%this->columns == 0 )
                            string += "\n  ";
                    }
                    string += std::to_string(this->value[index]);
                };

                string += " }";
                return string;
            }

            void clear()
            {
                this->value.resize(rows*columns, 0);
            }

            void setDimensions( int rows, int columns )
            {
                if ( this->rows == rows && this->columns == columns ) return;
                this->rows = rows;
                this->columns = columns;
                clear();
            }

            MatrixPosition getDimensions() const
            {
                return MatrixPosition( this->rows, this->columns );
            }

            std::vector<T> get() const
            {
                return this->value;
            }

            void set( std::vector<T> value )
            {
                assertCondition( value.size() == this->rows*this->columns, "Invalid value size");
                this->value = value;
            }

            void set( int rows, int columns, std::vector<T> value )
            {
                this->setDimensions(rows, columns);
                this->value = value;
            }

            T get( int row, int column ) const
            {
                assertCondition( row < this->rows && column < this->columns, "Index out of range");
                return this->value[column+row*this->columns];
            }

            void set( int row, int column, T value )
            {
                assertCondition( row < this->rows && column < this->columns, "Index out of range");
                this->value[column+row*this->columns] = value;
            }

            T get( MatrixPosition position ) const
            {
                return this->get( position.row, position.column );
            }

            void set( MatrixPosition position, T value )
            {
                this->set( position.row, position.column, value );
            }

            Matrix transpose()
            {
                Matrix<T> transpose(this->columns, this->rows);

                for ( int column = 0; column < this->rows; column++ )
                {
                    for ( int row = 0; row < this->columns; row++ )
                    {
                        transpose.set( column, row, this->get(row, column));
                    }
                }

                return transpose;
            }

            void operator=( std::vector<T> value )
            {
                set(value);
            }

            Matrix operator+=( const Matrix& left )
            {
                assertCondition( this->getDimensions() == left.getDimensions(), "Can't add matrices of different dimensions" );

                for ( int index = 0; index < this->value.size(); index++ )
                {
                    this->value[index] += left.value[index];
                }

                return *this;
            }

            Matrix operator-=( const Matrix& left )
            {
                assertCondition( this->getDimensions() == left.getDimensions(), "Can't add matrices of different dimensions" );

                for ( int index = 0; index < this->value.size(); index++ )
                {
                    this->value[index] -= left.value[index];
                }

                return *this;
            }

            Matrix operator*=( const Matrix& left )
            {
                assertCondition( this->columns == left.rows, "Can't add matrices of different dimensions" );
                Matrix tmp( *this );
                
                setDimensions(this->rows, left.columns);

                for ( int row = 0; row < this->rows; row++ )
                {
                    for ( int column = 0; column < this->columns; column++ )
                    {
                        T value = 0;
                        for ( int index = 0; index < left.rows; index++ )
                        {
                            value += tmp.get(row, index) * left.get(index, column);
                        }
                        this->set(row, column, value);
                    }
                }

                return *this;
            }

            Matrix operator+( const Matrix& left ) const
            {
                Matrix tmp( this );
                tmp += left;
                
                return tmp;
            }

            Matrix operator-( const Matrix& left ) const
            {
                Matrix tmp( this );
                tmp -= left;
                
                return tmp;
            }

            Matrix operator*( const Matrix& left ) const
            {
                Matrix tmp( *this );
                tmp *= left;

                return tmp;
            }

            Matrix dot( const Matrix& left ) const
            {
                return (*this) * left;
            }
    };

    template<typename T>
    std::ostream& operator<<( std::ostream& stream, const Matrix<T>& value )
    {
        std::cout << value.toString();
        return stream;
    }

    template <typename T>
    sf::Vector2<T> operator*( const Matrix<T>& left, const sf::Vector2<T>& right )
    {
        assertCondition( left.columns == 2, "Cannot apply non N x 2 matrices to a 2D vector" );

        sf::Vector2<T> vector;

        vector.x = 0;
        vector.y = 0;

        for ( int index = 0; index < left.columns; index++ )
        {
            vector.x += right.x * left.get(0, index);
            vector.y += right.y * left.get(1, index);
        }

        return vector;
    }


    template <typename T>
    void operator*=( sf::Vector2<T>& left, const Matrix<T>& right )
    {
        left = left * right;
    }


    template <typename T>
    sf::Vector3<T> operator*( const Matrix<T>& left, const sf::Vector3<T>& right )
    {
        assertCondition( 3 == left.columns, "Cannot apply non N x 3 matrices to a 3D vector" );

        sf::Vector3<T> vector;

        vector.x = right.x*left.get(0,0) + right.y*left.get(0,1) + right.z*left.get(0,2);
        vector.y = right.x*left.get(1,0) + right.y*left.get(1,1) + right.z*left.get(1,2);
        vector.z = right.x*left.get(2,0) + right.y*left.get(2,1) + right.z*left.get(2,2);

        return vector;
    }


    template <typename T>
    void operator*=( sf::Vector3<T>& left, const Matrix<T>& right )
    {
        left = right * left;
    }

#endif /* MATRICES_HPP */