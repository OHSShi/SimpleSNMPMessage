#include	"VB.hpp"
#include	<stdio.h>

int		main( int argc , char** argv )
{
	VB			vb;

	//vb.SetObjectID( "1.3.6.1.4.1.2680.1.2.7.3.2.0" );
	//vb.SetObjectID( "1.3.6.1.4.1.16394.2.1.1.8.0" );
	vb.SetObjectID( "1.3.6.1.4.1.128.2.1.1.8.0" );
	vb.SetValue( 100 );

	int ret = vb.Assemble();

	string 		rAssemble;
	if( ret > 0 )
	{
		rAssemble	= vb.GetAssemble();
		for( int i = 0 ; i < rAssemble.size() ; i++ )
		{
			printf( "[%02x] \n" , rAssemble[i] );
		}
	}
	
	ret = vb.Analyze( rAssemble );
	cout << "Analyzer ret == " << ret << endl;
	if( ret != 0 )
	{
		exit( -1 );
	}

	printf( "[%s] [%s]\n" , vb.GetPrintableObjectID().c_str() , vb.GetPrintableValue().c_str() );
}
