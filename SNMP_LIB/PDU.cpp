#include		"PDU.hpp"

PDU::PDU()
{
	mVarBindList.SetType ( C_SEQUENCE );
}

PDU::~PDU()
{ 
	for( int i = 0 ; i < mVarBind.size() ; i++ )
	{
		delete	mVarBind[ i ];
	}
}

int 	PDU::Assemble()
{
	string mVarBindTemp;
	mVarBindTemp.clear();

	vector< VB* >::iterator iter;
	for( iter = mVarBind.begin() ; iter != mVarBind.end() ; iter++ )
	{
		( *iter ) -> Assemble();
		mVarBindTemp += ( ( *iter ) -> GetAssemble() );
	}

	mVarBindList.SetData( mVarBindTemp );

	if( mType == C_TRAPPDU_DATATYPE )
	{
		mArgument[ "1.ENT_OID" ].Assemble();
		mArgument[ "2.SEND_ADDR" ].Assemble();
		mArgument[ "3.TRAP_TYPE" ].Assemble();
		mArgument[ "4.SPEC_CODE" ].Assemble();
		mArgument[ "5.TIMESTAMP" ].Assemble();
	}
	else
	{
		mArgument[ "1.REQUEST_ID" ].Assemble();
		mArgument[ "2.ERROR" ].Assemble();
		mArgument[ "3.ERROR_INDEX" ].Assemble();
	}

	mVarBindList.Assemble();

	BER ber;

	ber.SetType( mType );

	map< string , BER >::iterator		rArgumentIter;
	string		rData;
	rData.clear();
	for( rArgumentIter = mArgument.begin() ; rArgumentIter != mArgument.end() ; rArgumentIter++ )
	{
		rData	+= rArgumentIter->second.GetAssemble();
	}

	ber.SetData( rData + mVarBindList.GetAssemble() );

	ber.Assemble();

	mAssembleData = ber.GetAssemble();

	return mAssembleData.size();

}

string	PDU::GetAssemble()
{
	return mAssembleData;
}

int 	PDU::Analyze( const string& rData )
{
	BER 		ber;
	string		rAssembleData;
	int			pnt;

	int ret = ber.Analyze( rData );
	if( ret != 0 )
	{
		return ret;
	}

	SetType( ber.GetDataType() );

	rAssembleData		= ber.GetPrintableData();


	map< string , BER >::iterator		rArgumentIter;

	pnt		= 0;
	for( rArgumentIter = mArgument.begin() ; rArgumentIter != mArgument.end() ; rArgumentIter++ )
	{
		BER		ber;
		ret = ber.Analyze( rAssembleData.substr( pnt ) );

		if( ret != 0 )
		{
			return ret;
		}

		rArgumentIter->second		= ber;
		pnt		+= ( rArgumentIter->second.GetLength() + rArgumentIter->second.GetLengthOfSize() + 1 );
	}

	ret = mVarBindList.Analyze( rAssembleData.substr( pnt ) );
	if( ret != 0 )
	{
		return ret;
	}

	rAssembleData		= mVarBindList.GetPrintableData();
	long	rVBSize 	= mVarBindList.GetLength();

	pnt			= 0;

	for( int i = 0 ; i < mVarBind.size() ; i++ )
	{
		delete mVarBind[ i ];
	}
	mVarBind.clear();
	

	while( pnt < rVBSize )
	{
		VB*		vb	= new VB;

		ret  = vb->Analyze( rAssembleData.substr( pnt ) );

		if( ret != 0 )
		{
			return ret;
		}

		mVarBind.push_back( vb );
	
		pnt		+= ( vb->GetLength() + vb->GetLengthOfSize() + 1 );

	
	}

	return 0;
}

int		PDU::GetVBCount()
{
	return	mVarBind.size();
}

void 	PDU::SetVB( const string& rObjectID )
{
	VB*			vb	= new VB;
	vb->SetObjectID( rObjectID );

	mVarBind.push_back( vb );

}


void 	PDU::SetVB( const string& rObjectID , const string& rValue )
{
	VB*		vb	= new VB;
	vb->SetObjectID	( rObjectID );
	vb->SetValue	( rValue );

	mVarBind.push_back( vb );
}


void 	PDU::SetVB( const string& rObjectID , long rValue )
{
	VB*		vb = new VB;
	vb->SetObjectID	( rObjectID );
	vb->SetValue	( rValue );

	mVarBind.push_back( vb );
}

void	PDU::SetVB( const string& rObjectID , const char rDataType , const string& rValue )
{
	VB*	vb = new VB;
	vb->SetObjectID		( rObjectID );
	vb->SetValue		( rDataType , rValue );

	mVarBind.push_back( vb );
}

void	PDU::SetVB( const string& rObjectID , const char rDataType , const long long& rValue )
{
	VB*	vb = new VB;
	vb->SetObjectID		( rObjectID );
	vb->SetValue		( rDataType , rValue );

	mVarBind.push_back( vb );
}


void	PDU::SetRequestID( long rRequestID )
{
	mArgument[ "1.REQUEST_ID" ].SetData( rRequestID );
}


//void	PDU::SetError( char rError )
void	PDU::SetError( int rError )
{
	mArgument[ "2.ERROR" ].SetData( rError );
}


void	PDU::SetErrorIndex( int rErrorIndex )
{
	mArgument[ "3.ERROR_INDEX" ].SetData( rErrorIndex );
}

string	PDU::GetEnterpriseOid()
{
	return mArgument[ "1.ENT_OID" ].GetPrintableData();
}

string	PDU::GetSenderAddr()
{
	return mArgument[ "2.SEND_ADDR" ].GetPrintableData();
}

int		PDU::GetGenericTrap()
{
	return atoi( mArgument[ "3.TRAP_TYPE" ].GetPrintableData().c_str() );
}

int		PDU::GetSpecificTrap()
{
	return atoi( mArgument[ "4.SPEC_CODE" ].GetPrintableData().c_str() );
}

string	PDU::GetTimeTicks()
{
	return mArgument[ "5.TIMESTAMP" ].GetPrintableData();
}

void	PDU::SetType( char rType )
{
	mType = rType;
	mArgument.clear();

	if( mType == C_TRAPPDU_DATATYPE )
	{
		BER		rEndOid;
		BER		rSendAddr;
		BER		rTrapType;
		BER		rSpecCode;
		BER		rTimestamp;

		rEndOid.SetType( C_OBJECTID_DATATYPE );
		rSendAddr.SetType( C_NETADDR_DATATYPE );
		rTrapType.SetType( C_INTEGER_DATATYPE );
		rSpecCode.SetType( C_INTEGER_DATATYPE );
		rTimestamp.SetType( C_TIMETICKS_DATATYPE );

		mArgument.insert( make_pair( "1.ENT_OID"	,	rEndOid		) );
		mArgument.insert( make_pair( "2.SEND_ADDR" 	,	rSendAddr	) );
		mArgument.insert( make_pair( "3.TRAP_TYPE"	,	rTrapType	) );
		mArgument.insert( make_pair( "4.SPEC_CODE"	,	rSpecCode	) );
		mArgument.insert( make_pair( "5.TIMESTAMP"	,	rTimestamp	) );
	}
	else
	{
		BER			rRequestID;
		BER			rError;
		BER			rErrorIndex;

    	rRequestID.SetType   ( C_INTEGER_DATATYPE );
		rError.SetType       ( C_INTEGER_DATATYPE );
		rErrorIndex.SetType  ( C_INTEGER_DATATYPE );

		mArgument.insert( make_pair( "1.REQUEST_ID"	, rRequestID	) );
		mArgument.insert( make_pair( "2.ERROR"		, rError		) );
		mArgument.insert( make_pair( "3.ERROR_INDEX"	, rErrorIndex	) ); 
	}

}

string 	PDU::GetObjectID( int rIndex )
{
	vector< VB* >::iterator iter;
	iter = mVarBind.begin() + rIndex;

	return ( *iter ) -> GetPrintableObjectID();	
}


string 	PDU::GetValue( int rIndex )
{
	vector< VB* >::iterator iter;
	iter = mVarBind.begin() + rIndex;

	return ( *iter ) -> GetPrintableValue();
}

string	PDU::GetTypeAndValue( int rIndex )
{
	vector< VB* >::iterator iter;
	iter = mVarBind.begin() + rIndex;

	return ( *iter ) -> GetPrintableTypeAndValue();
}

VB*		PDU::GetVarBind( int rIndex )
{
	vector< VB* >::iterator iter;
	iter = mVarBind.begin() + rIndex;

	return	*iter;
}

long	PDU::GetRequestID()
{
	return atol( mArgument[ "1.REQUEST_ID" ].GetPrintableData().c_str() );
}


int		PDU::GetError()
{
	//return mArgument[ "2.ERROR" ].GetPrintableData()[0];
	//return ( char )( atoi( mArgument[ "2.ERROR" ].GetPrintableData().c_str() ) );
	//return	mArgument[ "2.ERROR" ].GetPrintableData()[0] - 0x30;
	return	atoi( mArgument[ "2.ERROR" ].GetPrintableData().c_str() );
}


int		PDU::GetErrorIndex()
{
	return atoi( mArgument[ "3.ERROR_INDEX" ].GetPrintableData().c_str() );
}

char	PDU::GetType()
{
	return	mType;
}

void	PDU::Init()
{
	mArgument.clear();

	for( int i = 0 ; i < mVarBind.size() ; i++ )
	{
		delete	mVarBind[ i ];
	}
	mVarBind.clear();
}

void	PDU::SetEnterpriseOid( string rEnterpriseOid )
{
	mArgument[ "1.ENT_OID" ].SetData( rEnterpriseOid );
}

void	PDU::SetSenderAddr( string rSenderAddr )
{
	mArgument[ "2.SEND_ADDR" ].SetData( rSenderAddr );
}

void	PDU::SetGenericTrap( int rGenericTrap )
{
	mArgument[ "3.TRAP_TYPE" ].SetData( rGenericTrap );
}

void	PDU::SetSpecificTrap( int rSpecificTrap )
{
	mArgument[ "4.SPEC_CODE" ].SetData( rSpecificTrap );
}

void	PDU::SetTimeTicks( string rTimeTicks )
{
	mArgument[ "5.TIMESTAMP" ].SetData( rTimeTicks );
}
