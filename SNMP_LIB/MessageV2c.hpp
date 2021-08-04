#ifndef     __MESSAGE_V2C_HPP__
#define     __MESSAGE_V2C_HPP__

#include		"PDUV2c.hpp"
#include		"SNMPMessage.hpp"

class MessageV2c : public SNMPMessage
{
	private :
		BER			mVersion;
		BER			mCommunity;

		PDUV2c		mPDU; 

		string		mAssembleData;

		int					AnalyzeSub( const string& rData );

	protected :

	public :
		MessageV2c();
		virtual				~MessageV2c();

		int					Assemble();
		int					Analyze( const string& rData );
		int					Analyze( char* rData , int rSize );

		int					GetVBCount();

		void				SetCommunity( string rCommunity );

		void				SetVB		( const string& rObjectID );
		void				SetVB		( const string& rObjectID , const string& rValue );
		void				SetVB		( const string& rObjectID , long rValue );

		void				SetVB( const string& rObjectID , const char rDataType , const string& rValue );
		void				SetVB( const string& rObjectID , const char rDataType , const long long& rValue );

		void				SetPDUType		( char rType );
		void				SetRequestID	( long rRequestID );
		//void				SetError		( char rError );
		void				SetError		( int rError );
		void				SetErrorIndex	( int rErrorIndex );
		void				SetType			( char rType );

		void				SetEnterpriseOid( string rEnterpriseOid );
		void				SetSenderAddr( string rSenderAddr );
		void				SetGenericTrap( int rGenericTrap );
		void				SetSpecificTrap( int rSpecificTrap );
		void				SetTimeTicks( string rTimeTicks );

		void                SetNonRepeaters( int rNonRepeaters );
		void                SetMaxRepetitions( int rMaxRepetitions );

		int					GetVersion		();
		string				GetCommunity	();
		string				GetObjectID		( int rIndex );
		string				GetValue		( int rIndex );
		string				GetTypeAndValue	( int rIndex );
		VB*					GetVarBind		( int rIndex );

		long				GetRequestID	();
		//char				GetError		();
		int					GetError		();
		int					GetErrorIndex	();
		char				GetPDUType		();

		
		string				GetAssemble ();
		void				Init();
	
		string				GetEnterpriseOid();
		string				GetSenderAddr();
		int					GetGenericTrap();
		int					GetSpecificTrap();
		string				GetTimeTicks();
};

#endif
