#include	"SNMPMessage.hpp"
#include	"BER.hpp"

static void GetTokens( const string& str, vector< long >& tokens , const string& delimiters = " " )
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0); // 맨 처음 문자가 구분자일 때
	string::size_type pos     = str.find_first_of(delimiters, lastPos);     // 구분자 찾기
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back( atol( str.substr(lastPos, pos - lastPos).c_str() ) ); // 찾은 token을 vector에 저장
		lastPos = str.find_first_not_of(delimiters, pos);        // 구분자 다음으로 이동
		pos = str.find_first_of(delimiters, lastPos);        // 다음구분자 찾기
	}
}

SNMPMessage::SNMPMessage()
{
}

SNMPMessage::~SNMPMessage()
{
}

int		SNMPMessage::GetSnmpMsgVersion( const string& rSnmpMsg )
{
	return	GetSnmpMsgVersion( ( char* )rSnmpMsg.c_str() , rSnmpMsg.size() );
}

int		SNMPMessage::GetSnmpMsgVersion( char* rSnmpMsg , int rSize )
{
	int	rPnt	= 0;

	if( rSize < 5 )
	{
		return	-2;	// Msg Not Closed.
	}

	char    rType;
	char    rLengthData;
	int     rLength;
	int     rLengthOfSize;

	rType   = rSnmpMsg[ rPnt++ ];
	if( rType != C_INTEGER_DATATYPE )
	{
		return	-1;
	}

	rLengthData = rSnmpMsg[ rPnt++ ];
	if( ( rLengthData & 0x80 ) == 0x80 )
	{
		int rIndex;
		rIndex  = ( rLengthData & 0x0F );

		//if( ( int )rSnmpMsg.size() < ( rIndex + 2 )  )
		if( rSize < ( rIndex + 2 )  )
		{
			return  -2;	// Msg Not Closed.
		}

		string  x;
		//x.assign( rSnmpMsg , rPnt , rIndex );
		x.insert( 0 , rSnmpMsg + rPnt , rIndex );

		rLength = BER::ConvHexToLength( x );

		rPnt    += rIndex;

		rLengthOfSize   = rIndex + 1;
	}
	else
	{
		rLength         = rLengthData;
		rLengthOfSize   = 1;
	}

	rPnt += 2;

	string  rVersionData;
	rVersionData.insert( 0 , rSnmpMsg + rPnt , 1 );

	int rVersion    = BER::ConvHexToLength( rVersionData );

	return	rVersion;

}

int		SNMPMessage::CompareOid( const string& rOid1 , const string& rOid2 )
{
#if 0
	string	rOid1Hex	= BER::ConvOIDToHex( rOid1 );
	string	rOid2Hex	= BER::ConvOIDToHex( rOid2 );

	return	rOid1Hex.compare( rOid2Hex );
#endif

	vector< long >	rVecOid1;
	vector< long >	rVecOid2;

	GetTokens( rOid1 , rVecOid1 , "." );
	GetTokens( rOid2 , rVecOid2 , "." );

	int	rLen1	= rVecOid1.size();
	int	rLen2	= rVecOid2.size();
	int	rLen	= ( rLen1 < rLen2 ) ? rLen1 : rLen2;

	for( int i = 0 ; i < rLen ; i++ )
	{
		if( rVecOid1[ i ] != rVecOid2[ i ] )
		{
			if( rVecOid1[ i ] < rVecOid2[ i ] )
			{
				return	-1;
			}
			else
			{
				return	1;
			}
		}
	}

	if( rLen1 < rLen2 )
	{
		return	-1;
	}
	if( rLen1 > rLen2 )
	{
		return	1;
	}

	return	0;
}

void	SNMPMessage::SetPeerIp( const string& rPeerIp )
{
	mPeerIp	= rPeerIp;
}

string	SNMPMessage::GetPeerIp()
{
	return	mPeerIp;
}
