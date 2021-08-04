#include		"Message.hpp"

Message::Message()
{
	mVersion.SetType	( C_INTEGER_DATATYPE );
	mVersion.SetData	( C_SNMP_V1 );
}

Message::~Message()
{
}

int Message::Assemble()
{
	string rVersion;
	string rCommunity;
	string rPDU;

	mVersion.Assemble();
	mCommunity.Assemble();

	mPDU.Assemble();

	rVersion	= mVersion.GetAssemble();
	rCommunity	= mCommunity.GetAssemble();
	rPDU		= mPDU.GetAssemble();

	BER ber;

	ber.SetType( C_SEQUENCE );
	ber.SetData( rVersion + rCommunity + rPDU );

	ber.Assemble();

	mAssembleData = ber.GetAssemble();

	return mAssembleData.size();

}

int Message::Analyze( const string& rData )
{
	BER ber;
	string		rAssembleData;

	Init();

	int ret = ber.Analyze( rData );
	if( ret != 0 )
	{
		return ret;
	}

	rAssembleData		= ber.GetPrintableData();

	return	AnalyzeSub( rAssembleData );
}

int Message::Analyze( char* rData , int rSize )
{
	BER ber;
	string		rAssembleData;

	Init();

	int ret = ber.Analyze( rData , rSize );
	if( ret != 0 )
	{
		return ret;
	}

	rAssembleData		= ber.GetPrintableData();

	return	AnalyzeSub( rAssembleData );
}

int Message::AnalyzeSub( const string& rAssembleData )
{
	int	ret;
	int	pnt;

	ret = mVersion.Analyze( rAssembleData );
	if( ret != 0 )
	{
		return ret;
	}

	pnt		= mVersion.GetLength() + mVersion.GetLengthOfSize() + 1;
	ret		= mCommunity.Analyze( rAssembleData.substr( pnt ) );
	if( ret != 0 )
	{
		return ret;
	}

	pnt		+= mCommunity.GetLength() + mVersion.GetLengthOfSize() + 1;
	ret		= mPDU.Analyze(	rAssembleData.substr( pnt ) );
	if( ret != 0 )
	{
		return ret;
	}

	return 0;
}


int Message::GetVBCount() 
{
	return mPDU.GetVBCount();
}

void Message::SetCommunity( string rCommunity )
{
	mCommunity.SetType	( C_OCTET_DATATYPE );
	mCommunity.SetData	( rCommunity );
}

void Message::SetVB( const string& rObjectID )
{
	mPDU.SetVB( rObjectID );
}

void Message::SetVB( const string& rObjectID , const string& rValue )
{
	mPDU.SetVB( rObjectID , rValue );
	
}

void Message::SetVB ( const string& rObjectID , long rValue )
{
	mPDU.SetVB( rObjectID , rValue );

}

void Message::SetVB( const string& rObjectID , const char rDataType , const string& rValue )
{
	mPDU.SetVB( rObjectID , rDataType , rValue );
}

void Message::SetVB( const string& rObjectID , const char rDataType , const long long& rValue )
{
	mPDU.SetVB( rObjectID , rDataType , rValue );
}

void Message::SetPDUType( char rType )
{
	mPDU.SetType( rType );
}

void Message::SetRequestID( long rRequestID )
{
	mPDU.SetRequestID( rRequestID );
}

//void Message::SetError( char rError )
void Message::SetError( int rError )
{
	mPDU.SetError( rError );
}

void Message::SetErrorIndex( int rErrorIndex )
{
	mPDU.SetErrorIndex( rErrorIndex );
}

int Message::GetVersion()
{
	return atoi( mVersion.GetPrintableData().c_str() );
}

string Message::GetCommunity()
{
	return mCommunity.GetPrintableData();
}


string Message::GetObjectID( int rIndex )
{
	return mPDU.GetObjectID( rIndex );
}

string Message::GetValue( int rIndex )
{
	return mPDU.GetValue( rIndex );
}

string Message::GetTypeAndValue( int rIndex )
{
	return mPDU.GetTypeAndValue( rIndex );
}

VB* Message::GetVarBind( int rIndex )
{
	return mPDU.GetVarBind( rIndex );
}

long Message::GetRequestID()
{
	return mPDU.GetRequestID();
}

//char Message::GetError()
int Message::GetError()
{
	return mPDU.GetError();
}

int Message::GetErrorIndex()
{
	return mPDU.GetErrorIndex();
}

char Message::GetPDUType()
{
	return mPDU.GetType();
}

string Message::GetAssemble()
{
	return mAssembleData;
}

void	Message::Init()
{
	mPDU.Init();
}

string	Message::GetEnterpriseOid()
{
	return		mPDU.GetEnterpriseOid();
}

string	Message::GetSenderAddr()
{
	return		mPDU.GetSenderAddr();
}

int		Message::GetGenericTrap()
{
	return		mPDU.GetGenericTrap();
}

int		Message::GetSpecificTrap()
{
	return		mPDU.GetSpecificTrap();
}

string	Message::GetTimeTicks()
{
	return		mPDU.GetTimeTicks();
}

void	Message::SetEnterpriseOid( string rEnterpriseOid )
{
	mPDU.SetEnterpriseOid( rEnterpriseOid );
}

void	Message::SetSenderAddr( string rSenderAddr )
{
	mPDU.SetSenderAddr( rSenderAddr );
}

void	Message::SetGenericTrap( int rGenericTrap )
{
	mPDU.SetGenericTrap( rGenericTrap );
}

void	Message::SetSpecificTrap( int rSpecificTrap )
{
	mPDU.SetSpecificTrap( rSpecificTrap );
}

void	Message::SetTimeTicks( string rTimeTicks )
{
	mPDU.SetTimeTicks( rTimeTicks );
}
