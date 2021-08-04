#include	"Message.hpp"
#include	<stdio.h>

int		main( int argc , char** argv )
{
	Message		message;

	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.0" , "ABCD" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.1" , "efg" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );
	message.SetVB( "1.3.6.1.4.1.2680.1.2.7.3.2.2" , "xxx" );

	message.SetCommunity	( "private" );
	message.SetPDUType		( C_GETREQUESTPDU_DATATYPE );
	message.SetRequestID	( 1 );
	message.SetError		( 0x00 );
	message.SetErrorIndex	( 0 );
	

	int ret = message.Assemble();

	string		rAssemble = message.GetAssemble();
	

	if( ret > 0 )
	{
		for( int i = 0; i < rAssemble.size() ; i++)
		{
			printf( "[%02x] \n" , rAssemble[i] );
		}
	}

	ret = message.Analyze( rAssemble );
	if( ret != 0 )
	{
		printf( "Analyze Error\n" );
		exit( -1 );
	}

	cout << "Version		= " << message.GetVersion()		<< endl;
	cout << "Community	= " << message.GetCommunity()	<< endl;
	cout << "RequestID	= " << message.GetRequestID()	<< endl;
	cout << "Error		= " << message.GetError()		<< endl;
	cout << "ErrorIndex	= " << message.GetErrorIndex()	<< endl;

	for( int i = 0 ; i <  message.GetVBCount() ; i++ )
	{
		cout << endl << "-----(" << i << ")-----" << endl;
		cout << "Object ID	= " << message.GetObjectID( i )		<< endl;
		cout << "Value		= " << message.GetValue( i )		<< endl;
	}
}

