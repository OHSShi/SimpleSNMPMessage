#include		"VB.hpp"

VB::VB()
{
	mValue.SetType( C_NULL_DATATYPE ); 
}

VB::~VB()
{ 

}

int		VB::Assemble()
{
	string		rObject;
	string		rValue;

	mObjectID.Assemble();
	mValue.Assemble();

	rObject		= mObjectID.GetAssemble();
	rValue		= mValue.GetAssemble();

	BER			ber;

	ber.SetType( C_SEQUENCE );
	ber.SetData( rObject + rValue );

	ber.Assemble();

	mAssembleData	= ber.GetAssemble(); 

	return		mAssembleData.size();
}

int		VB::Analyze( const string& rData )
{
	int		ret 	= mVarBind.Analyze( rData );
	if( ret != 0 )
	{
		return		ret;
	}

	string	rReadData	= mVarBind.GetPrintableData();

	ret = mObjectID.Analyze( rReadData );
	if( ret != 0 )
	{
		return	ret;
	}

	int		rLength 	= mObjectID.GetLength() + mObjectID.GetLengthOfSize() + 1;

	ret = mValue.Analyze( rReadData.substr( rLength ) );
	if( ret != 0 )
	{
		return	ret;
	}
	
	return		0;
}

string	VB::GetPrintableObjectID()
{
	return 		mObjectID.GetPrintableData();
}

string	VB::GetPrintableValue()
{
	return 		mValue.GetPrintableData();
}

string	VB::GetPrintableTypeAndValue()
{
	//mValue.PrintValueHex();	// for debug
	return 		mValue.GetPrintableTypeAndData();
}

char	VB::GetValueDataType()
{
	return	mValue.GetDataType();
}

void	VB::SetObjectID( const string& rObjectID )
{
	mObjectID.SetType( C_OBJECTID_DATATYPE );
	mObjectID.SetData( rObjectID );
}

void	VB::SetValue( const string& rValue )
{
	mValue.SetType( C_OCTET_DATATYPE );
	mValue.SetData( rValue );
}

void	VB::SetValue( const long   rValue )
{
	mValue.SetType( C_INTEGER_DATATYPE );
	char		tmpStr[ 100 ];
	sprintf( tmpStr , "%ld" , rValue ); 
	mValue.SetData( tmpStr ); 
}

void	VB::SetValue( const char rDataType , const string& rValue )
{
	int		ret	= 0;
	mValue.SetType( rDataType );
	switch( rDataType )
	{
		case C_INTEGER_DATATYPE:
			mValue.SetData( ( int )atoi( rValue.c_str() ) );
			break;

		case C_OCTET_DATATYPE:
		case C_OBJECTID_DATATYPE:
		case C_NETADDR_DATATYPE:
			mValue.SetData( rValue );
			break;

		case C_TIMETICKS_DATATYPE:
		case C_COUNTER_DATATYPE:
		case C_COUNTER64_DATATYPE:
			mValue.SetData( ( unsigned long long )( atoll( rValue.c_str() ) ) );
			break;
		case C_NULL_DATATYPE:
			break;
		default:
			break;

	}
}

void	VB::SetValue( const char rDataType , const long long& rValue )
{
	int		ret	= 0;
	mValue.SetType( rDataType );
	switch( rDataType )
	{
		case C_INTEGER_DATATYPE:
			mValue.SetData( ( int )rValue );
			break;

		case C_OCTET_DATATYPE:
		case C_OBJECTID_DATATYPE:
		case C_NETADDR_DATATYPE:
		{
			char	rTemp[ 64 ];
			memset( rTemp , 0x00 , sizeof( rTemp ) );
			snprintf( rTemp , sizeof( rTemp ) , "%lld" , rValue );
			mValue.SetData( rTemp );
		}
			break;

		case C_TIMETICKS_DATATYPE:
		case C_COUNTER_DATATYPE:
		case C_COUNTER64_DATATYPE:
			mValue.SetData( ( unsigned long long )rValue );
			break;
		case C_NULL_DATATYPE:
			break;
		default:
			break;

	}
}

string	VB::GetAssemble()
{
	return		mAssembleData;
}

long 	VB::GetLength()
{
	return mObjectID.GetLength() + mObjectID.GetLengthOfSize() + mValue.GetLength() + mValue.GetLengthOfSize() + 2;
}

int		VB::GetLengthOfSize()
{
	mVarBind.GetLengthOfSize();
}

