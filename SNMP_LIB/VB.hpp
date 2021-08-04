#ifndef		__VB_HPP__
#define		__VB_HPP__

#include		"BER.hpp"

class		VB
{
	private :
		BER				mVarBind;
		BER				mObjectID;
		BER				mValue;

		string			mAssembleData;

	protected :

	public :
		VB();
		virtual				~VB();

		int					Assemble();
		int					Analyze( const string& rData );

		string				GetPrintableObjectID();
		string				GetPrintableValue();
		string				GetPrintableTypeAndValue();
		char				GetValueDataType();

		void				SetObjectID( const string& rObjectID );
		void				SetValue( const string& rValue );
		void				SetValue( const long   rValue );

		void				SetValue( const char rDataType , const string& rValue );
		void				SetValue( const char rDataType , const long long& rValue );

		string				GetAssemble();

		long				GetLength();
		int					GetLengthOfSize();

};

#endif
