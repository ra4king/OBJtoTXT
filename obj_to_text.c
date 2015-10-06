#include <stdio.h>

void parse_obj(FILE* in, FILE* out) {
	char buffer[512];

	while(!feof(in)) {
		int header_num_read = fread(buffer, 1, 4, in);
		if(header_num_read != 4)
			break;
		
		int startAddress = (buffer[0] << 8) | buffer[1];

		int count = ((buffer[2] << 8) | buffer[3]) * 2;

		fprintf(out, ".orig %04X\n", startAddress);
		fprintf(out, "length: %d\n", count);

		while(count && !feof(in)) {
			int to_read = sizeof(buffer) < count ? sizeof(buffer) : count;
			int num_read = fread(buffer, 1, to_read, in);
			count -= num_read;

			for(int i = 0; i < num_read; i += 2) {
				fprintf(out, "%04X\t", ((buffer[i] << 8) | buffer[i+1]) & 0xFFFF);
				if((i+2) % 10 == 0)
					fprintf(out, "\n");
			}
		}
		
		fprintf(out, "\n");
	}
}

int main(int argc, char** argv) {
	if(argc != 3) {
		printf("Usage: obj_to_ext input.obj output\n");
		return 0;
	}
	
	FILE* in = fopen(argv[1], "r");
	if(!in) {
		printf("input file not found.\n");
		return -1;
	}

	FILE* out = fopen(argv[2], "w");
	if(!out) {
		printf("output file could not be created.\n");
		return -1;
	}
	
	parse_obj(in, out);
	
	fclose(in);
	fclose(out);	

	return 0;
}

