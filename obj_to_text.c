#include <stdio.h>

void parse_obj(FILE* in, FILE* out) {
	char buffer[512];

	while(!feof(in)) {
		int b1 = fgetc(in);
		int b2 = fgetc(in);
		int startAddress = (b1 << 8) | b2;

		int c1 = fgetc(in);
		int c2 = fgetc(in);
		int count = ((c1 << 8) | c2) * 2;

		fprintf(out, ".orig %04X\n", startAddress);
		fprintf(out, "length: %d\n", count);

		while(count && !feof(in)) {
			int num_read = fread(buffer, 1, sizeof(buffer), in);
			count -= num_read;

			for(int i = 0; i < num_read - 1; i += 2) {
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

