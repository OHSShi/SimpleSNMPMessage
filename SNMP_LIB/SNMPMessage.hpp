#ifndef     __SNMPMESSAGE_HPP__
#define     __SNMPMESSAGE_HPP__

#include	"SNMPConst.hpp"
#include	"VB.hpp"

class SNMPMessage
{
	private :
		string						mPeerIp;

	protected:

	public :
		SNMPMessage();
		virtual						~SNMPMessage();

		virtual int					Assemble() 				= 0;
		virtual int					Analyze( const string& rData )		= 0;
		virtual int					Analyze( char* rData , int rsize )	= 0;

		virtual int					GetVBCount() 						= 0;

		virtual void				SetCommunity( string rCommunity )	= 0;

		virtual void				SetVB( const string& rObjectID ) 						= 0;
		virtual void				SetVB( const string& rObjectID , const string& rValue )	= 0;
		virtual void				SetVB( const string& rObjectID , long rValue ) 		= 0;

		virtual void                SetVB( const string& rObjectID , const char rDataType , const string& rValue )			= 0;
		virtual void                SetVB( const string& rObjectID , const char rDataType , const long long& rValue )		= 0;

		virtual string				GetObjectID( int rIndex )		= 0;
		virtual string				GetValue( int rIndex )			= 0;
		virtual string				GetTypeAndValue( int rIndex )	= 0;
		virtual VB*					GetVarBind( int rIndex )		= 0;

//////////////////
		virtual string				GetAssemble() = 0;

		virtual void				SetPDUType		( char rType )		= 0;
		virtual void				SetRequestID	( long rRequestID )	= 0;
		//virtual void				SetError		( char rError ) 	= 0;
		virtual void				SetError		( int rError ) 	= 0;
		virtual void				SetErrorIndex	( int rErrorIndex )	= 0;

		virtual void				SetEnterpriseOid( string rEnterpriseOid ) = 0;
		virtual void				SetSenderAddr( string rSenderAddr ) = 0;
		virtual void				SetGenericTrap( int rGenericTrap ) = 0;
		virtual void				SetSpecificTrap( int rSpecificTrap ) = 0;
		virtual void				SetTimeTicks( string rTimeTicks ) = 0;

		// [ for V2, V3
		virtual void				SetNonRepeaters( int rNonRepeaters )		= 0;
		virtual void				SetMaxRepetitions( int rMaxRepetitions )	= 0;
		// ]

		virtual int					GetVersion()	= 0;
		virtual string				GetCommunity()	= 0;
		virtual long				GetRequestID()	= 0;
		//virtual char				GetError()		= 0;
		virtual int					GetError()		= 0;
		virtual int					GetErrorIndex()	= 0;
		virtual char				GetPDUType()	= 0;
		virtual void				Init()			= 0;

		virtual string				GetEnterpriseOid() = 0;
		virtual string				GetSenderAddr() = 0;
		virtual int					GetGenericTrap() = 0;
		virtual int					GetSpecificTrap() = 0;
		virtual string				GetTimeTicks() = 0;

		static int					GetSnmpMsgVersion( const string& rSnmpMsg );
		static int					GetSnmpMsgVersion( char* rSnmpMsg , int rSize );
		static int					CompareOid( const string& rOid1 , const string& rOid2 );

		void						SetPeerIp( const string& rPeerIp );
		string						GetPeerIp();

		// ERROR 관련 작업 예정

};

#endif
