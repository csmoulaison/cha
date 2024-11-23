#pragma once
#include <stdio.h>
#include <stdint.h>

struct {
	uint32_t max_records;
	uint32_t num_fields;
	uint32_t field_buffer_len;
} typedef ChaConfig;

struct {
	int success;
	uint32_t num_records;
} typedef ChaResult;

// Reads a file containing comma separated values, returning the number of
// records read if successful, and setting success equal to 0 if not.
//
// The out parameter is expected to be casted from a three dimensional array
// which exactly matches the values in ChaConfig.
//   (i.e. char out[max_records][num_fields][field_buffer_len])
//
// The read is unsuccessful if the number of records exceeds config.max_records,
// the number of fields does not equal config.num_fields, any field length
// exceeds config.field_buffer_len, or the file is not in the proper csv format.
ChaResult cha_read_csv(const char* filename, char* out, ChaConfig config) {
	// Used for pointer arithemtic on the out parameter
	uint32_t record_offset = config.num_fields * config.field_buffer_len;

	ChaResult res;
	res.success = 0;
	res.num_records = 0;
	
	FILE* file;
	file = fopen(filename, "r");

	if(file == NULL) {
		printf("Cha Error: File %s cannot be opened.\n", filename);
		return res;
	}

	uint32_t field_cur = 0;
	uint32_t field_len = 0;

	char c;
	while((c = fgetc(file)) != EOF) {
		if(res.num_records == config.max_records) {
			printf("Cha Error: Records in %s exceed the max.\n", filename);
			return res;
		}

		if(field_cur == config.num_fields) {
			printf("Cha Error: Fields in %s exceed the expected number at record %i.\n", filename, res.num_records + 1);
			return res;
		}

		if(c == '\n') {
			if(field_cur != config.num_fields - 1) {
				printf("Cha Error: Fields in %s fall short of the expected number at record %i.\n", filename, res.num_records + 1);
				return res;
			}
			
			res.num_records++;
			field_cur = 0;
			field_len = 0;
			continue;
		}
		
		if(c == ',') {
			field_cur++;
			field_len = 0;
			continue;
		}
		
		if(field_len >= config.field_buffer_len - 1) {
			printf("Cha Error: Field length %i in %s exceed the max at record %i.\n", field_len, filename, res.num_records + 1);
			return res;
		}

		uint32_t index = res.num_records * record_offset + field_cur * config.field_buffer_len + field_len;
		out[index] = c;
		out[index + 1] = '\0';
		field_len++;
	}

	fclose(file);

	res.success = 1;
	return res;
}
