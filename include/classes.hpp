#ifndef LOGS_H
#define LOGS_H

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>


namespace fs = std::filesystem;

std::string get_uuid(){
    FILE* pipe = popen("uuidgen", "r");
    if (!pipe) {
        return "";
    }
    char buffer[37]; // UUID tem 36 caracteres, mais um para o terminador nulo
    if (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        // Remover o caractere de nova linha no final, se presente
        buffer[strcspn(buffer, "\n")] = '\0';
        std::string uuidWithoutHyphens(buffer);
        uuidWithoutHyphens.erase(std::remove(uuidWithoutHyphens.begin(), uuidWithoutHyphens.end(), '-'), uuidWithoutHyphens.end());
    
        return uuidWithoutHyphens;
    }
    std::cout << "Erro ao ler UUID gerado!\n";
    return "";
}

namespace niatec_logs{
    class Log_Manager{
        
        std::string logs_folder_path;

        public:
            Log_Manager(){
                std::string root_folder = fs::current_path();
                if(!fs::exists("../logs/")){
                    fs::create_directory("../logs/");
                    this->logs_folder_path = "../logs/";
                    return;                
                }
                this->logs_folder_path = "../logs/";
            }

            std::string create_log_file(){
                // Used to generate a filename and a file
                std::string uuid = get_uuid(), datetimestring, filepath;
                
                datetimestring = "30112023-145533";
                filepath = this->logs_folder_path + datetimestring + "-" + uuid + ".log";

                return filepath;
            }

            bool create_log_file(std::string filename){
                // Used when we already have a filename

                return true;
            }

            void log_writer(std::string filepath, std::string log_content, std::string log_type=""){
                // Used to write into an existing file

                std::ofstream outfile(filepath, std::ios::app);

                // Verifica se o arquivo foi aberto corretamente
                if (!outfile.is_open()) {
                    std::cerr << "Erro ao abrir o arquivo: " << filepath << std::endl;
                    return;
                }

                // Writer
                outfile << "2023-30-15:35:56 " + log_type + log_content + "\n";

            }
    };
}

#endif