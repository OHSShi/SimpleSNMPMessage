#include "SendTrapData.h"
#include "Message.hpp"
#include "MessageV2c.hpp"
#include "ObjectDeleter.hpp"
#include <sys/sysinfo.h>

#include	<errno.h>

/*
void SendTrapData( string rOid , string rValue , string rIP , string rPort , string rEnterpriseOid 
					, string rSenderAddr , int rGenericTrap , int rSpecificTrap , string rTimeTicks )
*/

#define LOGDEBUG( format , args... ) printf( "[%s:%s:%d] "format"\n" , __FILE__ , __func__ , __LINE__ , ##args )

int	SendTrapData_V1( TrapData* rpTrapData )
{
	int sock;
	int server_addr_size;

	struct sockaddr_in server_addr;


	SNMPMessage *rpSnmp = 0;
	
	rpSnmp = new Message;

	ObjectDeleter< SNMPMessage* >	od( rpSnmp );
	
	rpSnmp->SetCommunity		( rpTrapData->mCommunity );
	rpSnmp->SetPDUType			( C_TRAPPDU_DATATYPE );

	rpSnmp->SetEnterpriseOid	( rpTrapData->mEnterpriseOid );
	rpSnmp->SetSenderAddr		( rpTrapData->mSenderAddr );
	rpSnmp->SetGenericTrap		( rpTrapData->mGenericTrap );
	rpSnmp->SetSpecificTrap		( rpTrapData->mSpecificTrap );
	rpSnmp->SetTimeTicks		( rpTrapData->mTimeTicks );
	
	for( map< string , string >::iterator rMapIter = rpTrapData->mMapOidValue.begin() ;
		 rMapIter != rpTrapData->mMapOidValue.end() ; rMapIter++ )
	{
		string	rOid	= rMapIter->first;
		string	rValue	= rMapIter->second;

		rpSnmp->SetVB( rOid , rValue );
	}

	int ret = rpSnmp -> Assemble();
	string rAssemble = rpSnmp -> GetAssemble();
	if( ret <= 0 )
	{
		LOGDEBUG( "Message Assemble Error. ret(%d)" , ret );
		return	-1;
	}

	sock = socket( PF_INET , SOCK_DGRAM , 0 );
	if( sock < 0 )
	{
		LOGDEBUG( "Socket Creation Fail. errno(%d)" , errno );
		return	-1;
	}
	memset( &server_addr , 0 , sizeof( server_addr ) );
	server_addr.sin_family          = AF_INET;
	server_addr.sin_port            = htons( atoi( rpTrapData->mPort ) );
	server_addr.sin_addr.s_addr     = inet_addr( rpTrapData->mIp );

	sendto( sock , rAssemble.c_str() , rAssemble.size() , 0 , ( struct sockaddr* )&server_addr , sizeof( server_addr ) );

	return	0;
};

int SendTrapData_V2( const string& rTrapOid )
{
	int	ret;
    int sock;
    int server_addr_size;

    struct sockaddr_in server_addr;

    SNMPMessage*    rpSnmp  = 0;
    rpSnmp  = new MessageV2c;

    ObjectDeleter< SNMPMessage* >   od( rpSnmp );

    rpSnmp->SetCommunity( "public" );
    rpSnmp->SetPDUType( C_TRAP2PDU_DATATYPE );
    rpSnmp->SetRequestID( 123456 );
    rpSnmp->SetError( 0x00 );
    rpSnmp->SetErrorIndex( 0 );


	struct sysinfo  rSysInfo;
	unsigned long rUpTime  = 0;
	ret = sysinfo( &rSysInfo );
	if( ret == 0 )
	{
		rUpTime = rSysInfo.uptime;
	}

    rpSnmp->SetVB( "1.3.6.1.2.1.1.3.0" , C_TIMETICKS_DATATYPE , rUpTime );			// sysUptimeInstance
    rpSnmp->SetVB( "1.3.6.1.6.3.1.1.4.1" , C_OBJECTID_DATATYPE , rTrapOid );	// snmpTrapOID

    ret = rpSnmp -> Assemble();
    string rAssemble = rpSnmp -> GetAssemble();
    if( ret <= 0 )
    {
        LOGDEBUG( "Message Assemble Error. ret(%d)" , ret );
        return  -1;
    }

    sock = socket( PF_INET , SOCK_DGRAM , 0 );
    if( sock < 0 )
    {
        LOGDEBUG( "Socket Creation Fail. errno(%d)" , errno );
        return  -1;
    }
    memset( &server_addr , 0 , sizeof( server_addr ) );
    server_addr.sin_family          = AF_INET;
    server_addr.sin_port            = htons( 9999 );
    server_addr.sin_addr.s_addr     = inet_addr( "70.11.238.52" );

    sendto( sock , rAssemble.c_str() , rAssemble.size() , 0 , ( struct sockaddr* )&server_addr , sizeof( server_addr ) );

}
