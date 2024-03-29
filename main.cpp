#include <iostream>
#include <string>

#include "classes.hpp"

niatec_logs::Log_Manager log_manager;

int main(){

    std::string log_file = log_manager.create_log_file();

    std::cout << "Filename: " << log_file << "\n";

    log_manager.log_writer(log_file, "Teste de escrita no arquivo de log.");
    log_manager.log_writer(log_file, "Teste de escrita com tipo de log.", "WARNING");
    log_manager.log_writer(log_file, "Teste de escrita com tipo de log de alerta.", "ALERT");
    log_manager.log_writer(log_file, "Teste de escrita com tipo critico de log.", "CRITICAL");
    log_manager.log_writer(log_file, "Teste de escrita com tipo debug de log.", "DEBUG");

    return 0;
}
