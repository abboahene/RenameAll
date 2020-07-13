#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>


int main()
{

    system("color 07");

    std::cout<<"\n 1.Drag the folder into this terminal\n";
    std::cout<<" 2.Press Enter\n";
    std::cout<<" 3.Type a prefix for your new filenames (Type 'none' if you don't want a prefix, names will only numbers)\n";
    std::cout<<" 4.Press Enter\n\n";


    while(true){
        std::cout <<" DRAG FOLDER HERE:";
        std::string dirAbsPath,prefix;
        std::cin >> dirAbsPath;
        std::cout <<" TYPE PREFIX:";
        std::cin >> prefix;
        if (prefix == "none") prefix = "";

        system(("dir /b " +dirAbsPath+ " > filenames.txt").c_str());

        std::ifstream in("filenames.txt");

        if(!in) {
            std::cout << "Cannot open input file `filenames.txt`.\n";
            return 1;
        }

        std::string filename;
        int count = 0;
        while(getline(in, filename)) {

            std::string ext;

            try{

                ext = filename.substr(filename.find_last_of("."), filename.size());

            }catch(std::out_of_range e){

                std::cerr << filename+" could not be renamed" <<std::endl;
                continue;

            }

            rename((dirAbsPath+"\\"+filename).c_str(),std::string(dirAbsPath+"\\"+prefix+std::to_string(++count)+ext).c_str());
            std::cout << " \\"+filename+" \r\r";
            usleep(200);
            system(("color 0"+std::to_string(count)).c_str());

        }

        system("color 07");
        in.close();
        std::cout<<" Done!!!\n";
        char stop;
        std::cout<< " Restart? Y/N: ";
        std::cin >> stop;
        if(tolower(stop) == 'n') break;

    }

    std::remove("filenames.txt");
    exit(0);
}
