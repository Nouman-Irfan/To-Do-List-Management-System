#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Class for storing task information

class Task
{
public:
    int id;
    string title;
    string category;
    int completed;
};

// Vector to store all tasks

vector<Task> tasks;

// ================= FUNCTION PROTOTYPES =================

void loadTasks();
void saveTasks();

void addTask();
void viewTasks();
void viewPendingTasks();
void viewCompletedTasks();

void markCompleted();
void deleteTask();

void menu();

int main()
{
    loadTasks();

    menu();

	system("pause");

    return 0;
}

// ================= FUNCTION DEFINITIONS =================

void loadTasks()
{
    ifstream file("tasks.txt");

    tasks.clear();

    Task tempTask;

    while (file >> tempTask.id)
    {
        file.ignore();

        getline(file, tempTask.title, '|');
        getline(file, tempTask.category, '|');

        file >> tempTask.completed;

        file.ignore();

        tasks.push_back(tempTask);
    }

    file.close();
}

void saveTasks()
{
    ofstream file("tasks.txt");

    for (int i = 0; i < tasks.size(); i++)
    {
        file << tasks[i].id << endl;

        file << tasks[i].title << "|";
        file << tasks[i].category << "|";
        file << tasks[i].completed << endl;
    }

    file.close();
}

void addTask()
{
    Task newTask;

    cout << "\n========== ADD TASK ==========" << endl;

    newTask.id = tasks.size() + 1;

    cin.ignore();

    cout << "Enter task title: ";
    getline(cin, newTask.title);

    cout << "Enter category: ";
    getline(cin, newTask.category);

    newTask.completed = 0;

    tasks.push_back(newTask);

    saveTasks();

    cout << "Task added successfully!" << endl;
}

void viewTasks()
{
    cout << "\n========== ALL TASKS ==========" << endl;

    if (tasks.size() == 0)
    {
        cout << "No tasks found." << endl;
        return;
    }

    for (int i = 0; i < tasks.size(); i++)
    {
        cout << "\nTask ID: " << tasks[i].id << endl;
        cout << "Title: " << tasks[i].title << endl;
        cout << "Category: " << tasks[i].category << endl;

        if (tasks[i].completed == 1)
        {
            cout << "Status: Completed" << endl;
        }
        else
        {
            cout << "Status: Pending" << endl;
        }
    }
}

void viewPendingTasks()
{
    cout << "\n========== PENDING TASKS ==========" << endl;

    int found = 0;

    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].completed == 0)
        {
            cout << "\nTask ID: " << tasks[i].id << endl;
            cout << "Title: " << tasks[i].title << endl;
            cout << "Category: " << tasks[i].category << endl;

            found = 1;
        }
    }

    if (found == 0)
    {
        cout << "No pending tasks found." << endl;
    }
}

void viewCompletedTasks()
{
    cout << "\n========== COMPLETED TASKS ==========" << endl;

    int found = 0;

    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].completed == 1)
        {
            cout << "\nTask ID: " << tasks[i].id << endl;
            cout << "Title: " << tasks[i].title << endl;
            cout << "Category: " << tasks[i].category << endl;

            found = 1;
        }
    }

    if (found == 0)
    {
        cout << "No completed tasks found." << endl;
    }
}

void markCompleted()
{
    int id;

    cout << "\nEnter Task ID to mark completed: ";
    cin >> id;

    int found = 0;

    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].id == id)
        {
            tasks[i].completed = 1;

            found = 1;

            saveTasks();

            cout << "Task marked as completed!" << endl;

            break;
        }
    }

    if (found == 0)
    {
        cout << "Task not found!" << endl;
    }
}

void deleteTask()
{
    int id;

    cout << "\nEnter Task ID to delete: ";
    cin >> id;

    int found = 0;

    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].id == id)
        {
            tasks.erase(tasks.begin() + i);

            for (int j = 0; j < tasks.size(); j++)
            {
                tasks[j].id = j + 1;
            }

            found = 1;

            saveTasks();

            cout << "Task deleted successfully!" << endl;

            break;
        }
    }

    if (found == 0)
    {
        cout << "Task not found!" << endl;
    }
}

void menu()
{
    int choice;

    do
    {
        cout << "\n========== TO-DO LIST APPLICATION ==========" << endl;

        cout << "1. Add Task" << endl;
        cout << "2. View All Tasks" << endl;
        cout << "3. View Pending Tasks" << endl;
        cout << "4. View Completed Tasks" << endl;
        cout << "5. Mark Task as Completed" << endl;
        cout << "6. Delete Task" << endl;
        cout << "7. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            addTask();
        }
        else if (choice == 2)
        {
            viewTasks();
        }
        else if (choice == 3)
        {
            viewPendingTasks();
        }
        else if (choice == 4)
        {
            viewCompletedTasks();
        }
        else if (choice == 5)
        {
            markCompleted();
        }
        else if (choice == 6)
        {
            deleteTask();
        }
        else if (choice == 7)
        {
            cout << "Exiting program..." << endl;
        }
        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 7);
}