#ifndef			__PDU_V2C_HPP__
#define			__PDU_V2C_HPP__

#include		"PDU.hpp"

class PDUV2c : public PDU
{
	private :
	
	protected :

	public :
		PDUV2c();
		virtual			~PDUV2c();

		int             Assemble();
		void            SetType         ( char rType );

		void            SetNonRepeaters( int rNonRepeaters );
		void            SetMaxRepetitions( int rNonRepeaters );

};

#endif
