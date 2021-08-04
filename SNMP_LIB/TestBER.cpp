#include	"BER.hpp"
#include	<stdio.h>

int		main( int argc , char** argv )
{
	BER			ber;

#if 0
	ber.SetType( atoi( argv[1] ) );
	ber.SetData( argv[2] );

	int ret = ber.Assemble();

	string 		rAssemble;
	if( ret > 0 )
	{
		rAssemble	= ber.GetAssemble();
		for( int i = 0 ; i < rAssemble.size() ; i++ )
		{
			printf( "[%02x] \n" , rAssemble[i] );
		}
	}

	BER			ber1;
	ret = ber1.Analyze( rAssemble );
	cout << "Analyzer ret == " << ret << endl;
	if( ret != 0 )
	{
		exit( -1 );
	}

	printf( "[%02x] , [%ld] , [%s]\n" ,  ber1.GetDataType() , ber1.GetLength() , ber1.GetPrintableData().c_str() );
#endif

	string	rStr	=  ber.ConvNumberToString( "16394" );


	for( int i = 0 ; i < rStr.size() ; i++ )
	{
		printf( "%02x " , rStr[ i ] );
	}
	cout << endl;

}
