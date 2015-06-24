/*

PRUTOOL

- Halt PRU
- Start PRU
- Load into PRU IRAM or DRAM

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>

#define RAM_SIZE 0x2000

#define PRU0_DRAM_BASE 0x4a300000
#define PRU1_DRAM_BASE 0x4a302000

#define PRU0_IRAM_BASE 0x4a334000
#define PRU1_IRAM_BASE 0x4a338000

#define PRU0_CTRL_BASE 0x4a322000
#define PRU1_CTRL_BASE 0x4a324000

void PrintUsage()
{
	printf("usage: prutool l prunumber iramfile dramfile\n");
	printf("       prutool i prunumber iramfile\n");
	printf("       prutool d prunumber dramfile\n");
	printf("       prutool h prunumber\n");
	printf("       prutool s prunumber\n");
}

void LoadMem(size_t length, off_t offset, void* source, size_t sourcelength)
{
	uint32_t mem_fd;
	void *ram;

	mem_fd = open("/dev/mem", O_RDWR|O_SYNC);
	ram = mmap(0, length, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, offset);
	close(mem_fd);

	memcpy(ram, source, sourcelength);

	munmap(0, length);
}

void LoadFileToRAM(off_t offset, char* filename)
{
	size_t length;
	char buffer[RAM_SIZE];
        FILE *file = fopen(filename, "rb");

        if(file == 0)
        {
                printf("Could not open file %s\n", filename);
                exit(0);
        }
        else
        {
		fseek(file, 0, SEEK_END);
		length = ftell(file);
		if(length > RAM_SIZE)
		{
			printf("Filesize %d, allowed size %d\n", length, RAM_SIZE);
			exit(1);
		}
		fseek(file, 0, SEEK_SET);
		fread(buffer, length, 1, file);
		printf("Read %d bytes form %s\n", length, filename);
		fclose(file);
		LoadMem(RAM_SIZE, offset, buffer, length);
		printf("%d bytes loaded to 0x%x\n", length, (uint32_t)offset);
        }
}

int main(int argc, char *argv[])
{
	uint8_t pru;

	if(argc < 3)
	{
		PrintUsage();
		exit(1);
	}

	switch(argv[2][0])
	{
		case '0':
			pru = 0;
		break;

		case '1':
			pru = 1;
		break;

		default:
			PrintUsage();
			exit(1);
		break;
	}

	switch(argv[1][0])
	{
		case 'l':
			if(argc != 5)
			{
				PrintUsage();
				exit(1);
			}

			if(pru == 0)
			{
				LoadFileToRAM(PRU0_IRAM_BASE, argv[3]);
				LoadFileToRAM(PRU0_DRAM_BASE, argv[4]);
			}
			else
			{
				LoadFileToRAM(PRU1_IRAM_BASE, argv[3]);
				LoadFileToRAM(PRU1_DRAM_BASE, argv[4]);
			}
		break;

		case 'i':
			if(argc != 4)
			{
				PrintUsage();
				exit(1);
			}

                        if(pru == 0)
                        {
                                LoadFileToRAM(PRU0_IRAM_BASE, argv[3]);
                        }
                        else
                        {
                                LoadFileToRAM(PRU1_IRAM_BASE, argv[3]);
                        }
		break;

		case 'd':
			if(argc != 4)
			{
				PrintUsage();
				exit(1);
			}

                        if(pru == 0)
                        {
                                LoadFileToRAM(PRU0_DRAM_BASE, argv[3]);
                        }
                        else
                        {
                                LoadFileToRAM(PRU1_DRAM_BASE, argv[3]);
                        }
		break;

		case 'h':
			if(argc != 3)
			{
				PrintUsage();
				exit(1);
			}

			char hcommand = 0x0;

                        if(pru == 0)
                        {
				LoadMem(RAM_SIZE, PRU0_CTRL_BASE, &hcommand, 1);
                        }
                        else
                        {
				LoadMem(RAM_SIZE, PRU1_CTRL_BASE, &hcommand, 1);
                        }

			printf("Halt PRU %d\n", pru);
		break;

		case 's':
			if(argc != 3)
			{
				PrintUsage();
				exit(1);
			}

                        char scommand = 0x3;

                        if(pru == 0)
                        {
                                LoadMem(RAM_SIZE, PRU0_CTRL_BASE, &scommand, 1);
                        }
                        else
                        {
                                LoadMem(RAM_SIZE, PRU1_CTRL_BASE, &scommand, 1);
                        }

			printf("Start PRU %d\n", pru);
		break;

		default:
			PrintUsage();
			exit(1);
		break;
	}

	return 0;
}

