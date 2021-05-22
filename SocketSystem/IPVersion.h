#ifndef IPTypeIncluded
#define IPTypeIncluded

typedef enum IPVersion
{
    IPVersionInvalid,

    IPVersion4,
    IPVersion6

}IPVersion;

IPVersion AnalyseIPVersion(char* ip);
char IsValidIP(char* ipAdress);
char IsValidIPv4(char* ipv4Adress);
char IsValidIPv6(char* ipv6Adress);

#endif