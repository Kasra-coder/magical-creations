
#include "Util.h"

using namespace peyknowruzi;


std::pair< bool, std::vector< std::string > > util::tokenize( const std::string_view inputStr, const std::size_t expectedTokenCount )
{
	if ( inputStr.empty( ) )
	{
		return { ( expectedTokenCount == 0 ) ? true : false, std::vector< std::string >( 0 ) };
	}

	std::stringstream ss;
	ss << inputStr.data( );

	std::vector< std::string > foundTokens { std::istream_iterator< std::string >( ss ),
											 std::istream_iterator< std::string >( ) };
	foundTokens.shrink_to_fit( );

	return { ( foundTokens.size( ) == expectedTokenCount ) ? true : false, foundTokens };
}

std::optional<int> util::isInteger( std::string_view token, const std::pair<int, int> acceptableRange ) noexcept
{
	if ( token.empty( ) )
	{
		return { };
	}

	if ( token.size( ) > 1 && token[ 0 ] == '+' && token[ 1 ] != '-' ) { token.remove_prefix( 1 ); }

	int value { };
	const auto [ ptr, ec ] { std::from_chars( token.begin( ), token.end( ), value, 10 ) };

	const auto& [ minAcceptableValue, maxAcceptableValue ] { acceptableRange };

	if ( ec != std::errc( ) || ptr != token.end( ) ||
		 value < minAcceptableValue || value > maxAcceptableValue ) { return { }; }

	return value;
}

bool util::convert_tokens_to_integers( const std::span<const std::string> tokens, const std::span<int> result_integers,
									   const std::pair<int, int> acceptableRange ) noexcept
{
	bool areTokensConvertibleToValidIntegers { };

	if ( tokens.empty( ) || tokens.size( ) > result_integers.size( ) )
	{ return areTokensConvertibleToValidIntegers = false; }

	for ( std::size_t idx = 0; idx < tokens.size( ); ++idx )
	{
		const std::optional<int> tempInteger { util::isInteger( tokens[ idx ], acceptableRange ) };

		if ( tempInteger ) { result_integers[ idx ] = tempInteger.value( ); }
		else { return areTokensConvertibleToValidIntegers = false; }
	}

	return areTokensConvertibleToValidIntegers = true;
}

bool util::convert_specific_tokens_to_integers( const std::span<const std::string> tokens, const std::span<int> result_integers,
				   								const std::span<const std::size_t> specificTokensIndices,
				   								const std::pair<int, int> acceptableRange ) noexcept
{
	bool areTokensConvertibleToValidIntegers { };

	if ( tokens.empty( ) || tokens.size( ) > result_integers.size( ) ||
		 specificTokensIndices.empty( ) || specificTokensIndices.size( ) > tokens.size( ) )
	{ return areTokensConvertibleToValidIntegers = false; }

	for ( const auto specificTokenIndex : specificTokensIndices )
	{
		if ( specificTokenIndex >= tokens.size( ) )
		{ return areTokensConvertibleToValidIntegers = false; }

		const std::optional<int> tempInteger { util::isInteger( tokens[ specificTokenIndex ], acceptableRange ) };

		if ( tempInteger ) { result_integers[ specificTokenIndex ] = tempInteger.value( ); }
		else { return areTokensConvertibleToValidIntegers = false; }
	}

	return areTokensConvertibleToValidIntegers = true;
}
