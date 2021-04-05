// PeykNowruzi, easy implementation
// repo available at https://github.com/Kasra-coder/magical-creations


#include <iostream>
#include <vector>
#include <memory>

using std::cout;
using std::cin;


class CharMatrix
{
public:
	inline CharMatrix( );
	inline CharMatrix( const int& Y_DIM, const int& X_DIM );
	inline ~CharMatrix( ) = default;
	inline CharMatrix( const CharMatrix& ) = delete;
	CharMatrix& operator=( const CharMatrix& ) = delete;
	inline CharMatrix( CharMatrix&& rhs ) noexcept;
	inline CharMatrix& operator=( CharMatrix&& rhs ) noexcept;

	inline const int& getY_DIM( ) const;
	inline const int& getX_DIM( ) const;
	inline std::vector<std::vector<char>>& getCharacterMatrix( );

	inline void writeToConsole( ) const;

	inline static char findCharType( const int(&coordArr)[4] );
	inline static auto initialize( const char& ch );
	inline static auto getCoords( );
	inline static void drawToScreen( );

private:
	int _Y_DIM;
	int _X_DIM;
	std::vector<std::vector<char>> _characterMatrix;
};

int main()
{
	CharMatrix::drawToScreen( );

	return 0;
}

inline CharMatrix::CharMatrix( )
	:_Y_DIM( 20 ), _X_DIM( 20 )
{
}

inline CharMatrix::CharMatrix( const int& Y_DIM, const int& X_DIM )
	: _Y_DIM( Y_DIM ), _X_DIM( X_DIM )
{
}

inline CharMatrix::CharMatrix( CharMatrix&& rhs ) noexcept
	:_Y_DIM( rhs._Y_DIM ), _X_DIM( rhs._X_DIM )
{
	_characterMatrix = std::move( rhs._characterMatrix );
	rhs._Y_DIM = 0;
	rhs._X_DIM = 0;
}

inline CharMatrix& CharMatrix::operator=( CharMatrix&& rhs ) noexcept
{
	if ( this != &rhs )
	{
		_characterMatrix = std::move( rhs._characterMatrix );
		_Y_DIM = rhs._Y_DIM;
		_X_DIM = rhs._X_DIM;

		rhs._Y_DIM = 0;
		rhs._X_DIM = 0;
	}

	return *this;
}

inline const int& CharMatrix::getY_DIM( ) const
{
	return _Y_DIM;
}

inline const int& CharMatrix::getX_DIM( ) const
{
	return _X_DIM;
}

inline std::vector<std::vector<char>>& CharMatrix::getCharacterMatrix( )
{
	return _characterMatrix;
}

inline void CharMatrix::writeToConsole( ) const
{
	for ( int row = 0; row < _Y_DIM; row++ )
	{
		for ( int col = 0; col < _X_DIM; col++ )
		{
			std::cout << _characterMatrix[row][col];
		}
	}
}

inline char CharMatrix::findCharType( const int(&coordArr)[4] )
{
	if ( abs(coordArr[0] - coordArr[2]) == 1 && abs(coordArr[1] - coordArr[3]) == 1 &&
				((coordArr[0] < coordArr[2] && coordArr[1] > coordArr[3]) || (coordArr[0] > coordArr[2] && coordArr[1] < coordArr[3])) )
	{
		return '/';
	}
	else if ( abs(coordArr[0] - coordArr[2]) == 1 && abs(coordArr[1] - coordArr[3]) == 1 &&
				((coordArr[0] < coordArr[2] && coordArr[1] < coordArr[3]) || (coordArr[0] > coordArr[2] && coordArr[1] > coordArr[3])) )
	{
		return '\\';
	}
	else if ( (coordArr[0] == coordArr[2]) && abs(coordArr[1] - coordArr[3]) == 1 )
	{
		return '|';
	}
	else if ( abs(coordArr[0] - coordArr[2]) == 1  && (coordArr[1] == coordArr[3]) )
	{
		return '-';
	}
	else
	{
		return '!';
	}
}

inline auto CharMatrix::initialize( const char& ch )
{
	std::unique_ptr<CharMatrix> up2Matrix = std::make_unique<CharMatrix>( 20, 168 );

	const int& Y_DIM = up2Matrix->getY_DIM( );
	const int& X_DIM = up2Matrix->getX_DIM( );
	std::vector<std::vector<char>>& characterMatrix = up2Matrix->getCharacterMatrix( );

	for ( int row = 0; row < Y_DIM; row++ )
	{
		characterMatrix.push_back( std::vector<char>() );
		for ( int col = 0; col < X_DIM - 1; col++ )
		{
			characterMatrix[row].push_back( ch );
		}
		characterMatrix[row].push_back( '\n' );
	}

	return up2Matrix;
}

inline auto CharMatrix::getCoords( )
{
	auto uniquePtr2Matrix = CharMatrix::initialize( ' ' );

	int coordArr[4] { 0, 0, 0, 0 };
	bool isAcceptable = true;

	unsigned int numOfSymbols;
	cin >> numOfSymbols;

	for ( unsigned int i = 0; i < numOfSymbols; ++i )
	{
		do
		{
			cin >> coordArr[0] >> coordArr[1] >> coordArr[2] >> coordArr[3];
			if ( coordArr[0] > 168 || coordArr[2] > 168 )
			{
				isAcceptable = false;
			}
			else
			{
				isAcceptable = true;
			}
		} while ( !isAcceptable );

		char ch = CharMatrix::findCharType( coordArr );
		std::vector<std::vector<char>>& characterMatrix = uniquePtr2Matrix->getCharacterMatrix( );
		if ( ch == '/' )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = '/';
			characterMatrix[coordArr[3]][coordArr[2]] = '/';
		}
		else if ( ch == '\\' )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = '\\';
			characterMatrix[coordArr[3]][coordArr[2]] = '\\';
		}
		else if ( ch == '|' )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = '|';
			characterMatrix[coordArr[3]][coordArr[2]] = '|';
		}
		else if ( ch == '-' )
		{
			characterMatrix[coordArr[1]][coordArr[0]] = '-';
			characterMatrix[coordArr[3]][coordArr[2]] = '-';
		}
		else
		{
			// pass (do nothing!)
		}

	}

	return uniquePtr2Matrix;
}

inline void CharMatrix::drawToScreen( )
{
	auto uniquePtr2Matrix = CharMatrix::getCoords( );

	uniquePtr2Matrix->writeToConsole( );
}
