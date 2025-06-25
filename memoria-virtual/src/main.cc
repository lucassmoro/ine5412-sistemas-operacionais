#include "disk.h"
#include "program.h"
#include "page_table.h"
#include "page_replacement.h"
#include <cstring>

int main(int argc, char *argv[])
{
	if(argc != 5) {
		printf("use: virtmem <npages> <nframes> <rand|fifo|custom> <alpha|beta|gamma|delta>\n");
		return 1;
	}

	int npages = atoi(argv[1]);
	int nframes = atoi(argv[2]);
	const char *algorithm = argv[3];
	const char *program = argv[4];

	// Validação dos parâmetros
	if (npages <= 0 || nframes <= 0) {
		cout << "Error: npages and nframes must be positive integers" << endl;
		return 1;
	}
	
	if (nframes < 3) {
		cout << "Warning: Using less than 3 frames may cause infinite page faults" << endl;
	}

	// Validação do algoritmo
	if (strcmp(algorithm, "rand") != 0 && 
	    strcmp(algorithm, "fifo") != 0 && 
	    strcmp(algorithm, "custom") != 0) {
		cout << "Error: Algorithm must be rand, fifo, or custom" << endl;
		return 1;
	}

	// Validação do programa
	if (strcmp(program, "alpha") != 0 && 
	    strcmp(program, "beta") != 0 && 
	    strcmp(program, "gamma") != 0 && 
	    strcmp(program, "delta") != 0) {
		cout << "Error: Program must be alpha, beta, gamma, or delta" << endl;
		return 1;
	}

	// cout << "Virtual Memory System Starting..." << endl;
	// cout << "Pages: " << npages << ", Frames: " << nframes << endl;
	// cout << "Algorithm: " << algorithm << ", Program: " << program << endl;
	// cout << "----------------------------------------" << endl;

	// Configurar algoritmo de substituição
	Page_Replacement::set_algorithm(string(algorithm));
	Page_Replacement::reset_statistics();

	Disk disk("myvirtualdisk", npages);
    Program my_program;

    Page_Table pt(npages, nframes, Page_Replacement::page_fault_handler);
	//Page_Replacement::initialize_data_structures(&pt, algorithm);
	
	unsigned char *virtmem = (unsigned char *) pt.page_table_get_virtmem();
	
    if(!strcmp(program,"alpha")) {
		my_program.alpha(virtmem, npages * Page_Table::PAGE_SIZE);

	} else if(!strcmp(program,"beta")) {
		my_program.beta(virtmem, npages * Page_Table::PAGE_SIZE);

	} else if(!strcmp(program,"gamma")) {
		my_program.gamma(virtmem, npages * Page_Table::PAGE_SIZE);

	} else if(!strcmp(program,"delta")) {
		my_program.delta(virtmem, npages * Page_Table::PAGE_SIZE);
	}

	// cout << "----------------------------------------" << endl;
	Page_Replacement::print_statistics();

	// Limpeza
	Page_Replacement::cleanup();
    pt.page_table_delete();
	disk.close_disk();
	
	return 0;
}