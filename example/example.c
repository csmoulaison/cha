#include "../cha.h"

#define FILENAME "example.csv"
#define MAX_RECORDS 32
#define NUM_FIELDS 3
#define FIELD_BUFFER_LEN 128

int main(int argc, char** argv) {
	ChaConfig config;
	config.max_records = MAX_RECORDS;
	config.num_fields = NUM_FIELDS;
	config.field_buffer_len = FIELD_BUFFER_LEN;

	char csv[MAX_RECORDS][NUM_FIELDS][FIELD_BUFFER_LEN];

	ChaResult result = cha_read_csv(FILENAME, (char*)csv, config);
	if(result.success == 0) {
		printf("Aborting...\n");
		return 1;
	}

	printf("Printing records...\n");
	for(int record = 0; record < result.num_records; record++) {
		printf("%i |", record);
		for(int field = 0; field < config.num_fields; field++) {
			printf(" %s |", csv[record][field]);
		}
		printf("\n");
	}

	printf("Records printed!\n");
	return 0;
}
