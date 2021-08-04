#ifndef		__BER_HPP__
#define		__BER_HPP__

#include		"SNMPConst.hpp"
#include		"math.h"

class BER
{
	private :
		char			mType;
		unsigned long	mLength;
		string			mData;

		int				mLengthOfSize;

		string			mReadableData;
		string			mAssembleData;

	protected :

	public :
		BER();
		virtual				~BER();

		virtual int			Assemble();
		virtual int			Analyze( const string& rData );
		virtual int			Analyze( char* rData , int rSize );
		virtual int			Analyze();

		virtual string		GetPrintableData();
		virtual string		GetPrintableTypeAndData();
		virtual void		SetData( string rData );
		virtual void		SetData( long long rData );
		virtual void		SetType( char rType );

		char				GetDataType();
		virtual long		GetLength();
		virtual	string		GetAssemble();

		static string 				ConvOIDToString( int rValue );
		static string 				ConvOIDToString( string rValue );

		string				ConvNetAddr( string rData );
		string 				ConvNumberToString( long long rValue );
		string 				ConvNumberToString( string rValue );

		string				ConvLengthToString( long rValue );

		void				Print();
		void				PrintValueHex();
		void				Print( string rData );
		long long			ConvHexToNumber( string rData );
		static long long	ConvHexToLength( string rData );

		int				 	GetLengthOfSize();

		static string		ConvOIDToHex( const string& rOid );
};

#endif
