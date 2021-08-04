#ifndef		__SNMPCONST_HPP__
#define		__SNMPCONST_HPP__

#include		<string>
#include		<vector>
#include		<map>
#include		<list>
#include		<iostream>
#include		<iterator>
#include		<algorithm>
#include		<stdio.h>
#include		<string.h>

using namespace			std;

#define	GET_DATATYPE_STR( x )	( x == C_INTEGER_DATATYPE ? "Integer" : \
								  x == C_OCTET_DATATYPE ? "Octet" : \
								  x == C_NULL_DATATYPE ? "Null" : \
								  x == C_OBJECTID_DATATYPE ? "ObjectId" : \
								  x == C_COUNTER_DATATYPE ? "Counter32" : \
								  x == C_NETADDR_DATATYPE ? "Address" : \
								  x == C_TIMETICKS_DATATYPE ? "Timeticks" : \
								  x == C_COUNTER64_DATATYPE ? "Counter64" : \
								  x == C_NOSUCHOBJECT ? "NoSuchObject" : \
								  x == C_NOSUCHINSTANCE ? "NoSuchInstance" : \
								  x == C_ENDOFMIBVIEW ? "EndOfMibView" : "Unknown" )

#define	GET_SNMP_VERSION_STR( x ) ( x == C_SNMP_V1 ? "version-1" : \
									x == C_SNMP_V2C ? "version-v2c" : \
									x == C_SNMP_V3 ? "version-3" : "Unknown" )

#define GET_SNMP_ERROR_STR( x )	( x == C_ERROR_NO ? "ERROR_NO" : \
								  x == C_ERROR_MESSAGE_TO_LARGE ? "ERROR_MESSAGE_TO_LARGE" : \
								  x == C_ERROR_OBJECT_NOT_FOUND ? "ERROR_OBJECT_NOT_FOUND" : \
								  x == C_ERROR_DATA_TYPE_NOT_MATCH ? "ERROR_DATA_TYPE_NOT_MATCH" : \
								  x == C_ERROR_READ_ONLY_PARAM_SET ? "ERROR_READ_ONLY_PARAM_SET" : \
								  x == C_ERROR_GENERAL ? "ERROR_GENERAL" :  \
								  x == C_ERROR_NOACCESS ? "ERROR_NOACCESS" : \
								  x == C_ERROR_WRONGTYPE ? "ERROR_WRONGTYPE" : \
								  x == C_ERROR_WRONGLENGTH ? "ERROR_WRONGLENGTH" : \
								  x == C_ERROR_WRONGENCODING ? "ERROR_WRONGENCODING" : \
								  x == C_ERROR_WRONGVALUE ? "ERROR_WRONGVALUE" : \
								  x == C_ERROR_NOCREATION ? "ERROR_NOCREATION" : \
								  x == C_ERROR_INCONSISTENTVALUE ? "ERROR_INCONSISTENTVALUE" : \
								  x == C_ERROR_RESOURCEUNVALIABLE ? "ERROR_RESOURCEUNVALIABLE" : \
								  x == C_ERROR_COMMITFAILED ? "ERROR_COMMITFAILED" : \
								  x == C_ERROR_UNDOFAILED ? "ERROR_UNDOFAILED" : \
								  x == C_ERROR_AUTHORIZATIONERROR ? "ERROR_AUTHORIZATIONERROR" : \
								  x == C_ERROR_NOTWRITABLE ? "ERROR_NOTWRITABLE" : \
								  x == C_ERROR_INCONSISTENTNAME ? "ERROR_INCONSISTENTNAME" : "Unknown" )

#define GET_SNMP_EXCEPTION_STR( x ) (	x == C_NOSUCHOBJECT ? "NOSUCHOBJECT" : \
										x == C_NOSUCHINSTANCE ? "NOSUCHINSTANCE" : \
										x == C_ENDOFMIBVIEW ? "ENDOFMIBVIEW" : "Unknown" )

const char		C_INTEGER_DATATYPE				= 0x02;
const char		C_OCTET_DATATYPE				= 0x04;
const char		C_NULL_DATATYPE					= 0x05;
const char		C_OBJECTID_DATATYPE				= 0x06;
const char		C_COUNTER_DATATYPE				= 0x41;
const char		C_NETADDR_DATATYPE				= 0x40;
const char		C_TIMETICKS_DATATYPE			= 0x43;

const char		C_GAUGE_DATATYPE				= 0x42;
const char		C_UNSIGNED_DATATYPE				= 0x42;

const char		C_COUNTER64_DATATYPE			= 0x46;

const char		C_SEQUENCE						= 0x30;
const char		C_GETREQUESTPDU_DATATYPE		= 0xA0;
const char		C_GETNEXTREQUESTPDU_DATATYPE	= 0xA1;
const char		C_GETRESPONSEPDU_DATATYPE		= 0xA2;
const char		C_SETREQUESTPDU_DATATYPE		= 0xA3;
const char		C_TRAPPDU_DATATYPE				= 0xA4;
const char		C_GETBULKREQUEST_DATATYPE		= 0xA5;
//const char	C_INFORM_DATATYPE				= 0xA6;
const char		C_TRAP2PDU_DATATYPE				= 0xA7;

const char		C_SNMP_V1						= 0x00;
const char		C_SNMP_V2C						= 0x01;
const char		C_SNMP_V3						= 0x03;


// Error code in SNMPv1, SNMPsec, SNMPv2p, SNMPv2c, SNMPv2u, SNMPv2*, and SNMPv3 PDUs 
const char		C_ERROR_NO						= 0x00;
const char		C_ERROR_MESSAGE_TO_LARGE		= 0x01;
const char		C_ERROR_OBJECT_NOT_FOUND		= 0x02;
const char		C_ERROR_DATA_TYPE_NOT_MATCH		= 0x03;
const char		C_ERROR_READ_ONLY_PARAM_SET		= 0x04;
const char		C_ERROR_GENERAL					= 0x05;

// Error code in SNMPv2p, SNMPv2c, SNMPv2u, SNMPv2*, and SNMPv3 PDUs 
const char		C_ERROR_NOACCESS				= 0x06;
const char		C_ERROR_WRONGTYPE				= 0x07;
const char		C_ERROR_WRONGLENGTH				= 0x08;
const char		C_ERROR_WRONGENCODING			= 0x09;
const char		C_ERROR_WRONGVALUE				= 0x0A;
const char		C_ERROR_NOCREATION				= 0x0B;
const char		C_ERROR_INCONSISTENTVALUE		= 0x0C;
const char		C_ERROR_RESOURCEUNVALIABLE		= 0x0D;
const char		C_ERROR_COMMITFAILED			= 0x0E;
const char		C_ERROR_UNDOFAILED				= 0x0F;
const char		C_ERROR_AUTHORIZATIONERROR		= 0x10;
const char		C_ERROR_NOTWRITABLE				= 0x11;

// Error code in SNMPv2c, SNMPv2u, SNMPv2*, and SNMPv3 PDUs 
const char		C_ERROR_INCONSISTENTNAME		= 0x12;

// Exception values for SNMPv2p, SNMPv2c, SNMPv2u, SNMPv2*, and SNMPv3 
const char		C_NOSUCHOBJECT					= 0x80;
const char		C_NOSUCHINSTANCE				= 0x81;
const char		C_ENDOFMIBVIEW					= 0x82;

// generic-trap filed in trap PDUs
#define SNMP_TRAP_COLDSTART     (0)
#define SNMP_TRAP_WARMSTART     (1)
#define SNMP_TRAP_LINKDOWN      (2)
#define SNMP_TRAP_LINKUP        (3)
#define SNMP_TRAP_AUTHFAIL      (4)
#define SNMP_TRAP_EGPNEIGHBORLOSS   (5)
#define SNMP_TRAP_ENTERPRISESPECIFIC    (6)

#endif
