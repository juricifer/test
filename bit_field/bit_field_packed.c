#include <stdio.h>
#include <string.h>

typedef struct _command_data {
	struct {
		unsigned m_bitPSReverseStatus  : 1;
		unsigned m_bitPSSystemStatus   : 1;
		unsigned                       : 2;
		unsigned m_bitBUCReverseStatus : 1;
		unsigned m_bitBUCSystemStatus  : 1;
		unsigned                       : 2;
	} __attribute__((packed)) _BUCPSM_STATUS;
	
	struct {
		unsigned m_PrkSns_RearCenter   : 3;
		unsigned                       : 1;
		unsigned m_PrkSns_FrontCenter  : 3;
		unsigned                       : 1;
		
		unsigned m_PrkSns_RearRight    : 3;
		unsigned                       : 1;
		unsigned m_PrkSns_RearLeft     : 3;
		unsigned                       : 1;
		
		unsigned m_PrkSns_FrontRight   : 2;
		unsigned                       : 2;
		unsigned m_PrkSns_FrontLeft    : 3;
		unsigned                       : 1;
	} __attribute__((packed)) _SENSORS_STATUS;
	
} __attribute__((packed)) _CMD_DATA;

typedef union _U {
	int c;
    _CMD_DATA cmd;
} _UN;

void Dec2Bin(int n)
{
	int i = 0;
	for (; i<32; i++)
	{
		printf("%c", n<0 ? '1' : '0');
		if (0 == (i+1)%4) printf(" ");
		n = n<<1;
	}
	printf("\n");
}

int main()
{
//	_CMD_DATA cmd;
	_UN u;
	printf("sizeof(cmd) = %d\n", sizeof(u.cmd));
//	memcpy(&cmd, msg_buffer, sizeof(int));
//	1000 1100 0000 0000 0000 0010 1110 1110
//	1111 1111 1111 1111 1111 1111 1111 0001
//	memset(&u.cmd, 0x00000001, sizeof(u.cmd));
	u.c = 0x9c1012ee;
	printf("c = %d\n", u.c);

//	0x8c0002ee: expect result: 1 0 1 1 0 0 0 1 7 7
	printf("params\n==========================\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n" \
		, u.cmd._BUCPSM_STATUS.m_bitPSReverseStatus \
		, u.cmd._BUCPSM_STATUS.m_bitPSSystemStatus \
		, u.cmd._BUCPSM_STATUS.m_bitBUCReverseStatus \
		, u.cmd._BUCPSM_STATUS.m_bitBUCSystemStatus \
		, u.cmd._SENSORS_STATUS.m_PrkSns_RearCenter \
		, u.cmd._SENSORS_STATUS.m_PrkSns_FrontCenter \
		, u.cmd._SENSORS_STATUS.m_PrkSns_RearRight \
		, u.cmd._SENSORS_STATUS.m_PrkSns_RearLeft \
		, u.cmd._SENSORS_STATUS.m_PrkSns_FrontRight \
		, u.cmd._SENSORS_STATUS.m_PrkSns_FrontLeft);

	printf("11111 = %x,    %x\n", u.cmd._BUCPSM_STATUS, u.cmd._SENSORS_STATUS);
	unsigned char* pchar = (unsigned char*)&u.c;
	printf("[0] = %x, [1] = %x, [2] = %x, [3] = %x\n", pchar[0], pchar[1], pchar[2], pchar[3]);

	pchar = (unsigned char*)&u.cmd;
	printf("[0] = %x, [1] = %x, [2] = %x, [3] = %x\n", pchar[0], pchar[1], pchar[2], pchar[3]);

	void* pDist = &u.cmd._BUCPSM_STATUS;
	void* pDist2 = &u.cmd._SENSORS_STATUS;
	printf("pDist = %x, pDist2 = %x\n", pDist, pDist2);

	//Dec2Bin(2);
/*
	int x = 2;
	char str[33] = {0};
	itoa(x, str, 2);
	printf("x = %d, str = %s\n", x, str);
*/
	//Dec2Bin(u.c);
	return 0;
}
