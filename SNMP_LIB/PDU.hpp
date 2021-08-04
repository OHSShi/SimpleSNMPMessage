#ifndef			__PDU_HPP__
#define			__PDU_HPP__

#include		"BER.hpp"
#include		"VB.hpp"

class PDU
{
	private :

	protected :
		map< string , BER >		mArgument;

		BER						mVarBindList;
		vector< VB* >			mVarBind;

		string					mAssembleData; 
		char					mType;

	public :
		PDU();
		virtual			~PDU();

		int				Assemble();
		int				Analyze( const string& rData );

		int				GetVBCount();

		void			SetVB		( const string& rObjectID );
		void			SetVB		( const string& rObjectID , const string& rValue );
		void			SetVB		( const string& rObjectID , long rValue );

		void			SetVB( const string& rObjectID , const char rDataType , const string& rValue );
		void			SetVB( const string& rObjectID , const char rDataType , const long long& rValue );

		void			SetRequestID	( long rRequestID );
		//void			SetError		( char rError );
		void			SetError		( int rError );
		void			SetErrorIndex	( int rErrorIndex );
		void			SetType			( char rType );

		void			SetEnterpriseOid( string rEnterpriseOid );
		void			SetSenderAddr( string rSenderAddr );
		void			SetGenericTrap( int rGenericTrap );
		void			SetSpecificTrap( int rSpecificTrap );
		void			SetTimeTicks( string rTimeTicks );

		string			GetObjectID	( int rIndex );
		string			GetValue	( int rIndex );
		string			GetTypeAndValue( int rIndex );
		VB*				GetVarBind  ( int rIndex );

		long			GetRequestID	();
		//char			GetError		();
		int				GetError		();
		int				GetErrorIndex	();
		char			GetType			();


		string			GetAssemble(); 

		void			Init();

		string			GetEnterpriseOid();
		string			GetSenderAddr();
		int				GetGenericTrap();
		int				GetSpecificTrap();
		string			GetTimeTicks();
};

#endif
