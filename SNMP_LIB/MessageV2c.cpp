#include		"MessageV2c.hpp"

MessageV2c::MessageV2c()
{
	mVersion.SetType	( C_INTEGER_DATATYPE );
	mVersion.SetData	( C_SNMP_V2C );
}

MessageV2c::~MessageV2c()
{
}

int MessageV2c::Assemble()
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

int MessageV2c::Analyze( const string& rData )
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

int MessageV2c::Analyze( char* rData , int rSize )
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

int MessageV2c::AnalyzeSub( const string& rAssembleData )
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

int MessageV2c::GetVBCount() 
{
	return mPDU.GetVBCount();
}

void MessageV2c::SetCommunity( string rCommunity )
{
	mCommunity.SetType	( C_OCTET_DATATYPE );
	mCommunity.SetData	( rCommunity );
}

void MessageV2c::SetVB( const string& rObjectID )
{
	mPDU.SetVB( rObjectID );
}

void MessageV2c::SetVB( const string& rObjectID , const string& rValue )
{
	mPDU.SetVB( rObjectID , rValue );
	
}

void MessageV2c::SetVB ( const string& rObjectID , long rValue )
{
	mPDU.SetVB( rObjectID , rValue );

}

void MessageV2c::SetVB( const string& rObjectID , const char rDataType , const string& rValue )
{
	mPDU.SetVB( rObjectID , rDataType , rValue );
}

void MessageV2c::SetVB( const string& rObjectID , const char rDataType , const long long& rValue )
{
	mPDU.SetVB( rObjectID , rDataType , rValue );
}

void MessageV2c::SetPDUType( char rType )
{
	mPDU.SetType( rType );
}

void MessageV2c::SetRequestID( long rRequestID )
{
	mPDU.SetRequestID( rRequestID );
}

//void MessageV2c::SetError( char rError )
void MessageV2c::SetError( int rError )
{
	mPDU.SetError( rError );
}

void MessageV2c::SetErrorIndex( int rErrorIndex )
{
	mPDU.SetErrorIndex( rErrorIndex );
}

int MessageV2c::GetVersion()
{
	return atoi( mVersion.GetPrintableData().c_str() );
}

string MessageV2c::GetCommunity()
{
	return mCommunity.GetPrintableData();
}


string MessageV2c::GetObjectID( int rIndex )
{
	return mPDU.GetObjectID( rIndex );
}

string MessageV2c::GetValue( int rIndex )
{
	return mPDU.GetValue( rIndex );
}

string MessageV2c::GetTypeAndValue( int rIndex )
{
	return mPDU.GetTypeAndValue( rIndex );
}

VB* MessageV2c::GetVarBind( int rIndex )
{   
	return mPDU.GetVarBind( rIndex );
}

long MessageV2c::GetRequestID()
{
	return mPDU.GetRequestID();
}

//char MessageV2c::GetError()
int MessageV2c::GetError()
{
	return mPDU.GetError();
}

int MessageV2c::GetErrorIndex()
{
	return mPDU.GetErrorIndex();
}

char MessageV2c::GetPDUType()
{
	return mPDU.GetType();
}

string MessageV2c::GetAssemble()
{
	return mAssembleData;
}

void	MessageV2c::Init()
{
	mPDU.Init();
}

string	MessageV2c::GetEnterpriseOid()
{
	return		mPDU.GetEnterpriseOid();
}

string	MessageV2c::GetSenderAddr()
{
	return		mPDU.GetSenderAddr();
}

int		MessageV2c::GetGenericTrap()
{
	return		mPDU.GetGenericTrap();
}

int		MessageV2c::GetSpecificTrap()
{
	return		mPDU.GetSpecificTrap();
}

string	MessageV2c::GetTimeTicks()
{
	return		mPDU.GetTimeTicks();
}

void	MessageV2c::SetEnterpriseOid( string rEnterpriseOid )
{
	mPDU.SetEnterpriseOid( rEnterpriseOid );
}

void	MessageV2c::SetSenderAddr( string rSenderAddr )
{
	mPDU.SetSenderAddr( rSenderAddr );
}

void	MessageV2c::SetGenericTrap( int rGenericTrap )
{
	mPDU.SetGenericTrap( rGenericTrap );
}

void	MessageV2c::SetSpecificTrap( int rSpecificTrap )
{
	mPDU.SetSpecificTrap( rSpecificTrap );
}

void	MessageV2c::SetTimeTicks( string rTimeTicks )
{
	mPDU.SetTimeTicks( rTimeTicks );
}

void	MessageV2c::SetNonRepeaters( int rNonRepeaters )
{
	mPDU.SetNonRepeaters( rNonRepeaters );
}

void 	MessageV2c::SetMaxRepetitions( int rMaxRepetitions )
{
	mPDU.SetMaxRepetitions( rMaxRepetitions );
}
