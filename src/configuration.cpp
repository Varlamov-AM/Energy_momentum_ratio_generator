#include <vector> 
#include <iostream>

void get_configuration_data(std::vector<std::vector<double>>* params){

    FILE* fp = fopen("config_parameters.conf", "r");
    if (fp == NULL){
        std::cout << 
        "Program configuration error. Configuration file didn't exist!" << 
        std::endl;
        exit(EXIT_FAILURE);
    } 

    char* line = NULL;
    size_t len = 0;
    std::vector<double> par_energy;
    std::vector<double> par_momentum;

    bool flag_energy_data   = false;
    bool flag_momentum_data = false;

    while ((getline(&line, &len, fp)) != -1){
        int i = 0;
        bool flag = false;
        char* par = new char[20]; 
        int tmp_c = 0;
        while (line[i] != '\n'){
            if (flag){
                par[tmp_c] = line[i];
                tmp_c++;  
            }
            if (line[i] == '='){
                flag = true;
                if (line[i - 2] == 'e'){
                    flag_energy_data   = true;
                    flag_momentum_data = false;
                } 
                if (line[i - 2] == 'm'){
                    flag_energy_data   = false;
                    flag_momentum_data = true;
                }
            }
            i++;
        }
        double param = atof(par);
        if (flag_energy_data == true){
            par_energy.push_back(param);
            std::cout << "Energy resolution params: " << param << std::endl;
        }
        if (flag_momentum_data == true){
            par_momentum.push_back(param);
            std::cout << "Momentum resolution params: " << param << std::endl;
        }
    }
    (*params).push_back(par_energy);
    (*params).push_back(par_momentum);
    fclose(fp);
    if (line){
        free(line);
    }
    std::cout << "The program has been successfully configured!" << std::endl;
    
    return;
}  
