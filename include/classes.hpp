#ifndef NT_LOG_HPP
#define NT_LOG_HPP

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>

namespace fs = std::filesystem;

namespace niatec_logs{

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

    class Log_Manager{
            
        std::string logs_folder_path;

        public:
            Log_Manager(std::string log_folder=""){
                std::string root_folder = fs::current_path();
                log_folder = (log_folder.empty()) ? root_folder+"/logs/" : root_folder+"/"+log_folder; 
                std::cout << "Logs Folder: " << log_folder << "\n";
                if(!fs::exists(log_folder)){
                    fs::create_directory(log_folder);   
                }
                this->logs_folder_path = log_folder;
            }

            std::string create_log_file(){
                // Used to generate a filename and a file
                std::string uuid = get_uuid(), datetimestring, filepath;

                // Date & Time 4 LOG
                time_t time_now = time(0);
                std::tm* time_info = std::localtime(&time_now);

                std::stringstream formatted_time;
                formatted_time << std::put_time(time_info, "%Y-%m-%d-%H-%M-%S"); //2023-11-30-15-35-56 = year-month-day-hour-minute-second
                std::string formatted_time_str = formatted_time.str();
                
                filepath = this->logs_folder_path + formatted_time_str + "-" + uuid + ".log";

                return filepath;
            }

            void log_writer(std::string filepath, std::string log_content, std::string log_type="INFO"){
                // Used to write into an existing file

                std::ofstream outfile(filepath, std::ios::app);

                // Date & Time 4 LOG
                time_t time_now = time(0);
                std::tm* time_info = std::localtime(&time_now);

                std::stringstream formatted_time;
                // formatted_time << std::put_time(time_info, "%d/%m/%Y %I:%M %p");
                formatted_time << std::put_time(time_info, "%Y-%m-%d-%H:%M:%S"); //2023-30-11-15:35:56
                std::string formatted_time_str = formatted_time.str();

                // Verifica se o arquivo foi aberto corretamente
                if (!outfile.is_open()) {
                    std::cerr << "Erro ao abrir o arquivo: " << filepath << std::endl;
                    return;
                }

                log_type = (log_type.empty()) ? "" : log_type;

                // Writer
                outfile << formatted_time_str << "; " << log_type << "; " << log_content << ";\n";

            }
        };
}

#endif