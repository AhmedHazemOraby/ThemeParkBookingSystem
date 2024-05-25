#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40

struct visitor
{
    int sr_no;
    char name[MAX];
    char id[MAX];
    int ticket_no;
};

void add_visitor()
{
    // Declare a file pointer and a visitor structure
    FILE *fp;
    struct visitor v;

    // Declare a variable for storing the user's choice
    int choice;

    // Open the file "Tickets.txt" for appending
    fp = fopen("Tickets.txt", "a");

    // If the file couldn't be opened, print an error message and exit the program
    if (fp == NULL)
    {
        printf("File not found");
        exit(1);
    }

    // Prompt the user to enter a choice for the visitor's location
    printf("Enter 1 if local, 2 if international: ");
    scanf("%d", &choice);

    // Use a switch statement to determine which information to prompt the user for based on their choice
    switch (choice)
    {
    case 1:
        // If the user chose local, prompt them for the visitor's serial number, name, ID, and ticket number
        printf("Enter the visitor's serial number: ");
        scanf("%d", &v.sr_no);
        printf("Enter the visitor's name: ");
        getchar();
        gets(v.name);
        printf("Enter the visitor's ID: ");
        scanf("%s", &v.id);
        printf("Enter the visitor's ticket number: ");
        scanf("%d", &v.ticket_no);

        // Write the visitor's information to the file, including the designation "(Local)"
        fprintf(fp, "%d %d %s %s (Local)\n", v.sr_no, v.ticket_no, v.name, v.id);
        printf("The information of the visitor %s is recorded\n", v.name);
        break; 
    case 2:
        // If the user chose international, prompt them for the visitor's serial number, name, ID, and ticket number
        printf("Enter the visitor's serial number: ");
        scanf("%d", &v.sr_no);
        printf("Enter the visitor's name: ");
        getchar();
        gets(v.name);
        printf("Enter the visitor's ID: ");
        scanf("%s", &v.id);
        printf("Enter the visitor's ticket number: ");
        scanf("%d", &v.ticket_no);

        // Write the visitor's information to the file, including the designation "(International)"
        fprintf(fp, "%d %d %s %s (International)\n",  v.sr_no, v.ticket_no, v.name, v.id);
        printf("The information of the visitor %s is recorded\n", v.name);
        break;
    default:
        // If the user entered an invalid choice, print an error message
        printf("Invalid choice");
        break;
    }

    // Close the file
    fclose(fp);
}

void display_visitor()
{
    // Declare a file pointer and a visitor structure
    FILE *fp;
    struct visitor v;

    // Open the file "Tickets.txt" for reading
    fp = fopen("Tickets.txt", "r");

    // If the file couldn't be opened, print an error message and exit the program
    if (fp == NULL)
    {
        printf("File not found");
        exit(1);
    }

    // Declare a string to store each line of the file as it's read
    char line[80];

    // Read each line of the file until the end is reached
    while (fgets(line, 80, fp) != NULL)
    {
        // Try to parse the line as a local visitor's information
        int fields_read = sscanf(line, "%d %d %[^(] %s", &v.sr_no, &v.ticket_no, v.name, v.id);

        // If the line was successfully parsed as a local visitor's information, print the visitor's information
        if (fields_read == 4)
        {
            printf("%d %d %s %s\n", v.sr_no, v.ticket_no, v.name, v.id);
        }
        // If the line couldn't be parsed as a local visitor's information, try parsing it as an international visitor's information
        else
        {
            char type[10];
            fields_read = sscanf(line, "%d %d %[^(] %s %[^)]", &v.sr_no, &v.ticket_no, v.name, v.id, type);

            // If the line was successfully parsed as an international visitor's information, print the visitor's information
            if (fields_read == 5)
            {
                printf("%d %d %s %s %s\n", v.sr_no, v.ticket_no, v.name, v.id, type);
            }
        }
    }

    // Close the file
    fclose(fp);
}

void search_visitor()
{
    // Declare a file pointer and a visitor structure
    FILE *fp;
    struct visitor v;

    // Declare variables for storing the search criteria (ticket number, name, or ID) and the user's choice
    int ticket_no;
    char name[MAX];
    char id[MAX];
    int choice1;

    // Declare a variable to keep track of whether a match was found
    int match_found = 0; 

    // Open the file "Tickets.txt" for reading
    fp = fopen("Tickets.txt", "r");

    // If the file couldn't be opened, print an error message and exit the program
    if (fp == NULL)
    {
        printf("File not found");
        exit(1);
    }

    // Prompt the user to enter a choice for the search criteria
    printf("Enter 1 to search by ticket number, 2 to search by name, 3 to search by ID: ");
    scanf("%d", &choice1);

    // Use a switch statement to determine which search criteria to use based on the user's choice
    switch (choice1)
    {
    case 1:
        // If the user chose to search by ticket number, prompt them for the ticket number
        printf("Enter the ticket number: ");
        scanf("%d", &ticket_no);

        // Read each visitor's information from the file until the end is reached
        while (fscanf(fp, "%d %d %s %s", &v.sr_no, &v.ticket_no, v.name, v.id) == 4)
        {
            // If the visitor's ticket number matches the search criteria, print the visitor's information and set match_found to 1
            if (v.ticket_no == ticket_no)
            {
                printf("Match found:\n");
                printf("%d %d %s %s\n", v.sr_no, v.ticket_no, v.name, v.id);
                match_found = 1;
                break;
            }
        }
        break;
    case 2:
        // If the user chose to search by name, prompt them for the name
        printf("Enter the visitor's name: ");
        getchar();
        gets(name);
        while (fscanf(fp, "%d %d %[^(] %s", &v.sr_no, &v.ticket_no, v.name, v.id) == 4)
        {
            if (strcmp(name, v.name) == 0)
            {
                printf("Match found:\n");
                printf("%d %d %s %s\n", v.sr_no, v.ticket_no, v.name, v.id);
                match_found = 1;
                break;
            }
        }
        if (match_found == 0)
        {
            printf("No match found\n");
        }
        break;
    case 3:
        printf("Enter the ID: ");
        scanf("%s", id);
        while (fscanf(fp, "%d %d %s %s", &v.sr_no, &v.ticket_no, v.name, v.id) == 4)
        {
            if (strcmp(v.id, id) == 0)
            {
                printf("Match found:\n");
                printf("%d %d %s %s\n", v.sr_no, v.ticket_no, v.name, v.id);
                match_found = 1;
                break;
            }
        }
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
    if (match_found == 0)
    {
        printf("No match found\n");
    }
    fclose(fp);
}

void delete_visitor()
{
    FILE *fp;
    struct visitor v;
    int ticket_no;
    char name[MAX];
    char id[MAX];
    int choice1;
    int match_found = 0; 

    // Open the "Tickets.txt" file in read mode
    fp = fopen("Tickets.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // Prompt the user to choose how to search for the visitor to delete
    printf("Enter 1 to search by ticket number, 2 to search by name, 3 to search by ID: ");
    scanf("%d", &choice1);

    // Read the user's search criteria
    switch (choice1)
    {
        case 1:
            printf("Enter the ticket number: ");
            scanf("%d", &ticket_no);
            break;
        case 2:
            printf("Enter the name: ");
            getchar();
            gets(name);
            break;
        case 3:
            printf("Enter the ID: ");
            scanf("%s", id);
            break;
        default:
            printf("Invalid choice\n");
            return;
    }

    // Open a new file in write mode
    FILE *fp_temp = fopen("Temp.txt", "w");
    if (fp_temp == NULL)
    {
        printf("Error creating temp file\n");
        fclose(fp);
        exit(1);
    }

    // Read each line of the "Tickets.txt" file
    char line[80];
    while (fgets(line, 80, fp) != NULL)
    {
        // Extract the visitor information from the line
        int fields_read = sscanf(line, "%d %d %[^(] %s", &v.sr_no, &v.ticket_no, v.name, v.id);
        if (fields_read == 4)
        {
            // Check if the visitor matches the search criteria
            if ((choice1 == 1 && v.ticket_no == ticket_no) || 
                (choice1 == 2 && strcmp(v.name, name) == 0) || 
                (choice1 == 3 && strcmp(v.id, id) == 0))
            {
                // If a match is found, set the flag and skip this visitor
                match_found = 1;
                continue;
            }
        }
        else
        {
            char type[10];
            fields_read = sscanf(line, "%d %d %[^(] %s %[^)]", &v.sr_no, &v.ticket_no, v.name, v.id, type);
            if (fields_read == 5)
            {
                // Check if the visitor matches the search criteria
                if ((choice1 == 1 && v.ticket_no == ticket_no) || 
                    (choice1 == 2 && strcmp(v.name, name) == 0) || 
                    (choice1 == 3 && strcmp(v.id, id) == 0))
                {
                    // If a match is found, set the flag and skip this visitor
                    match_found = 1;
                    continue;
                }
            }
        }

        // If the visitor does not match the search criteria, write their information to the temp file
        fprintf(fp_temp, "%d %d %s %s\n", v.sr_no, v.ticket_no, v.name, v.id);
    }

    // Close both files
    fclose(fp);
    fclose(fp_temp);

    // If a match was found, delete the "Tickets.txt" file and rename the temp file
    if (match_found)
    {
        int remove_result = remove("Tickets.txt");
        if (remove_result != 0)
        {
            printf("Error deleting file\n");
            exit(1);
        }

        int rename_result = rename("Temp.txt", "Tickets.txt");
        if (rename_result != 0)
        {
            printf("Error renaming file\n");
            exit(1);
        }

        printf("Visitor deleted successfully\n");
    }
    else
    {
        // If no match was found, delete the temp file and display a message
        remove("Temp.txt");
        printf("No matching visitor found\n");
    }
}

void display_total_tickets()
{
    // File pointer to the "Tickets.txt" file
    FILE *fp;
    
    // Buffer for storing each line read from the file
    char line[80];
    
    // Counter for the total number of tickets sold
    int total_tickets = 0;
    
    // Open the "Tickets.txt" file in read mode
    fp = fopen("Tickets.txt", "r");
    
    // Check if the file was successfully opened
    if (fp == NULL)
    {
        // If the file could not be opened, display an error message and exit the program
        printf("File not found");
        exit(1);
    }
    
    // Read each line of the file until the end of the file is reached
    while (fgets(line, 80, fp) != NULL)
    {
        // Increment the total number of tickets sold for each line read
        total_tickets++;
    }
    
    // Print the total number of tickets sold
    printf("Total tickets sold: %d\n", total_tickets);
    
    // Close the file
    fclose(fp);
}
int main()
{
    int choice3;
    while (1)
    {
        printf("1. Add Visitor\n2. Display Visitor\n3. Search Visitor\n4. Delete Visitor\n5. Display Total Tickets Sold\n6. Exit\nEnter your choice:\t");
        scanf("%d", &choice3);
        switch (choice3)
        {
        case 1:
            add_visitor();
            break;
        case 2:
            display_visitor();
            break;
        case 3:
            search_visitor();
            break;
        case 4:
            delete_visitor();
            break;
        case 5:
            display_total_tickets();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice");
            break;
        }
    }
}