#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>

void display_tasks() {
	std::ifstream ReadFile;
	std::string text, listfile = "list.txt";
	ReadFile.open(listfile);
	std::cout << " " << std::endl;
	for (int task_val = 1; getline(ReadFile, text); task_val++) {
		std::cout << "Task " << task_val << " - ";
		std::cout << text << std::endl;
	}
	ReadFile.close();
}

void add_task() {
	std::ofstream File;
	std::ifstream ReadFile;
	std::string write, listfile = "list.txt";
	ReadFile.open(listfile);
	File.open(listfile, std::ios::app);
	std::cout << "Enter the task -> ";
	std::cin.ignore();
	std::getline(std::cin, write);
	std::cout << std::endl << "Task entered: " << write << std::endl;
	if (ReadFile.is_open())
	{
		File << write << std::endl;
	}
	File.close();
	ReadFile.close();
}

void delete_task() {
	std::ofstream File;
	std::ifstream ReadFile;
	std::string delete_line, line, listfile = "list.txt", tempfile = "temp.txt", text, text_for_delete;
	File.open(listfile, std::ios::app);
	ReadFile.open(listfile);
	std::cout << std::endl << "What task did you complete? -> ";
	std::cin.ignore();
	std::getline(std::cin, delete_line);

	if (!ReadFile.is_open()) {
		std::cerr << "Error in opening: " << listfile << std::endl;
	}

	std::ofstream Temp;
	Temp.open(tempfile, std::ios::app);

	if (!Temp.is_open()) {
		std::cerr << "Error in opening: " << tempfile << std::endl;
	}

	ReadFile.close();
	ReadFile.open(listfile);

	while (std::getline(ReadFile, text_for_delete)) {
		if (text_for_delete != delete_line) {
			Temp << text_for_delete << std::endl;
		}
	}

	File.close();
	ReadFile.close();
	Temp.close();


	if (std::remove(listfile.c_str())) {
		std::cerr << "Error deleting the original file." << std::endl;
	}

	if (std::rename("temp.txt", listfile.c_str())) {
		std::cerr << "Erorr renaming the temp file." << std::endl;
	}

	std::cout << "Marked as completed succesfully." << std::endl;

}

int main()
{
	std::ofstream File;
	std::ifstream ReadFile;
	system("color D");
	int choice = 1;

	std::cout << R"(
		
___________              ________           .____    .__          __   
\__    ___/___           \______ \   ____   |    |   |__| _______/  |_ 
  |    | /  _ \   ______  |    |  \ /  _ \  |    |   |  |/  ___/\   __\
  |    |(  <_> ) /_____/  |    `   (  <_> ) |    |___|  |\___ \  |  |  
  |____| \____/          /_______  /\____/  |_______ \__/____  > |__|  
                                 \/                 \/       \/        

		)" << '\n';

	while (choice == 1 || choice == 2 || choice == 3) {
		std::cout << std::endl << "Options \n";
		std::cout << "1 - Display the list\n2 - Add a task\n3 - Mark a task as completed\n4 - Quit\n\n-> ";
		std::cin >> choice;

		switch (choice) 
		{
			
		case 1: display_tasks();
			
		case 2: add_task();
		
		case 3: delete_task();
		
		}

	if (choice != 4) {
		std::cout << "You've chosen an invalid option. Please choose from the following options:" << std::endl;
		choice = 1;
		while (choice == 1 || choice == 2 || choice == 3) {
			std::cout << std::endl << "Options \n";
			std::cout << "1 - Display the list\n2 - Add a task\n3 - Mark a task as completed\n4 - Quit\n\n-> ";
			std::cin >> choice;

			switch (choice)
			{
			case 1: display_tasks();

			case 2: add_task();
	
			case 3: delete_task();

			default: std::cout << "You've chosen an invalid question.";
			}
		}

	}

	return 0;
}
