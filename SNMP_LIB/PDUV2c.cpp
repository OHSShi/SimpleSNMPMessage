#include		"PDUV2c.hpp"

PDUV2c::PDUV2c()
{
	mVarBindList.SetType ( C_SEQUENCE );
}

PDUV2c::~PDUV2c()
{ 
}

int 	PDUV2c::Assemble()
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
	else if( mType == C_GETBULKREQUEST_DATATYPE )
	{
		mArgument[ "1.REQUEST_ID" ].Assemble();
		mArgument[ "2.NON_REPEATERS" ].Assemble();
		mArgument[ "3.MAX_REPETITIONS" ].Assemble();
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

void	PDUV2c::SetType( char rType )
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
	else if( mType == C_GETBULKREQUEST_DATATYPE )
	{
		BER			rRequestID;
		BER			rNonRepeaters;
		BER			rMaxRepetitions;

    	rRequestID.SetType   	( C_INTEGER_DATATYPE );
		rNonRepeaters.SetType   ( C_INTEGER_DATATYPE );
		rMaxRepetitions.SetType ( C_INTEGER_DATATYPE );

		mArgument.insert( make_pair( "1.REQUEST_ID"			, rRequestID		) );
		mArgument.insert( make_pair( "2.NON_REPEATERS"		, rNonRepeaters		) );
		mArgument.insert( make_pair( "3.MAX_REPETITIONS"	, rMaxRepetitions	) ); 

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

void	PDUV2c::SetNonRepeaters( int rNonRepeaters )
{
	mArgument[ "2.NON_REPEATERS" ].SetData( rNonRepeaters );
}

void	PDUV2c::SetMaxRepetitions( int rNonRepeaters )
{
	mArgument[ "3.MAX_REPETITIONS" ].SetData( rNonRepeaters );
}


