#include <stdio.h>
#include <string.h>
#include "dec2bin.h"

int main()
{
	struct {
		char c;
	} C;

	typedef struct {
		unsigned m_bitPSReverseStatus  : 1;
		unsigned m_bitPSSystemStatus   : 1;
		unsigned                       : 2;
		unsigned m_bitBUCReverseStatus : 1;
		unsigned m_bitBUCSystemStatus  : 1;
		unsigned                       : 2;
	} _BUCPSM_STATUS;
	
    typedef struct {
		unsigned m_PrkSns_RearCenter   : 3;
		unsigned                       : 1;
		unsigned m_PrkSns_FrontCenter  : 3;
		unsigned                       : 1;
		
		unsigned m_PrkSns_RearRight    : 3;
		unsigned                       : 1;
		unsigned m_PrkSns_RearLeft     : 3;
		unsigned                       : 1;
		
		unsigned m_PrkSns_FrontRight   : 3;
		unsigned                       : 1;
		unsigned m_PrkSns_FrontLeft    : 3;
		unsigned                       : 1;
	} _SENSORS_STATUS;

    union {
        int i;
        _BUCPSM_STATUS s;
    } un;
	printf("sizeof(C) = %d\n", sizeof C);//1
	_BUCPSM_STATUS bstat;
	_SENSORS_STATUS sstat;
	printf("sizeof(_BUCPSM_STATUS) = %d\n", sizeof bstat);//4
	printf("sizeof(_SENSORS_STATUS) = %d\n", sizeof sstat);//4
    memset(&un, 0x00000005, sizeof(bstat));
    Dec2Bin(0x00000005);
    Dec2Bin((int)un.i);

    struct {
       _BUCPSM_STATUS a;
       _SENSORS_STATUS b;
    } __attribute__((packed)) st;
    printf("sizeof(st) = %d\n", sizeof st);
	return 0;
}

