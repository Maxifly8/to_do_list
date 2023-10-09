#include <iostream>
#include <list>
#include <unistd.h>
#include <string>
#include <ctime>
#define C_SIZE 200

class toDoItem
{
private:
	short id;
	std::string description;
	bool completed;

public:
	toDoItem():id(0), description(""), completed(false) {}	
	~toDoItem() = default;
	
	void create(std::string new_description)
	{
		id = rand() % 100 + 1;	//generates ID between 1 and 100
		description = new_description;
	}
	
	short getId()
	{
		return id;
	}
	
	std::string getDescription()
	{
		return description;
	}
	
	bool is_completed()
	{
		return completed;
	}
	
	void setCompleted(bool value)
	{
		completed = value;
	}
};

main()
{
	std::string version = "v0.3";
	std::list<toDoItem> todoitems;
	std::list<toDoItem>::iterator it;
	todoitems.clear();
	srand(time(NULL)); //getting new random seed every time we run a programm
	std::cin.clear();
	FILE *item_list;
	item_list = fopen("item_list.txt", "at");
	if(item_list == NULL)
	{
		std::cout << "File could not be created.";
		return -1;
	}
	item_list = fopen("item_list.txt", "rt");
	if(item_list == NULL)
	{
		std::cout << "File could not be loaded.";
		return -1;
	}

	for(;;) //getting descriptions from .txt file
	{
		char *temp_description;
		temp_description = new char[C_SIZE];
		if(fgets(temp_description, C_SIZE - 1, item_list) == NULL)
			break;
			
		temp_description[strcspn(temp_description, "\n")] = '\0'; //stop trailing new line after \n; replacing \n with \0
		toDoItem tempItem;
		tempItem.create(temp_description);
		todoitems.push_back(tempItem);
		delete[] temp_description;
	}
	fclose(item_list);
	
	for(;;) //starting the main sequence
	{
		system("cls");
		std::cout << "Current To Do List version - " << version << "\n\n\n\n";
		
		for(it = todoitems.begin(); it != todoitems.end(); ++it)
		{
			std::string isCompleted = it -> is_completed() ? "Done!" : "Not done yet!";
			std::cout << it -> getId() << " || " << it -> getDescription() << " || " << isCompleted << "\n";
		}
		
		if(todoitems.empty())
			std::cout << "Looks like nothing is planned yet!\nTry to add new entry for the To Do List:\n";
			
		std::cout << "\n\n\nPress 'a' to add a thing on the list;\n";
		std::cout << "Press 'c' to mark a thing as completed;\n";
		std::cout << "Press 'r' to remove a thing from the list;\n"; 
		std::cout << "Press 'u' to mark a thing uncompleted;\n";
		std::cout << "Press 'q' to save and quit the programm;\n";
		std::cout << "Please, choose an option: ";
		
		char operation;
		std::cin >> operation;
		
		if(operation == 'q')
		{
			std::cout << "\n\nQuitting the programm...";
			std::cout << "\nSaving current list...";
			FILE *item_list;
			item_list = fopen("item_list.txt", "wt");
			for(it = todoitems.begin(); it != todoitems.end(); ++it) //saving descriptions to a .txt file
			{
				std::string temp = it -> getDescription();
				fputs(temp.c_str(), item_list); //converts c++ string to c *char
				fputs("\n", item_list);
			}
			fclose(item_list);
			sleep(2);
			exit(0);
		}
		else if(operation == 'c')
		{
			std::cout << "Insert ID of item you want to be completed: ";
			short id_completed;
		flag_1:
			std::cin >> id_completed;
			bool found_1 = false;
			for(it = todoitems.begin(); it != todoitems.end(); ++it)
			{
				if(id_completed == it -> getId())
				{
					it -> setCompleted(true);
					found_1 = true;
					break;
				}
			}
			if(!found_1)
			{
				std::cout << "ID was not found, please try again: ";
				goto flag_1;
			}
		}
		else if(operation == 'u')
		{
			std::cout << "Insert ID of item you want to be completed: ";
		flag_2:
			short id_uncompleted;
			std::cin >> id_uncompleted;
			bool found_2 = false;
			for(it = todoitems.begin(); it != todoitems.end(); ++it)
			{
				if(id_uncompleted == it -> getId())
				{
					it -> setCompleted(false);
					found_2 = true;
					break;
				}
			}
			if(!found_2)
			{
				std::cout << "ID was not found, please try again: ";
				goto flag_2;
			}
		}
		else if(operation == 'a')
		{
			std::cout << "Add a new description: ";
			std::string input_description;
			std::cin.clear(); //clear input stream buffer
			std::cin.ignore();
			std::getline(std::cin, input_description);
			toDoItem newItem;
			newItem.create(input_description);
			todoitems.push_back(newItem);	
		}
			
		else if(operation == 'r')
		{
			std::cout << "Please, enter the ID you want to be removed: ";
			short remove_id;
			std::cin >> remove_id;
			for(it = todoitems.begin(); it != todoitems.end(); ++it)
			{
				if(remove_id == it -> getId())
				{
					it = todoitems.erase(it);
					break;
				}
			}
		}
	
		//break;
	}
	return 0;
}
