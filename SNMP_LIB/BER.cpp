#include		"BER.hpp"

const static int gDistinctionNum    = 1;
#define is_bigendian() ( ( *( char* )&gDistinctionNum ) == 0 )

BER::BER()
{
}

BER::~BER()
{
}

string BER::ConvLengthToString( long rValue )
{
	string		value;

	value 	= ConvNumberToString( rValue );
	if( rValue > 128 )
	{
		char		head[2];
		
		head[ 0 ] = ( 0x80 | value.size() );
		head[ 1 ] = 0x00;


		value.insert( 0 , head );
	}

	return	value;
}

int	BER::Assemble()
{
	switch( mType )
	{
		case C_TIMETICKS_DATATYPE :
		case C_NETADDR_DATATYPE :
		case C_INTEGER_DATATYPE :
		case C_OCTET_DATATYPE :
		case C_NULL_DATATYPE :
		case C_OBJECTID_DATATYPE :
		case C_SEQUENCE :
		case C_GETREQUESTPDU_DATATYPE :
		case C_GETNEXTREQUESTPDU_DATATYPE :
		case C_GETRESPONSEPDU_DATATYPE :
		case C_SETREQUESTPDU_DATATYPE :
		case C_TRAPPDU_DATATYPE :
		case C_TRAP2PDU_DATATYPE :
		case C_COUNTER64_DATATYPE :
		case C_GETBULKREQUEST_DATATYPE :

		case C_NOSUCHOBJECT:
		case C_NOSUCHINSTANCE :
		case C_ENDOFMIBVIEW :
			break;
		default :
			return 0;
	}

	mAssembleData.clear();

	switch( mType )
	{
		case C_NETADDR_DATATYPE :
			mAssembleData	= ConvNetAddr( mReadableData );
			break;
		case C_INTEGER_DATATYPE :
		case C_TIMETICKS_DATATYPE :
		case C_COUNTER_DATATYPE :
		case C_GAUGE_DATATYPE :
		case C_COUNTER64_DATATYPE :
			mAssembleData = ConvNumberToString( mReadableData );
			break;
		case C_NULL_DATATYPE :
		case C_NOSUCHOBJECT:
		case C_NOSUCHINSTANCE :
		case C_ENDOFMIBVIEW :
			break;
		case C_OBJECTID_DATATYPE :
		{
			int firstOID		= -1;
			int secondOID		= -1;
			int oid				= 0;
			int	pnt				= 0;
			int	i;

			char tmpStr[ 100 ];
			string rData = mReadableData + ".";

			for( i = 0 ; i < rData.size() ; i++ )
			{
				if( rData[i] == '.' )
				{
					tmpStr[pnt]		= 0x00;
					oid		= atoi( tmpStr );
					if( firstOID == -1 )
					{
						firstOID		= oid;
					}
					else if( secondOID == -1 )
					{
						secondOID		= oid;

						oid		= firstOID * 40 + secondOID;
						mAssembleData	= oid;
					}
					else
					{
						mAssembleData += ConvOIDToString( tmpStr );
					}

					pnt				= 0; 
				}
				else
				{
					tmpStr[pnt++]		= rData[i];
				}
			}
		}

			break;

		case C_OCTET_DATATYPE : 
		case C_SEQUENCE :
		case C_GETREQUESTPDU_DATATYPE :
		case C_GETRESPONSEPDU_DATATYPE :
		case C_GETNEXTREQUESTPDU_DATATYPE :
		case C_SETREQUESTPDU_DATATYPE :
		case C_TRAPPDU_DATATYPE :
		case C_TRAP2PDU_DATATYPE :
		case C_GETBULKREQUEST_DATATYPE :
			mAssembleData	= mReadableData;
			break;
	}
#if 0
cout << "XX : ";
for( int i = 0 ; i < mAssembleData.size() ; i++ )
{
	printf( "%02X " , mAssembleData[ i ] );
}
cout << endl;
#endif
	mLength		= mAssembleData.size();

#if 0
if( mType == C_OBJECTID_DATATYPE )
{
	cout << "XXXXX : ";
	for( int i = 0 ; i < mAssembleData.size() ; i++ )
	{
		printf( "%02x " , mAssembleData[ i ] );
	}
	cout << endl;
}
#endif

	mAssembleData.insert( 0 , ConvOIDToString( mType ) );
	mAssembleData.insert( 1 , ConvLengthToString( mLength ) );

	return		mAssembleData.size();
}

string	BER::ConvNetAddr( string rData )
{
	vector<string> str_vector;

	string::size_type start = rData.find_first_not_of( "." );

	start   = 0;
	do
	{
		string::size_type end = rData.find_first_of( ".", start );
		if ( string::npos == end )
		{
			str_vector.push_back( rData.substr( start ));
			start = string::npos;
		}
		else
		{
			str_vector.push_back( rData.substr( start, end - start ));
			start   = end + 1;
		}
	}
	while ( string::npos != start );

	if( str_vector.size() != 4 )
	{
		str_vector.clear();
		str_vector.push_back( "0" );
		str_vector.push_back( "0" );
		str_vector.push_back( "0" );
		str_vector.push_back( "0" );
	}

	string		rValue;
	for( int i = 0 ; i < 4 ; i++ )
	{
		rValue += ConvNumberToString( str_vector[i] );
	}

	return rValue;
}

long long	BER::ConvHexToNumber( string rData )
{
#if 0
	char		tmpStr[ 100 ];
	long long		rValue = 0;

	int			rLength	= rData.size();

	for( int i = 0 ; i < rLength ; i++ )
	{
		if( i == rLength - 1 )
		{
			rValue += ( rData[i] & 0xff );
		}
		else
		{
			rValue += (long long)( pow( 256 , ( rLength - i - 1 ) ) * ( rData[i] & 0xff ) );
		}

	}

	return		rValue; 
#endif

	long long rRet = 0;
	if( rData[ 0 ] & ( char )0x80 )
	{
		//rRet = 0xFFFFFFFFFFFFFFFF;
		rRet = ~0;	// -1. 2's complement 0xFFFFFFFFFFFFFFFF
	}
	char* rpPnt = ( char* )&rRet;

	if( !is_bigendian() )
	{
		for( int i = 0 , j = rData.size() - 1; i < rData.size() ; i++ , j-- )
		{
			memcpy( rpPnt + i , ( char* )rData.c_str() + j , sizeof( char ) );
		}
	}
	else	// Test ¾ÈÇØº½.
	{
		memcpy( rpPnt + ( sizeof( rRet ) - rData.size() ) , ( char* )rData.c_str() , sizeof( rData ) );
	}

	return  rRet;
}

long long	BER::ConvHexToLength( string rData )
{
	long long rRet = 0;
	char* rpPnt = ( char* )&rRet;

	if( !is_bigendian() )
	{
		for( int i = 0 , j = rData.size() - 1; i < rData.size() ; i++ , j-- )
		{
			memcpy( rpPnt + i , ( char* )rData.c_str() + j , sizeof( char ) );
		}
	}
	else	// Test ¾ÈÇØº½.
	{
		memcpy( rpPnt + ( sizeof( rRet ) - rData.size() ) , ( char* )rData.c_str() , sizeof( rData ) );
	}

	return  rRet;
}

string	BER::GetAssemble()
{
	return		mAssembleData;
}

int		BER::Analyze( const string& rData )
{
	mAssembleData	= rData;

	return	Analyze();
}

int		BER::Analyze( char* rData , int rSize )
{
	mAssembleData.insert( 0 , rData , rSize );

	return	Analyze();
}

int		BER::Analyze()
{
	char		rLength;
	int			pnt			= 0;

	mType = mAssembleData[pnt++];

	switch( mType )
	{
		case C_NETADDR_DATATYPE :
		case C_TIMETICKS_DATATYPE :
		case C_COUNTER_DATATYPE :
		case C_INTEGER_DATATYPE :
		case C_OCTET_DATATYPE :
		case C_NULL_DATATYPE :
		case C_OBJECTID_DATATYPE :
		case C_SEQUENCE :
		case C_GETREQUESTPDU_DATATYPE :
		case C_GETNEXTREQUESTPDU_DATATYPE :
		case C_GETRESPONSEPDU_DATATYPE :
		case C_SETREQUESTPDU_DATATYPE :
		case C_TRAPPDU_DATATYPE :
		case C_TRAP2PDU_DATATYPE :
		case C_GAUGE_DATATYPE :
		case C_COUNTER64_DATATYPE :
		case C_GETBULKREQUEST_DATATYPE :

		case C_NOSUCHOBJECT:
		case C_NOSUCHINSTANCE :
		case C_ENDOFMIBVIEW :
			break;
		default :
			//cout << "XXX : " << mType << endl;
			printf( "Unknown Type(0x%02x)\n" , mType );

			return -1;
	}

	rLength		 = mAssembleData[pnt++];
	if( ( rLength & 0x80 ) == 0x80 )
	{
		int			rIndex;

		rIndex	= ( rLength & 0x0f );

		string x;

		//x.assign( mAssembleData , pnt , rIndex );
		x.insert( 0 , ( char* )mAssembleData.c_str() + pnt , rIndex );
		mLength = ConvHexToLength( x );
		pnt		+= rIndex; 

		mLengthOfSize		= rIndex + 1;
	}
	else
	{
		mLength		= rLength;
		mLengthOfSize		= 1;
	}
	
	//mData.assign( mAssembleData , pnt , mLength );
	mData.insert( 0 , ( char* )mAssembleData.c_str() + pnt , mLength );

	if( mLength > mData.size() )
	{
		return 1;
	}


	mReadableData.clear();
	int			i;
	switch( mType )
	{
		case C_NETADDR_DATATYPE :
		{
			char	tmpStr[5];
			int		rValue = 0;

			for( i = 0 ; i < mLength ; i++ )
			{
				rValue	= ( mData[i] & 0xff );

				sprintf( tmpStr , "%d" , rValue );

				if( i != 0 )
				{
					mReadableData += ".";
				}

				mReadableData	+= tmpStr;
			}
		} 
			break;
		case C_TIMETICKS_DATATYPE :
		case C_COUNTER_DATATYPE :
		case C_GAUGE_DATATYPE :
		case C_COUNTER64_DATATYPE :
		{
			unsigned long long	rValue = ConvHexToNumber( mData );
			char		tmpStr[ 100 ];

			sprintf( tmpStr , "%llu" , rValue );
			mReadableData = tmpStr; 
		}
			break;

		case C_INTEGER_DATATYPE :
		{
			char		tmpStr[ 100 ];

			int			rValue = ConvHexToNumber( mData );
			sprintf( tmpStr , "%d" , rValue );

			mReadableData = tmpStr; 
		}
			break;

		case C_OBJECTID_DATATYPE :
		{
			int firstOID		= mData[0];
			int devideValue		= firstOID/40;
			int modValue		= firstOID - devideValue * 40;

			char	tmpStr[64];

			sprintf( tmpStr , "%d.%d" , devideValue , modValue );
			mReadableData = tmpStr;

			for( i = 1 ; i < rLength ; )
			{
				mReadableData += ".";

				if( ( mData[i] & 0x80 ) == 0x80 )
				{
#if 0
					int j = 0;
					for( ; ( mData[ i + j ] & 0x80 ) == 0x80 ; j++ )
					{
					}

					int val;
					if( j == 2 )
					{
						val = ( mData[i] & 0x7f ) * 16384;
						val += ( mData[ i + 1 ] & 0x7f ) * 128;
						val += mData[ i + 2];
					}
					else if( j == 1 )
					{

						val = ( mData[i] & 0x7f ) * 128;
						//val = ( unsigned int )( ( mData[i] - 128 ) * 128 );
						//i++;
						val += mData[i + 1];
					}

					i += j;
					sprintf( tmpStr , "%d" , val );
					mReadableData += tmpStr;
#endif
					int j               = 0;
					int rTempNum        = 0x80;
					int val             = 0;

					vector< int >       rVecTemp;

					for( ; ( mData[ i + j ] & 0x80 ) == 0x80 ; j++ )
					{
						rVecTemp.push_back( mData[ i + j ] & 0x7f );
					}

					i += j;

					for( j = rVecTemp.size() - 1 ; j >= 0 ; j-- )
					{
						val += ( rVecTemp[ j ] * rTempNum );
						rTempNum = rTempNum * 0x80;
					}

					val += mData[ i ];
					sprintf( tmpStr , "%d" , val );
					mReadableData += tmpStr;
				}
				else
				{
					sprintf( tmpStr , "%d" , mData[i] );
					mReadableData += tmpStr;
				}

				i++;
			}

		}
			break;

		case C_OCTET_DATATYPE :
		case C_SEQUENCE :
		case C_GETREQUESTPDU_DATATYPE :
		case C_GETNEXTREQUESTPDU_DATATYPE :
		case C_GETRESPONSEPDU_DATATYPE :
		case C_SETREQUESTPDU_DATATYPE :
		case C_TRAPPDU_DATATYPE :
		case C_TRAP2PDU_DATATYPE :
		case C_GETBULKREQUEST_DATATYPE :
			mReadableData	= mData;
			break;
		case C_NOSUCHOBJECT:
		case C_NOSUCHINSTANCE :
		case C_ENDOFMIBVIEW :
			break;

	}
	return		0;
}

string	BER::GetPrintableData()
{
	return		mReadableData;
}

string	BER::GetPrintableTypeAndData()
{
	string	rRetStr( GET_DATATYPE_STR( mType ) );
	return	rRetStr + ":" + mReadableData;
}

void	BER::SetData( long long rData )
{
	char tmpStr[ 100 ];

	sprintf( tmpStr , "%lld" , rData );

	SetData( tmpStr );
}

void	BER::SetData( string rData )
{
	mReadableData	= rData;
}

void	BER::SetType( char rType )
{
	mType	= rType;
}

char	BER::GetDataType()
{
	return		mType;
}

long	BER::GetLength()
{
	return		mLength;
}

string	BER::ConvNumberToString( long long rValue )
{
#if 0
	char    tmpStr[10];
	string  rHex;

	rHex.clear();

	long long       value       = rValue;
	char*   rPnt    = ( char* )&rValue;

	for( int i = 0 ; i < sizeof( rValue ) ; i++ )
	{
		value       = value / 256;

		memcpy( tmpStr , &rPnt[ i ] , 1 );
		rHex.insert( 0 , tmpStr , 1 );

		if( value == 0 )
		{
			break;
		}
	}
	return      rHex;
#endif

	char    tmpStr[ 64 ];
	string  rHex;

	rHex.clear();

	long long       value       = rValue;
	char*   rPnt    = ( char* )&rValue;

	if( !is_bigendian() )
	{
		for( int i = 0 ; i < sizeof( rValue ) ; i++ )
		{
			memcpy( tmpStr , &rPnt[ i ] , 1 );
			rHex.insert( 0 , tmpStr , 1 );
		}
	}
	else	// Test ¾ÈÇØº½.
	{
		memcpy( tmpStr , rPnt , sizeof( rValue ) );
		rHex.insert( 0 , tmpStr , sizeof( rValue ) );
	}

	bool	rNegativeFlag = false;
	int		rCount = 0;

	if( rHex[ 0 ] == ( char )0x00 )
	{
		int	rHexSize = rHex.size();
		for( int i = 0 ; i < rHexSize - 1 ; i++ )
		{
			if( rHex[ i ] == ( char )0x00 )
			{
				rCount++;
				continue;
			}
			break;
		}
		rHex.erase( 0 , rCount );
	}
	else
	{
		int	rHexSize = rHex.size();
		for( int i = 0 ; i < rHexSize - 1 ; i++ )
		{
			if( rHex[ i ] == ( char )0xFF )
			{
				rNegativeFlag	= true;
				rCount++;
				continue;
			}
			break;
		}
		rHex.erase( 0 , rCount );
		if( rNegativeFlag == true )
		{
			if( !( rHex[ 0 ] & 0x80 ) )
			{
				char	rTemp[ 2 ] = { 0xFF , 0x00 };
				rHex.insert( 0 , rTemp , 1 );
			}
		}
	}
	

#if 0
for( int i = 0 ; i < rHex.size() ; i++ )
{
	printf( "%02x " , rHex[ i ] );
}
cout << endl;
#endif

	return      rHex;
}


string	BER::ConvNumberToString( string rValue )
{
	return		ConvNumberToString( atoll( rValue.c_str() ) );
}

string	BER::ConvOIDToString( string rValue )
{
	int		value;

	value = atoi( rValue.c_str() );
	return ConvOIDToString( value );
}

string	BER::ConvOIDToString( int rValue )
{
	string  value;

#if 0
	if( rValue >= 16384 )
	{
		val1 = rValue / 16384;
		val2 = rValue - ( val1 * 16384 );
		//val2 = rValue % 16384;
		if( val2 >= 128 )
		{
			int val3 = val2 / 128;
			int val4 = val2 % 128;

			value   = val1 | 0x80;
			value   += val3 | 0x80;
			value   += val4;
		}
		else
		{
			value   = val1 | 0x80;
			value   += ( char )0x80;
			value   += ( char )val2;
		}
	}
	else if( rValue >= 128 )
	{
		val1 = rValue / 128;
		val2 = rValue - ( val1 * 128 );
		//val2 = rValue % 128;


		value   =  val1 | 0x80;;
		value   += ( char )val2;
	}
	else
	{
		value   = rValue;
	}
#endif

	if( rValue < 0x80 )
	{
		value   = rValue;
	}
	else
	{
		vector< char >  rVecChar;
		while( rValue > 0 )
		{
			if( rVecChar.size() == 0 )
			{
				rVecChar.push_back( rValue % 0x80 );
			}
			else
			{
				rVecChar.push_back( ( rValue % 0x80 ) | 0x80 );
			}
			rValue = rValue / 0x80;
		}

		for( int i = rVecChar.size() - 1 ; i >= 0 ; i-- )
		{
			value += rVecChar[ i ];
		}

	}


	return   value;
}

void	BER::Print()
{
	cout << "DATA PRINT" << endl;
	for( int i = 0 ; i < mAssembleData.size() ; i++ )
	{
		printf( "[%02x]\n" , mAssembleData[i] );
	}
}

void	BER::PrintValueHex()
{
	cout << "VALUE PRINT" << endl;
	for( int i = 0 ; i < mData.size() ; i++ )
	{
		printf( "[%02x]\n" , mData[i] );
	}
}

void	BER::Print( string rData )
{
	cout << "DATA PRINT" << endl;
	for( int i = 0 ; i < rData.size() ; i++ )
	{
		printf( "[%02x]\n" , rData[i] );
	}
}

int		BER::GetLengthOfSize()
{
	return		mLengthOfSize;
}

string	BER::ConvOIDToHex( const string& rOid )
{
	int firstOID        = -1;
	int secondOID       = -1;
	int oid             = 0;
	int pnt             = 0;
	int i;

	char tmpStr[ 128 ];
	string	rRetStr;
	string rData = rOid + ".";

	for( i = 0 ; i < rData.size() ; i++ )
	{
		if( rData[i] == '.' )
		{
			tmpStr[pnt]     = 0x00;
			oid     = atoi( tmpStr );
			if( firstOID == -1 )
			{
				firstOID        = oid;
			}
			else if( secondOID == -1 )
			{
				secondOID       = oid;

				oid     = firstOID * 40 + secondOID;
				rRetStr   = oid;
			}
			else
			{
				rRetStr += ConvOIDToString( tmpStr );
			}

			pnt             = 0;
		}
		else
		{
			tmpStr[pnt++]       = rData[i];
		}
	}

	return	rRetStr;
}
