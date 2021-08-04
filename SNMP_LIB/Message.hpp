#ifndef     __MESSAGE_HPP__
#define     __MESSAGE_HPP__

#include		"PDU.hpp"
#include		"SNMPMessage.hpp"

class Message : public SNMPMessage
{
	private :
		BER			mVersion;
		BER			mCommunity;

		PDU			mPDU; 

		string		mAssembleData;

		int					AnalyzeSub( const string& rData );

	protected :

	public :
		Message();
		virtual				~Message();

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

		// [ for V2
		virtual void                SetNonRepeaters( int rNonRepeaters )		{}
		virtual void                SetMaxRepetitions( int rMaxRepetitions )	{}
		// ]
};

#endif
