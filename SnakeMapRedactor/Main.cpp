#pragma once
#include "MapEditor.h"



int main() {

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    
    string logo = R"MAP(
           __  __          _____          
          |  \/  |   /\   |  __ \         
          | \  / |  /  \  | |__) |        
          | |\/| | / /\ \ |  ___/         
          | |  | |/ ____ \| |             
          |_|  |_/_/    \_\_|             
  ______ _____ _____ _______ ____  _____  
 |  ____|  __ \_   _|__   __/ __ \|  __ \ 
 | |__  | |  | || |    | | | |  | | |__) |
 |  __| | |  | || |    | | | |  | |  _  / 
 | |____| |__| || |_   | | | |__| | | \ \ 
 |______|_____/_____|  |_|  \____/|_|  \_\
)MAP";
    printRaw(logo, 40, 2, Cyan);
}