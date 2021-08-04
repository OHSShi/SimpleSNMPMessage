#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include <map>

using namespace std;

typedef struct 
{
	//char*   Oid;
	//char*   Value;
	
	map< string , string >	mMapOidValue;

	char*	mCommunity;

	char*   mIp;
	char*   mPort;

	char*   mEnterpriseOid;
	char*   mSenderAddr;
	int     mGenericTrap;
	int     mSpecificTrap;
	char*   mTimeTicks;
} TrapData; 

/*
void SendTrapData( string rOid , string rValue , string rIP , string rPort , string rEnterpriseOid
					, string rSenderAddr , int rGenericTrap , int rSpecificTrap , string rTimeTicks );
*/

//int	SendAlarmTrap( ... )
int SendTrapData_V1( TrapData* rTrapData );
int SendTrapData_V2( const string& rTrapOid );
