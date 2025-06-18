#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

#include "page_table.h"
#include "disk.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <random>

using namespace std;

class Page_Replacement
{
public:
    /*
     * This is the method called when a page fault occurs. Your work begins here!
     */
    static void page_fault_handler(Page_Table *pt, int page);
    
    /*
     * Set the page replacement algorithm to use
     */
    static void set_algorithm(const std::string& algorithm);
    
    /*
     * Print execution statistics
     */
    static void print_statistics();
    
    /*
     * Reset statistics counters
     */
    static void reset_statistics();
    
    /*
     * Cleanup resources
     */
    static void cleanup();

    // ADICIONADO
    static void initialize_data_structures(Page_Table *pt, const std::string& algorithm);
    static int find_free_frame();
    static int random_replacement(int nframes);
    static int fifo_replacement();
    static int custom_replacement();
    static int choose_frame_for_replacement(int nframes);
    static void load_page_from_disk(int page, int frame);
    static void save_page_to_disk(int page, int frame);
private: 
    static std::vector<bool> frame_table;           // Tabela de frames livres/ocupados
    static std::vector<int> frame_to_page;          // Mapeia frame para página
    static std::queue<int> fifo_queue;              // Fila FIFO para substituição
    static std::string current_algorithm;           // Algoritmo atual
    static Disk* disk_ptr;            // Ponteiro para o disco
    static bool initialized;                // Flag de inicialização
    static int page_faults;
    static int disk_reads;
    static int disk_writes;
    static bool eh_fifo;
    static deque<int> custom_deque;
};

#endif