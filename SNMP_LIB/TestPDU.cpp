#include	"PDU.hpp"
#include	<stdio.h>

int		main( int argc , char** argv )
{
	PDU		pdu;

#if 0
	pdu.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.0" , "ABC" );
	pdu.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.1" , "test" );
#endif

	
#if 1
	pdu.SetType( C_GETRESPONSEPDU_DATATYPE );
	
	pdu.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.0" );
	pdu.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.0" );
	pdu.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.0" );
	pdu.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.0" );
	pdu.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.0" );
#endif
	



	pdu.SetRequestID	( 1 );
	pdu.SetError		( 1000 );
	pdu.SetErrorIndex	( 0 );

	int ret = pdu.Assemble();

	string		rAssemble = pdu.GetAssemble();
	if( ret > 0 )
	{
		for( int i = 0 ; i < rAssemble.size() ; i++ )
		{
			printf( "[%02x] \n" , rAssemble[i] );
		}
	}


	ret = pdu.Analyze( rAssemble );
	if( ret != 0 )
	{
		printf( "Analyze Error\n" );
		exit( -1 );
	}

	for( int i = 0 ; i < pdu.GetVBCount() ; i++ )
	{
	    cout << "Object ID  = " << pdu.GetObjectID(i)   << endl;
		cout << "Value      = " << pdu.GetValue(i) 		 << endl;
	}

	cout << "Object ID	= " << pdu.GetObjectID(0) 	<< endl;
	cout << "Object ID	= " << pdu.GetObjectID(1) 	<< endl;

	cout << "Value		= " << pdu.GetValue(0) 	<< endl;
	cout << "Value		= " << pdu.GetValue(1) 	<< endl;

	cout << "Request ID	= " << pdu.GetRequestID() 	<< endl;
	cout << "Error		= " << pdu.GetError() 		<< endl;
	cout << "ErrorIndex	= " << pdu.GetErrorIndex() 	<< endl;

}
